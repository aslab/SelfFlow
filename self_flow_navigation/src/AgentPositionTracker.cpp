#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#define TOPICNAME "/self_flow/tracker"

using namespace std::chrono_literals;
using std::placeholders::_1;

//Add support for storing location coordinates in a file



class AgentPositionTracker : public rclcpp::Node
{
  private:
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr NavPub;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr SelfSub;
//    rclcpp::TimerBase::SharedPtr timer_;


  public:
    AgentPositionTracker()
    : Node("agent_tracker") //generate node name
    {
	NavPub = this->create_publisher<geometry_msgs::msg::PoseStamped>("/move_base_simple/goal", 10);
	SelfSub = this->create_subscription<std_msgs::msg::String>(TOPICNAME, 1, std::bind(&AgentPositionTracker::PositionCallback, this, _1));
//	timer_ = this->create_wall_timer(500ms, std::bind(&AgentPositionTracker::timer_callback, this));
    }


    void PositionCallback(const std_msgs::msg::String::SharedPtr msg)
    {
	if (msg->data=="home")
	{
	  auto message = geometry_msgs::msg::PoseStamped();
	  message.header.stamp.sec=0;
	  message.header.frame_id="map";
	  message.pose.position.x= 0.0;
	  message.pose.position.y= 0.0;
	  message.pose.position.z= 0.0;
//	  message.pose.orientation.w= 0.0;
	  NavPub->publish(message);
	  RCLCPP_INFO(this->get_logger(), "Requested position x='%f', y='%f',  z='%f'",message.pose.position.x, message.pose.position.y, message.pose.position.z);
	}
	else if (msg->data=="object")
	{
	  auto message = geometry_msgs::msg::PoseStamped();
	  message.header.stamp.sec=0;
	  message.header.frame_id="map";
	  message.pose.position.x= -1.0;
	  message.pose.position.y= -5.0;
	  message.pose.position.z= 0.0;
	  NavPub->publish(message);
	  RCLCPP_INFO(this->get_logger(), "Requested position x='%f', y='%f',  z='%f'",message.pose.position.x, message.pose.position.y, message.pose.position.z);
	}

//	else if (msg->data=="map")
//	else if (msg->data=="poi")
    }
  };

