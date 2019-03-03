using System;
using System.IO;

namespace Task2 {
    class TimedMaturityAccount : SavingsAccount {
        public TimedMaturityAccount(StreamReader fin) : base(fin) { }

        public override void withdraw(double sum) {
            if (balance >= sum) {
                balance -= sum;
                Console.WriteLine("Операция совершена. На счету: " + balance + $"(-{sum})");
                DateTime closedDate = openDate.Add(timeOfHolding.TimeOfDay);
                if (DateTime.Now < closedDate) {
                    Console.WriteLine("Поскольку снятие денежных средств приходится до окончания " +
                                      "срока вклада, была удержана сумма в размере 5%: " + sum * 0.05);
                }
            } else {
                Console.WriteLine("Недостаточно средств на счету");
            }
        }

        public override void printInfo(TextWriter fout) {
            fout.WriteLine("Тип счета: Со временем погашением платежа");
            fout.WriteLine("ФИО клиента: " + FIO + " Номер счета: " + Number + " Процентная ставка: " +
                           interestRate + "% Дата открытия: " + openDate.ToString("d") + " Срок хранения: " +
                           (TimeSpan.FromTicks(timeOfHolding.Ticks).Days + 365));
        }
    }
}