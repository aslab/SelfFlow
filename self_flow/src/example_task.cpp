class example_task : public base_task //move to found
{
private:

  int id=1;

  int location_id=-1;
  tf location;

public:

  virtual void execute()
  {
	
  }

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

	if(!location)
	return 1;
  }

  virtual double utility()
  {
	double ut=0.0;


	return ut;
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

  void global_callback override (int child id)
  }
}

