#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "self_flow/msg/task.hpp"
#include "self_flow/msg/bid.hpp"
#include "self_flow/msg/feedback.hpp"

#include "idle_task.cpp"
//#include "example_task.cpp"


#define TASK_TOPIC "/self_flow/task"
#define BID_TOPIC "/self_flow/bid"
#define FEEDBACK_TOPIC "/self_flow/feedback"


using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node
{
private:

    std::string my_name;

    double curr_ut=0.0;


    double my_delta=0.0;
    double best_delta=0.0;
    std::string auction_task;

    std::unordered_map<std::string, std::shared_ptr<base_task>> taskmap;


    std::shared_ptr<base_task> current_task;
    std::vector<std::shared_ptr<base_task>> task_queue;

    rclcpp::Publisher<self_flow::msg::Feedback>::SharedPtr FeedbackPub;
    rclcpp::Subscription<self_flow::msg::Feedback>::SharedPtr FeedbackSub;

    rclcpp::Publisher<self_flow::msg::Task>::SharedPtr TaskPub;
    rclcpp::Subscription<self_flow::msg::Task>::SharedPtr TaskSub;
    rclcpp::Publisher<self_flow::msg::Bid>::SharedPtr BidTopicPub;
    rclcpp::Subscription<self_flow::msg::Bid>::SharedPtr BidTopicSub;
    rclcpp::TimerBase::SharedPtr timer1;
    rclcpp::TimerBase::SharedPtr timer0;


public:

    AgentNode(std::string name): Node(name)
    {
	my_name=name;
        TaskPub = this->create_publisher<self_flow::msg::Task>(TASK_TOPIC, 1);
        TaskSub = this->create_subscription<self_flow::msg::Task>(TASK_TOPIC, 1, std::bind(&AgentNode::TaskCallback, this, _1));
        BidTopicPub = this->create_publisher<self_flow::msg::Bid>(BID_TOPIC, 1);
        BidTopicSub = this->create_subscription<self_flow::msg::Bid>(BID_TOPIC, 1, std::bind(&AgentNode::BidCallback, this, _1));
        FeedbackPub = this->create_publisher<self_flow::msg::Feedback>(FEEDBACK_TOPIC, 1);
        FeedbackSub = this->create_subscription<self_flow::msg::Feedback>(FEEDBACK_TOPIC, 1, std::bind(&AgentNode::feedback_cb, this, _1));
        timer0 = this->create_wall_timer(5s, std::bind(&AgentNode::timer0Callback, this));

/////////////TASK DEFINITION ///////////////////////////////////////

	std::shared_ptr<base_task> tmp_ptr;

//	tmp_ptr=std::make_shared<example_task>(* new example_task);
//	taskmap["example_task"]=tmp_ptr;

	tmp_ptr=std::make_shared<idle_task>(* new idle_task);
        taskmap["idle_task"]=tmp_ptr;

	add_task("idle_task");

    }



//////////////////////ROS MSGS//////////////////////////////////////

    void CollabTask(std::string id)
    {
        auto msg=self_flow::msg::Task();
        msg.id=id;
        msg.agent=my_name;
        msg.type=4; //0: petition 1: accepted 2:finished 3: failed 4: collaborative
	TaskPub->publish(msg);
	std::string l="Collaborative task: ";
	l+=id;
	RCLCPP_INFO(this->get_logger(), l);
    }

    void AuctionTask(std::string id)
   {
	auto msg=self_flow::msg::Task();
	msg.id=id;
	msg.agent=my_name;
	msg.type=0; //0: petition 1: accepted 2:finished 3: failed
	TaskPub->publish(msg);
	std::string l="Auctioned task: ";
	l+=id;
	RCLCPP_INFO(this->get_logger(), l);
    }

    void TaskCallback(const self_flow::msg::Task::SharedPtr msg)
    {
	if(msg->type==0)
	{
		auction_task=msg->id;
		my_delta=taskmap.at(msg->id)->utility()-curr_ut;
		auto reply=self_flow::msg::Bid();
		reply.utility=my_delta;
		reply.id=msg->id;
		reply.agent=my_name;
		BidTopicPub->publish(reply);
	}
/*	if(msg->type==1) //delete or update task

	if(msg->type==2) //update

*/
	if(msg->type==4) //collab
	{
		add_task("msg->id");
	}

    }

    void BidCallback(const self_flow::msg::Bid::SharedPtr msg)
    {

	if(msg->utility > best_delta ) best_delta=msg->utility;


    }

//////////////////// TASK FUNCTIONS //////////////


    void add_task(std::string taskname)
    {
	auto temp=taskmap.at(taskname);
	task_queue.push_back(temp);
	if(temp->RequisiteCheck())
	{
		std::vector<std::string> reqlist = temp->RequisiteLoad();
        	for (auto it : reqlist)
		{
			if(TaskStatus.count(it)==0)	//making sure the task has not already been requested
			{
				pub_feedback(it, 0);
				if(temp->is_collab) CollabTask(it);
				else AuctionTask(it);
			}
		}
	}
    }


    void pub_feedback(std::string task_id,bool status)
    {
	if (!task_id.empty())
	{
		auto message = self_flow::msg::Feedback();
		message.name=task_id;
		message.status=status;
	    	FeedbackPub->publish(message);
	}
    }

    void feedback_cb(const self_flow::msg::Feedback::SharedPtr msg)
    {
	std::cout << "feedback: " << msg->name << std::endl;
	TaskStatus[std::string(msg->name)]=msg->status;
    }


    void timer0Callback()
    {
	if(!auction_task.empty()&&best_delta==my_delta) //add auctioned task
	{
		add_task(auction_task);
		auction_task="";
	}

	double ut=0.0;
	std::shared_ptr<base_task> temp_task;
	for (auto it : task_queue)	//find best task
	{
		if(!it->RequisiteCheck() && it->utility()>ut)
		{
			ut=it->utility();
			temp_task=it;
		}
	}
	if(current_task!=temp_task) 	//start best task
	{
		std::cout<<"new task started"<<std::endl;
		current_task=temp_task;
		current_task->init();
	        timer1 = this->create_wall_timer(1s, std::bind(&AgentNode::timer1Callback, this));
	}
    }


    void timer1Callback()  //task tick
    {
	int status=current_task->tick();
	if (status==1)
	{
		std::string temp="Task in progress: ";
		temp+=std::string(current_task->fb());
		RCLCPP_INFO(this->get_logger(), temp);
	}
	else if (status==2)
	{
		RCLCPP_INFO(this->get_logger(), "Task completed");
		pub_feedback(std::string(current_task->fb()),1);
		timer1->cancel();
	}
    }

};




