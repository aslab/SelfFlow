#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "self_flow_core/msg/task.hpp"


#include "TaskList.hpp"
#include "TaskStatus.hpp"


#define TASK_TOPIC "/self_flow/task"
#define ONTO_TOPIC "/self_flow/knowledge"


using namespace std::chrono_literals;
using std::placeholders::_1;


class AgentNode : public rclcpp::Node
{
private:

    std::string my_name;

    double curr_ut=0.0;

    std::unordered_map<std::string, std::shared_ptr<base_task>> task_list; //list of available tasks

    std::unordered_map<std::string, double> pending_tasks; //list of tasks to be evaluated

    std::unordered_map<std::string, std::shared_ptr<base_task>> task_queue;  //local task queue

    std::shared_ptr<base_task> current_task; 	//active task

    rclcpp::Publisher<self_flow_core::msg::Task>::SharedPtr TaskPub;
    rclcpp::Subscription<self_flow_core::msg::Task>::SharedPtr TaskSub;
    rclcpp::Publisher<self_flow_core::msg::Task>::SharedPtr OntoPub;
    rclcpp::Subscription<self_flow_core::msg::Task>::SharedPtr OntoSub;
    rclcpp::TimerBase::SharedPtr timer0;
    rclcpp::TimerBase::SharedPtr timer1;


public:

    AgentNode(std::string name): Node(name)
    {
	my_name=name;
        TaskPub = this->create_publisher<self_flow_core::msg::Task>(TASK_TOPIC, 1);
        TaskSub = this->create_subscription<self_flow_core::msg::Task>(TASK_TOPIC, 1, std::bind(&AgentNode::task_callback, this, _1));
        OntoPub = this->create_publisher<self_flow_core::msg::Task>(ONTO_TOPIC, 1);
        OntoSub = this->create_subscription<self_flow_core::msg::Task>(ONTO_TOPIC, 1, std::bind(&AgentNode::onto_callback, this, _1));
        timer1 = this->create_wall_timer(5s, std::bind(&AgentNode::timer1Callback, this));

/////////////TASK DEFINITION ///////////////////////////////////////


	RCLCPP_INFO(this->get_logger(), "Starting Agent...");

//	tmp_ptr=std::make_shared<example_task>(* new example_task);
//	task_list["example_task"]=tmp_ptr;

//	load all tasks from this agent using ontology

	std::shared_ptr<base_task> tmp_ptr;
	tmp_ptr=std::make_shared<idle_task>(* new idle_task);
        task_list["idle_task"]=tmp_ptr;
//	  tmp_ptr=std::make_shared<home_task>(* new home_task);
//        task_list["home_task"]=tmp_ptr;
//        tmp_ptr=std::make_shared<find_object_task>(* new find_object_task);
//        task_list["find_object_task"]=tmp_ptr;

	add_task("idle_task");



	for (auto taskid : taskidlist)
	{
		knowledge_request(taskid, my_name);
	}
	this->task_update();
    }



//////////////////////TASK MSGS//////////////////////////////////////

    void pub_feedback(std::string id,uint8_t status)
    {
	auto message = self_flow_core::msg::Task();
	message.id=id;
	message.agent=my_name;
	message.status=status;
    	TaskPub->publish(message);
	std::string l="Task status: ";
	l+=status;
	RCLCPP_INFO(this->get_logger(), l);
    }

    void AuctionTask(std::string id)
   {
	auto msg=self_flow_core::msg::Task();
	msg.id=id;
	msg.agent=my_name;
	msg.status=0; //0: request 1: auction response 2: collaboration request 3: individual request 10: in progress  11: finished 12: failed
	TaskPub->publish(msg);
	std::string l="Auctioned task: ";
	l+=id;
	RCLCPP_INFO(this->get_logger(), l);
    }

    void task_callback(const self_flow_core::msg::Task::SharedPtr msg)
    {
	TaskStatus[msg->id]=msg->status;
	if(msg->status==0 && task_list.count(msg->id)) //task auction received
	{

		//strip #
		double ut=task_list.at(msg->id)->utility();
		std::string l="Task received: ";
		l+=msg->id;
		l+=" , my utility: ";
		l+=std::to_string(ut);
		RCLCPP_INFO(this->get_logger(), l);
		pending_tasks[msg->id]=double(ut);
//		timer0->cancel(); //breaks for some reason
		timer0 = this->create_wall_timer(3s, std::bind(&AgentNode::timer0Callback, this));
	}

	else if(msg->status==1 && pending_tasks.at(msg->id) < msg->utility)	// If better bidder is found
	{
		RCLCPP_INFO(this->get_logger(), "Task declined: lower utility");
		timer0->cancel();
		pending_tasks.erase(msg->id);
		return;
	}

//	else if (msg->status==2 && task_list.at(msg->id)->is_collab()) //task collaboration petition received
//	{
//		RCLCPP_INFO(this->get_logger(), "Collaborative Task accepted");
//		add_task(msg->id);
//	}

	else if(msg->status==3 && msg->agent==my_name)  //individual request
	{
		add_task(msg->id);
	}

	else if(msg->status==10)//in progress
	{
		task_queue.erase(msg->id);
		pending_tasks.erase(msg->id);
	}
	else if(msg->status==11)//finished
	{
		task_queue.erase(msg->id);
		pending_tasks.erase(msg->id);
	}
	else if(msg->status==12)//failed
	{
		task_queue.erase(msg->id);
		pending_tasks.erase(msg->id);
	}
    }


/////////////////////////ONTOLOGY INTERFACING///////////////////////////

