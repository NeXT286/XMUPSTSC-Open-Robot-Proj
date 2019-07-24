//*****************************************
//光敏电阻接受光线较低时，点亮LED
//同时从串口输出光敏电阻DA值
//光敏电阻->A0
//LED->3(注意调整PS2处3脚跳线帽)
//*****************************************
#define LED ________ //定义LED所在IO
#define LDR A0//红外接收IO
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口初始，设置波特率
  pinMode(LED,OUTPUT);//设置LED所在IO输出
  digitalWrite(LED,LOW);//初始化LED不亮
  pinMode(LDR,INPUT);//设置红外光敏二极管所在IO输入
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrRev;
  ldrRev=analogRead(LDR);
  Serial.print("LDR:");//从串口输出调试信息
  Serial.println(ldrRev);//从串口输出调试信息
  if(ldrRev>________)//如果接收红外强度超过600
    digitalWrite(LED,________);//LED亮
  else//否则的话
    digitalWrite(LED,________);//LED不亮

}
