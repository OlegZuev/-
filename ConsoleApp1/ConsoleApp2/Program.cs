using System;

namespace ConsoleApp2 {
    class Program {
        public static void Main(string[] args) {
            int t1 = Convert.ToInt32(Console.ReadLine());
            int v1 = Convert.ToInt32(Console.ReadLine());
            int t2 = Convert.ToInt32(Console.ReadLine());
            int v2 = Convert.ToInt32(Console.ReadLine());
            int t3 = Convert.ToInt32(Console.ReadLine());
            int v3 = Convert.ToInt32(Console.ReadLine());
            double path = (t1 * v1 + t2 * v2 + t3 * v3) / 2.0;
            double time = 0;
            int s1 = t1 * v1;
            int s2 = t2 * v2;
            int s3 = t3 * v3;

            if (s1 >= path) {
                time += path / v1;
            } else if (s1 + s2 >= path) {
                path -= s1;
                time += t1 + path / v2;
            } else if (s1 + s2 + s3 >= path) {
                path -= s1 - s2;
                time += t1 + t2 + path / v3;
            }       
            Console.WriteLine(time);
        }
    }
}