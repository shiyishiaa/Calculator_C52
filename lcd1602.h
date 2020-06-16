#define uint unsigned int
#define uchar unsigned char

#define firstLine 0x80//��һ��λ�ö���
#define secondLine 0x80+0x40//�ڶ���λ�ö���

sbit rs = P2 ^0;//RS����
sbit en = P2 ^2;//EN����
sbit rw = P2 ^1;//RW����

//��Һ��д����
void write_1602com(uchar com) {
    rs = 0;
    rw = 0;
    P0 = com;
    delay(1);
    en = 1;
    delay(1);
    en = 0;
}

//��Һ��д����
void write_1602dat(uchar dat) {
    rs = 1;
    rw = 0;
    P0 = dat;
    delay(1);
    en = 1;
    delay(1);
    en = 0;
    position++;//д��һλ���ݺ�ָ���һ����־Ϊ�����һ
    if (position == 0x80 + 16)//ָ��ӵ���һ��ĩβ���Զ�ת���ڶ���
    {
        write_1602com(secondLine);
        position = secondLine;
    }
    if (position == (secondLine + 16))//ָ��ӵ��ڶ���ĩβ���Զ�ת����һ��
    {
        write_1602com(0x80);
        position = firstLine;
    }
}

//Һ����ʼ��
void lcd_init() {
    write_1602com(0x38);//������ʾ��ʽΪ��16*2����ʾ��5*7����8λ���ݽӿ�
    write_1602com(0x0f);//0x0f--��ʾ�������ã���ʾ��겢��˸
    write_1602com(0x06);//0x06--��д��ָ���1
    write_1602com(0x01);//���LCD��ʾ����
}
