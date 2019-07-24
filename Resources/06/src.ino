//*****************************************
//OLED显示测试
//*****************************************
void setup() {
  // put your setup code here, to run once:
  OLED_Init();//OLED初始化
}

void loop() {
  // put your main code here, to run repeatedly:
  static int loopCnt=0;//定义一个变量记录主循环的次，初始化0
  OLED12864_ShowStr(0,0,"Hello World!") ; //用OLED输出固定的字符串
  char a[]="               ";//定义一个字符串变量（字符数组）
  sprintf(a,"LoopCnt:%d",loopCnt++);//填充字符串变量
  OLED12864_ShowStr(0,1,a) ; //用OLED输出字符串变量
  delay(1000);//延时1000ms
}
