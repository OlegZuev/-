using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    class Program {
        static void Main(string[] args) {
            StreamReader fin = new StreamReader("../../input.txt"); //Предусмотрено, что входной файл корректен
            StreamWriter fout = new StreamWriter("../../output.txt");
            Label[] register = new Label[10];
            for (int i = 0; i < register.Length; i++) {
                string data = fin.ReadLine();
                if (data.Split(' ').Length == 2) {
                    register[i] = new Label(data);
                } else {
                    register[i] = new ProLabel(data);
                }
            }
            Clinic clinic = new Clinic(register);
            clinic.printAllInfo();
            string number = clinic.getNumber("Вася");
            clinic.printAllInfoPro(fout);
            clinic.sortLabels();
            fin.Close();
            fout.Close();
        }
    }

    class Clinic {
        Label[] register;

        public Clinic(Label[] register) {
            this.register = register;
        }

        public void printAllInfo() {
            foreach (var label in register) {
                label.printInfo(Console.Out);
            }
        }

        public void printAllInfoPro(StreamWriter fout) {
            foreach (var label in register) {
                if (label is ProLabel) {
                    label.printInfo(Console.Out);
                    label.printInfo(fout);
                }
            }
        }

        public string getNumber(string nickname) {
            foreach (var label in register) {
                if (label.Nickname == nickname) {
                    return label.Number;
                }
            }

            return null;
        }

        public void sortLabels() {
            for (int i = 1; i < register.Length; i++) {
                for (int j = 0; j < register.Length - i; j++) {
                    if (string.CompareOrdinal(register[j].Nickname, register[j + 1].Nickname) > 0) {
                        Label temp = register[j];
                        register[j] = register[j + 1];
                        register[j + 1] = temp;
                    }
                }
            }
        }
    }

    class Label {
        public string Nickname { get; }
        public string Number { get; }

        public Label(string data) {
            string[] temp = data.Split(' ');
            Nickname = temp[0];
            Number = temp[1];
        }

        public virtual void printInfo(TextWriter fout) {
            fout.WriteLine("Кличка: " + Nickname + " Телефонный номер: " + Number);
        }
    }

    class ProLabel : Label {
        public string registerNumber { get; }

        public ProLabel(string data) : base(data) {
            registerNumber = data.Split(' ')[2];
        }

        public override void printInfo(TextWriter fout) {
            fout.WriteLine("Кличка: " + Nickname + " Телефонный номер: " + Number +
                              " Телефон отдела регистрации: " + registerNumber);
        }
    }
 }
