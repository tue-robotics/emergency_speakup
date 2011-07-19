#include "ros/ros.h"
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

using namespace std;

ros::Time time_init, time_current;
ros::Publisher pub;
ros::Subscriber sub;
bool alarm_state = false;
std_msgs::String speech_msg;
bool button_state = false;


void emergencyCallback(const std_msgs::BoolPtr&  msg)
{
	if (msg->data && !button_state) 
	{
		speech_msg.data = string("My emergency button is pressed, I am very sorry for my behaviour.");
		pub.publish(speech_msg);
		button_state = true;
	} 
	else if (!msg->data && button_state) 
	{
		speech_msg.data = string("Emergency button released, let's go");
		pub.publish(speech_msg);
		button_state = false;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "emergency_speakup");
	ros::NodeHandle n;
	
	sub = n.subscribe("/emergency_switch", 1, emergencyCallback);
	pub = n.advertise<std_msgs::String>("/amigo_speak_up", 50);
	
	time_init = ros::Time::now();	
	
	ros::Rate loop_rate(1.0);

	while(n.ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
