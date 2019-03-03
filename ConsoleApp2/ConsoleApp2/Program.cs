using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp2 {
    class Program {
        static void Main(string[] args) {
            double length = Convert.ToDouble(Console.ReadLine());
            double result = length * 2.54;
            Console.WriteLine((int)(result / 100) + "м " + (int)(result % 100) + "см "
                              + (int)((result * 100) % 100 * 10) / 100.0 + "мм");
        }
    }
}
