using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1 {
    class Program {
        static void Main(string[] args) {
            StreamReader fin1 = new StreamReader("../../Planes.txt");
            StreamReader fin2 = new StreamReader("../../Autos.txt");
            StreamWriter fout = new StreamWriter("../../Result.txt");
            Transport[] planes = new Transport[10];
            List<Transport> autos = new List<Transport>();
            for (int i = 0; i < 10; i++) {
                planes[i] = new Plane(fin1);
            }
            for (int i = 0; i < 10; i++) {
                autos.Add(new Auto(fin2));
            }
            Console.Write("Введите номер запрашиваемого самолёта(от 0 до 9): ");
            int n = Convert.ToInt32(Console.ReadLine());
            fout.WriteLine($"Мощность и максимальная высота полёта самолёта №{n}: " + planes[n].Power + 
                           " л.с. и "+((Plane)planes[n]).MaxHeight + " м.");
            Transport superCar = autos[0];
            foreach (var auto in autos) {
                if (superCar.Cost < auto.Cost) {
                    superCar = auto;
                }
            }
            fout.Write("Состояние техосмотра самой дорогой машины: " + (((Auto)superCar).IsInspectionPassed ? "пройден" : "не пройден"));
            fout.Close();
            fin1.Close();
            fin2.Close();
        }
    }

    class Transport {
        public int Power { get; }
        public int Cost { get; }
        public int Number { get; }
        public string Mark { get; }

        public Transport(StreamReader fin) {
            Power = Convert.ToInt32(getWord(fin));
            Cost = Convert.ToInt32(getWord(fin));
            Number = Convert.ToInt32(getWord(fin));
            Mark = getWord(fin);
        }

        protected string getWord(StreamReader fin) {
            string word = "";
            char c;
            while (!fin.EndOfStream && (c = (char) fin.Read()) != ' ') {
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

    class Plane : Transport {
        public int MaxHeight { get; }

        public Plane(StreamReader fin) : base(fin) {
            MaxHeight = Convert.ToInt32(getWord(fin));
        }
    }

    class Auto : Transport {
        public int Mileage { get; }
        public bool IsInspectionPassed { get; }

        public Auto(StreamReader fin) : base(fin) {
            Mileage = Convert.ToInt32(getWord(fin));
            IsInspectionPassed = Convert.ToBoolean(getWord(fin));
        }
    }
}
