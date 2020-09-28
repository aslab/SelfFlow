#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "position.hpp"
class AgentPositionTracker : public rclcpp::Node
{
  public:
    AgentPositionTracker()
    : Node("agent_tracker") //generate node name
    {
	publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/move_base_simple/goal", 10);
	timer_ = this->create_wall_timer(500ms, std::bind(&AgentPositionTracker::timer_callback, this));
    }

    void timer_callback()
    {
        if (req_pos.on)
        {
	  auto message = geometry_msgs::msg::PoseStamped();
	  message.header.stamp.sec=0;
	  message.header.frame_id="odom";
	  message.pose.position.x= req_pos.x;
	  message.pose.position.y= req_pos.y;
	  message.pose.position.z= req_pos.z;
	  message.pose.orientation.w= req_pos.w;
	  req_pos.on=0;
	  publisher_->publish(message);
	  RCLCPP_INFO(this->get_logger(), "Requested position x='%f', y='%f',  z='%f'",message.pose.position.x, message.pose.position.y, message.pose.position.z);
        }
    }
  private:
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
  };

