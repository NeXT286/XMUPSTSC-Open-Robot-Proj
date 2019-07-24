/***************************************************************************
全局变量
初始化函数
	void carInit()
	功能：电机初始化
	输入参数：无
	输出参数：无
功能函数
	void carMove(int leftSpeed, int rightSpeed)
	功能：车辆移动
	输入参数：
		leftSpeed：
			功能：左轮速度
			取值范围：-255~255
			说明：负值为后退，0为停止，正值为前进
		rightSpeed：
			功能：右轮速度
			取值范围：-255~255
			说明：负值为后退，0为停止，正值为前进
***************************************************************************/

#define Right_motor_go  2 //右电机前进管脚
#define Right_motor_pwm   6; //右电机控速管脚 PWMB
#define Left_motor_pwm   5;  //左电机控速管脚 PWMA
#define Left_motor_go  4 //左电机前进管脚


void carInit()
{
  pinMode(Left_motor_go, OUTPUT); // PIN 5 (PWM)
  pinMode(Right_motor_go, OUTPUT); // PIN 6 (PWM)
  pinMode(Left_motor_pwm, OUTPUT);
  pinMode(Right_motor_pwm, OUTPUT);
}

//输入-255~255
void carMove(int leftSpeed, int rightSpeed)
{
  if (leftSpeed > 255)
    leftSpeed = 255;
  if (leftSpeed < -255)
    leftSpeed = -255;
  if (leftSpeed < 10 && leftSpeed > -10)
    leftSpeed = 0;

  if (leftSpeed >= 0 && leftSpeed <= 255)
  {
    //左电机前进
    digitalWrite(Left_motor_go, LOW); //左电机前进使能
    //digitalWrite(Left_motor_back, LOW);  //左电机后退禁止
    analogWrite(Left_motor_pwm, leftSpeed);
  }
  else if (leftSpeed < 0 && leftSpeed >= -255)
  {
    leftSpeed = 0 - leftSpeed;
    //左电机后退
    digitalWrite(Left_motor_go, HIGH); //左电机前进禁止
    //digitalWrite(Left_motor_back, HIGH);  //左电机后退使能
    analogWrite(Left_motor_pwm, leftSpeed);
  }
  if (rightSpeed > 255)
    rightSpeed = 255;
  if (rightSpeed < -255)
    rightSpeed = -255;
  if (rightSpeed < 10 && rightSpeed > -10)
    rightSpeed = 0;

  if (rightSpeed >= 0 && rightSpeed <= 255)
  {
    //右电机前进
    digitalWrite(Right_motor_go, LOW); //右电机前进使能
    //digitalWrite(Right_motor_back, LOW);  //右电机后退禁止
    analogWrite(Right_motor_pwm, rightSpeed);
  }
  else if (rightSpeed < 0 && rightSpeed >= -255)
  {
    rightSpeed = 0 - rightSpeed;
    //右电机后退
    digitalWrite(Right_motor_go, HIGH); //右电机前进禁止
    //digitalWrite(Right_motor_back, HIGH);  //右电机后退使能
    analogWrite(Right_motor_pwm, rightSpeed);
  }
}
