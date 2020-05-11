#include <cstdint>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "self_flow/msg/task_auction.hpp"
#include "self_flow/msg/task_bid.hpp"
#include "self_flow/msg/task_assign.hpp"

#define UTILITY_T double

#define AUCTION_TOPIC "/self_flow/auction_task"
#define BID_TOPIC "/self_flow/bid_task"
//Note: the assign_tasks topic will be replaced with a ros2 action server



using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node
{
private:

    bool auction_pending=0;
    std::string atid;
    bool busy=0;
    std::string my_name;

    std::unordered_map<std::string,*base_task> taskmap;

    std::SharedPtr<base_task> current_task;
    std::vector<base_task> ostensible_tasks;

    rclcpp::Publisher<self_flow::msg::Task>::SharedPtr AuctionTopicPub;
    rclcpp::Subscription<self_flow::msg::Task>::SharedPtr AuctionTopicSub;
    rclcpp::Publisher<self_flow::msg::Bid>::SharedPtr BidTopicPub;
    rclcpp::Subscription<self_flow::msg::Bid>::SharedPtr BidTopicSub;
    rclcpp::Publisher<self_flow::msg::Task>::SharedPtr CollabTopicPub;
    rclcpp::Subscription<self_flow::msg::Task>::SharedPtr CollabTopicSub;
    rclcpp::TimerBase::SharedPtr timer1;
//    rclcpp::TimerBase::SharedPtr timer2;



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
        timer1 = this->create_wall_timer(10s, std::bind(&AgentNode::timer1Callback, this));
//      timer2 = this->create_wall_timer(1s, std::bind(&AgentNode::timer1sCallback, this));

    }




//////////////////////ROS MSGS//////////////////////////////////////

    void CollabTask(std::string id){}

    void CollabCallback(const self_flow::msg::TaskAuction::SharedPtr msg){}

    void AuctionTask(std::string id)
    {
	auto msg=self_flow::msg::TaskAuction();
	msg.id=id;
	msg.agent=my_name;
	msg.type=0; //0: petition 1: accepted 2:finished 3: failed
	AuctionTopicPub->publish(msg);
	RCLCPP_INFO(this->get_logger(), "Auctioned task");
    }

    void AuctionCallback(const self_flow::msg::TaskAuction::SharedPtr msg)
    {
	if(!busy&&msg.type==0)
	{
		double ut=taskmap.at(msg.id)->utility();
		auto reply=self_flow::msg::TaskBid();
		reply.utility=ut;
		reply.id=msg.id;
		reply.agent=my_name;
		BidTopicPub->publish(reply);
	}
	if(msg.type==1) //delete or update task

	if(msg.type==2) //update

	if(msg.type==3) //??

    }

    void BidCallback(const self_flow::msg::TaskBid::SharedPtr msg)
    {
	//store all bids, if im the best bidder publish task accepted otherwise nothing for now(maybe wait and accept if 2nd?)



    }

//////////////////// TIMER CALLBACKS ////////////////////

    void timer1Callback()
    {
    }

};




