// #include <iostream>
// #include <string>
// using namespace std;
//
// int main()
// {
//     string s;
//     cin >> s;
//     string str = s + s + s;
//     for (int i = 4; i < 8; ++i) {
//         if (str[i] == 'g') {
//             if (str[i - 1] == 'b') {
//                 switch (str[i + 1]) {
//                 case 'g':
//                     cout << 1;
//                     break;
//                 case 'w':
//                     cout << 2;
//                     break;
//                 case 'r':
//                     cout << 4;
//                     break;
//                 }
//             }
//             if (str[i - 1] == 'w') {
//                 switch (str[i + 1]) {
//                 case 'r':
//                     cout << 3;
//                     break;
//                 case 'b':
//                     cout << 6;
//                     break;
//                 }
//             }
//             if (str[i - 1] == 'r') {
//                 cout << 5;
//             }
//         }
//     }
// }