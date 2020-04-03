#ifndef _TASKLIST_
#define _TASKLIST_
#include <string>


struct task
{
 std::string name;
 ID_T id;
};

const task find_ball = {"find_ball",1};

const task grab_ball = {"grab_ball",2};

const task power_mgmt ={"power_mgmt",3};
//etc

#endif
