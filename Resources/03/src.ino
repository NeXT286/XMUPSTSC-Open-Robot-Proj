void setup() 
{ 
  pinMode(13, OUTPUT);   //将 13 号数字口设置为输出 
} 
void loop() 
{ 
  digitalWrite(13, HIGH);   // 点亮 LED 灯 (HIGH 表示数字引脚输出高电平) 
  delay(1000);    // 等待 1000 毫秒，即等待 1 秒 
  digitalWrite(13, LOW);  //熄灭 LED 灯 (LOW 表示数字引脚输出低电平) 
  delay(1000);    //等待 1000 毫秒，即等待 1 秒 
} 
