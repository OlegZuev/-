using System;
using System.IO;

namespace Task2 {
    class Bank {
        public static void countOfPenalty(Account[] accounts) {
            int countOfPenalty = 0;
            foreach (var account in accounts) {
                if (account.GetType() == typeof(CheckingAccount) && ((CheckingAccount) account).CountOfOperation < 0) {
                    countOfPenalty += Math.Abs(((CheckingAccount) account).CountOfOperation);
                }
            }

            Console.WriteLine("Количество штрафов у аккаунтов типа Текущий счет: " + countOfPenalty);
        }

        public static void accrueInterest(Account[] accounts) {
            foreach (var account in accounts) {
                if (account.getClosedDate() == DateTime.Today) {
                    account.accrueInterest();
                }
            }
        }

        public static void transferMoney(Account[] accounts) {
            Account from = null;
            Account to = null;
            Console.Write("Введите номера счетов(откуда, куда) и сумму перевода: ");
            long number1 = Convert.ToInt64(Console.ReadLine());
            long number2 = Convert.ToInt64(Console.ReadLine());
            int sum = Convert.ToInt32(Console.ReadLine());
            foreach (var account in accounts) {
                if (account.Number == number1) {
                    @from = account;
                }

                if (account.Number == number2) {
                    to = account;
                }

                if (@from != null && to != null) {
                    break;
                }
            }

            to?.addFunds(sum);
            @from?.withdraw(sum);
        }

        public static void printInfoInFileOnlyTimedMaturityAccount(Account[] accounts, StreamWriter fout) {
            foreach (var account in accounts) {
                if (account.GetType() == typeof(TimedMaturityAccount)) {
                    account.printInfo(fout);
                }
            }
        }

        public static void printInfoAll(Account[] accounts) {
            foreach (var account in accounts) {
                account.printInfo(Console.Out);
            }
        }

        public static string getWord(StreamReader fin) {
            string word = "";
            char c;
            while (!fin.EndOfStream && (c = (char)fin.Read()) != ' ') {
                if ((c == '\t' || c == '\n' || c == '\r') && word != "") {
                    break;
                }
                if (c == '\t' || c == '\n' || c == '\r') {
                    continue;
                }
                word += c;
            }

            return word;
        }
    }
}