class base_task
{
private:

  int id=1;

public:

  virtual void execute(){RCLCPP_ERROR(this->get_logger(), "Misconstructed task");}


  void init()
  {
	if(!RequisiteCheck()){this->execute();}
  }

  void init(int id) //
  {
	this->id=id;
	if(!RequisiteCheck()){this->execute();}
  }

  virtual int RequisiteCheck() //check and start requisites for this task
  {
	RCLCPP_ERROR(this->get_logger(), "Misconstructed task");
	return 1;
  }

  virtual double utility()
  {
	RCLCPP_ERROR(this->get_logger(), "Misconstructed task");
	return 0.0;
  }

  virtual int tick()	//do task stuff and provide feedback
  {
        RCLCPP_ERROR(this->get_logger(), "Misconstructed task");
        return 3;  //3:error, 2: not started, 1:in process, 0:finished
  }

  virtual void on_complete()
  {
	//publish on /tasks/$id string/void for calling a callback
  }

  virtual void global_callback(int child_id)
  {
	//update status depending on child id
  }
}

