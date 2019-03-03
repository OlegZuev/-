using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2 {

    class Program {
        static void Main(string[] args) {
            Client[] clients = {
                new Client("Заводской", 5574_654729, new[]{new Deposit(1235475, 50000)}), 
                new Client("Кузнецов", 6626_950021, new[]{new Deposit(3224753, 150000)}), 
                new Client("Николаев", 5174_654729, new[]{new Deposit(1423677, 52000)}), 
                new Client("Стокарев", 3571_124759, new[]{new Deposit(8123470, 160000)}), 
                new Client("Смирнов", 1524_152729, new[]{new Deposit(1349553, 59000)}), 
            };

            Bank bank = new Bank(clients);
            bank.printCapital();
            bank.transferMoney(clients[0].Deposits[0], clients[2].Deposits[0], 5000);
            bank.giveRewardClientWithLargerDeposit();
        }
    }

    class Client {
        public string Lastname { get; }
        public long PassportNumber { get; }
        public int CountDeposits => Deposits.Length;
        public Deposit[] Deposits { get; }

        public Client(string lastname, long passportNumber, Deposit[] deposits) {
            Lastname = lastname;
            PassportNumber = passportNumber;
            Deposits = deposits;
        }

        public Deposit getLargerDeposit() {
            Deposit goodDeposit = Deposits[0];
            foreach (var deposit in Deposits) {
                if (deposit.Value > goodDeposit.Value) {
                    goodDeposit = deposit;
                }
            }

            return goodDeposit;
        }
    }

    class Deposit {
        public long Number { get; }
        public double Value { get; set; }

        public Deposit(long number, double value) {
            Number = number;
            Value = value;
        }

        public bool checkMoney(double value) {
            return value < Value;
        }
    }

    class Bank {
        Client[] clients;

        public Bank(Client[] clients) {
            this.clients = clients;
        }

        public void giveRewardClientWithLargerDeposit() {
            Client goodClient = clients[0];
            foreach (var client in clients) {
                if (client.getLargerDeposit().Value > goodClient.getLargerDeposit().Value) {
                    goodClient = client;
                }
            }
            goodClient.getLargerDeposit().Value *= 1.02;
        }

        public void printCapital() {
            double sumOfDeposit = 0.0;
            foreach (var client in clients) {
                foreach (var deposit in client.Deposits) {
                    sumOfDeposit += deposit.Value;
                }
            }
            Console.WriteLine("Сумма вкладов всех вкладчиков: " + sumOfDeposit);
        }

        public void transferMoney(Deposit from, Deposit to, double amount) {
            if (from.checkMoney(amount)) {
                from.Value -= amount;
                to.Value += amount;
            }
        }
    }
}
