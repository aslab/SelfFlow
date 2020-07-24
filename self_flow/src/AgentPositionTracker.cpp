
class AgentPositionTracker : public rclcpp::Node
{
  public:
    AgentPositionTracker()
    : Node("name of the node") //generate node name
    {
	publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/move_base_simple/goal", 10); //possible to change goal topic name?
	timer_ = this->create_wall_timer(
	000ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
	auto message = geometry_msgs::msg::PoseStamped();
	message.header.stamp.sec=0;
	message.header.frame_id="odom"; //change?
	message.pose.position.x= 1.0;
	message.pose.position.y= 0.5;
	message.pose.position.z= 0.0;
	message.pose.orientation.w=1.0;
	RCLCPP_INFO(this->get_logger(), "Requesting position x='%f', y='%f',  z='%f'",message.pose.position.x, message.pose.position.y, message.pose.position.z);
	publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  };

