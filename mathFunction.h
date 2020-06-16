#define uchar unsigned char
#define uint unsigned int

uchar position = 0x80;//液晶指针位置跟随标志

void delay(uint t)//延时函数
{
    uchar i;
    while (t--)for (i = 110; i > 0; i--);
}

// 浮点数位数计算
// 函数返回值为浮点数位数
// 如1.23e6返回6，1.23e-5返回-5
char floatTail(float dat) {
    char i = 0;
    if (dat < 0)dat = 0 - dat;
    if (dat > 1) {
        while (dat >= 1) {
            dat = dat / 10;
            i++;
        }
        i = (char) (i - 1);
    } else if ((dat > 0) && dat <= 1) {
        while (dat < 1) {
            dat = dat * 10;
            i++;
        }
        return i = (char) (0 - i);
    }
    return i;
}

//阶乘函数 只能对小于35的整数进行计算，否则数据错误
float factorial(uchar dat) {
    float ans = 1;
    while (dat > 0) {
        ans = ans * (float) dat;
        dat = dat - 1;
    }
    return ans;
}

//组合计算函数
float permutation(uchar n, uchar r) {
    return factorial(n) / factorial(r) / factorial(n - r);
}

//排列计算函数
float combination(uchar n, uchar r) {
    return factorial(n) / factorial(n - r);
}

//累加计算函数
float accumulation(float dat, float dat2) {
    return (dat + dat2) * (fabs(dat2 - dat) + 1) / 2;
}

