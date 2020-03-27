#include "tasklist.h"
#include "implementation.cpp"
#include "confidence.cpp"


#define UTILITY_T 
#define TIME_T ros::Time
#define AGENT_ID_T uint32_t
#define MY_MSG_TYPE 


typedef struct xtask{ //task
	task taskdata;
	TIME_T pub_time;
	AGENT_ID_T publisher;
	UTILITY_T utility;
	uint8_t status=0; //1 published 2 started 3 completed
}



class task_queue{
  private:
	vector<xtask> queue;

  public:
	void add_task(MY_MSG_TYPE message){
		xtask temp;
		temp.task=sort(message.task) ??
		temp.pub_time=message.clock;
		temp.publisher=message.agent_id;
		temp.instance_id=message.instance_id;
		temp.status=1;
		queue.push_back(temp);
		this->update();
	}
	void update_task(MY_MSG_TYPE message){
		if(message.type == 2 || message.type == 3){
			int i=0;
			while(queue[i].instance_id!=message.instance_id){i++;} //add exception
			queue[i].status=message.type;
			queue[i].end_time=message.clock;
			queue[i].achiever=message.agent_id;
	}

	MY_MSG_TYPE read(ID_T instance){
		int i=0;
		while(queue[i].intance_id!=instance){i++;}
		MY_MSG_TYPE message;
		message.type=5;
		message.task=queue[i].task.name;
		message.task_id=queue[i].task.id;
		message.instance_id=queue[i].instance_id;
		message.clock=queue[i]. ???
		message.agent_id=queue[i]. ???
		return message;

	}

	void calc_utility(){
		for (std::vector<xtask>::iterator it = queue.begin(); it!= queue.end(); ++it){
			it.utility=ability(it.taskdata.id)*confidence()*interest();
	}

	void update(){

		calc_utility();
		//execute_best();
	}
}











