#include "widget.h"
#include <QMetaType>


Widget::Widget(int init_argc,char** init_argv,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    qnode(init_argc,init_argv)
{
ui->setupUi(this);
  //设定背景为黑色
  //ui->widget->setBackground(QBrush(Qt::black));
  //设定右上角图形标注可见
ui->widget->legend->setVisible(true);
  //设定右上角图形标注的字体
ui->widget->legend->setFont(QFont("Helvetica", 9));

ui->widget->addGraph();
//设置右上角图形标注名称
ui->widget->graph(0)->setName("直线");
//设置X轴文字标注
ui->widget->xAxis->setLabel("time");
//设置Y轴文字标注
ui->widget->yAxis->setLabel("temp/shidu");

//设置Y轴坐标范围
ui->widget->yAxis->setRange(-2,2);
//在坐标轴右侧和上方画线，和X/Y轴一起形成一个矩形
rectBar = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);

rectBar->setWidth(0.0001);

rectBar->setAntialiased(false);
rectBar->setStackingGap(0.1);
rectBar->setPen(QPen(QColor(0, 168, 140).lighter(10)));
rectBar->setBrush(QColor(0, 168, 140));
QTimer *timer = new QTimer(this);

timer ->start(50);

//qRegisterMetatType<QVector<double>>("QVector<double>");

connect(timer, SIGNAL(timeout()),this, SLOT(refresh()));

//connect(&qnode, SIGNAL(get_camtime(double)), this, SLOT(get_camtime(double)));

connect(&qnode, SIGNAL(get_camtime_buf(QVector<double>)), this, SLOT(get_camtime_buf(QVector<double>)),Qt::DirectConnection);
//connect(&qnode, SIGNAL(get_acceltime_buf(QVector<double>)), this, SLOT(get_acceltime_buf(QVector<double>)),Qt::DirectConnection);
//connect(&qnode, SIGNAL(get_odomtime_buf(QVector<double>)), this, SLOT(get_odomtime_buf(QVector<double>)),Qt::DirectConnection);
connect(&qnode, SIGNAL(get_gyrotime_buf(QVector<double>)), this, SLOT(get_gyrotime_buf(QVector<double>)),Qt::DirectConnection);
//connect(&qnode, SIGNAL(get_imutime_buf(QVector<double>)), this, SLOT(get_imutime_buf(QVector<double>)),Qt::DirectConnection);


//connect(&qnode, SIGNAL(get_imutime(double)), this, SLOT(get_imutime(double)));

//connect(&qnode, SIGNAL(get_odomtime(double)), this, SLOT(get_odomtime(double)));

//connect(&qnode, SIGNAL(get_gyrotime(double)), this, SLOT(get_gyrotime(double)));

//connect(&qnode, SIGNAL(get_acceltime(double)), this, SLOT(get_acceltime(double)));

}


void Widget::add_data(double time, double c){
//    int plottableCount = ui->widget->plottableCount();
//         if (plottableCount != 0)
//              ui->widget->clearPlottables();

        rectBar->addData(time,c);

}

void Widget::refresh(){

    if(cam_time.size() >= 30 * record_period){
    ui->widget->xAxis->setRange(cam_time[0]-0.1, cam_time[30 * record_period -1]+0.2);
    printf("refresh x axis ! ");
    }
    else{
        ui->widget->xAxis->setRange(cam_time.front()-0.1,cam_time.last()+0.1);
    }

    QVector<double> odom_value = QVector<double>(odom_time.size(), -0.5);
    QVector<double> gyro_value = QVector<double>(gyro_time.size(), -0.5);
    QVector<double> imu_value = QVector<double>(imu_time.size(), -0.5);
    QVector<double> cam_value = QVector<double>(cam_time.size(), 1.0);


    rectBar->setData(cam_time,cam_value);
    rectBar->addData(odom_time,odom_value);
    rectBar->addData(gyro_time,gyro_value);
    rectBar->addData(imu_time,imu_value);
    {
        QMutexLocker locker(&_accelmutex);
        QVector<double> accel_value = QVector<double>(accel_time.size(), -0.50);
//        printf("accel size %d \n", accel_time.size());
        rectBar->addData(accel_time,accel_value);
    }
//    printf("refresh finished \n");
    ui->widget->replot();
}

void Widget::save(){
    ui->widget->saveBmp("a.bmp",800,600);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_save_bmp_clicked()
{
    static int a = 0;
    a++;
    ui->widget->saveBmp(path + QString::number(a)+".bmp",10000,600);
}

void Widget::on_save_path_textChanged()
{
    path = ui->save_path->toPlainText();
    printf("save path: %s \n",path.toStdString().c_str());
}

void Widget::get_imutime(double time){
    imu_time.push_back(time -start_time);
    if(imu_time.size() >= record_period *hz*10)
        imu_time.pop_front();
}

void Widget::get_gyrotime(double time){
    gyro_time.push_back(time -start_time);
    if(gyro_time.size() >= record_period *hz*15)
        gyro_time.pop_front();
}
void Widget::get_acceltime(double time){
    accel_time.push_back(time -start_time);
    if(accel_time.size() >= record_period *hz*20)
        accel_time.pop_front();
}
void Widget::get_odomtime(double time){
    odom_time.push_back(time -start_time);
    if(odom_time.size() >= record_period *hz*10)
        odom_time.pop_front();
}
void Widget::get_camtime(double time){
    if (!started){
        start_time = time;
        started =1;
    }
    cam_time.push_back(time -start_time );
    printf("------------------------------------------ \n");
    if(cam_time.size() >= record_period *hz)
        cam_time.pop_front();
}

void Widget::get_camtime_buf(QVector<double> buf){
     cam_time += buf;
    if(cam_time.size() > record_period *hz){
        cam_time.erase(cam_time.begin(),cam_time.end()-buf.size());
    }
}

void Widget::get_imutime_buf(QVector<double> buf){
     imu_time += buf;
    if(imu_time.size() > record_period *hz*25){
        imu_time.erase(imu_time.begin(),imu_time.begin() + buf.size());
    }
}

void Widget::get_gyrotime_buf(QVector<double> buf){
     gyro_time += buf;
    if(gyro_time.size() > record_period *hz*15){
        gyro_time.erase(gyro_time.begin(),gyro_time.begin()+ buf.size());
    }
}

void Widget::get_acceltime_buf(QVector<double> buf){
    {
//     QMutexLocker locker(&_accelmutex);
     accel_time += buf;
     printf("accel 加载完毕: %d \n", buf.size());
    }
    if(accel_time.size() > record_period *hz*15){
        accel_time.erase(accel_time.begin(),accel_time.begin() + buf.size());
    }
}

void Widget::get_odomtime_buf(QVector<double> buf){
     odom_time += buf;
     printf("widget received odom \n");
    if(odom_time.size() > record_period *hz){
        odom_time.erase(odom_time.begin(),odom_time.begin() + buf.size());
    }
}
