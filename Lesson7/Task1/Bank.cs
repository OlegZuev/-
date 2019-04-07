using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Task1 {
    class Bank {
        public List<Client> Clients;

        public Bank() {
            StreamReader fin;
            try {
                fin = new StreamReader("../../input.txt");
            } catch(Exception e) {
                MessageBox.Show(e.Message);
                return;
            }

            string line;
            while ((line = fin.ReadLine()) != null) {
                string[] data = line.Split(' ');
                Deposit[] deposits = new Deposit[int.Parse(data[2])];
                for (int i = 0; i < deposits.Length; i++) {
                    string[] temp = fin.ReadLine().Split(' ');
                    deposits[i] = new Deposit(temp[0], double.Parse(temp[1]));
                }
                Clients.Add(new Client(data[0], data[1], deposits));
            }            
        }
    }
}
