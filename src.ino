//*****************************************
//车辆前进、后退、左转、右转、停止
//*****************************************
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口初始化，设置波特率
  carInit();//车辆电机初始化
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Forward ");//串口打印调试信息
  carMove(100,100);//左右侧轮前进,车辆前进
  delay(1000);//延时1s
  Serial.println("Back ");
  carMove(______,________);//左右侧轮后退,车辆后退
  delay(1000);
  Serial.println("Left ");
  carMove(______,________);//左轮后退，右轮前进，车辆左转
  delay(1000);
  Serial.println("Right ");
  carMove(______,___  ___);//左轮前进，右轮后退，车辆右转
  delay(1000);
  Serial.println("Stop ");
  carMove(0,0);//左轮0，右轮0，车辆停止
  delay(1000);
}
