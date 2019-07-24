#define Beep ___________ //定义蜂鸣器所在 IO 
void setup() 
{ 
  // put your setup code here, to run once: 
  Serial.begin(______________);//串口初始，设置波特率 
  pinMode(Beep,_____________);//设置蜂鸣器所在 IO 输出 
  digitalWrite(Beep,_______________);//初始化蜂鸣器不发声 
  Serial.print("This is my work,my name is __________________");//从串口输出调试信息 
} 
void loop() 
{ 
  // put your main code here, to run repeatedly: 
  int Val;
  Val=Serial.read();//读取 PC 机发送的指令或字符，并将该指令或字符赋给 val 
  if(Val=='H')//判断接收到的指令或字符是否是“H”。 
  {//如果接收到的是“H”字符 
    Serial.println("OK,Sir,Beep will be on"); 
    digitalWrite(Beep,__________________);//打开蜂鸣器 
  } 
  if(Val=='L')//判断接收到的指令或字符是否是“L”。 
  {//如果接收到的是“L”字符 
    Serial.println("OK,Sir,Beep will be off"); 
    digitalWrite(Beep,___________________);//打开蜂鸣器 
  } 
} 
