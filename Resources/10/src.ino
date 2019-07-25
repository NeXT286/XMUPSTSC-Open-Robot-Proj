//*****************************************
//测试舵机，并在OLED显示角度
//*****************************************
#include <Servo.h>

Servo myservo;//实例化舵机
#define SERVO 9//设置舵机控制IO
#define MIDDLE_ANGLE 90//设置舵机中位（平衡）角度



void setup()
{
  Serial.begin(115200);//初始化串口
  OLED_Init();//初始化OLED
  myservo.attach(SERVO);       // 选择控制的舵机的IO
  myservo.write(MIDDLE_ANGLE); // 指定舵机转向的角度

}

void loop()
{
  static unsigned char addFlag = 1;//角度加减标志，用这个标志控制舵机角度是增加还是减少
  static int servoAngle = MIDDLE_ANGLE;//舵机角度
  if (servoAngle >= MIDDLE_ANGLE + 45)//如果正转超过平衡角+45度
    addFlag = 0;//角度加减标志置0
  else if (servoAngle <= MIDDLE_ANGLE - 45)//如果反转超过平衡角-45度
    addFlag = 1;//角度加减标志置1
  if (addFlag == 1)//如果角度标志为1
    servoAngle+=2;//舵机角度每次递增
  else//否则的话（角度标志不为1）
    servoAngle-=2;//舵机角度每次递减
  char a[20];//定义一个用于显示的字符串变量（字符数组）
  sprintf(a, "Angle:%d  ", servoAngle); //填充字符串变量
  OLED12864_ShowStr(0, 1, a) ; //用OLED输出字符串变量
  myservo.write(servoAngle); // 指定舵机转向的角度
  delay(50);//延时给舵机运行的时间

}
