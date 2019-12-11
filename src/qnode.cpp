/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2018
 **/

/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include <qnode.h>
#include <QMetaType>

/*****************************************************************************
** Namespaces
*****************************************************************************/
namespace rqt_Ui
{

/*****************************************************************************
** Implementation
*****************************************************************************/

std::string IMU_TOPIC = "/camera/imu";
std::string IMAGE0_TOPIC = "/camera/color/image_raw";  //"/d400/color/image_raw";
std::string ACC_TOPIC = "/d400/accel/sample";
std::string GYRO_TOPIC = "/d400/gyro/sample";
std::string ODOM_TOPIC = "/odom";

QNode::QNode(int argc, char** argv )
    : init_argc(argc), init_argv(argv)
{
    init();
}

QNode::~QNode()
{
    if(ros::isStarted())
    {
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }
    wait();
}

bool QNode::init()
{
    ros::init(init_argc,init_argv,"test_gui");
    if (!ros::master::check())
    {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.

     sub_imu = n.subscribe(IMU_TOPIC, 2000, &QNode::imu_callback, this);
     sub_img = n.subscribe(IMAGE0_TOPIC, 100, &QNode::img_callback,this);
//     sub_acc = n.subscribe(ACC_TOPIC, 2000, &QNode::acc_callback, this);
//     sub_gyro = n.subscribe(GYRO_TOPIC, 2000, &QNode::gyro_callback, this);
//     odom = n.subscribe(ODOM_TOPIC, 2000, &QNode::odom_callback, this);

     start();
    return true;
}

void QNode::run()
{
    //ros::Rate loop_rate(1);
    ros::Duration initDur(0.1);
    int count = 0;
    while (ros::ok())
    {

        ros::spinOnce();
        //loop_rate.sleep();
        initDur.sleep();
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}





void QNode::imu_callback(const sensor_msgs::ImuConstPtr &imu_msg)
{

    double t = imu_msg->header.stamp.toSec();
    static QVector<double> buf;
    buf.push_back(t - start_time);
    if(buf.size() > 50){
        Q_EMIT    get_imutime_buf( buf);
        buf.clear();
    }
    return;
}

void QNode::img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    double t = img_msg->header.stamp.toSec();
    if(!started){
        started =1;
        start_time = t;
    }
    static QVector<double> buf;
    buf.push_back(t - start_time);
    if(buf[buf.size()-1] - buf[0] >1){
        Q_EMIT    get_camtime_buf( buf);
        buf.clear();
    }
    return;
}
void QNode::acc_callback(const sensor_msgs::ImuConstPtr &imu_msg)
{
    double t = imu_msg->header.stamp.toSec();
    static QVector<double> buf;
    buf.push_back(t - start_time);
    if(buf.size() > 50){
        Q_EMIT    get_acceltime_buf( buf);
        printf("buf clear \n");
        buf.clear();
    }
    return;
}
void QNode::gyro_callback(const sensor_msgs::ImuConstPtr &imu_msg)
{
    double t = imu_msg->header.stamp.toSec();
    static QVector<double> buf;
    buf.push_back(t - start_time);
    if(buf.size() > 50){
        Q_EMIT    get_gyrotime_buf( buf);
        buf.clear();
    }

    return;
}


void QNode::odom_callback(const nav_msgs::OdometryConstPtr &odom_msg)
{
    double t = odom_msg->header.stamp.toSec();
    static QVector<double> buf;
    buf.push_back(t - start_time);
    if(buf.size() > 5){
        printf("qnote received odom \n");
        Q_EMIT    get_odomtime_buf( buf);
        buf.clear();
    }

    return;
}

}  // namespace test_gui
