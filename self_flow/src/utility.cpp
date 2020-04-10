#include "tasklist.h"
//#include "implementation.cpp"
#include "confidence.cpp"


struct xtask
{
	task * task_;
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
	xtask * best;

  public:
	void add_task(MY_MSG_TYPE message)
	{
		xtask temp;
		temp.task_=find_task(message.task_id); //find related task
//		temp.pub_time=message.stamp; 		??
		temp.publisher=message.agent_id;
		temp.instance_id=message.instance_id;
		temp.status=1;
		queue.push_back(temp);
		std::cout << "added task: " << temp.task_->name << std::endl;
		this->update();
	}

	void calc_utility()
	{
		UTILITY_T max=0;
		for (auto it : queue)
		{
			it.utility= it.task_->ability();// * confidence();// * interest();
			if (it.utility >= max)
			{
				max=it.utility;
				best=&it;
			}
		}
	}


	void update()
	{
		calc_utility();
		best->task_->execute();
		print_tasks_o.execute();
	}
};




/////////////////////////////////////////////////////////////////////////////////////////////////////


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









