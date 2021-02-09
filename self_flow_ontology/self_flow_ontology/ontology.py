import sys
from owlready2 import *
import rclpy
from rclpy.node import Node


from std_msgs.msg import String
from self_flow_core.msg import Task


#onto_path.append("./") Store updated ontology?
onto = get_ontology("/home/jdcdp/git/SelfFlow/self_flow_ontology/owl/SelfFlow.owl")
onto.load()

agent1 = onto.Turtlebot3("mapper")
agent2 = onto.Turtlebot3("gripper")

ab1 = onto.GroundNavigation("nav2")
ab2 = onto.SLAM("cartographer")
ab3 = onto.SLAM("slam_toolbox")
ab4 = onto.ObjectDetection("opencv")
ab5 = onto.ObjectInteraction("base_interaction")

agent1.hasAbility = [ab1,ab2,ab3,ab4]
agent2.hasAbility = [ab1,ab5]


task1 = onto.Task("home")
task1.dependsOn = [ab1]

task2 = onto.Task("moveto_coordinate")
task2.dependsOn = [ab1]

task3 = onto.Task("find_object")
task3.dependsOn = [ab1,ab4]

task4 = onto.Task("interact_assist")
task4.dependsOn = [ab1,ab4]

task5 = onto.Task("interact")
task5.dependsOn = [ab1,ab5]

task6 = onto.Task("map")
task6.dependsOn = [ab1,ab3] # 'or' relationship with ab2?



class OntologyReasoner(Node):

    def __init__(self):
        super().__init__('ontology_reasoner')
        self.publisher_ = self.create_publisher(Task, '/self_flow/knowledge', 10)

        self.subscription = self.create_subscription(
            Task,
            '/self_flow/knowledge',
            self.onto_callback,
            10)

        self.subscription  # prevent unused variable warning
        self.get_logger().info('Loaded ontology')



    def onto_callback(self, msg):
        if msg.status==0:   # request
           self.get_logger().info('Knowledge request received: "%s"' % msg.agent)
           if msg.agent=="any":
             agents=find_agents(msg.id)
             for agent in agents:
                self.get_logger().info('Found available agent: {0}'.format(agent.name))
                msgt = Task()
                msgt.agent=agent.name
                msgt.status=1
                msgt.id=msg.id
                self.publisher_.publish(msgt)

           else :
             if(check_ability(find_agent(msg.agent),msg.id)):
                self.get_logger().info('Ability {0} available'.format(msg.id))
                msgt = Task()
                msgt.agent=msg.agent
                msgt.status=1
                msgt.id=msg.id
                self.publisher_.publish(msgt)


def find_agents(task):

       deps=find_task(task).dependsOn
       agents=onto.Turtlebot3.instances()
       for agent in agents:
         for dep in deps:
             if(not(check_ability(agent,id))):
                agents.remove(agent)
                break
       return agents

def find_agent(name):
       agents=onto.Turtlebot3.instances()
       for agent in agents:
         if (agent.name==name):
            return agent

def find_task(id):
       tasks=onto.Task.instances()
       for task in tasks:
         if (task.name==id):
            return task

def check_ability(agent,ability):
        for ab in agent.hasAbility:
            if (ab.name==ability):
                return 1
        return 0



def main(args=None):
    if args is None:
        args = sys.argv


    rclpy.init(args=args)

    reasoner_node = OntologyReasoner()

    rclpy.spin(reasoner_node)
    reasoner_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()



