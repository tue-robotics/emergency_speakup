#include "ros/ros.h"
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <time.h>

using namespace std;

ros::Publisher pub;
ros::Subscriber sub;
bool alarm_state = false;
std_msgs::String speech_msg;
bool button_state = false;

void emergencyCallback(const std_msgs::BoolPtr&  msg)
{
    // Emergency button pressed
	if (msg->data && !button_state) 
	{
        std::vector<std::string> sentences;
        sentences.push_back("Let's pause here for a while");
        sentences.push_back("Somebody touched a red button");
        sentences.push_back("I may seem a little slow, but I had a rough night");
        sentences.push_back("I am sorry for my behaviour");
        sentences.push_back("I am a bad Amigo");
        sentences.push_back("Stop. Hammertime!");
        sentences.push_back("I am getting too old for this shit!");

        speech_msg.data = sentences[rand() % sentences.size()];
		pub.publish(speech_msg);
		button_state = true;
	} 

    // Emergency button released
	else if (!msg->data && button_state) 
	{
        std::vector<std::string> sentences;
        sentences.push_back("Let's move on");
        sentences.push_back("Here we go again");
        sentences.push_back("I'll try to do better this time");
        sentences.push_back("My emergency button is released again");
        sentences.push_back("Lets make this fun");
        sentences.push_back("Lets get ready to rumble");

        speech_msg.data = sentences[rand() % sentences.size()];
		pub.publish(speech_msg);
		button_state = false;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "emergency_speakup");
	ros::NodeHandle n("~");
    ros::NodeHandle globalNh;
    srand(time(NULL));
	
	sub = globalNh.subscribe("emergency_switch", 1, emergencyCallback);
	pub = globalNh.advertise<std_msgs::String>("text_to_speech/input", 50);
	
	ros::Rate loop_rate(1.0);

	while(n.ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
