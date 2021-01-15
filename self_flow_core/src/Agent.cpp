#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "self_flow_core/msg/task.hpp"
#include "self_flow_core/msg/bid.hpp"

//#include "TaskList.hpp"


#define TASK_TOPIC "/self_flow/task"
#define BID_TOPIC "/self_flow/bid"


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

    std::unordered_map<std::string, std::shared_ptr<base_task>> taskmap; //list of programmed tasks


    std::shared_ptr<base_task> current_task;
    std::vector<std::shared_ptr<base_task>> task_queue;  //local task queue

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
        timer0 = this->create_wall_timer(3s, std::bind(&AgentNode::timer0Callback, this));

/////////////TASK DEFINITION ///////////////////////////////////////

	std::shared_ptr<base_task> tmp_ptr;

//	tmp_ptr=std::make_shared<example_task>(* new example_task);
//	taskmap["example_task"]=tmp_ptr;

	RCLCPP_INFO(this->get_logger(), "Starting Agent...");


	tmp_ptr=std::make_shared<idle_task>(* new idle_task);
        taskmap["idle_task"]=tmp_ptr;
	tmp_ptr=std::make_shared<home_task>(* new home_task);
        taskmap["home_task"]=tmp_ptr;
        tmp_ptr=std::make_shared<find_object_task>(* new find_object_task);
        taskmap["find_object_task"]=tmp_ptr;



	add_task("idle_task");

    }



//////////////////////ROS MSGS//////////////////////////////////////

    void CollabTask(std::string id)
    {
        auto msg=self_flow::msg::Task();
        msg.id=id;
        msg.agent=my_name;
        msg.status=4; //0: request 1: in progress 2:finished 3: failed 4: collaborative
	TaskPub->publish(msg);
	std::string l="New collaborative task: ";
	l+=id;
	RCLCPP_INFO(this->get_logger(), l);
    }

    void AuctionTask(std::string id)
   {
	auto msg=self_flow::msg::Task();
	msg.id=id;
	msg.agent=my_name;
	msg.status=0; //0: request 1: in progress 2:finished 3: failed 4: collaborative
	TaskPub->publish(msg);
	std::string l="Auctioned task: ";
	l+=id;
	RCLCPP_INFO(this->get_logger(), l);
    }

    void TaskCallback(const self_flow::msg::Task::SharedPtr msg)
    {

	if (taskmap.find(msg->id)==taskmap.end())
	{
	        RCLCPP_INFO(this->get_logger(), "Bad task id");
		return;
	}

        TaskStatus[std::string(msg->id)]=msg->status;

	if(msg->status==0) //task auction
	{
		RCLCPP_INFO(this->get_logger(), "Task received");
		auction_task=msg->id;
		my_delta=taskmap.at(msg->id)->utility()-curr_ut;
		auto reply=self_flow::msg::Bid();
		reply.utility=my_delta;
		reply.id=msg->id;
		reply.agent=my_name;
		BidTopicPub->publish(reply);
                timer0->cancel();
		timer0 = this->create_wall_timer(3s, std::bind(&AgentNode::timer0Callback, this));
	}

	if(msg->status==4) //collab
	{
		add_task(msg->id);
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
			    if(temp->is_collab)
			    {
				CollabTask(it);
				pub_feedback(it, 4);
			    }
			    else AuctionTask(it);
			    {
				AuctionTask(it);
				pub_feedback(it, 1);
			    }
			}
		}
	}
    }


    void pub_feedback(std::string task_id,uint8_t status)
    {
	if (!task_id.empty())
	{
		auto message = self_flow::msg::Task();
		message.id=task_id;
		message.agent=my_name;
		message.status=status;
	    	TaskPub->publish(message);
	}
    }


    void taskUpdate() //continuous check on task priorities
    {
	double ut=0.0;
	std::shared_ptr<base_task> temp_task=current_task;
	for (auto it : task_queue)	//find best task
	{
		if(TaskStatus.count(it->id()))
		{
			if(it->RequisiteCheck()==0 && it->utility()>ut && TaskStatus[it->id()]!=1)
			{
				ut=it->utility();
				temp_task=it;
			}
		}

		else
		{
			if(it->RequisiteCheck()==0 && it->utility()>ut)
			{
				ut=it->utility();
				temp_task=it;
			}
		}

	}
	if(current_task!=temp_task) 	//start new task
	{
		current_task=temp_task;
		current_task->init();
	        timer1 = this->create_wall_timer(5s, std::bind(&AgentNode::timer1Callback, this));
//	        timer1 = this->create_wall_timer(current_task->tick_rate(), std::bind(&AgentNode::timer1Callback, this)); //TO BE IMPLEMENTED
		std::string l="New task started: ";
		l+=current_task->id();
		RCLCPP_INFO(this->get_logger(), l);

	}
    }




    void timer0Callback()
    {
	if(!auction_task.empty()&&best_delta==my_delta) //add auctioned task
	{
		add_task(auction_task);
		auction_task="";
	}

	best_delta=0.0;
	this->taskUpdate();
    }


    void timer1Callback()  //task tick
    {
	int status=current_task->tick();
	if (status==1)
	{
		std::string temp="Task in progress: ";
		temp+=std::string(current_task->id());
		pub_feedback(current_task->id(),1);
		RCLCPP_INFO(this->get_logger(), temp);
	}
	else if (status==2)
	{
		RCLCPP_INFO(this->get_logger(), "Task completed");
		pub_feedback(current_task->id(),2);
		timer1->cancel();
	}
	else if (status==3)
	{
		RCLCPP_INFO(this->get_logger(), "Task failed");
		pub_feedback(current_task->id(),0); //auto retry
		timer1->cancel();
	}
    }

};




