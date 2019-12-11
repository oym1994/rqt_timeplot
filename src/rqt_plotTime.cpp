#include "widget.h"
#include <QApplication>
#include <unistd.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <nodelet/nodelet.h>
#include <QMetaType>

//char *str;
//char **argv = &str;
//int d=1;
//int &dd =d;
//QApplication a(dd,argv);
//Widget w;
//std::string IMU_TOPIC = "/camera/imu";
//std::string IMAGE0_TOPIC = "/d400/color/image_raw";
//std::string ACC_TOPIC = "/d400/accel/sample";
//std::string GYRO_TOPIC = "/d400/gyro/sample";
//std::string ODOM_TOPIC = "/odom";



//void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg)
//{
//    double t = imu_msg->header.stamp.toSec();
//    w.get_imutime(t);
//    printf("收到imu消息 \n");
//    return;
//}

//void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
//{
//    double t = img_msg->header.stamp.toSec();
//    w.get_camtime(t);
//    printf("收到image消息 \n");
//    return;
//}
//void acc_callback(const sensor_msgs::ImuConstPtr &imu_msg)
//{
//    double t = imu_msg->header.stamp.toSec();
//    w.get_acceltime(t);
//    printf("收到acc消息 \n");

//    return;
//}
//void gyro_callback(const sensor_msgs::ImuConstPtr &imu_msg)
//{
//    double t = imu_msg->header.stamp.toSec();
//    w.get_gyrotime(t);
//    printf("收到gyro消息 \n");

//    return;
//}


//void odom_callback(const nav_msgs::OdometryConstPtr &odom_msg)
//{
//    double t = odom_msg->header.stamp.toSec();
//    w.get_odomtime(t);
//    printf("收到odom消息 \n");

//    return;
//}




int main(int argc, char *argv[])
{
    ros::init(argc, argv, "rqt_plotTime");  //ros初始化,从命令行传入参数,vins_estimator是节点名
    QApplication a(argc,argv);
    Widget w(argc,argv);
    w.show();
    a.exec();
    return 0;
}
