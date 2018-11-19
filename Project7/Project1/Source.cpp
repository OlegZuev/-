#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int hours = n / 3600;
    int minutes = n % 3600 / 60;
    std::cout << "It is " << hours << " hours " << minutes << " minutes.";
    return 0;
}