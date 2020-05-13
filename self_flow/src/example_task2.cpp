#include "base_task.cpp"
#include "requisite.cpp"

class example_task2 : public base_task
{
private:

  std::shared_ptr<requisite> parent;
  int count=0;
  int status=0;
  bool (*requ)();

public:

  example_task2(bool (*req)() ){requ=req;}

  virtual void execute()
  {
	status=1;
  }

  virtual int RequisiteCheck() //check and start requisites for this task
  {
	if(requ())return 0;
	else return -1;
  }

  double utility() override
  {
	double ut=0.8;
	return ut;
  }

  virtual int tick()	//do task stuff and provide feedback
  {
	count++;
	if(count==5){status=2;}
        return status;  //-1:error, 0: not started, 1:in process, 2:finished
  }

//  void global_callback(int child id) override
//  {
//  }
};


