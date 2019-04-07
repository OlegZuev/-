using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1 {
    class Deposit {
        public string Number { get; }
        public double Amount { get; private set; }

        public Deposit(string number, double amount) {
            Number = number;
            Amount = amount;
        }
    }
}
