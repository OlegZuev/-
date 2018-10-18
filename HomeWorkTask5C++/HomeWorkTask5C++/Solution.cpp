#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int h, m, s;
    cout << "¬ведите данные о текущем времени:\n"
         << "h -> ";
    cin >> h;
    cout << "m -> ";
    cin >> m;
    cout << "s -> ";
    cin >> s;
    cout << fixed << setprecision(2) << "f = " << h * 30.0 + m * 0.5 + s / 120.0 << " градусов.";
}