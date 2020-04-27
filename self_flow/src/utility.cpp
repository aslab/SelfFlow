#include "tasklist.h"


class task_queue
{
  public:

	void store_task(TASK_MSG_TYPE message)
	{
		xtask temp;
		std::vector<xtask>::iterator it;
		for (it=queue.begin(); it!=queue.end() && it->instance_id!=message.instance_id; ++it){} //find element

		if(message.type == 1 ) // && it==queue.end()) disable check for debbuging
		{
			temp.task_ptr=find_task(message.task_id); //find related task
//			temp.pub_time=message.stamp;
                	temp.instance_id=message.instance_id;
			queue.push_back(temp);
			std::cout << "Task stored: " << temp.task_ptr->name << std::endl;
        	        this->update();
		}
		else if(message.type == 2)
		{
                        it->started=1;
		}
		else if (message.type == 3)
		{
			queue.erase(it);
		}
		else {std::cout << "message parse error" << std::endl;}

	}


	void calc_utility()
	{
		UTILITY_T max=0;
		for (auto it : queue)
		{
			it.utility= it.task_ptr->ability();// * confidence();// * interest();
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
		if(best->task_ptr->id==102){this->show_active_tasks();} //debug task
		best->task_ptr->execute();
	//	queue.erase(best); send instead a message with task completed
	}

	void show_active_tasks()
	{
	  std::cout << "executing show_active_tasks... " << std::endl;
          for (auto it : queue)
          {
          	std::cout << "task name: " << it.task_ptr->name << ", task id: " << it.task_ptr->id <<", utility: "<< it.utility;
		if(it.started){std::cout << "(STARTED)";}
		std::cout << std::endl;
	  }
	}
};




