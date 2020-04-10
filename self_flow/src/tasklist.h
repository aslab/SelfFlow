#ifndef _TASKLIST_
#define _TASKLIST_
#include <string>


class task
{
 public:
	std::string name;
	ID_T id;
	virtual	void execute()
	{
	  std::cout << "Error, task " << this->name << " is empty" << std::endl;
	}
	virtual	UTILITY_T ability(){return 0;}
};

std::vector<task> tasklist; 		//Change this


class autotask: public task
{
 public:
	autotask(std::string name, ID_T id)
        {
          this->name=name;
          this->id=id;
          tasklist.push_back(*this);
        }
};


task * find_task(ID_T id)
{
    std::cout << "Looking for task" << std::endl;
  for (std::vector<task>::iterator it=tasklist.begin(); it!=tasklist.end();it++)
  {
	if (it->id==id){return &(*it);}
  }
  std::cout << "id error" << std::endl;
  return &(tasklist[0]);
}



//////////////////////////////////////////////
//		TASKS
//////////////////////////////////////////////


class empty_task: public autotask
{
  public:
        empty_task() : autotask("empty_task",666){}
}empty_task_o;



class find_ball: public autotask
{
  public:
	find_ball() : autotask("find_ball",1){}

}find_ball_o;


class print_tasks: public autotask
{
  public:
        print_tasks() : autotask("print_tasks",101){}
	UTILITY_T ability(){return .8;}
	void execute()
	{
	  std::cout << "executing print_tasks... " << std::endl;
	  for (auto it : tasklist)
          {
            std::cout << "task name: " << it.name << ", task id: " << it.id << std::endl;
          }
	}
}print_tasks_o;



///////////////////////////////////////////
//		IMPLEMENTATIONS 		(move to another file?)
//////////////////////////////////////////



//task grab_ball = {"grab_ball",2};

//task power_mgmt ={"power_mgmt",3};
//etc

#endif
