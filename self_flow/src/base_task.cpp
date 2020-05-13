#ifndef _BASE_TASK_
#define _BASE_TASK_

class base_task
{

public:

  int id=1;

  virtual void execute(){std::cout << "Misconstructed task" << std::endl;}

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
	std::cout << "Misconstructed task" << std::endl;
	return -1;
  }

  virtual double utility()
  {
	std::cout << "Misconstructed task" << std::endl;
	return -1.0;
  }

  virtual int tick()	//do task stuff and provide feedback
  {
	std::cout << "Misconstructed task" << std::endl;
        return -1;  //-1:error, 0: not started, 1:in process, 2:finished

  }

/*
  virtual void global_callback(int child_id)
  {
	//update status depending on child id
  }
*/
};

#endif
