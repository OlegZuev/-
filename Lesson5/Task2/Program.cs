using System;
using System.IO;

namespace Task2 {
    class Program {
        static void Main(string[] args) {
            StreamReader fin = new StreamReader("../../Accounts.txt");
            StreamWriter fout = new StreamWriter("../../Result.txt");
            int n = Convert.ToInt32(fin.ReadLine());
            Account[] accounts = new Account[n];
            for (int i = 0; i < n; i++) {
                string type = Bank.getWord(fin);
                switch (type) {
                    case "Checking":
                        accounts[i] = new CheckingAccount(fin);
                        break;
                    case "Saving":
                        accounts[i] = new SavingsAccount(fin);
                        break;
                    case "Timed":
                        accounts[i] = new TimedMaturityAccount(fin);
                        break;
                }
            }
            Bank.printInfoAll(accounts);
            Bank.printInfoInFileOnlyTimedMaturityAccount(accounts, fout);
            Bank.transferMoney(accounts);
            Bank.accrueInterest(accounts);
            Bank.countOfPenalty(accounts);
            fin.Close();
            fout.Close();
        }
    }
}
