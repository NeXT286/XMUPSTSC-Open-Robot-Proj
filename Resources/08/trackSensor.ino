/***************************************************************************
初始化函数
  void trackSensorInit()
  功能：循迹传感器初始化
  输入参数：无
  输出参数：无
功能函数
  int GetL2()
  功能：获取左外侧循迹传感器的值
  输入参数：无
  输出参数：
    功能：0代表黑线，1代表白线
  int GetL1()
  功能：获取左内侧循迹传感器的值
  输入参数：无
  输出参数：
    功能：0代表黑线，1代表白线
  int GetR1()
  功能：获取右内侧循迹传感器的值
  输入参数：无
  输出参数：
    功能：0代表黑线，1代表白线
  int GetR2()
  功能：获取右外侧循迹传感器的值
  输入参数：无
  输出参数：
    功能：0代表黑线，1代表白线
    
***************************************************************************/

//循迹红外引脚定义
//TrackSensorLeftPin1 TrackSensorLeftPin2 TrackSensorRightPin1 TrackSensorRightPin2
//      13                  A2                  A3                   3
int TrackSensorLeftPin2  =  13;  //定义左边第一个循迹红外传感器引脚为A2
int TrackSensorLeftPin1  =  A2;  //定义左边第二个循迹红外传感器引脚为A1
int TrackSensorRightPin1 =  A3;  //定义右边第一个循迹红外传感器引脚为A3
int TrackSensorRightPin2 =  3;  //定义右边第二个循迹红外传感器引脚为A4

void trackSensorInit()
{
      //定义四路循迹红外传感器为输入接口
  pinMode(TrackSensorLeftPin1, INPUT);
  pinMode(TrackSensorLeftPin2, INPUT);
  pinMode(TrackSensorRightPin1, INPUT);
  pinMode(TrackSensorRightPin2, INPUT);

  //四路循迹红外传感器初始化为高电平
  digitalWrite(TrackSensorLeftPin1, HIGH);
  digitalWrite(TrackSensorLeftPin2, HIGH);
  digitalWrite(TrackSensorRightPin1, HIGH);
  digitalWrite(TrackSensorRightPin2, HIGH);
}
int GetL2()
{
  return digitalRead(TrackSensorLeftPin2);  
}
int GetL1()
{
  return digitalRead(TrackSensorLeftPin1);  
}
int GetR1()
{
  return digitalRead(TrackSensorRightPin1);  
}
int GetR2()
{
  return digitalRead(TrackSensorRightPin2);  
}
