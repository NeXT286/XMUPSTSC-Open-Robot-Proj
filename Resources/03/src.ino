//*****************************************
//从串口输出HelloWorld
//*****************************************
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口初始，设置波特率

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Hello ");//从串口输
  Serial.println("World!");//从串口输出后换行
}
