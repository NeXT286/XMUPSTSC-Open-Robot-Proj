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
