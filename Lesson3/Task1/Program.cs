using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1 {
    enum TypeInsurance {
        Home,
        Auto
    }
    
    class Program {
        static void Main(string[] args) {
            Client[] clients = {
                new Client("Сергей", TypeInsurance.Auto, 25000),
                new Client("Марина", TypeInsurance.Home, 31000),
                new Client("Валерий", TypeInsurance.Auto, 25000),
                new Client("Сокол", TypeInsurance.Auto, 55000),
                new Client("Дмитрий", TypeInsurance.Home, 120000),
            };
            InsuranceCompany company = new InsuranceCompany(clients);
            Client[] goodClients = company.getClientsWithSumOver2000();
            foreach (var client in goodClients) {
                client.printInformation();
            }
            company.printCountOfAutoInsurance();
            company.printMaxValueOfInsurance();
        }
    }

    class Client {
        public string Name { get; }
        public TypeInsurance Type { get; }
        public double ValueOfInsurance { get; }

        public Client(string name, TypeInsurance type, double valueOfInsurance) {
            Name = name;
            Type = type;
            ValueOfInsurance = valueOfInsurance;
        }

        public void printInformation() {
            Console.WriteLine("Имя: " + Name + " Вид страховки: " + (Type == 0 ? "Дом" : "Машина") + " Размер страховки: " + ValueOfInsurance);
        }
    }

    class InsuranceCompany {
        Client[] clients;

        public InsuranceCompany(Client[] clients) {
            this.clients = clients;
        }

        public Client[] getClientsWithSumOver2000() {
            Client[] result = new Client[clients.Length];
            for (int i = 0; i < clients.Length; i++) {
                if (clients[i].ValueOfInsurance > 2000) {
                    result[i] = clients[i];
                }
            }
            return result;
        }

        public void printMaxValueOfInsurance() {
            double maxValue = 0;
            foreach (var client in clients) {
                if (client.ValueOfInsurance > maxValue) {
                    maxValue = client.ValueOfInsurance;
                }
            }
            Console.WriteLine("Максимальный размер страховки: " + maxValue);
        }

        public void printCountOfAutoInsurance() {
            int count = 0;
            foreach (var client in clients) {
                if (client.Type == TypeInsurance.Auto) {
                    count++;
                }
            }
            Console.WriteLine("Количество автомобильных страховок: " + count);
        }
    }
}
