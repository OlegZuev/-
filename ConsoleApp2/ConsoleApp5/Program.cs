using System;

namespace ConsoleApp5 {
    class Program {
        public static void Main(string[] args) {
            Console.Write("Введите желаемую сумму в рублях (Купюры: 5000, 1000, 500, 100, 50, 10): ");
            int money = Convert.ToInt32(Console.ReadLine());
            int[] countOfBills = new int[6];
            int[] bills = {5000, 1000, 500, 100, 50, 10};
            for (int i = 0; money >= 10; i++) {
                countOfBills[i] = money / bills[i];
                money -= countOfBills[i] * bills[i];
            }
            Console.WriteLine("Банкоматом будет выдано:");
            for (int i = 0; i < bills.Length; i++) {
                if (countOfBills[i] > 0) {
                    Console.WriteLine("Купюр в " + bills[i] + ": " + countOfBills[i]);
                }
            }
        }
    }
}
