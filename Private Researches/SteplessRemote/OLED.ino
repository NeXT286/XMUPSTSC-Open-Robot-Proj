/*
全局变量
初始化函数
	void OLED_Init()
	功能：OLED初始化
	输入参数：无
	输出参数：无
功能函数
	void OLED12864_ShowStr(unsigned char x, unsigned char y, char ch[])
	功能：OLED显示字符串
	输入参数：
		x：
			功能：x轴显示位置
			取值范围：0-120
		y：
			功能：y轴显示位置
			取值范围：0-6
                ch[]：
			功能：待显示的字符串

*/

#define OLED_12864_Address 0x78
#define SCL 7
#define SDA 8

PROGMEM static const unsigned char F6x8[][6] =
    {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // sp
        {0x00, 0x00, 0x00, 0x2f, 0x00, 0x00}, // !
        {0x00, 0x00, 0x07, 0x00, 0x07, 0x00}, // "
        {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14}, // #
        {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12}, // $
        {0x00, 0x62, 0x64, 0x08, 0x13, 0x23}, // %
        {0x00, 0x36, 0x49, 0x55, 0x22, 0x50}, // &
        {0x00, 0x00, 0x05, 0x03, 0x00, 0x00}, // '
        {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00}, // (
        {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00}, // )
        {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14}, // *
        {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08}, // +
        {0x00, 0x00, 0x00, 0xA0, 0x60, 0x00}, // ,
        {0x00, 0x08, 0x08, 0x08, 0x08, 0x08}, // -
        {0x00, 0x00, 0x60, 0x60, 0x00, 0x00}, // .
        {0x00, 0x20, 0x10, 0x08, 0x04, 0x02}, // /
        {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
        {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
        {0x00, 0x42, 0x61, 0x51, 0x49, 0x46}, // 2
        {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
        {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
        {0x00, 0x27, 0x45, 0x45, 0x45, 0x39}, // 5
        {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
        {0x00, 0x01, 0x71, 0x09, 0x05, 0x03}, // 7
        {0x00, 0x36, 0x49, 0x49, 0x49, 0x36}, // 8
        {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
        {0x00, 0x00, 0x36, 0x36, 0x00, 0x00}, // :
        {0x00, 0x00, 0x56, 0x36, 0x00, 0x00}, // ;
        {0x00, 0x08, 0x14, 0x22, 0x41, 0x00}, // <
        {0x00, 0x14, 0x14, 0x14, 0x14, 0x14}, // =
        {0x00, 0x00, 0x41, 0x22, 0x14, 0x08}, // >
        {0x00, 0x02, 0x01, 0x51, 0x09, 0x06}, // ?
        {0x00, 0x32, 0x49, 0x59, 0x51, 0x3E}, // @
        {0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C}, // A
        {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36}, // B
        {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22}, // C
        {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
        {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41}, // E
        {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01}, // F
        {0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
        {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
        {0x00, 0x00, 0x41, 0x7F, 0x41, 0x00}, // I
        {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01}, // J
        {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41}, // K
        {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40}, // L
        {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
        {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
        {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
        {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06}, // P
        {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
        {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46}, // R
        {0x00, 0x46, 0x49, 0x49, 0x49, 0x31}, // S
        {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01}, // T
        {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
        {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
        {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
        {0x00, 0x63, 0x14, 0x08, 0x14, 0x63}, // X
        {0x00, 0x07, 0x08, 0x70, 0x08, 0x07}, // Y
        {0x00, 0x61, 0x51, 0x49, 0x45, 0x43}, // Z
        {0x00, 0x00, 0x7F, 0x41, 0x41, 0x00}, // [
        {0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55}, // 55
        {0x00, 0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
        {0x00, 0x04, 0x02, 0x01, 0x02, 0x04}, // ^
        {0x00, 0x40, 0x40, 0x40, 0x40, 0x40}, // _
        {0x00, 0x00, 0x01, 0x02, 0x04, 0x00}, // '
        {0x00, 0x20, 0x54, 0x54, 0x54, 0x78}, // a
        {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38}, // b
        {0x00, 0x38, 0x44, 0x44, 0x44, 0x20}, // c
        {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F}, // d
        {0x00, 0x38, 0x54, 0x54, 0x54, 0x18}, // e
        {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02}, // f
        {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C}, // g
        {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78}, // h
        {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00}, // i
        {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00}, // j
        {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00}, // k
        {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00}, // l
        {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78}, // m
        {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78}, // n
        {0x00, 0x38, 0x44, 0x44, 0x44, 0x38}, // o
        {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18}, // p
        {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC}, // q
        {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08}, // r
        {0x00, 0x48, 0x54, 0x54, 0x54, 0x20}, // s
        {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20}, // t
        {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
        {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
        {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
        {0x00, 0x44, 0x28, 0x10, 0x28, 0x44}, // x
        {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, // y
        {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44}, // z
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14}  // horiz lines
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void I2C_init() //初始化
{
        pinMode(SDA, OUTPUT);
        pinMode(SCL, OUTPUT);
        digitalWrite(SDA, HIGH);
        __asm__("nop\n\t");
        digitalWrite(SCL, HIGH);
        __asm__("nop\n\t"); //空闲时，两条线均为高电平
}

/*I2C通信起始信号*/
void I2C_start()
{
        digitalWrite(SCL, HIGH); //此时主机有总线控制权，先把SCL线拉高
        __asm__("nop\n\t");      //稳定一下
        digitalWrite(SDA, HIGH); //把SDA线拉高，以便发出起始信号（不确定是否为高）
        delayMicroseconds(5);    //通信协议规定延时大于4.7us
        digitalWrite(SDA, LOW);  //拉低SDA线，制造下降沿的起始信号
        delayMicroseconds(5);    //通信协议规定延时大于4us
}

/*I2C通信终止信号*/
void I2C_stop()
{
        digitalWrite(SDA, LOW);  //拉低SDA线，以便发出终止信号
        __asm__("nop\n\t");      //稳定一下
        digitalWrite(SCL, HIGH); //拉高SCL线
        delayMicroseconds(5);    //通信协议规定延时大于4us
        digitalWrite(SDA, HIGH); //拉高SDA线
        delayMicroseconds(5);    //通信协议规定延时大于4.7us
}

/*从机应答检测*/
char Test_ack()
{
        digitalWrite(SCL, HIGH);
        //拉高SCL线，以便主机读取从机发出的应答或非应答信号
        delayMicroseconds(5); //通信协议规定延时大于4us
        pinMode(SDA, INPUT);
        if (digitalRead(SDA))
        //主机读取的SDA线为高，说明从机发送了一个非应答信号
        {
                pinMode(SDA, OUTPUT);
                digitalWrite(SCL, LOW); /*接下来准备发送停止信号，所以让时钟总线SCL拉低，
                                让I2C_stop();函数中的SDA可变为0*/
                __asm__("nop\n\t");     //稳定总线
                I2C_stop();
                //Serial.println("No");
                return 0; //结束检测从机应答函数
        }
        else
        //主机读取的SDA线为低，说明从机发送了一个应答信号
        {
                pinMode(SDA, OUTPUT);
                digitalWrite(SCL, LOW); /*将时钟总线SCL拉低，此时SDA上数据的变化才有效，
                                因为接下来会继续发数据*/
                __asm__("nop\n\t");     //稳定总线
                //Serial.println("Yes");
                return 1;
        }
}

/*I2C通信：发送一个字节*/
void I2C_send_byte(unsigned char byte)
{
        unsigned char i;        //声明一个计数变量i
        for (i = 0; i < 8; i++) //一个字节有8位，发8次
        {
                digitalWrite(SCL, LOW); //拉低SCL，让数据总线SDA变化有效
                __asm__("nop\n\t");     //稳定总线
                if (byte & 0x80)        //1000 0000 & byte
                                        /*如果（要发送数据的当前传输位）byte的最高位为1，执行该if语句，
  如果（要发送数据的当前传输位）byte的最高位为0，不执行该if语句*/
                {
                        digitalWrite(SDA, HIGH);
                        //（当前传输位）byte的最高位为1，即把1放到SDA线上
                        __asm__("nop\n\t"); //稳定总线
                }
                else
                //如果（当前发送位）byte的最高位为0（不为1），给SDA送0
                {
                        digitalWrite(SDA, LOW);
                        __asm__("nop\n\t"); //稳定总线
                }
                digitalWrite(SCL, HIGH); //拉高SCL线，使从机能够从SDA线上读取到当前的数据
                __asm__("nop\n\t");      //稳定总线
                byte <<= 1;
                /*使byte左移一位，即原来已被发送到SDA线上的最高位被移除，
第七位（还未发送的数据位）变成最高位变为下一次循环的当前发送位*/
        }
        digitalWrite(SCL, LOW);
        //发送完数据之后，将SCL拉低，以便从机改变SDA线，发出应答信号
        __asm__("nop\n\t");      //稳定总线
        digitalWrite(SDA, HIGH); //释放总线控制权
        __asm__("nop\n\t");      //稳定总线
}

char OLED12864_Write_Commmand(unsigned char cmd, char start, char stopb)
{
        if (start)
        {
                I2C_start();
                I2C_send_byte(OLED_12864_Address + 0); //写从机地址，并且加上读写标志位（最后一位）
                if (!Test_ack())
                {
                        return 0;
                }
                /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/
        }
        I2C_send_byte(0x80 | 0x00 | 0x00); //Co位为1（接下来要传指令），DC为0（接下来是指令）
        if (!Test_ack())
        {
                return 0;
        }
        /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/

        I2C_send_byte(cmd);
        if (!Test_ack())
        {
                return 0;
        }
        /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/

        if (stopb)
                I2C_stop();

        return 1;
}

//初始化OLED
void OLED_Init(void)
{
        I2C_init();
        delay(300);
        I2C_init();

        OLED12864_Write_Commmand(0xAE, 1, 0); //display off
        OLED12864_Write_Commmand(0x20, 0, 0); //Set Memory Addressing Mode
        OLED12864_Write_Commmand(0x10, 0, 0); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
        OLED12864_Write_Commmand(0xb0, 0, 0); //Set Page Start Address for Page Addressing Mode,0-7
        OLED12864_Write_Commmand(0xc8, 0, 0); //Set COM Output Scan Direction
        OLED12864_Write_Commmand(0x00, 0, 0); //---set low column address
        OLED12864_Write_Commmand(0x10, 0, 0); //---set high column address
        OLED12864_Write_Commmand(0x40, 0, 0); //--set start line address
        OLED12864_Write_Commmand(0x81, 0, 0); //--set contrast control register
        OLED12864_Write_Commmand(0xff, 0, 0); //???? 0x00~0xff
        OLED12864_Write_Commmand(0xa1, 0, 0); //--set segment re-map 0 to 127
        OLED12864_Write_Commmand(0xa6, 0, 0); //--set normal display
        OLED12864_Write_Commmand(0xa8, 0, 0); //--set multiplex ratio(1 to 64)
        OLED12864_Write_Commmand(0x3F, 0, 0); //
        OLED12864_Write_Commmand(0xa4, 0, 0); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
        OLED12864_Write_Commmand(0xd3, 0, 0); //-set display offset
        OLED12864_Write_Commmand(0x00, 0, 0); //-not offset
        OLED12864_Write_Commmand(0xd5, 0, 0); //--set display clock divide ratio/oscillator frequency
        OLED12864_Write_Commmand(0xf0, 0, 0); //--set divide ratio
        OLED12864_Write_Commmand(0xd9, 0, 0); //--set pre-charge period
        OLED12864_Write_Commmand(0x22, 0, 0); //
        OLED12864_Write_Commmand(0xda, 0, 0); //--set com pins hardware configuration
        OLED12864_Write_Commmand(0x12, 0, 0);
        OLED12864_Write_Commmand(0xdb, 0, 0); //--set vcomh
        OLED12864_Write_Commmand(0x20, 0, 0); //0x20,0.77xVcc
        OLED12864_Write_Commmand(0x8d, 0, 0); //--set DC-DC enable
        OLED12864_Write_Commmand(0x14, 0, 0); //
        OLED12864_Write_Commmand(0xaf, 0, 1); //--turn on oled panel
        OLED12864_Fill(0x00);
        OLED12864_Write_Commmand(0xAE, 1, 0); //display off
        OLED12864_Write_Commmand(0x20, 0, 0); //Set Memory Addressing Mode
        OLED12864_Write_Commmand(0x10, 0, 0); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
        OLED12864_Write_Commmand(0xb0, 0, 0); //Set Page Start Address for Page Addressing Mode,0-7
        OLED12864_Write_Commmand(0xc8, 0, 0); //Set COM Output Scan Direction
        OLED12864_Write_Commmand(0x00, 0, 0); //---set low column address
        OLED12864_Write_Commmand(0x10, 0, 0); //---set high column address
        OLED12864_Write_Commmand(0x40, 0, 0); //--set start line address
        OLED12864_Write_Commmand(0x81, 0, 0); //--set contrast control register
        OLED12864_Write_Commmand(0xff, 0, 0); //???? 0x00~0xff
        OLED12864_Write_Commmand(0xa1, 0, 0); //--set segment re-map 0 to 127
        OLED12864_Write_Commmand(0xa6, 0, 0); //--set normal display
        OLED12864_Write_Commmand(0xa8, 0, 0); //--set multiplex ratio(1 to 64)
        OLED12864_Write_Commmand(0x3F, 0, 0); //
        OLED12864_Write_Commmand(0xa4, 0, 0); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
        OLED12864_Write_Commmand(0xd3, 0, 0); //-set display offset
        OLED12864_Write_Commmand(0x00, 0, 0); //-not offset
        OLED12864_Write_Commmand(0xd5, 0, 0); //--set display clock divide ratio/oscillator frequency
        OLED12864_Write_Commmand(0xf0, 0, 0); //--set divide ratio
        OLED12864_Write_Commmand(0xd9, 0, 0); //--set pre-charge period
        OLED12864_Write_Commmand(0x22, 0, 0); //
        OLED12864_Write_Commmand(0xda, 0, 0); //--set com pins hardware configuration
        OLED12864_Write_Commmand(0x12, 0, 0);
        OLED12864_Write_Commmand(0xdb, 0, 0); //--set vcomh
        OLED12864_Write_Commmand(0x20, 0, 0); //0x20,0.77xVcc
        OLED12864_Write_Commmand(0x8d, 0, 0); //--set DC-DC enable
        OLED12864_Write_Commmand(0x14, 0, 0); //
        OLED12864_Write_Commmand(0xaf, 0, 1); //--turn on oled panel
        OLED12864_Fill(0x00);
}
////////////////////////////////////////////////////////////////
/*写连续数据函数，第一个参数为数据，第二个参数为发送连多少位连续的数据，第三、四个参数选择是否需要通信开始和结束函数，=1有，=0没有*/
char OLED12864_Write_Continuous_Data(const unsigned char *dat, unsigned char count, char start, char stopb)
{
        unsigned char i = 0; //定义计数变量
        if (start)
        {
                I2C_start();
                I2C_send_byte(OLED_12864_Address + 0); //写从机地址，并且加上读写标志位（最后一位）
                if (!Test_ack())
                {
                        return 0;
                }
                /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/
        }
        I2C_send_byte(0x00 | 0x40 | 0x00); //Co位为0（接下来只传数据），DC为1（接下来是数据）
        if (!Test_ack())
        {
                return 0;
        }
        /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/
        for (i = 0; i < count; i++)
        {
                //I2C_send_byte(*dat++);
                I2C_send_byte(pgm_read_byte(dat++));
                if (!Test_ack())
                {
                        return 0;
                }
                /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/
        }

        if (stopb)
                I2C_stop();

        return 1;
}

/*写相同的连续数据函数，第一个参数为数据，第二参数为发送的次数*/
char OLED12864_Write_Same_Continuous_Data(unsigned char dat, unsigned char count)
{
        unsigned char i = 0; //定义计数变量
        I2C_start();
        I2C_send_byte(OLED_12864_Address + 0); //写从机地址，并且加上读写标志位（最后一位）
        if (!Test_ack())
        {
                return 0;
        }
        /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/

        I2C_send_byte(0x00 | 0x40 | 0x00); //Co位为0（接下来只传数据），DC为1（接下来是数据）

        if (!Test_ack())
        {
                return 0;
        }
        /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/
        for (i = 0; i < count; i++)
        {
                if (i % 2 == 0)
                        I2C_send_byte(dat);
                else
                        I2C_send_byte(0);
                if (!Test_ack())
                {
                        return 0;
                }
                /*执行从机应答检测函数，如果从机发送了非应答信号，那么就退出数据发送函数*/
        }

        I2C_stop();

        return 1;
}

//Fill screen wit data
//0x00 is black
//0xff is blue
void OLED12864_Fill(unsigned char fill_Data)
{
        unsigned char m;
        //uint8_t n;
        for (m = 0; m < 8; m++)
        {
                OLED12864_Write_Commmand(0xb0 + m, 1, 0); //page0-page1
                OLED12864_Write_Commmand(0x00, 0, 0);     //low column start address
                OLED12864_Write_Commmand(0x10, 0, 1);     //high column start address
                OLED12864_Write_Same_Continuous_Data(fill_Data, 128);
        }
}

//Set the cursor position of start
void OLED12864_SetPos(unsigned char x, unsigned char y)
{
        OLED12864_Write_Commmand(0xb0 + y, 1, 0);
        OLED12864_Write_Commmand(((x & 0xf0) >> 4) | 0x10, 0, 0);
        OLED12864_Write_Commmand((x & 0x0f) | 0x01, 0, 1);
}

//--------------------------------------------------------------
// show string
// x,y -- start position(x:0~127,column; y:0~7,row);
// ch[] -- the string to show;
// TextSize -- (1:6*8 ; 2:8*16)
//OLED12864_ShowStr(0,3,"I2C Test",1);// 6*8
//OLED12864_ShowStr(0,4,"Hello Delta",2) //8*16
//--------------------------------------------------------------
void OLED12864_ShowStr(unsigned char x, unsigned char y, char ch[])
{
        unsigned char c = 0, i = 0, j = 0;

        while (ch[j] != '\0' && ch[j] != '\n')
        {
                c = (unsigned char)ch[j] - 32;
                if (x > 120)
                {
                        x = 0;
                        y++;
                }
                OLED12864_SetPos(x, y);
                OLED12864_Write_Continuous_Data(F6x8[c], 6, 1, 1); //将该位的指针传给函数，并且写连续的6个数据即可

                x += 6;
                j++;
        }
}
void OLED12864_ShowStr(unsigned char x, unsigned char y, const char ch[])
{
        unsigned char c = 0, i = 0, j = 0;

        while (ch[j] != '\0' && ch[j] != '\n')
        {
                c = (unsigned char)ch[j] - 32;
                if (x > 120)
                {
                        x = 0;
                        y++;
                }
               
                OLED12864_SetPos(x, y);
                OLED12864_Write_Continuous_Data(F6x8[c], 6, 1, 1); //将该位的指针传给函数，并且写连续的6个数据即可

                x += 6;
                j++;
        }
}
