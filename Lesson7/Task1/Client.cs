using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1 {
    class Client {
        public string Lastname { get; }
        public string Passport { get; }
        public Deposit[] Deposits { get; }

        public Client(string lastname, string passport, Deposit[] deposits) {
            Lastname = lastname;
            Passport = passport;
            Deposits = deposits;
        }
    }
}
