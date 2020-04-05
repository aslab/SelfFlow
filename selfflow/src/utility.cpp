#include "tasklist.h"
//#include "implementation.cpp"
#include "confidence.cpp"
#include "ability.cpp"


struct xtask
{
	task taskdata;
	TIME_T pub_time;
	AGENT_ID_T publisher;
	UTILITY_T utility;
	uint8_t status=0; //1 published 2 started 3 completed
	uint32_t instance_id; //??
};

class task_queue
{
  private:
	std::vector<xtask> queue;

  public:
	void add_task(MY_MSG_TYPE message)
	{
		xtask temp;
//		temp.taskdata=sort(message)  //find related task
//		temp.pub_time=message.stamp; 		??
		temp.publisher=message.agent_id;
		temp.instance_id=message.instance_id;
		temp.status=1;
		queue.push_back(temp);
		this->update();
	}
//	void update_task(MY_MSG_TYPE message) //change
//	{
//		if(message.type == 2 || message.type == 3)
//		{
//			int i=0;
//			while(queue[i].instance_id!=message.instance_id){i++;} //add exception
//			queue[i].status=message.type;
//			queue[i].end_time=message.stamp;
//			queue[i].publisher=message.agent_id;
//		}
//	}

//	MY_MSG_TYPE read(ID_T instance)
//	{
//		int i=0;
//		while(queue[i].instance_id!=instance){i++;}
//		MY_MSG_TYPE message;
//		message.type=5;
//		message.task=queue[i].task.name;
//		message.task_id=queue[i].task.id;
//		message.instance_id=queue[i].instance_id;
//		message.agent_id=queue[i]. ???
//		return message;
//	}

	void calc_utility()
	{
		for (std::vector<xtask>::iterator it = queue.begin(); it!= queue.end(); ++it)
			{
			it->utility=ability(it->taskdata.id)*confidence();//*interest();
			}
	}

	void update()
	{

		calc_utility();
		//execute_best();
	}
};











