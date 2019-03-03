using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task4 {
    class Program {
        static void Main(string[] args) {
            Auto[] autos = {
                new Auto(572, 2500000, true), 
                new Auto(242, 3100000, true), 
                new Auto(726, 7502500, false), 
                new Auto(572, 2600000, true), 
                new Auto(632, 5570000, false), 
                new Auto(332, 1500000, true), 
                new Auto(777, 8150500, true), 
                new Auto(156, 4332000, false), 
            };
            GIBDD gibdd = new GIBDD(autos);
            gibdd.printAutoNotPassedInspection();
        }
    }

    class GIBDD {
        Auto[] autos;

        public GIBDD(Auto[] autos) {
            this.autos = autos;
        }

        public double calcTaxWithAuto(int number) {
            foreach (var auto in autos) {
                if (auto.Number == number) {
                    return auto.Value * 0.04;
                }
            }
            return 0.0;
        }

        public void printAutoNotPassedInspection() {
            Console.WriteLine("Не прошли техосмотр автомобили под номерами:");
            foreach (var auto in autos) {
                if (!auto.CheckInspection) {
                    Console.WriteLine(auto.Number);
                }
            }
        }

        public void checkInspectionWithWealthAuto() {
            Auto autoWithMaxValue = autos[0];
            foreach (var auto in autos) {
                if (autoWithMaxValue.Value < auto.Value) {
                    autoWithMaxValue = auto;
                }
            }
            if (autoWithMaxValue.CheckInspection) {
                Console.WriteLine("Автомобиль под номером: " + autoWithMaxValue.Number + " прошёл техосмотр.");
            } else {
                Console.WriteLine("Автомобиль под номером: " + autoWithMaxValue.Number + " не прошёл техосмотр.");
            }
        }

        public void printInformation() {
            Console.WriteLine("Информация об автомобилях:");
            foreach (var auto in autos) {
                Console.WriteLine("Номер: " + auto.Number + " Стоимость: " + auto.Value +
                                  " Техосмотр: " + (auto.CheckInspection ? "пройден" : "не пройден"));
            }
        }
    }

    class Auto {
        public int Number { get; }
        public double Value { get; }
        public bool CheckInspection { get; }

        public Auto(int number, double value, bool checkInspection) {
            Number = number;
            Value = value;
            CheckInspection = checkInspection;
        }
    }
}
