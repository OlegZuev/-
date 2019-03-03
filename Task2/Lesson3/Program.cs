using System;

namespace Lesson3 {
    class Program {
        static void Main(string[] args) {
            Auto mersedes = new Auto("Мерседес", 600, "ГР572");
            mersedes.start();
            mersedes.stop();
            Auto folcvagen = new Auto("Фольцваген", 2201, "ГР652-5");
            folcvagen.start();
            folcvagen.stop();
        }
    }

    class Auto {
        string mark;
        int model;
        string number;

        public Auto(string mark, int model, string number) {
            this.mark = mark;
            this.model = model;
            this.number = number;
        }

        public void start() {
            Console.WriteLine("Машина " + mark + " " + model + " завелась.");
        }

        public void stop() {
            Console.WriteLine("Машина " + mark + " " + model + " остановилась.");
        }
    }
}