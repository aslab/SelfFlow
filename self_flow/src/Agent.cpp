#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "self_flow/msg/task.hpp"
#include "self_flow/msg/bid.hpp"
#include "std_msgs/msg/string.hpp"

#include "idle_task.cpp"
#include "example_task.cpp"
#include "example_task2.cpp"

#define AUCTION_TOPIC "/self_flow/task"
#define BID_TOPIC "/self_flow/bid"
#define COLLAB_TOPIC "/self_flow/collab"


using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node, public requisite
{
private:

    bool auction_pending=0;
    std::string my_name;

    double curr_ut=0.0;

    std::unordered_map<std::string, std::shared_ptr<base_task>> taskmap;


    std::shared_ptr<base_task> current_task;
    std::vector<base_task> ostensible_tasks;

    rclcpp::Publisher<self_flow::msg::Task>::SharedPtr AuctionTopicPub;
    rclcpp::Subscription<self_flow::msg::Task>::SharedPtr AuctionTopicSub;
    rclcpp::Publisher<self_flow::msg::Bid>::SharedPtr BidTopicPub;
    rclcpp::Subscription<self_flow::msg::Bid>::SharedPtr BidTopicSub;
    rclcpp::Publisher<self_flow::msg::Task>::SharedPtr CollabTopicPub;
    rclcpp::Subscription<self_flow::msg::Task>::SharedPtr CollabTopicSub;
    rclcpp::TimerBase::SharedPtr timer1;
//    rclcpp::TimerBase::SharedPtr timer2;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr FeedbackTopicPub;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr FeedbackTopicSub;


public:

    AgentNode(std::string name): Node(name)
    {
	my_name=name;
        AuctionTopicPub = this->create_publisher<self_flow::msg::Task>(AUCTION_TOPIC, 1);
        AuctionTopicSub = this->create_subscription<self_flow::msg::Task>(AUCTION_TOPIC, 1, std::bind(&AgentNode::AuctionCallback, this, _1));
        BidTopicPub = this->create_publisher<self_flow::msg::Bid>(BID_TOPIC, 1);
        BidTopicSub = this->create_subscription<self_flow::msg::Bid>(BID_TOPIC, 1, std::bind(&AgentNode::BidCallback, this, _1));
        CollabTopicPub = this->create_publisher<self_flow::msg::Task>(COLLAB_TOPIC, 1);
        CollabTopicSub = this->create_subscription<self_flow::msg::Task>(COLLAB_TOPIC, 1, std::bind(&AgentNode::CollabCallback, this, _1));
//      timer2 = this->create_wall_timer(1s, std::bind(&AgentNode::timer1sCallback, this));


	std::shared_ptr<base_task> tmp_ptr=std::make_shared<example_task>(* new example_task);
	taskmap["example_task"]=tmp_ptr;
	std::shared_ptr<base_task> tmp_ptr2=std::make_shared<example_task2>(* new example_task2(this->req));
	taskmap["example_task2"]=tmp_ptr2;


	start_task("example_task2");
    }



    void exe_req() override
    {
	start_task("example_task");
    }

//////////////////////ROS MSGS//////////////////////////////////////

    void CollabTask(std::string id){}

    void CollabCallback(const self_flow::msg::Task::SharedPtr msg){}

    void AuctionTask(std::string id)
    {
	auto msg=self_flow::msg::Task();
	msg.id=id;
	msg.agent=my_name;
	msg.type=0; //0: petition 1: accepted 2:finished 3: failed
	AuctionTopicPub->publish(msg);
	RCLCPP_INFO(this->get_logger(), "Auctioned task");
    }

    void AuctionCallback(const self_flow::msg::Task::SharedPtr msg)
    {
	if(msg->type==0)
	{
		double ut=taskmap.at(msg->id)->utility()-curr_ut;
		auto reply=self_flow::msg::Bid();
		reply.utility=ut;
		reply.id=msg->id;
		reply.agent=my_name;
		BidTopicPub->publish(reply);
	}
/*	if(msg->type==1) //delete or update task

	if(msg->type==2) //update

	if(msg->type==3) //??
*/
    }

    void BidCallback(const self_flow::msg::Bid::SharedPtr msg)
    {
	//store all bids, if im the best bidder accept task, publish task_accepted, otherwise nothing for now(maybe wait and accept if 2nd?)

	start_task("msg->id");

    }

////////////////////CURRENT TASK FUNCTIONS //////////////


    void start_task(std::string taskname)
    {
	current_task=taskmap.at(taskname);
	if(&current_task)
	{
		curr_ut=current_task->utility();
		current_task->init();
		std::cout << "task init"<< std::endl;
	        timer1 = this->create_wall_timer(1s, std::bind(&AgentNode::timer1Callback, this));
	}
	else
	{
		std::cout << "error" << std::endl;
	}
    }

/*
    FeedbackTopicPub = this->create_publisher<std_msgs::msg::String>(COLLAB_TOPIC, 1);
    FeedbackTopicSub = this->create_subscription<std_msgs::msg::String>(COLLAB_TOPIC, 1, std::bind(&AgentNode::CollabCallback, this, _1));


    void pub_feedback(std::string feedback)
    {
	auto message = std_msgs::msg::String();
	message.data=feedback;
    	FeedbackTopicPub->publish(message);
    }

    void feedback_cb(const std_msgs::msg::String::SharedPtr msg)
    {
    }
*/

    void timer1Callback()
    {
	int status=current_task->tick();

	if (status==1)
	{
		std::string temp="Task in progress, id: ";
		temp+=std::to_string(current_task->id);
		RCLCPP_INFO(this->get_logger(), temp);
	}
	else if (status==2)
	{
		RCLCPP_INFO(this->get_logger(), "Task completed");
		timer1->cancel();
		complete();
	}
    }

};