    void onto_callback(const self_flow_core::msg::Task::SharedPtr msg)
    {

	if (msg->status==1)
	{
	if (msg->agent==my_name)
	{
	    std::string l="New task available: ";
	    l+=msg->id;
	    RCLCPP_INFO(this->get_logger(), l);
	    std::shared_ptr<base_task> tmp_ptr;
	    if(msg->id=="idle")
	    {
		tmp_ptr=std::make_shared<idle_task>(* new idle_task);
        	task_list["idle"]=tmp_ptr;
	    }
	    else if(msg->id=="home")
	    {
		tmp_ptr=std::make_shared<home_task>(* new home_task);
        	task_list["home"]=tmp_ptr;
	    }
	    else if(msg->id=="find_object")
	    {
		tmp_ptr=std::make_shared<find_object_task>(* new find_object_task);
       		task_list["find_object"]=tmp_ptr;
	    }
	    else if(msg->id=="interact")
	    {
		tmp_ptr=std::make_shared<interact_task>(* new interact_task);
       		task_list["interact"]=tmp_ptr;
	    }
	    else if(msg->id=="interact_assist")
	    {
		tmp_ptr=std::make_shared<interact_assist_task>(* new interact_assist_task);
       		task_list["interact_assist"]=tmp_ptr;
	    }
	    else if(msg->id=="map")
	    {
		tmp_ptr=std::make_shared<map_task>(* new map_task);
       		task_list["map"]=tmp_ptr;
	    }
	    else if(msg->id=="moveto_coordinate")
	    {
		tmp_ptr=std::make_shared<moveto_coordinate_task>(* new moveto_coordinate_task);
       		task_list["moveto_coordinate"]=tmp_ptr;
	    }
	    else
	    {
		RCLCPP_ERROR(this->get_logger(), "Bad task id");
	    }
	    }
	}

//	else if(msg->id==help_required)
//	{

//	}

    }


   void knowledge_request(std::string ability,std::string agent)
   {
	auto msg=self_flow_core::msg::Task();
        msg.id=ability;
        msg.agent=agent;
        msg.status=0; //0: request, 1: reply
        OntoPub->publish(msg);
        std::string l="Requesting knowledge to ontology: is ";
        l+=agent;l+=" able to perform ";l+=ability;l+=" ?";
        RCLCPP_INFO(this->get_logger(), l);
   }


/////////////////////////////////TASK MANAGEMENT//////////////////////////////////////////////


    void add_task(std::string taskname)
    {
	auto temp=task_list.at(taskname);
	if(temp->RequisiteCheck())
	{
		std::vector<std::string> reqlist = temp->RequisiteLoad();
        	for (auto it : reqlist)
		{
			if(TaskStatus.count(it)==0)	//making sure the task has not already been requested
			{
				AuctionTask(it);
			}
			else	//if task was already pending search for suitable agents
			{
//				ability_query[it]
				knowledge_request(it, std::string("any"));
			}
		}
	}
	task_queue[taskname]=temp;
    }


    void task_update() //continuous check on task priorities
    {
	double ut=0.0;
	std::shared_ptr<base_task> temp_task=current_task;
	for (auto taskpair : task_queue)	//find best task
	{
		auto task=taskpair.second;
		if(TaskStatus.count(task->id()))
		{
			if(task->RequisiteCheck()==0 && task->utility()>ut && TaskStatus[task->id()]!=10) //if task has no requisites to make, has bigger utility and has not already started
			{
				ut=task->utility();
				temp_task=task;
			}
		}

		else
		{
			if(task->RequisiteCheck()==0 && task->utility()>ut)
			{
				ut=task->utility();
				temp_task=task;
			}
		}

	}
	if(current_task!=temp_task) 	//start new task
	{
		current_task=temp_task;
		current_task->init();
//		if temp_task->is_collab(){publish_status(temp_task->id)}
	        timer1 = this->create_wall_timer(5s, std::bind(&AgentNode::timer1Callback, this)); //continuous status check
//	        timer1 = this->create_wall_timer(current_task->tick_rate(), std::bind(&AgentNode::timer1Callback, this)); //TO BE IMPLEMENTED
		std::string l="New task started: ";
		l+=current_task->id();
		RCLCPP_INFO(this->get_logger(), l);

	}
    }

    void timer0Callback() //timer for auction end
    {
	for(auto task : pending_tasks)
	{
		if (task.second!=0.0)
		{
			add_task(task.first);
		}

	}
	this->task_update();
    }

    void timer1Callback()  //task status check
    {
	int status=current_task->tick();
	if (status==11)
	{
		RCLCPP_INFO(this->get_logger(), "Task completed");
		pub_feedback(current_task->id(),11);
		timer1->cancel();
	}
	else if (status==12)
	{
		RCLCPP_INFO(this->get_logger(), "Task failed");
		pub_feedback(current_task->id(),12);
		timer1->cancel();
	}
	else if (status==10)
	{
		RCLCPP_INFO(this->get_logger(), "Task in progress");
		pub_feedback(current_task->id(),10);
	}
    }

};



int main(int argc, char * argv[])
{
 rclcpp::init(argc, argv);

  auto agent = std::make_shared<AgentNode>("mapper");
  rclcpp::spin(agent);

  return 0;
}

