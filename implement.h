#define uchar unsigned char
#define uint unsigned int

uchar charReceived/*接收的字符*/, i/*通用数*/, high/*两位数的十位*/, low/*个位*/;
bit secondFunction;//第二功能标志
float val1/*运算数1*/, val2/*运算数2*/, ans/*最终结果*/;
char tab[32]/*输入接收数组*/, digit/*浮点数位数*/;
char tab2[9]/*输出缓冲数组*/;
uchar symbol/*运算符号标志*/;

//键盘键码数组，部分为ASCII码
//键盘上的空白按钮，键并没有用上
//这是由于单片机ROM只有8K，不能再扩展功能了（十六进制），但是保留按键
uchar code keyval[5][8]={
0X20,0Xaa,0X2e,0XA3,0X2a,0X44,0X38,0X33,
0XB3,0X3d,0XA7,0XA2,0Xb0,0X43,0X37,0X32,
0X20,0XA9,0XA6,0XA1,0x2b,0X42,0X36,0X31,
0XB2,0XA8,0XA5,0XA0,0X46,0X41,0X35,0x30,
0XB4,0XB1,0X2d,0XA4,0X2F,0X45,0X39,0X34,
};

//数据处理函数
void come_in() {
    val1 = atof(tab);    //ASCII码转浮点数
    for (i = 0; i < 32; i++)//数组复位0
    {
        tab[i] = 0;
    }
    i = 0;
}

//键盘扫描程序
//5*8键盘，列在P3口的低5位上，行在P1口上
//返回值为keyval[]中的对应键码
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
    while (P1 != 0xff);//松手检测
    return (keyval[column][row]);
}

void keypad() {
    P3 = 0xe0 & P3;//
    P1 = 0xff;//
    if (P1 != 0xff);// 判断有无按键
    delay(10);//延时去抖
    if (P1 != 0xff)//再次判断
    {
        charReceived = keyscan();//扫描键盘，取得键码
        if (((charReceived >= 0x30) && (charReceived <= 0x39)) || (charReceived == 0x2e) || (charReceived == 0x2d) ||
            (charReceived == 0x45))//判断键码是否为浮点数关键字
        {
            write_1602dat(charReceived);//显示键码
            tab[i] = (char) charReceived;//数据给tab[]
            i++;
        } else {
            switch (charReceived)//判断键码
            {
                default:
                    break;
                case 0x2b://加号
                {
                    come_in();//数据处理
                    write_1602dat('+');//写加号
                    symbol = charReceived;//取得运算符
                    val2 = val1;//数据转移
                    val1 = 0;//val1复位，等待下一个数
                    break;
                }
                case 0xb0://减号
                {
                    come_in();
                    write_1602dat('-');//写减号
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0x2a://乘号
                {
                    come_in();
                    write_1602dat('*');//写乘号
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0x2f://除号
                {
                    come_in();
                    write_1602dat('/');//写除号
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa0://N次方
                {
                    come_in();
                    write_1602dat('^');//写‘^’
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa1://N次方根
                {
                    come_in();
                    write_1602dat('r');//写根号
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
                    if (secondFunction == 0)//判断第二功能标准，如果0，写“sin:”
                    {
                        write_1602dat('s');
                        write_1602dat('i');
                        write_1602dat('n');
                        write_1602dat(':');
                    } else//如果1，写“asin:”
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
                    if (secondFunction == 0)//判断第二功能标准，如果0，写“cos:”
                    {
                        write_1602dat('c');
                        write_1602dat('o');
                        write_1602dat('s');
                        write_1602dat(':');
                    } else//如果1，写“acos:”
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
                    if (secondFunction == 0)//判断第二功能标准，如果0，写“tan:”
                    {
                        write_1602dat('t');
                        write_1602dat('a');
                        write_1602dat('n');
                        write_1602dat(':');
                    } else//如果1，写“atan:”
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
                    write_1602dat(0x7e);//写对数符号
                    write_1602dat('l');
                    write_1602dat('o');
                    write_1602dat('g');
                    write_1602dat(0x7f);
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa6://阶乘
                {
                    come_in();
                    write_1602dat('!');//写阶乘符号
                    symbol = charReceived;
                    val2 = val1;
                    val1 = 0;
                    break;
                }
                case 0xa7://排列组合
                {
                    come_in();
                    write_1602dat(0x7e);
                    if (secondFunction == 0)
                        write_1602dat('C');//判断第二功能标准，如果0，则为排列，如果1为组合”
                    else write_1602dat('A');
                    write_1602dat(0x7f);
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xa8://累加
                {
                    come_in();
                    write_1602dat(0x7e);//写累加符号
                    val2 = val1;
                    symbol = charReceived;
                    val1 = 0;
                    break;
                }
                case 0xaa://left
                {
                    position = position + 1;//左移
                    write_1602com(position);
                    i = i + 1;
                    break;
                }
                case 0xa9://right
                {
                    position = position - 1;//右移
                    write_1602com(position);
                    i = i - 1;
                    break;
                }
                case 0xb1://删除
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
                case 0xb2://第二功能
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
                case 0x3d://OK键
                {
                    come_in();
                    switch (symbol) {
                        case 0x2b:
                            ans = val1 + val2;
                            break;//加
                        case 0xb0:
                            ans = val2 - val1;
                            break;//减
                        case 0x2a:
                            ans = val2 * val1;
                            break;//乘
                        case 0x2f:
                            ans = val2 / val1;
                            break;//除
                        case 0xa0:
                            ans = pow(val2, val1);
                            break;//N次方
                        case 0xa1:
                            ans = exp(log(val1) / val2);
                            break;//开N次方
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
                            break;//阶乘
                        case 0xa7: {
                            if (secondFunction == 0)
                                ans = permutation((uchar) val2, (uchar) val1);
                            else
                                ans = combination((uchar) val2, (uchar) val1);
                        }
                            break;//组合
                        case 0xa8:
                            ans = accumulation(val2, val1);
                            break;//累加
                        default:
                            ans = val1;
                    }
                    sprintf(tab2, "%f", ans);//浮点数转字符串
                    digit = floatTail(ans);//取得浮点数位数
                    if (digit > 7)//位数大于7科学计数显示
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
                        if (digit > 9)//大于9，取得位数十位，个位，分别显示
                        {
                            high = digit / 10;
                            low = digit % 10;
                            write_1602dat(high + '0');
                            write_1602dat(low + '0');
                        } else
                            write_1602dat(digit + '0');
                    } else if (digit < (-7))//位数为负数
                    {
                        digit = (char) -digit;//变正数
                        ans = ans * pow(10, digit);//ans变假分数
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
                case 0xb4:        //复位键
                {
                    write_1602com(0x01);//清显示
                    write_1602com(0x80);//指针复位
                    position = 0x80;
                    for (i = 0; i < 32; i++) {
                        tab[i] = 0;//tab[]清0
                    }
                    for (i = 0; i < 9; i++) {
                        tab2[i] = 0;//tab2[]清0
                    }
                    val2 = 0;//该清0的都清0
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