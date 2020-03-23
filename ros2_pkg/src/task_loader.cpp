#include "tasklist.h"
#define TIME_T int
#define AGENT_ID_T int
#define ID_T int
#include <string>
#include <sstream>
#include "msg/pub.?" ??

class xtask{ //task metadata
 private:
	task task1;
	TIME_T pub_time;
	TIME_T end_time;
	AGENT_ID_T publisher;
	AGENT_ID_T achiever;
	ID_T instance_id;
	bool is_completed=0;
	ID_T instance();
//	CHECKSUM_T checksum;
	MY_MSG_TYPE message; //?

 public:
	xtask(task task, ID_T instance_id, TIME_T time, AGENT_ID_T publisher_id){
	 this->task1=task;
	 this->instance_id=instance_id;
	 this->pub_time=time;
	 this->publisher=publisher_id;
//	 this->checksum=checksum(task_queue);
	}

	void prepare_msg(){
		message.type=1;
		message.name=task1.name;
		message.task_id=task1.id;
		message.instance_id=task1.instance_id;
		message.time=time();
		message.agent_id=publisher;
		message.checksum=checksum(public_task_queue.end().message);
	}
};

 vector<xtask> public_task_queue;

public_task_queue.end().

// void store_task{
//	task_queue.push_back(xtask)
//}
// void publish_task(){

//}
// void complete_task(){

//}
