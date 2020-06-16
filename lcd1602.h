#define uint unsigned int
#define uchar unsigned char

#define firstLine 0x80//第一行位置定义
#define secondLine 0x80+0x40//第二行位置定义

sbit rs = P2 ^0;//RS引脚
sbit en = P2 ^2;//EN引脚
sbit rw = P2 ^1;//RW引脚

//向液晶写命令
void write_1602com(uchar com) {
    rs = 0;
    rw = 0;
    P0 = com;
    delay(1);
    en = 1;
    delay(1);
    en = 0;
}

//向液晶写数据
void write_1602dat(uchar dat) {
    rs = 1;
    rw = 0;
    P0 = dat;
    delay(1);
    en = 1;
    delay(1);
    en = 0;
    position++;//写完一位数据后，指针加一，标志为跟随加一
    if (position == 0x80 + 16)//指针加到第一行末尾，自动转到第二行
    {
        write_1602com(secondLine);
        position = secondLine;
    }
    if (position == (secondLine + 16))//指针加到第二行末尾，自动转到第一行
    {
        write_1602com(0x80);
        position = firstLine;
    }
}

//液晶初始化
void lcd_init() {
    write_1602com(0x38);//设置显示格式为：16*2行显示，5*7点阵，8位数据接口
    write_1602com(0x0f);//0x0f--显示开关设置，显示光标并闪烁
    write_1602com(0x06);//0x06--读写后指针加1
    write_1602com(0x01);//清除LCD显示内容
}
