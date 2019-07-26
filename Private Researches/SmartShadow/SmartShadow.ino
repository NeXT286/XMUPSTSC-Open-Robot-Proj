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
    if(TL2==0 && TR2==1)//左外侧传感器发现黑线
      LeftRecover();
    else if(TL2==1 && TR2==0)//右外侧传感器发现黑线
      RightRecover();
    else if(TL2==1&& TL1==0 && TR1==1 && TR2==1)//左内侧传感器发现黑线
      LeftTurn();
    else if(TL2==1&& TL1==1 && TR1==0 && TR2==1)//右内侧传感器发现黑线
      RightTurn();
    else
      carMove(100,100);//前进
  }
}
