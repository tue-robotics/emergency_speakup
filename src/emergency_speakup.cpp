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
		int sentence=rand()%4;
		switch(sentence)
		{
        case 0:
			speech_msg.data = string("Let's pause here for a while");
		case 1:
        	speech_msg.data = string("Somebody touched a red button");
		case 2:
        	speech_msg.data = string("I may seem a little slow, but I had a rough night");
		case 3:
        	speech_msg.data = string("Let's pause here for a while");
		case 4:
        	speech_msg.data = string("Let's pause here for a while");
		}

		
		pub.publish(speech_msg);
		button_state = true;
	} 
	else if (!msg->data && button_state) 
	{
		speech_msg.data = string("Let's move on");
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
