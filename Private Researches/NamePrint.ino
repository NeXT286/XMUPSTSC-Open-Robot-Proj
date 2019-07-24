//*****************************************
//从串口输出HelloWorld
//*****************************************
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口初始，设置波特率
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("My name is ");//从串口输
  Serial.println("___]___     ________        |");//从串口输出后换行
  Serial.println("  /|\\       |      |     ___|___   ");
  Serial.println(" / | \\      |______|      __|__    ");
  Serial.println("/  |  \\     |      |    ____|____  ");
  Serial.println("  ___       |______|       / \\     ");
  Serial.println("   _/*      ,   ,         /   \\    ");
  Serial.println("___]___     |   |   |   _/  |  \\_  ");
  Serial.println("   |        |__ |__/      *\\|/*    ");
  Serial.println("   |        | / |         _/|\\_    ");
  Serial.println("  \\|        |/  |____|     _|      ");
  delay(1000);
  
}
