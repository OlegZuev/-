using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    class Program {
        static void Main(string[] args) {
            StreamReader fin = new StreamReader("../../input.txt");
            DateTime before = DateTime.Now;
            string s;
            while (!fin.EndOfStream) {
                s = fin.ReadLine();
            }
//            int c;
//            while (!fin.EndOfStream) {
//                c = fin.Read();
//            }
            DateTime after = DateTime.Now;
            Console.WriteLine("Время в мс: " + (after - before).Milliseconds);
        }
    }
}
