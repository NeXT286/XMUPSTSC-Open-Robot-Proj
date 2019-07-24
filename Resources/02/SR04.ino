/*
初始化函数
	void SR04_Init()
	功能：超声测距模块初始化
	输入参数：无
	输出参数：无
功能函数
	float GetDistance()
	功能：测距
	输入参数：无
	输出参数：距离，单位：cm,浮点类型数据

*/

#define TrigPin  10
#define EchoPin  11

void SR04_Init()
{
  pinMode(TrigPin, OUTPUT);
  // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
  pinMode(EchoPin, INPUT);
}

// 单位CM
float GetDistance()
{
  // 产生一个10us的高脉冲去触发TrigPin
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  float ret= pulseIn(EchoPin, HIGH,5000) / 58.00;
  if(ret==0)
    ret=1000;
  return ret;
}
