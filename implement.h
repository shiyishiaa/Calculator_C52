#define uchar unsigned char
#define uint unsigned int

uchar charReceived/*���յ��ַ�*/, i/*ͨ����*/, high/*��λ����ʮλ*/, low/*��λ*/;
bit secondFunction;//�ڶ����ܱ�־
float val1/*������1*/, val2/*������2*/, ans/*���ս��*/;
char tab[32]/*�����������*/, digit/*������λ��*/;
char tab2[9]/*�����������*/;
uchar symbol/*������ű�־*/;

//���̼������飬����ΪASCII��
//�����ϵĿհװ�ť������û������
//�������ڵ�Ƭ��ROMֻ��8K����������չ�����ˣ�ʮ�����ƣ������Ǳ�������
uchar code keyval[5][8]={
0X20,0Xaa,0X2e,0XA3,0X2a,0X44,0X38,0X33,
0XB3,0X3d,0XA7,0XA2,0Xb0,0X43,0X37,0X32,
0X20,0XA9,0XA6,0XA1,0x2b,0X42,0X36,0X31,
0XB2,0XA8,0XA5,0XA0,0X46,0X41,0X35,0x30,
0XB4,0XB1,0X2d,0XA4,0X2F,0X45,0X39,0X34,
};

//���ݴ�����
void come_in() {
    val1 = atof(tab);    //ASCII��ת������
    for (i = 0; i < 32; i++)//���鸴λ0
    {
        tab[i] = 0;
    }
    i = 0;
}

//����ɨ�����
//5*8���̣�����P3�ڵĵ�5λ�ϣ�����P1����
//����ֵΪkeyval[]�еĶ�Ӧ����
uchar keyscan() {
    uchar ch;
    uchar row, column;
    P3 = 0x1f | P3;
    P3_3 = 0;
    if (P1 != 0xff) {
        column = 0;
        ch = P1;
    } else {
        P3_2 = 0;
        if (P1 != 0xff) {
            column = 1;
            ch = P1;
        } else {
            P3_1 = 0;
            if (P1 != 0xff) {
                column = 2;
                ch = P1;
            } else {
                P3_0 = 0;
                if (P1 != 0xff) {
                    column = 3;
                    ch = P1;
                } else {
                    P3_4 = 0;
                    if (P1 != 0xff) {
                        column = 4;
                        ch = P1;
                    }
                }
            }
        }
    }
    switch (ch) {
        default:
            break;
        case 0xfe:
            row = 0;
            break;
        case 0xfd:
            row = 1;
            break;
        case 0xfb:
            row = 2;
            break;
        case 0xf7:
            row = 3;
            break;
        case 0xef:
            row = 4;
            break;
        case 0xdf:
            row = 5;
            break;
        case 0xbf:
            row = 6;
            break;
        case 0x7f:
            row = 7;
            break;
    }
    while (P1 != 0xff);//���ּ��
    return (keyval[column][row]);
}

