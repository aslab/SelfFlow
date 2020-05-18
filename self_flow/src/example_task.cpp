#include "base_task.hpp"

class example_task : public base_task
{
private:

  int count=0;
  int status=0;

public:

  void execute() override
  {
	status=1;
  }

  int RequisiteCheck() override
  {
        if(Requisite.count("requisite_name")&&Requisite.at("requisite_name"))return 0;
        else return 1;
  }

  std::vector<std::string> RequisiteLoad() override
  {
        std::vector<std::string> v;
        v.push_back(std::string("requisite_name"));
        return v;
  }


  double utility() override
  {
	double ut=0.8;
	return ut;
  }

  int tick() override	//do task stuff and provide feedback
  {
	count++;
	if(count==5){status=2;}
        return status;  //-1:error, 0: not started, 1:in process, 2:finished
  }

  std::string fb()
  {
	return "example_task";
  }
};


