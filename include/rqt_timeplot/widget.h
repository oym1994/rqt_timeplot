#ifndef WIDGET_H
#define WIDGET_H

#include <qnode.h>
#include <QWidget>
#include "ui_widget.h"
#include  <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <nav_msgs/Odometry.h>
#include <QMutex>

using namespace rqt_Ui;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(int init_argc,char** init_argv,QWidget *parent = 0);
    void add_data (double time, double c);
    ~Widget();
    QCPBars *rectBar;
    void save();

    bool createROSIO(int init_argc,char** init_argv);
    void odom_callback(const nav_msgs::OdometryConstPtr &odom_msg);
    void gyro_callback(const sensor_msgs::ImuConstPtr &imu_msg);
    void acc_callback(const sensor_msgs::ImuConstPtr &imu_msg);
    void img_callback(const sensor_msgs::ImageConstPtr &img_msg);
    void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg);

public slots:
    void refresh();
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




private slots:
    void on_save_bmp_clicked();

    void on_save_path_textChanged();


private:
    Ui::Widget *ui;
    ros::NodeHandle nh;
    ros::Subscriber sub_imu ;
    ros::Subscriber sub_img ;
    ros::Subscriber sub_acc ;
    ros::Subscriber sub_gyro ;
    ros::Subscriber odom ;

    QString path="";

    QVector<double> accel_time;
    QVector<double> gyro_time;
    QVector<double> imu_time;
    QVector<double> odom_time;
    QVector<double> cam_time;
    double record_period = 2;
    int hz =30;
    double start_time = 0;
    bool started = 0;
    QNode qnode;
    QMutex _accelmutex;

//    int init_argc;
//    char** init_argv;

};

#endif // WIDGET_H
