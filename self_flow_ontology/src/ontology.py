import sys
from owlready2 import *
import rclpy

#from std_msgs.msg import String


def XXX_callback(msg):
    print('I heard: [%s]' % msg.data)


def main(args=None):
    if args is None:
        args = sys.argv


#    onto_path.append("./")
    onto = get_ontology("../owl/SelfFlow.owl")
    onto.load()


    agent = onto.Turtlebot3("my_name")

    agent.hasAbility = [
     onto.GroundNavigation("tb3_nav2"),
     onto.ObjectDetection("opencv")
    ]


    sync_reasoner()


    rclpy.init(args=args)

    node = rclpy.create_node('ontology_reasoner')

    sub = node.create_subscription(String, 'topicname', XXX_callback)
    assert sub  # prevent unused warning

    while rclpy.ok():
        rclpy.spin_once(node)


if __name__ == '__main__':
    main()


