#include <Servo.h>
#include <MsTimer2.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;
Servo myservo;
#define SERVO 9
#define MIDDLE_ANGLE 90
float gyro_y;
float gy0;
float rgyro = 0.35;
#define Beep 12 //定义蜂鸣器所在IO
#define LED_PIN 13
#define IR_Rev A1//红外接收IO
bool blinkState = false;
////////////////////////////
int Accel[3] = {0, 0, 0};
int Gyro[3] = {0, 0, 0};
int GyroOffset[3] = {0, 0, 0};
float AccelAngle, Angle; //,Compensate;
int ms5 = 0, s1 = 0;
//float GravAccel;
///////////////////////////
void carCtrl(int RX, int RY, unsigned int key);
void setup()
{
  Serial.begin(115200);
  OLED_Init();
  Serial.println("OLED Initialization success");
  OLED12864_ShowStr(0,0,"OLED [OK]");
  wDogInit();
  myservo.attach(SERVO);       // 选择控制的舵机
  myservo.write(MIDDLE_ANGLE); // 指定舵机转向的角度
  OLED12864_ShowStr(0,1,"SERVO [OK]");
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  delay(200);
  feetDog();
  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  accelgyro.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  OLED12864_ShowStr(0,2,"MPU6050 [OK]");
  feetDog();
  delay(200);
  feetDog();
  getGyroOffset(GyroOffset);
  MsTimer2::set(5, onTimer); //设置中断，每5ms进入一次中断服务程序 onTimer()
  MsTimer2::start();         //开始计时
  OLED12864_ShowStr(0,3,"TIMER [OK]");
  carInit();
  Serial.println("Motor Initialization success");
  OLED12864_ShowStr(0,4,"Moter [OK]");
  PS2Init();
  Serial.println("PS2 Initialization success");
  OLED12864_ShowStr(0,5,"PS2 [OK]");
  OLED12864_ShowStr(0,6,"SYSTEM STARTUP...");
  pinMode(Beep,OUTPUT);//设置蜂鸣器所在IO输出
  digitalWrite(Beep,HIGH);//初始化蜂鸣器不发声
  SR04_Init();//超声测距模块初始化
  feetDog();
  delay(800);
  feetDog();
  OLED12864_Fill(0x00);
}

void loop()
{
  int _accel[3] = {0, 0, 0};
  int _gyro[3] = {0, 0, 0};
  float _accelAngle, _angle;
  static int rSpeed = 0, lSpeed = 0;

  for (int i = 0; i < 3; i++)
  {
    _accel[i] = Accel[i];
    _gyro[i] = Gyro[i];
  }
  _accelAngle = AccelAngle;
  _angle = Angle;
  //电机、舵机测试
  char disStr2[10]="";
  char disStr3[10]="";
  carInit();
  if(s1%2==0)
  {
    carMove(70,70);
    myservo.write(80);
    strcat(disStr2,"Forward");
    strcat(disStr3,"Servo:70");
  }
  else
  {
    carMove(-70,-70);
    myservo.write(100);
    strcat(disStr2,"Back");
    strcat(disStr3,"Servo:90");
  }
  OLED12864_ShowStr(0,2,disStr2);
  OLED12864_ShowStr(0,3,disStr3);
  //测距
  float distance;//用于存放距离的变量
  char distanceStr[10]="No echo!";//用于存放距离字符串的字符数组
  cli();
  distance=GetDistance();//调用测距函数
  sei();
  if(distance<5)
    digitalWrite(Beep,LOW);
  else
    digitalWrite(Beep,HIGH);  
  //循迹传感器
  char disStr4[10]="";
  byte sensor;
  trackSensorInit();
  sensor = trackSensorRead();//读取循迹传感器
  trackSensorUninit();
  sprintf(disStr4,"trackSens:%s    ", toBinary(sensor));
  //LDR/IR
  int irRev;
  irRev=analogRead(IR_Rev);
  //接收手柄按键
  unsigned int button = 0;
  int LX = 0, LY = 0, RX = 0, RY = 0;
  button = PS2Read(&LX, &LY, &RX, &RY);
  //carCtrl(LX, RY,button);
  feetDog();
  //显示
  char disStr[20];
  sprintf(disStr,"Angle:%d   ",(int)_angle);
  OLED12864_ShowStr(0,0,disStr);
  sprintf(disStr,"LX:%3d  RY:%3d   ",LX,RY);
  OLED12864_ShowStr(0,1,disStr);
  if(distance<1000)
    sprintf(disStr,"Dist:%d        ",(int)distance);
  else
    sprintf(disStr,"Dist:No echo");
  OLED12864_ShowStr(0,4,disStr);
  OLED12864_ShowStr(0,5,disStr4);
  sprintf(disStr,"IR:%3d   ",irRev);
  OLED12864_ShowStr(0,6,disStr);
}

void onTimer()
{
  sei(); //全局中断开启
  ms5++;
  if (ms5 >= 200)
  {
    ms5 = 0;
    s1++;
  }
  read6050(Accel, Gyro);
  AccelAngle = accelAngle(Accel[0], Accel[2]);
  for (int i = 0; i < 3; i++)
    Gyro[i] -= GyroOffset[i];
  int _accel[3] = {0, 0, 0};
  int _gyro[3] = {0, 0, 0};
  float _accelAngle;
  for (int i = 0; i < 3; i++)
  {
    _accel[i] = Accel[i];
    _gyro[i] = Gyro[i];
  }
  _accelAngle = AccelAngle;
  Angle = AccelAngle;
  //Angle = Kalman_Filter(_accelAngle, -_gyro[1]);
  
 
  
}
