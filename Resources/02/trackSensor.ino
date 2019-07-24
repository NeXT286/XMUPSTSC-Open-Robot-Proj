//循迹传感器数据定义
#define  TRACKSENSOR_L2 0x08
#define  TRACKSENSOR_L1 0x04
#define  TRACKSENSOR_R1 0x02
#define  TRACKSENSOR_R2 0x01

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
  //digitalWrite(TrackSensorLeftPin1, HIGH);
  //digitalWrite(TrackSensorLeftPin2, HIGH);
  //digitalWrite(TrackSensorRightPin1, HIGH);
  //digitalWrite(TrackSensorRightPin2, HIGH);
  delay(10);
}

void trackSensorUninit()
{
      //定义四路循迹红外传感器为输入接口
  pinMode(TrackSensorLeftPin1, OUTPUT);
  pinMode(TrackSensorLeftPin2, OUTPUT);
  pinMode(TrackSensorRightPin1, OUTPUT);
  pinMode(TrackSensorRightPin2, INPUT);
  delay(10);
}

byte trackSensorRead()
{
  //检测到黑线时循迹模块相应的指示灯亮，端口电平为LOW
  //未检测到黑线时循迹模块相应的指示灯灭，端口电平为HIGH
  byte ret;
  ret=0;
  if(digitalRead(TrackSensorLeftPin2))
    ret+=8;
  if(digitalRead(TrackSensorLeftPin1))
    ret+=4;
  if(digitalRead(TrackSensorRightPin1))
    ret+=2;
  if(digitalRead(TrackSensorRightPin2))
    ret+=1;
  return ret ;
}
