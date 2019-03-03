using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task3 {
    class Program {
        static void Main(string[] args) {
            List<Client> clients = new List<Client> {
                new Client("Заводской", 5574_654729,
                    new List<Deposit> {new Deposit(1235475, 73500, 2.5, new DateTime(2015, 7, 25), new DateTime(2017, 7, 25))}),
                new Client("Кузнецов", 6626_950021,
                    new List<Deposit> {new Deposit(1235475, 35000, 1, new DateTime(2016, 9, 29), new DateTime(2019, 9, 29))}),
                new Client("Николаев", 5174_654729,
                    new List<Deposit> { new Deposit(1235475, 57000, 2, new DateTime(2017, 5, 7), new DateTime(2019, 11, 7))}),
                new Client("Стокарев", 3571_124759,
                    new List<Deposit> { new Deposit(1235475, 134000, 3, new DateTime(2014, 3, 15), new DateTime(2017, 3, 15))}),
                new Client("Смирнов", 1524_152729,
                    new List<Deposit> { new Deposit(1235475, 258000, 4, new DateTime(2018, 6, 13), new DateTime(2019, 6, 13))})
            };

            Bank bank = new Bank(clients);
            bank.printClientWithMaxPercent();
            bank.printMinDeposit();
            clients.Add(new Client("Ковалевский", 7521_654729,
                    new List<Deposit> { new Deposit(1235475, 73500, 2.5, new DateTime(2015, 7, 25), new DateTime(2017, 7, 25))}));
            clients.Add(new Client("Кириенко", 5271_654729,
                    new List<Deposit> { new Deposit(1235475, 73500, 2.5, new DateTime(2015, 7, 25), new DateTime(2017, 7, 25)) }));
            bank.deleteClientsWithClosingDeposits();
            List<Client> trustedClients= bank.getClientsWithLongDeposit();
            Console.WriteLine("Вклады со сроком 2 и более лет открыты у:");
            foreach (var client in trustedClients) {
                Console.WriteLine(client.Lastname);
            }
        }
    }

    class Client {
        public string Lastname { get; }
        public long PassportNumber { get; }
        public int CountDeposits => Deposits.Capacity;
        public List<Deposit> Deposits { get; }

        public Client(string lastname, long passportNumber, List<Deposit> deposits) {
            Lastname = lastname;
            PassportNumber = passportNumber;
            Deposits = deposits;
        }

        public Deposit getDepositWithMaxPercent() {
            Deposit goodDeposit = Deposits[0];
            foreach (var deposit in Deposits) {
                if (deposit.YearPercent > goodDeposit.YearPercent) {
                    goodDeposit = deposit;
                }
            }

            return goodDeposit;
        }

        public Deposit getDepositWithMinValue() {
            Deposit poorDeposit = Deposits[0];
            foreach (var deposit in Deposits) {
                if (deposit.Value < poorDeposit.Value) {
                    poorDeposit = deposit;
                }
            }

            return poorDeposit;
        }
    }

    class Deposit {
        public long Number { get; }
        public double Value { get; set; }
        public double YearPercent { get; }
        public DateTime OpeningDate { get; }
        public DateTime ClosingDate { get; }

        public Deposit(long number, double value, double yearPercent, DateTime openingDate, DateTime closingDate) {
            Number = number;
            Value = value;
            YearPercent = yearPercent;
            OpeningDate = openingDate;
            ClosingDate = closingDate;
        }

        public bool checkMoney(double value) {
            return value < Value;
        }
    }

    class Bank {
        List <Client> clients;

        public Bank(List<Client> clients) {
            this.clients = clients;
        }

        public void printClientWithMaxPercent() {
            Client goodClient = clients[0];
            foreach (var client in clients) {
                if (client.getDepositWithMaxPercent().YearPercent > goodClient.getDepositWithMaxPercent().YearPercent) {
                    goodClient = client;
                }
            }
            Console.WriteLine("Наибольший процент по депозиту принадлежит " + goodClient.Lastname +
                              " в размере " + goodClient.getDepositWithMaxPercent().YearPercent + "%");
        }

        public void printMinDeposit() {
            Client poorClient = clients[0];
            foreach (var client in clients) {
                if (client.getDepositWithMinValue().Value < poorClient.getDepositWithMinValue().Value) {
                    poorClient = client;
                }
            }

            Deposit poorDeposit = poorClient.getDepositWithMinValue();
            Console.WriteLine("Номер счёта с минимальным вкладом: " + poorDeposit.Number + "\n" +
                              "Год открытия: " + poorDeposit.OpeningDate.Year);
        }

        public void transferMoney(Deposit from, Deposit to, double amount) {
            if (from.checkMoney(amount)) {
                from.Value -= amount;
                to.Value += amount;
            }
        }

        public List<Client> getClientsWithLongDeposit() {
            List<Client> trustedClients = new List<Client>();
            foreach (var client in clients) {
                foreach (var deposit in client.Deposits) {
                    if (deposit.ClosingDate.Subtract(deposit.OpeningDate) > TimeSpan.FromDays(365 * 2)) {
                        trustedClients.Add(client);
                        break;
                    }
                }
            }

            return trustedClients;
        }

        public void deleteClientsWithClosingDeposits() {
            foreach (var client in clients.ToList()) {
                bool isOpenDeposit = false;
                foreach (var deposit in client.Deposits) {
                    if (deposit.ClosingDate > DateTime.Now) {
                        isOpenDeposit = true;
                    }
                }
                if (!isOpenDeposit) {
                    clients.Remove(client);
                }
            }
        }
    }
}
