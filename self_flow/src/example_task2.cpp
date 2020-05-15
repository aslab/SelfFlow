#include "base_task.hpp"

class example_task2 : public base_task
{
private:

  int count=0;
  int status=0;

public:

  example_task2()
  {
	Requisite["example_done"]=0;
  }

  void execute() override
  {
	status=1;
  }

  int RequisiteCheck() override
  {
	if(Requisite.count("example_done")&&Requisite.at("example_done"))return 0;
	else return 1;
  }

  std::vector<std::string> RequisiteLoad() override
  {
	std::vector<std::string> v;
	v.push_back(std::string("example_task"));
	return v;
  }

  double utility() override
  {
	double ut=0.9;
	return ut;
  }

  int tick() override
  {
	count++;
	std::cout << "example2";
	if(count==5){status=2;}
        return status;  //-1:error, 0: not started, 1:in process, 2:finished
  }
};


