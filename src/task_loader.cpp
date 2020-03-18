#include "tasklist.h"
#define TIME_T int
#define AGENT_ID_T int
#define ID_T int
#include <string>
#include <sstream>

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
 public:
	xtask(task task, ID_T instance_id, TIME_T time, AGENT_ID_T publisher_id){
	 this->task1=task;
	 this->instance_id=instance_id;
	 this->pub_time=time;
	 this->publisher=publisher_id;
//	 this->checksum=checksum(task_queue);
	}

	std::string print(){
		std::ostringstream data;
		data<<"msg_pub"<<std::endl<<
		"task: " << task1.name<< std::endl<<
		"task_id: " << task1.id << std::endl<<
		"instance_id; " << instance_id<< std::endl<<
		"time: " << pub_time << std::endl<<
		"publisher_id: " << publisher
//		"checksum"
		;
		return std::string(data.str());
	}
};

// vector<xtask> public_task_queue;
//
// void store_task{
//	task_queue.push_back(xtask)
//}
// void publish_task(){

//}
// void complete_task(){

//}
