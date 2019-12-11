/**
 * @file /include/test_gui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2018
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/
#ifndef ui_QNODE_HPP_
#define ui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <string>
#include <QThread>
#include <QStringListModel>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <nav_msgs/Odometry.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/
namespace rqt_Ui
{

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
    Q_OBJECT
public:
    QNode(int argc, char** argv);
    virtual ~QNode();
    bool init();
    bool init(const std::string &master_url, const std::string &host_url);
    void run();

    /*********************
    ** Logging
    **********************/
    enum LogLevel
    {
        Debug,
        Info,
        Warn,
        Error,
        Fatal
    };

    QStringListModel* loggingModel()
        {return &logging_model;}
    void log( const LogLevel &level, const std::string &msg);

    void RecvTopicCallback(const std_msgs::StringConstPtr &msg);
    void odom_callback(const nav_msgs::OdometryConstPtr &odom_msg);
    void gyro_callback(const sensor_msgs::ImuConstPtr &imu_msg);
    void acc_callback(const sensor_msgs::ImuConstPtr &imu_msg);
    void img_callback(const sensor_msgs::ImageConstPtr &img_msg);
    void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg);



    QStringListModel* loggingModelLis()
        {return &logging_listen;}
    void log_listen(const LogLevel &level, const std::string &msg);

    void ros_test(const std::string s);
Q_SIGNALS:
    void loggingUpdated();
    void loggingListen();
    void rosShutdown();
    void get_camtime(double time);
    void get_imutime(double time);
    void get_gyrotime(double time);
    void get_acceltime(double time);
    void get_odomtime(double time);

    void get_camtime_buf(QVector<double> buf);
    void get_gyrotime_buf(QVector<double> buf);
    void get_imutime_buf(QVector<double> buf);
    void get_acceltime_buf(QVector<double> buf);
    void get_odomtime_buf(QVector<double> buf);

private:
    int init_argc;
    char** init_argv;
    ros::Publisher chatter_publisher;
    ros::Subscriber chatter_subscriber;
    QStringListModel logging_model;
    QStringListModel logging_listen;
    ros::Subscriber sub_imu ;
    ros::Subscriber sub_img ;
    ros::Subscriber sub_acc ;
    ros::Subscriber sub_gyro ;
    ros::Subscriber odom ;
    double start_time =0;
    bool started = 0;
};

}  // namespace test_gui

#endif /* test_gui_QNODE_HPP_ */