void keypad() {
    P3 = 0xe0 & P3;//
    P1 = 0xff;//
    if (P1 != 0xff);// �ж����ް���
    delay(10);//��ʱȥ��
    if (P1 != 0xff)//�ٴ��ж�
    {
        charReceived = keyscan();//ɨ����̣�ȡ�ü���
        if (((charReceived >= 0x30) && (charReceived <= 0x39)) || (charReceived == 0x2e) || (charReceived == 0x2d) ||
            (charReceived == 0x45))//�жϼ����Ƿ�Ϊ�������ؼ���
        {
            write_1602dat(charReceived);//��ʾ����
            tab[i] = (char) charReceived;//���ݸ�tab[]
            i++;
        } else {
            switch (charReceived)//�жϼ���
            {
                default:
                    break;
                case 0x2b://�Ӻ�
                {
                    come_in();//���ݴ���
                    write_1602dat('+');//д�Ӻ�
                    symbol = charReceived;//ȡ�������
                    val2 = val1;//����ת��
                    val1 = 0;//val1��λ���ȴ���һ����
                    break;
                }
                case 0xb0://����
                {
                    come_in();
                    write_1602dat('-');//д����
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0x2a://�˺�
                {
                    come_in();
                    write_1602dat('*');//д�˺�
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0x2f://����
                {
                    come_in();
                    write_1602dat('/');//д����
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa0://N�η�
                {
                    come_in();
                    write_1602dat('^');//д��^��
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa1://N�η���
                {
                    come_in();
                    write_1602dat('r');//д����
                    write_1602dat('o');
                    write_1602dat('o');
                    write_1602dat('t');
                    write_1602dat(':');
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa2://sin
                {
                    if (secondFunction == 0)//�жϵڶ����ܱ�׼�����0��д��sin:��
                    {
                        write_1602dat('s');
                        write_1602dat('i');
                        write_1602dat('n');
                        write_1602dat(':');
                    } else//���1��д��asin:��
                    {
                        write_1602dat('a');
                        write_1602dat('s');
                        write_1602dat('i');
                        write_1602dat('n');
                        write_1602dat(':');
                    }
                    symbol = charReceived;
                    val1 = 0;
                }
                    break;
                case 0xa3://cos
                {
                    if (secondFunction == 0)//�жϵڶ����ܱ�׼�����0��д��cos:��
                    {
                        write_1602dat('c');
                        write_1602dat('o');
                        write_1602dat('s');
                        write_1602dat(':');
                    } else//���1��д��acos:��
                    {
                        write_1602dat('a');
                        write_1602dat('c');
                        write_1602dat('o');
                        write_1602dat('s');
                        write_1602dat(':');
                    };
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa4://tan
                {
                    if (secondFunction == 0)//�жϵڶ����ܱ�׼�����0��д��tan:��
                    {
                        write_1602dat('t');
                        write_1602dat('a');
                        write_1602dat('n');
                        write_1602dat(':');
                    } else//���1��д��atan:��
                    {
                        write_1602dat('a');
                        write_1602dat('t');
                        write_1602dat('a');
                        write_1602dat('n');
                        write_1602dat(':');
                    };
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa5://log
                {
                    come_in();
                    write_1602dat(0x7e);//д��������
                    write_1602dat('l');
                    write_1602dat('o');
                    write_1602dat('g');
                    write_1602dat(0x7f);
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa6://�׳�
                {
                    come_in();
                    write_1602dat('!');//д�׳˷���
                    symbol = charReceived;
                    val2 = val1;
                    val1 = 0;
                    break;
                }
                case 0xa7://�������
                {
                    come_in();
                    write_1602dat(0x7e);
                    if (secondFunction == 0)
                        write_1602dat('C');//�жϵڶ����ܱ�׼�����0����Ϊ���У����1Ϊ��ϡ�
                    else write_1602dat('A');
                    write_1602dat(0x7f);
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa8://�ۼ�
                {
                    come_in();
                    write_1602dat(0x7e);//д�ۼӷ���
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xaa://left
                {
                    position = position + 1;//����
                    write_1602com(position);
                    i = i + 1;
                    break;
                }
                case 0xa9://right
                {
                    position = position - 1;//����
                    write_1602com(position);
                    i = i - 1;
                    break;
                }
                case 0xb1://ɾ��
                {
                    position = position - 1;
                    write_1602com(position);
                    write_1602dat(0x20);

                    position = position - 1;
                    write_1602com(position);
                    i = i - 1;
                    tab[i] = ' ';
                    break;
                }
                case 0xb2://�ڶ�����
                {
                    P3_6 = !P3_6;
                    secondFunction = !secondFunction;
                    break;
                }
                case 0xb3://led
                {
                    P2_3 = !P2_3;
                    break;
                }
                case 0x3d://OK��
                {
                    come_in();
                    switch (symbol) {
                        case 0x2b:
                            ans = val1 + val2;
                            break;//��
                        case 0xb0:
                            ans = val2 - val1;
                            break;//��
                        case 0x2a:
                            ans = val2 * val1;
                            break;//��
                        case 0x2f:
                            ans = val2 / val1;
                            break;//��
                        case 0xa0:
                            ans = pow(val2, val1);
                            break;//N�η�
                        case 0xa1:
                            ans = exp(log(val1) / val2);
                            break;//��N�η�
                        case 0xa2: {
                            if (secondFunction == 0)
                                ans = sin(val1);
                            else
                                ans = asin(val1);
                            secondFunction = 0;
                        }
                            break;//sin
                        case 0xa3: {
                            if (secondFunction == 0)
                                ans = cos(val1);
                            else
                                ans = acos(val1);
                            secondFunction = 0;
                        }
                            break;//cos
                        case 0xa4: {
                            if (secondFunction == 0)
                                ans = tan(val1);
                            else
                                ans = atan(val1);
                            secondFunction = 0;
                        }
                            break;//tan
                        case 0xa5:
                            ans = log(val1) / log(val2);
                            break;//log
                        case 0xa6:
                            ans = factorial((uchar) val2);
                            break;//�׳�
                        case 0xa7: {
                            if (secondFunction == 0)
                                ans = permutation((uchar) val2, (uchar) val1);
                            else
                                ans = combination((uchar) val2, (uchar) val1);
                        }
                            break;//���
                        case 0xa8:
                            ans = accumulation(val2, val1);
                            break;//�ۼ�
                        default:
                            ans = val1;
                    }
                    sprintf(tab2, "%f", ans);//������ת�ַ���
                    digit = floatTail(ans);//ȡ�ø�����λ��
                    if (digit > 7)//λ������7��ѧ������ʾ
                    {
                        for (i = 8; i > 1; i--) {
                            tab2[i] = tab2[i - 1];
                        }
                        tab2[1] = '.';
                        write_1602com(secondLine + 9);
                        position = secondLine + 8;
                        write_1602dat('x');
                        write_1602dat('1');
                        write_1602dat('0');
                        write_1602dat('^');
                        if (digit > 9)//����9��ȡ��λ��ʮλ����λ���ֱ���ʾ
                        {
                            high = digit / 10;
                            low = digit % 10;
                            write_1602dat(high + '0');
                            write_1602dat(low + '0');
                        } else
                            write_1602dat(digit + '0');
                    } else if (digit < (-7))//λ��Ϊ����
                    {
                        digit = (char) -digit;//������
                        ans = ans * pow(10, digit);//ans��ٷ���
                        sprintf(tab2, "%f", ans);
                        write_1602com(secondLine + 9);
                        position = secondLine + 9;
                        write_1602dat('x');
                        write_1602dat('1');
                        write_1602dat('0');
                        write_1602dat('^');
                        write_1602dat('-');
                        if (digit > 9) {
                            high = digit / 10;
                            low = digit % 10;
                            write_1602dat(high + '0');
                            write_1602dat(low + '0');
                        } else
                            write_1602dat(digit + '0');
                    }
                    write_1602com(secondLine);
                    position = secondLine;
                    for (i = 0; i < 8; i++) {
                        write_1602dat(tab2[i]);
                        delay(1);
                    }
                    write_1602com(secondLine + 15);
                    position = secondLine + 15;
                    break;
                }
                case 0xb4:        //��λ��
                {
                    write_1602com(0x01);//����ʾ
                    write_1602com(0x80);//ָ�븴λ
                    position = 0x80;
                    for (i = 0; i < 32; i++) {
                        tab[i] = 0;//tab[]��0
                    }
                    for (i = 0; i < 9; i++) {
                        tab2[i] = 0;//tab2[]��0
                    }
                    val2 = 0;//����0�Ķ���0
                    val1 = 0;
                    secondFunction = 0;
                    ans = 0;
                    i = 0;
                    high = 0;
                    low = 0;
                    charReceived = 0;
                    symbol = 0;
                    P3_6 = 0;
                    break;
                }
            }
        }
    }
}