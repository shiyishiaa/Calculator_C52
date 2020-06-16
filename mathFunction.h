#define uchar unsigned char
#define uint unsigned int

uchar position = 0x80;//Һ��ָ��λ�ø����־

void delay(uint t)//��ʱ����
{
    uchar i;
    while (t--)for (i = 110; i > 0; i--);
}

// ������λ������
// ��������ֵΪ������λ��
// ��1.23e6����6��1.23e-5����-5
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

//�׳˺��� ֻ�ܶ�С��35���������м��㣬�������ݴ���
float factorial(uchar dat) {
    float ans = 1;
    while (dat > 0) {
        ans = ans * (float) dat;
        dat = dat - 1;
    }
    return ans;
}

//��ϼ��㺯��
float permutation(uchar n, uchar r) {
    return factorial(n) / factorial(r) / factorial(n - r);
}

//���м��㺯��
float combination(uchar n, uchar r) {
    return factorial(n) / factorial(n - r);
}

//�ۼӼ��㺯��
float accumulation(float dat, float dat2) {
    return (dat + dat2) * (fabs(dat2 - dat) + 1) / 2;
}

