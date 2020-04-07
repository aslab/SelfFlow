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
	  std::cout << "Error, task " << this->name << "is empty" << std::endl;
	}
	virtual	UTILITY_T ability(){return 0;}
};

std::vector<task> tasklist;


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
  for (auto it : tasklist)
  {
	if (it.id==id){return &it;}
  }
  return 0;
}



//////////////////////////////////////////////
//		TASKS
//////////////////////////////////////////////



class find_ball: public autotask
{
  public:
	find_ball() : autotask("find_ball",1){}

}find_ball_o;



class print_tasks: public autotask
{
  public:
        print_tasks() : autotask("print_tasks",101){}
	void execute();
}print_tasks;



///////////////////////////////////////////
//		IMPLEMENTATIONS 		(move to another file)
//////////////////////////////////////////



void print_tasks::execute()
{
	for (auto it : tasklist)
          {
            std::cout << "task name: " << it.name << ", task id: " << it.id;
          }
}

//void print_tasks::ability(){return 0.5;}

//task grab_ball = {"grab_ball",2};

//task power_mgmt ={"power_mgmt",3};
//etc

#endif
