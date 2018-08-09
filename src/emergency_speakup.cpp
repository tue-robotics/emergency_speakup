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

std::vector<std::string> sentences_pressed;
std::vector<std::string> sentences_released;

void emergencyCallback(const std_msgs::BoolPtr&  msg)
{
    // Emergency button pressed
    if (msg->data && !button_state)
    {
        speech_msg.data = sentences_pressed[rand() % sentences_pressed.size()];
        pub.publish(speech_msg);
        button_state = true;
    }

    // Emergency button released
    else if (!msg->data && button_state)
    {
        speech_msg.data = sentences_released[rand() % sentences_released.size()];
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

    sentences_pressed.push_back("Let's pause here for a while");
    sentences_pressed.push_back("Somebody touched a red button");
    sentences_pressed.push_back("I may seem a little slow, but I had a rough night");
    sentences_pressed.push_back("I am sorry for my behaviour");
    sentences_pressed.push_back("I am a bad Amigo");
    sentences_pressed.push_back("Stop. Hammertime!");
    sentences_pressed.push_back("I am getting too old for this shit!");
    sentences_pressed.push_back("Houston,,,, We have a problem");
    sentences_pressed.push_back("I find your lack of faith disturbing");
    sentences_pressed.push_back("Man is a robot with defects");
    sentences_pressed.push_back("It is not a bug,,,,, it is a feature!");
    sentences_pressed.push_back("If at first you do not succeed,,, we have a lot in common");

    sentences_released.push_back("Let's move on");
    sentences_released.push_back("Here we go again");
    sentences_released.push_back("I'll try to do better this time");
    sentences_released.push_back("My emergency button is released again");
    sentences_released.push_back("Lets make this fun");
    sentences_released.push_back("Lets get ready to rumble");
    sentences_released.push_back("You will respect my autonomy!");

    while(n.ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
