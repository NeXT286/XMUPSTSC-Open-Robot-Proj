//循迹传感器获取函数定义(这样定义可以使代码简洁)
#define TL2 GetL2()
#define TL1 GetL1()
#define TR1 GetR1()
#define TR2 GetR2()

void setup() {
  // put your setup code here, to run once:
  carInit();//电机初始化
  trackSensorInit();//循迹传感器初始化
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1)
  {
    if(TL2==_____ && TR2==___________)//左外侧传感器发现黑线
      carMove(_______,_______);//左大转
    if(TL2==1 && TR2==0)//右外侧传感器发现黑线
      carMove(_______,_______);//右大转
    if(TL2==______&& TL1==________ && TR1==______ && TR2==_________)//左内侧传感器发现黑线
      carMove(______,__________);//左转
    if(TL2==________&& TL1==______ && TR1==______ && TR2==_______)//右内侧传感器发现黑线
      carMove(________,_______);//右转
    else
      carMove(________,_______);//前进
  }
}
