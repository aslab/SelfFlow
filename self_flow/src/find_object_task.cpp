#include "base_task.hpp"
#include "position.hpp"
#include <stdlib.h>     /* srand, rand */

class find_object_task : public base_task
{
private:

  int count=0;
  int status=0;

public:

  std::string id() override
  {
	std::string name="find_object_task";
	return name;
  }

  void execute() override
  {
	status=1;
  }

  int RequisiteCheck() override
  {
//        if(TaskStatus.count("map")&&TaskStatus.at("map"))return 0;
//        else return 1;
	return 0;
  }

  std::vector<std::string> RequisiteLoad() override
  {
        std::vector<std::string> v;
        v.push_back(std::string("map"));
        return v;
  }


  double utility() override
  {
	double ut=0.6;
	return ut;
  }

  int tick() override	//do task stuff and provide feedback
  {
	count++;
	if(count==5)
	{
		count=0;
//		status=2;
		float x=(rand()%1000)/10.0 -50.0;
		float y=(rand()%1000)/10.0 -50.0;
		request_position(x,y,0.0,0.0);
        }
	return status;  //-1:error, 0: not started, 1:in process, 2:finished
  }

  int tick_rate() override
  {
	return 20;
  }

};


