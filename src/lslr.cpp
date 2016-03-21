#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>



double right = 0;
double left = 0;
double front = 0;

geometry_msgs::Twist mr,ml,mf; 
ros::Publisher twist_pub ;



geometry_msgs::Twist td()
{
    geometry_msgs::Twist retorno;
    
    if (right > 0.1 && left == 0 && front == 0){
        retorno.linear.x = 0;
        retorno.angular.z = 0.5;
    }
    else if(left > 0.1 && right == 0 && front == 0)
    {
        retorno.linear.x = 0;
        retorno.angular.z = -0.5;
    }
    else if (right == 0 && left == 0 && front > 0.1)
    {
        retorno.linear.x = -0.5;
        retorno.angular.z = 0.5;
    }
    else if(right > 0.1 && left >0.1 && front > 0.1)
    {
        retorno.linear.x = -0.5;
        retorno.angular.z = 0.5;
    }
    else if(right > 0.1 && left > 0.1 && front == 0)
    {
        retorno.linear.x = -0.5;
        retorno.angular.z = -0.5;
    }
    else if(right > 0.1 && front > 0.1 && left == 0)
    {
        retorno.linear.x = 0;
        retorno.angular.z = 0.5;
    }
    else if (front > 0.1 && left > 0.1 && right == 0)
    {
        retorno.linear.x = 0;
        retorno.angular.z = -0.5;
    }
    else
    {
        retorno.linear.x = 0.5;
        retorno.angular.z = 0;
    }
    
    
    
    return retorno;
    
}

void rightcallback (const std_msgs::Float32ConstPtr &r)
{
    right = r->data;
}

void leftcallback (const std_msgs::Float32ConstPtr &l)
{
    left = l->data;  
    
}

void frontcallback (const std_msgs::Float32ConstPtr &f)
{
    front = f->data;
}



int main (int argc, char **argv)
{
    ros::init(argc,argv, "lslr");
    ros::NodeHandle nh;
    ros::Subscriber sub1 = nh.subscribe("/vrep/vehicle/rightSonar", 1, rightcallback);
    ros::Subscriber sub2 = nh.subscribe("/vrep/vehicle/leftSonar", 1, leftcallback);
    ros::Subscriber sub3 = nh.subscribe("/vrep/vehicle/frontSonar", 1, frontcallback);
    
    twist_pub = nh.advertise <geometry_msgs::Twist>("gogo", 1);
        ros::Rate loop_rate(50);
    
      while (ros::ok())
      {
          
          twist_pub.publish(td());
          
          
          loop_rate.sleep();
          ros::spinOnce();
          
      }
    
}