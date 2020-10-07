#!/usr/bin/python2
import rospy
from geometry_msgs.msg import *
from nav_msgs.msg import *
from pose_graph_msgs.msg import *
from std_msgs.msg import *

class ODOM:
    def __init__(self):
        self.world_frame_id = "world"
        self.base_frame_id = "imu_link_enu"
        
        self.sub=rospy.Subscriber('pose_graph_listener', pose_graph_msgs.PoseGraph, pose_graph_cb)
        self.pub=rospy.Publisher('pose_graph_odom', Odometry, queue_size=10)
    
    def pose_graph_cb(self, pgraph):
        self.pose_graph_length = pgraph.size()
        print self.pose_graph_length
        for i in range(self.pose_graph_length):
            self.odom=Odometry()
            self.odom.child_frame_id=self.base_frame_id
            self.odom.header=pgraph[i].header
            self.odom.header.frame_id=self.world_frame_id
            self.odom.pose.pose=pgraph[i].pose
            self.pub.publish(self.odom)
            # rospy.sleep(rospy.Rate(20))

def main():
    rospy.init_node('posegraph2odom')
    create_odom=ODOM()

if __name__ == '__main__':
    main()        