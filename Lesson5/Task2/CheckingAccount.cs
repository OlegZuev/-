using System;
using System.IO;

namespace Task2 {
    class CheckingAccount : Account {
        public int CountOfOperation { get; private set; }

        public CheckingAccount(StreamReader fin) : base(fin) {
            CountOfOperation = 30;
        }

        public override void accrueInterest() { /* Do nothing */}

        public override void withdraw(double sum) {
            if (balance >= sum) {
                balance -= sum;
                if (CountOfOperation <= 0) {
                    Console.WriteLine("Количество операций исчерпано. Наложен штраф в 5% от суммы.");
                    balance -= sum * 0.05;
                    sum *= 1.05;
                }
                Console.WriteLine("Операция совершена. На счету: " + balance + $"(-{sum})");
                CountOfOperation--;
            } else {
                Console.WriteLine("Недостаточно средств на счету");
            }
        }

        public override void addFunds(double sum) {
            balance += sum;
            if (CountOfOperation <= 0) {
                Console.WriteLine("Количество операций исчерпано. Наложен штраф в 5% от суммы.");
                balance -= sum * 0.05;
                sum *= 0.95;
            }
            Console.WriteLine("Операция совершена. На счету: " + balance + $"(+{sum})");
            CountOfOperation--;
        }

        public override void printInfo(TextWriter fout) {
            fout.WriteLine("Тип счета: Текущий");
            fout.WriteLine("ФИО клиента: " + FIO + " Номер счета: " + Number +
                           " Дата открытия: " + openDate.ToString("d") + " Срок хранения: " +
                           (TimeSpan.FromTicks(timeOfHolding.Ticks).Days + 365));
        }
    }
}