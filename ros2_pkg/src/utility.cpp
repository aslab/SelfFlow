#include "tasklist.h"


 void security(){
//private task "emergency stop" with interest=0 unless there is a risk involved
        tasks.push_back(emergency_stop);
 }


 void pwr_mgmt(){
//private task for battery management with an exponential interest curve dependant on remaining battery
        tasks.push_back(battery);
 }

 void comply(UTILITY_T u){
//store public tasks with interest=.5
        for (std::vector<xtask>::iterator it = public_task_queue.begin(); it!= public_task_queue.end(); ++it){
                tasks.pushback((*it).task);
        }
	//do something about interest, maybe a formula
 }

 task * find_best(std::vector<task> tasks);

	task * taskptr;
	UTILITY_T util=0,curr_util;
	for (std::vector<task>::iterator it = tasks.begin(); it!= tasks.end(); ++it){

        	curr_util=evaluate_utility(it);
        	if (curr_ut>ut){
        	util=curr_util;
        	taskptr=it; //is this right?
  	}
  	return taskptr;
 }







