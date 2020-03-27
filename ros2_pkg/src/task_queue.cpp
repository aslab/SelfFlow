#include <stdio>
#include <string>
#include "tasklist.h"
#include "msg/?"

#define TIME_T ros::Time
#define AGENT_ID_T uint32_t
#define ID_T uint32_t

typedef struct xtask{ //task metadata
	task task_self;
	TIME_T pub_time;
	TIME_T end_time;
	AGENT_ID_T publisher;
	AGENT_ID_T achiever;
	ID_T instance_id;
	uint8_t status=0; //1 published 2 started 3 completed
}


class task_queue{
  private:
	vector<xtask> queue;

  public:
	void store(MY_MSG_TYPE message){
		xtask temp;
		temp.task=sort(message.task) ??
		temp.pub_time=message.clock;
		temp.publisher=message.agent_id;
		temp.instance_id=message.instance_id;
		temp.status=1;
		queue.push_back(temp);
	}
	void update(MY_MSG_TYPE message){
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
}



