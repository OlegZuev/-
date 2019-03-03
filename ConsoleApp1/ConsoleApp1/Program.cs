using System;

namespace ConsoleApp1
{
    class Program
    {
        public static void Main(string[] args)
        {
            double length = Convert.ToDouble(Console.ReadLine());
            double result = length * 2.54;
            Console.WriteLine((int)(result / 100) + "м " + (int)(result % 100) + "см "
                              + (int)(result * 100 % 100) / 10.0 + "мм.");
        }
    }
}
