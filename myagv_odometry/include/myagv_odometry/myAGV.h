#ifndef MYAGV_H
#define MYAGV_H

#include <ros/ros.h>
#include <ros/time.h>
#include <sensor_msgs/Imu.h>
#include "std_msgs/Float32.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <boost/asio.hpp>

//#define sampleFreq	20.5f			// sample frequency in Hz
#define twoKpDef	1.0f				// (2.0f * 0.5f)	// 2 * proportional gain
#define twoKiDef	0.0f				// (2.0f * 0.0f)	// 2 * integral gain
#define TOTAL_RECEIVE_SIZE 27         	// 27 字节 //The length of the data sent by the esp32 //esp32发送过来的数据的长度
#define OFFSET_COUNT 	200

class MyAGV
{
public:
	MyAGV();
	~MyAGV();
	bool init();
	float invSqrt(float number);
	void execute(double linearX, double linearY, double angularZ);
	void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
	void accelerometerOffset(float gx, float gy, float gz);
	void publisherOdom();
	void publisherImuSensor();
	void publisherImuSensorRaw();
	void Publish_Voltage();

private:
	bool readSpeed();
	void writeSpeed(double movex, double movey, double rot);
	void restore();
	void restoreRun();

	ros::Time currentTime, lastTime;

	double x;
	double y;
	double theta;

	double vx;
	double vy;
	double vtheta;

	double ax;
	double ay;
	double az;

	double wx;
	double wy;
	double wz;
    
	float Gyroscope_Xdata_Offset;
	float Gyroscope_Ydata_Offset;
	float Gyroscope_Zdata_Offset;
	float sampleFreq;
	float Battery_voltage,Backup_Battery_voltage; 
	unsigned short Offest_Count;
    sensor_msgs::Imu imu_data;
	ros::NodeHandle n;
	ros::Publisher pub_odom,pub_voltage,pub_imu,pub,pub_imu_raw;
	tf::TransformBroadcaster odomBroadcaster;
};


#endif // !MYAGV_H
