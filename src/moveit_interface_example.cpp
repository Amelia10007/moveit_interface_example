#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>

using namespace moveit::planning_interface;

MoveItErrorCode moveByJointValues(MoveGroupInterface &moveGroup, const std::vector<double> &jointRadians){
    if (!moveGroup.setJointValueTarget(jointRadians))
    {
        return moveit::planning_interface::MoveItErrorCode(moveit_msgs::MoveItErrorCodes::INVALID_GOAL_CONSTRAINTS);
    }
    return moveGroup.move();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "moveit_interface_example");
    ros::NodeHandle node;

    //moveitの動作計画を使用するために必要
    ros::AsyncSpinner spinner(2);
    spinner.start();

    MoveGroupInterface moveGroupInterface("arm");

    moveGroupInterface.setMaxVelocityScalingFactor(1.0);

    const std::vector<double> jointRadians = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    const auto moveResult = moveByJointValues(moveGroupInterface, jointRadians);

    if (moveResult == MoveItErrorCode::SUCCESS)
    {
        ROS_INFO("Succeeded to move cobotta");
    }
    else
    {
        ROS_WARN_STREAM("Failed to move cobotta. error code: " << moveResult);
    }

    ros::waitForShutdown();
    return 0;
}
