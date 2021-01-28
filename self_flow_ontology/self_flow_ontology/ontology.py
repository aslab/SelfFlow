import sys
from owlready2 import *
import rclpy
from rclpy.node import Node


from std_msgs.msg import String
from self_flow_core.msg import Task


#onto_path.append("./") Store updated ontology?
onto = get_ontology("/home/jdcdp/git/SelfFlow/self_flow_ontology/owl/SelfFlow.owl")
onto.load()

agent1 = onto.Turtlebot3("my_name")

agent1.hasAbility = [
    onto.GroundNavigation("home")
]
agent2 = onto.Turtlebot3("gripper")

agent2.hasAbility = [
    onto.GroundNavigation("home"),
    onto.GroundNavigation("move"),
    onto.ObjectInteraction("grab_item")
]
agent3 = onto.Turtlebot3("finder")

agent3.hasAbility = [
    onto.GroundNavigation("home"),
    onto.GroundNavigation("find_object"),
    onto.ObjectDetection("detect_object")
]




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


def find_agents(id):
	#make this work
       agents=onto.Turtlebot3.instances()
       for agent in agents:
         if(not(check_ability(agent,id))):
            agents.remove(agent)
       return agents

def find_agent(name):
	#make this work
       agents=onto.Turtlebot3.instances()
       for agent in agents:
         if (agent.name==name):
            return agent

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



