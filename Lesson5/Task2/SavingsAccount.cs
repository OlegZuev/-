using System;
using System.IO;

namespace Task2 {
    class SavingsAccount : Account {
        protected int interestRate;

        public SavingsAccount(StreamReader fin) : base(fin) {
            interestRate = Convert.ToInt32(getWord(fin));
        }
        
        public override void accrueInterest() {
            balance *= 1 + interestRate / 100.0;
        }

        public override void withdraw(double sum) {
            if (balance >= sum) {
                balance -= sum;
                Console.WriteLine("Операция совершена. На счету: " + balance + $"(-{sum})");
            } else {
                Console.WriteLine("Недостаточно средств на счету");
            }
        }
        
        public override void addFunds(double sum) {
            balance += sum;
            Console.WriteLine("Операция совершена. На счету: " + balance + $"(+{sum})");
        }

        public override void printInfo(TextWriter fout) {
            fout.WriteLine("Тип счета: Сберегательный");
            fout.WriteLine("ФИО клиента: " + FIO + " Номер счета: " + Number + " Процентная ставка: " +
                           interestRate + "% Дата открытия: " + openDate.ToString("d") + " Срок хранения: " +
                           (TimeSpan.FromTicks(timeOfHolding.Ticks).Days + 365));
        }
    }
}