using System;

namespace Task3 {
    class Program {
        static void Main(string[] args) {
            Journalist[] journalists = {
                new Journalist("Сергей", 25000),
                new Journalist("Илья", 27000),
                new Journalist("Матвей", 25600),
                new Journalist("Василий", 29600),
                new Journalist("Елена", 28400)
            };
            Newspaper star = new Newspaper("Звезда", 1000, 5, journalists);
            star.printInformation();
            star.printSumOfSalary();
            star.poorJournalists();
            
        }
    }

    class Newspaper {
        string name;
        int numberOfCopies;
        int numberPolos;
        Journalist[] journalists;

        public Newspaper(string name, int numberOfCopies, int numberPolos, Journalist[] journalists) {
            this.name = name;
            this.numberOfCopies = numberOfCopies;
            this.numberPolos = numberPolos;
            this.journalists = journalists;
        }

        public void printInformation() {
            Console.WriteLine("Название: " + name + "\n" +
                              "Тираж: " + numberOfCopies + "\n" +
                              "Количество полос: " + numberPolos + "\n" +
                              "Журналисты:");
            foreach (var t in journalists) {
                t.printInformation();
            }
        }

        public double sumOfSalary() {
            double sumOfSalary = 0;
            foreach (var t in journalists) {
                sumOfSalary += t.Salary;
            }
            return sumOfSalary;
        }

        public void printSumOfSalary() {
            Console.WriteLine("Суммарная зарплата: " + sumOfSalary());
        }

        public void poorJournalists() {
            double avgSalary = sumOfSalary() / journalists.Length;
            Console.WriteLine("Маленькая зарплату имеют:");
            foreach (var t in journalists) {
                if (t.Salary < avgSalary) {
                    Console.WriteLine(t.Name);
                }
            }
        }

        public void increaseSalary(int percent) {
            double avgSalary = sumOfSalary() / journalists.Length;
            foreach (var t in journalists) {
                if (t.Salary < avgSalary) {
                    t.changeSalary(percent);
                }
            }
        }

        public void decreaseSalary(int percent) {
            double avgSalary = sumOfSalary() / journalists.Length;
            foreach (var t in journalists) {
                if (t.Salary > avgSalary) {
                    t.changeSalary(-percent);
                }
            }
        }

        public void getJournalistWithThatSalary(double salary) {
            Console.WriteLine("Зарплату в " + salary + " получают:");
            foreach (var t in journalists) {
                if (Math.Abs(t.Salary - salary) < 0.001) {
                    Console.WriteLine(t.Name);                   
                }
            }
        }
    }

    class Journalist {
        public double Salary { get; private set; }

        public string Name { get; }

        public Journalist(string name, double salary) {
            Name = Name;
            Salary = salary;
        }

        public void changeSalary(int percent) {
            Salary *= 1 + percent / 100.0;
        }

        public void printInformation() {
            Console.WriteLine("Имя: " + Name + " Зарплата: " + Salary);
        }
    }
}
