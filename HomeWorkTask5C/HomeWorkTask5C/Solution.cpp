#include <stdio.h>

int main()
{
    int h, m, s;
    printf("������� ������ � ������� �������:\n"
           "h -> ");
    scanf("%d", &h);
    printf("m -> ");
    scanf("%d", &m);
    printf("s -> ");
    scanf("%d", &s);
    printf("f = %.2f ��������.", h * 30.0 + m * 0.5 + s / 120.0);
    return 0;
}