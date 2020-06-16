/*
 * 5*8�������룬lcd1602��ʾ
 * ���ܣ������Ϊ�����ȸ�����
 * �� 19 �����㹦�ܣ�
 * �ӣ������ˣ�����ƽ����������N�η�
 * ��N�η������Һ��������Һ��������к���
 * �����ң������ң������У���������
 * �׳ˣ�N<=34�������У���ϣ��ۼ�
 * ���ܼ�:��λ������ɾ����ȷ�������ڶ����ܼ�������ư���
*/

#include "intrins.h"
#include "AT89X52.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "mathFunction.h"
#include "lcd1602.h"
#include "implement.h"

#define uchar unsigned char
#define uint unsigned int

void init()//��ʾ��ϵͳ��ʼ������
{
    EA = 1;                //�����ж�
    ET1 = 1;                //T1��
    TMOD = 0X10;            //����T1������ʽ1
    TH1 = 0X3C;
    TL1 = 0XB0;    //���ü������ã�����Ϊ12M����50000�����壬50ms��

    P2_3 = 1;                //����ƿ������ţ�Ĭ�Ͽ�����
    P3_6 = 0;                //�ڶ����ܼ�ָʾ��

    lcd_init();            //Һ����ʾ��ʼ������

    write_1602com(0x80);    //��ʾָ���ʼ��
    TR1 = 1;                    //T0��ʼ����
}

int main() {
    init();            //���ó�ʼ������
    while (1)        //�ȴ��ж�
    {
        PCON = 0X01;    //����Ϊ����ģʽ
    }
}

void t1(void) interrupt 3 {
    TH1 = 0X3C;
    TL1 = 0XB0;    //������ֵ��������
    keypad();            //���̼��
}
