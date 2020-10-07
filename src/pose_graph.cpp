#include <ros/ros.h>
#include <cartographer_ros_msgs/TrajectoryQuery.h>
#include <cartographer_ros_msgs/StatusResponse.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <pose_graph_msgs/PoseGraph.h>
#include <iostream>
#include <fstream>

using namespace std;

ros::Publisher pose_graph_pub;

void trajectory_callback(const vector<geometry_msgs::PoseStamped>&);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pose_graph_client");
    ros::NodeHandle n;
    pose_graph_pub = n.advertise<pose_graph_msgs::PoseGraph>("pose_graph", 100);
    ros::ServiceClient pgraph_client = n.serviceClient<cartographer_ros_msgs::TrajectoryQuery>("trajectory_query");
    cartographer_ros_msgs::TrajectoryQuery srv;
    srv.request.trajectory_id = 0;
    if(pgraph_client.call(srv))
    {
        cout << "Trajectory Status: " << srv.response.status.message << endl;
        cout << "Trajectory Size: " << srv.response.trajectory.size() <<endl;
    }
    else
    {
        ROS_ERROR("Failed to call service 'trajectory_query'");
        return -1;
    }


    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        trajectory_callback(srv.response.trajectory);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

void trajectory_callback(const vector<geometry_msgs::PoseStamped>& msg)
{
    pose_graph_msgs::PoseGraph pose_graph;
    pose_graph.poseGraph = msg;
    pose_graph_pub.publish(pose_graph);
}