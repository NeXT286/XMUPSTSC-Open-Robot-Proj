//*****************************************
//超声测距，距离通过OLED与串口输出
//*****************************************
#define buzz 12
void setup() {
  // put your setup code here, to run once:
  OLED_Init();//OLED初始化
  SR04_Init();//超声测距模块初始化
  carInit();
  Serial.begin(9600);//串口初始化
  pinMode(buzz,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance;//用于存放距离的变量
  char distanceStr[10]="No echo!";//用于存放距离字符串的字符数组
  distance=GetDistance();//调用测距函数
  //整理显示信息
  if(distance<1000)//如果测出的距离小于1000
    dtostrf(distance,3,1,distanceStr);//将浮点型的距离转换成字符串
  char disStr[20]="Dist:";//定义一个用于显示的字符串变量（字符数组）
  strcat(disStr,distanceStr);//字符串拼接（前<-后）
  strcat(disStr,"     ");//字符串拼接（前<-后）加一些空格用于覆盖上一次的显示数据
  Serial.println(disStr);//从串口输出显示字符串
  OLED12864_ShowStr(0,1,disStr) ; //用OLED输出显示字符串
  if(distance<=30)
  {
    digitalWrite(buzz,LOW);
    if(distance<=20)
    {
      int a=random(0,2);
      if(a==0)
      {
        carMove(80,-80);
        delay(700);
      }
      if(a==1)
      {
        carMove(-80,80);
        delay(700);
      }
    }
  }
  else
  {
    digitalWrite(buzz,HIGH);
    carMove(80,80);
  }
}
