//*****************************************
//在OLED中显示PS2手柄摇杆和按键值
//*****************************************
void setup() {
  // put your setup code here, to run once:
  OLED_Init();//OLED初始化
  PS2Init();//PS2初始化
  carInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long button = 0;//存放按键值
  int LX = 0, LY = 0, RX = 0, RY = 0;//存放左右摇杆值
  button = PS2Read(&LX, &LY, &RX, &RY);//读取PS2手柄按键和摇杆
  char a[20];//定义一个字符串变量（字符数组）
  sprintf(a,"LX:%3d  LY:%3d",LX,LY);//填充字符串变量,左摇杆xy
  OLED12864_ShowStr(0,0,a) ; //用OLED输出字符串变量
  sprintf(a,"RX:%3d  RY:%3d",RX,RY);//填充字符串变，右摇杆xy
  OLED12864_ShowStr(0,1,a) ; //用OLED输出字符串变量
  sprintf(a,"Button Code:0x%04x",button);//填充字符串变，按键值
  OLED12864_ShowStr(0,2,a) ; //用OLED输出字符串变量
  carCtrl(RX,RY);
}

void carCtrl(int RX,int RY)
{
  int ySpeed = 0, xSpeed = 0, leftSpeed = 0,rightSpeed = 0;
  if ((0 - (RY - 0x80))>=0)
  {
    ySpeed = (0 - (RY - 0x80))*(0 - (RY - 0x80))/64;//0x80为二进制的128，即摇杆的中值
  }
  if ((0 - (RY - 0x80))<=0)
  {
    ySpeed = -(0 - (RY - 0x80))*(0 - (RY - 0x80))/64;//0x80为二进制的128，即摇杆的中值
  }
  if ((RX - 0x80)>=0)
  {
    xSpeed = (RX - 0x80)*(RX - 0x80)/64;
  }
  if ((RX - 0x80)<=0)
  {
    xSpeed = -(RX - 0x80)*(RX - 0x80)/64;
  }
  leftSpeed = ySpeed + xSpeed;
  rightSpeed = ySpeed - xSpeed;
  carMove(leftSpeed, rightSpeed);
}
