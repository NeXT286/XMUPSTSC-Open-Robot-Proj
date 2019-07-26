void LeftRecover()
{
  while(1)
  {
    carMove(0,120);
    if(TL2==1&& TL1==0 && TR1==0 && TR2==1)
    {
      break;
    }
  }
}

void RightRecover()
{
  while(1)
  {
    carMove(120,0);
    if(TL2==1&& TL1==0 && TR1==0 && TR2==1)
    {
      break;
    }
  }
}

void LeftTurn()
{
  while(1)
  {
    carMove(20,80);
    if(TL2==1&& TL1==0 && TR1==0 && TR2==1)
    {
      break;
    }
  }
}

void RightTurn()
{
  while(1)
  {
    carMove(80,20);
    if(TL2==1&& TL1==0 && TR1==0 && TR2==1)
    {
      break;
    }
  }
}
