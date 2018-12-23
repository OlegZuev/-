// #include <iostream>
// using namespace std;
//
// double countSequence(double a, int n);
//
// int main()
// {
//     int n;
//     double a;
//     cin >> a >> n;
//     cout << fixed << countSequence(a, n);
//     return 0;
// }
//
// double countSequence(double a, int n)
// {
//     double divider = a * a;
//     int multi = 1;
//     double sum = 0;
//     for (int i = 0; i < n; ++i) {
//         sum += multi / divider;
//         multi *= (i + 1) * 2 * ((i + 1) * 2 + 1);
//         divider *= a * a;
//     }
//     return sum;
// }