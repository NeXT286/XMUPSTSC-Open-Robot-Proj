/*
全局变量
初始化函数
	void PS2Init()
	功能：PS2手柄初始化
	输入参数：无
	输出参数：无
功能函数
	unsigned int PS2Read(int *lx,int *ly,int *rx,int *ry)
	功能：读取PS2手柄的按键和摇杆值
	输入参数：
		*lx：
			功能：将左摇杆x轴数值写入lx指向的地址
			回传值范围：0-128-255
		*ly：
			功能：将左摇杆y轴数值写入lx指向的地址
			回传值范围：0-128-255
    *rx：
			功能：将右摇杆x轴数值写入lx指向的地址
			回传值范围：0-128-255
		*ry：
			功能：将右摇杆y轴数值写入lx指向的地址
			回传值范围：0-128-255
  输出参数：
      按下按键的代码
*/
#include <PS2X_lib.h> 
//接口定义
#define PS2_DAT        3      
#define PS2_CMD        A3  
#define PS2_SEL        A2  
#define PS2_CLK        13  
//按键定义
//These are our button constants
#define PSB_SELECT      0x0001
#define PSB_L3          0x0002
#define PSB_R3          0x0004
#define PSB_START       0x0008
#define PSB_PAD_UP      0x0010
#define PSB_PAD_RIGHT   0x0020
#define PSB_PAD_DOWN    0x0040
#define PSB_PAD_LEFT    0x0080
#define PSB_L2          0x0100
#define PSB_R2          0x0200
#define PSB_L1          0x0400
#define PSB_R1          0x0800
#define PSB_GREEN       0x1000
#define PSB_RED         0x2000
#define PSB_BLUE        0x4000
#define PSB_PINK        0x8000
#define PSB_TRIANGLE    0x1000
#define PSB_CIRCLE      0x2000
#define PSB_CROSS       0x4000
#define PSB_SQUARE      0x8000

#define pressures   true
#define rumble      true
PS2X ps2x; // create PS2 Controller Class
int error = 0;
byte type = 0;
byte vibrate = 0;
int PS2LX=80,PS2LY=80,PS2RX=80,PS2RY=80;

void PS2Init()
{
  pinMode(PS2_DAT, INPUT); // 
  pinMode(PS2_CMD, OUTPUT); // 
  pinMode(PS2_SEL, OUTPUT); //
  pinMode(PS2_CLK, OUTPUT); // 
  for(int i=0;i<3;i++)
  {
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  }
  if (error == 0) 
  {
    //Serial.print("Found Controller, configured successful ");
    //Serial.print("pressures = ");
    if (pressures)
      ;//Serial.println("true ");
    else
      ;//Serial.println("false");
    //Serial.print("rumble = ");
    if (rumble)
      ;//Serial.println("true)");
    else
      ;//Serial.println("false");
    //Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    //Serial.println("holding L1 or R1 will print out the analog stick values.");
    //Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    ;//Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    ;//Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    ;//Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      //Serial.print("Unknown Controller type found ");
      break;
    case 1:
      //Serial.print("DualShock Controller found ");  //杩欑
      break;
    case 2:
      //Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      //Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}

//返回按下按键的，返回值和按键定义的值位与后可判断按键
//摇杆的值存入PS2LX,PS2LY,PS2RX,PS2RY;
unsigned int PS2Read(int *lx,int *ly,int *rx,int *ry)
{
  ps2x.read_gamepad(false, vibrate); //读手柄的值，包括摇杆与按？
  unsigned int ret=ps2x.ButtonDataByte();
  *ly = ps2x.Analog(PSS_LY);
  *lx = ps2x.Analog(PSS_LX);
  *ry = ps2x.Analog(PSS_RY);
  *rx = ps2x.Analog(PSS_RX);
  //ps2x.read_gamepad(false, vibrate); //读手柄的值，包括摇杆与按
  return ret;
  
}
