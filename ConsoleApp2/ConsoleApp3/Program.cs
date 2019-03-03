using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing.Reader;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp3 {
    class Program {
        static void Main(string[] args) {
            int t1 = Convert.ToInt32(Console.ReadLine());
            int v1 = Convert.ToInt32(Console.ReadLine());
            int t2 = Convert.ToInt32(Console.ReadLine());
            int v2 = Convert.ToInt32(Console.ReadLine());
            int t3 = Convert.ToInt32(Console.ReadLine());
            int v3 = Convert.ToInt32(Console.ReadLine());
            double halfPath = (t1 * v1 + t2 * v2 + t3 * v3) / 2.0;
            int s1 = t1 * v1;
            int s2 = t2 * v2;

            double time = 0.0;
            if (halfPath < s1) {
                time += halfPath / v1;
            } else if (halfPath < s1 + s2) {
                halfPath -= s1;
                time += t1 + halfPath / v2;
            } else {
                halfPath -= s1 + s2;
                time += t1 + t2 + halfPath / v3;
            }
            Console.WriteLine(time);
        }
    }
}
