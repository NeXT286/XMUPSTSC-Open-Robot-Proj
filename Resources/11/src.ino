//*****************************************
//通过陀螺仪和舵机保持舵机上平台的平衡
//*****************************************
#include <MsTimer2.h>//定时器库
#include "Wire.h"//I2C协议库
#include "I2Cdev.h"//I2C设备库
#include "MPU6050.h"//MPU6050库
#include <Servo.h>

MPU6050 accelgyro;//实例化6050
int Accel[3] = {0, 0, 0};//用于存放xyz三轴加速度的全局变量
int Gyro[3] = {0, 0, 0};//用于存放xyz三轴角速度的全局变量
int GyroOffset[3] = {0, 0, 0};//用于存放xyz三轴角速度零偏的全局变量
float AccelAngle, Angle; //存放加速度计算出的角度和滤波后角度的全局变量

Servo myservo;//实例化舵机
#define SERVO 9//设置舵机控制IO
#define MIDDLE_ANGLE 90//设置舵机中位（平衡）角度

void setup()
{
  Serial.begin(115200);//串口初始化
  OLED_Init();//OLED初始化
  Serial.println("OLED Initialization success");//从串口输出调试信息
  OLED12864_ShowStr(0,0,"OLED [OK]");//从OLED输出调试信息
  wDogInit();//看门狗初始化（1s内必须喂狗）
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();//I2C初始化，用于与6050通信
  delay(200);//延时200ms确保6050上电
  feetDog();//喂狗
  // initialize device
  Serial.println("Initializing I2C devices...");//从串口输出调试信息
  accelgyro.initialize();//6050初始化
  accelgyro.initialize();//再次初始化6050，确保初始化完成
  // verify connection
  Serial.println("Testing device connections...");//从串口输出调试信息
  //测试6050连接，并从串口输出测试结果
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  OLED12864_ShowStr(0,1,"MPU6050 [OK]");//从OLED输出调试信息
  feetDog();//喂狗
  delay(200);//延时200ms准备从6050读取数据
  feetDog();//喂狗
  myservo.attach(SERVO);       // 初始化控制的舵机的IO
  myservo.write(MIDDLE_ANGLE); // 指定舵机转向的角度
  OLED12864_ShowStr(0,2,"SERVO [OK]");//从OLED输出调试信息
  MsTimer2::set(5, onTimer); //设置中断，每5ms进入一次中断服务程序 onTimer()
  MsTimer2::start();         //开始计时
  OLED12864_ShowStr(0,2,"TIMER [OK]");//从OLED输出调试信息
  OLED12864_ShowStr(0,3,"SYSTEM STARTUP...");//从OLED输出调试信息
  feetDog();//喂狗
  delay(600);//延时600ms让系统静置，准备从6050读取角速度零偏
  getGyroOffset(GyroOffset);//读取角速度零偏
  feetDog();//喂狗
  OLED12864_Fill(0x00);//OLED清屏
}

void loop()
{
  static int _accel[3] = {0, 0, 0};//用于临时存放三轴加速度的局部变量
  static int _gyro[3] = {0, 0, 0};//用于临时存放三轴角速度的局部变量
  static float _accelAngle, _angle;//用于临时存放加速度计算出的角度和滤波后角度的局部变量
  //由于6050读取速度超过OLED显示的速度，为确保OLED显示数据的一致性，我们先将数据从全局变量读取到局部变量中，在对局部变量进行显示
  for (int i = 0; i < 3; i++)//循环3次
  {
    _accel[i] = Accel[i];//拷贝三轴加速度
    _gyro[i] = Gyro[i];//拷贝三轴角速度
  }
  _accelAngle = AccelAngle;//拷贝加速度计算出的角度
  _angle = Angle;//拷贝滤波后角度

  feetDog();//喂狗
  //显示
  char disStr[20];//存放显示信息的字符串
  sprintf(disStr,"Angle:%d   ",(int)_angle);//拼接显示字符串
  ///////////////////////////***以下添加代码***///////////////////////////
  //////////////////////////让OLED显示俯仰角信息///////////////////////////
  ________________________________
  ///////////////////////////***以上添加代码***///////////////////////////
}
//中断服务程序，每5ms进入一次
void onTimer()
{
  sei(); //全局中断开，保证下次可继续进入中断
  read6050(Accel, Gyro);//读取6050的三轴加速度与角速度的原始数据
  AccelAngle = accelAngle(Accel[0], Accel[2]);//根据加速度计算倾角
  for (int i = 0; i < 3; i++)//循环3次
    Gyro[i] -= GyroOffset[i];//三轴角速度去零偏
  Angle = Kalman_Filter(AccelAngle, -Gyro[1]);//根据加速度倾角与角速度通过滤波计算真实倾角
  
  int servoAngle;//舵机角度
  ///////////////////////////***以下添加代码***///////////////////////////
  ///////////////////////根据当前俯仰角计算舵机角度/////////////////////////
  //////////////////////////让舵机指向指定角度/////////////////////////////
  ________________________________
  ________________________________
  ///////////////////////////***以上添加代码***///////////////////////////
  servoAngle = MIDDLE_ANGLE + Angle; // 根据当前倾角计算舵机角度
  myservo.write(servoAngle);          // 指定舵机转向的角度
}
