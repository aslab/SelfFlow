#include "tasklist.h"


/* ejemplo:
 task=select(t_id);
 ability=task.ability()
 task.execute()
*/




vector<task> tasks;




void clear_tasks(){
        tasks.clear();
}



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
 }

 void find_best(tasklist my_tasks);

  task * task;
  UTILITY_T ut=0;
  for i in tasklist{

        curr_ut=evaluate_ability(my_tasks[i]);
        if (curr_ut>ut){
        ut=curr_ut;
        task=&my_tasks[i];
  }
 }




/* ejemplo:
 task=select(t_id);
 ability=task.ability()
 task.execute()
*/



