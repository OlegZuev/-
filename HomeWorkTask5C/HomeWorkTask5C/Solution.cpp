#include <stdio.h>

int main()
{
    int h, m, s;
    printf("¬ведите данные о текущем времени:\n"
           "h -> ");
    scanf("%d", &h);
    printf("m -> ");
    scanf("%d", &m);
    printf("s -> ");
    scanf("%d", &s);
    printf("f = %.2f градусов.", h * 30.0 + m * 0.5 + s / 120.0);
    return 0;
}