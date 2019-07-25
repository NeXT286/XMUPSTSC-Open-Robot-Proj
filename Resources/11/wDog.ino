/*
全局变量
初始化函数
	void wDogInit()
	功能：看门狗初始化，初始化后每1s内必须进行一次喂狗，否则会重启
	输入参数：无
	输出参数：无
功能函数
	void feetDog()
	功能：喂狗
	输入参数：无
	输出参数：无
*/
#include <avr/wdt.h> 
void wDogInit()
{
  //启动看门狗，设置喂狗时间不能超过2秒  
  wdt_enable(WDTO_1S);
}

void feetDog()
{
  //喂狗。如果超过2S没有喂狗，则单片机重启。 
  //也就是说，如果本循环执行时间超过2S的话，单片机就会自动重启。
  wdt_reset(); 
}
