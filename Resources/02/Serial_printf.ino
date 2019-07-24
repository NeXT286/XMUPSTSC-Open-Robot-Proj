char s[10];
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printfInit(int baud)
{
  Serial.begin(baud);
  fdevopen( &serial_putc, 0 );
}

char* toBinary(byte a)
{
  itoa(a, s, 2);
  return s;
}
