using System;
using System.IO;

namespace Task2 {
    abstract class Account {
        protected string FIO;
        public long Number { get; }
        protected double balance;
        
        protected DateTime openDate;
        protected DateTime timeOfHolding;

        protected Account(StreamReader fin) {
            FIO = getWord(fin) + " " + getWord(fin) + " " + getWord(fin);
            Number = Convert.ToInt64(getWord(fin));
            balance = Convert.ToInt32(getWord(fin));
            openDate = DateTime.Parse(getWord(fin));
            timeOfHolding = DateTime.Parse(getWord(fin));
        }

        public abstract void withdraw(double sum);

        public abstract void addFunds(double sum);

        public abstract void accrueInterest();

        public abstract void printInfo(TextWriter fout);

        public DateTime getClosedDate() {
            return openDate.Add(timeOfHolding.TimeOfDay);
        }

        protected string getWord(StreamReader fin) {
            string word = "";
            char c;
            while (!fin.EndOfStream && (c = (char)fin.Read()) != ' ') {
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
}