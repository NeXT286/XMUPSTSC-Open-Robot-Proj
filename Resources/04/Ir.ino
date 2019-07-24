//*****************************************
//红外光敏二极管接受红外较高时，蜂鸣器鸣响
//同时从串口输出红外光敏二极管DA值
//*****************************************
#define Beep 12 //定义蜂鸣器所在IO
#define IR_Rev A1//红外接收IO
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口初始，设置波特率
  pinMode(Beep,OUTPUT);//设置蜂鸣器所在IO输出
  digitalWrite(Beep,HIGH);//初始化蜂鸣器不发声
  pinMode(IR_Rev,INPUT);//设置红外光敏二极管所在IO输入
}

void loop() {
  // put your main code here, to run repeatedly:
  int irRev;
  irRev=analogRead(IR_Rev);
  Serial.print("IR_Rev:");//从串口输出调试信息
  Serial.println(irRev);//从串口输出调试信息
  if(irRev>600)//如果接收红外强度超过600
    digitalWrite(Beep,_________);//蜂鸣器响
  else//否则的话
    digitalWrite(Beep,_________);//蜂鸣器停

}
