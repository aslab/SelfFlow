#ifndef _BASE_TASK_
#define _BASE_TASK_
#include "TaskStatus.hpp"

class base_task
{

public:

  int id=1;

  bool is_collab=1;

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

  virtual int RequisiteCheck() //return number of tasks required before this
  {
	std::cout << "Misconstructed task" << std::endl;
	return -1;
  }

  virtual std::vector<std::string> RequisiteLoad() //return number of tasks required before this
  {
	std::cout << "Misconstructed task" << std::endl;
	std::vector<std::string> v;
	return v;
  }

  virtual std::string fb()
  {
	return "";
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
};

#endif
