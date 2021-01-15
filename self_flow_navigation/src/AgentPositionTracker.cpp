#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "position.hpp"
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
	if (msg.data=="home")
	{
	  auto message = geometry_msgs::msg::PoseStamped();
	  message.header.stamp.sec=0;
	  message.header.frame_id="map";
	  message.pose.position.x= req_pos.x;
	  message.pose.position.y= req_pos.y;
	  message.pose.position.z= req_pos.z;
	  message.pose.orientation.w= req_pos.w;
	  NavPub->publish(message);
	  RCLCPP_INFO(this->get_logger(), "Requested position x='%f', y='%f',  z='%f'",message.pose.position.x, message.pose.position.y, message.pose.position.z);
	}
    }
  };

