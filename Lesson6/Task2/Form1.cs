using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Task2 {
    public partial class Form1 : Form {
        double sandwich = 30.0;
        double potato = 25.0;
        double sauсe = 6.0;
        double cocaCola = 40.0;

        public Form1() {
            InitializeComponent();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e) {
            recalculation(checkBox1, sandwich);
        }    

        private void checkBox2_CheckedChanged(object sender, EventArgs e) {
            recalculation(checkBox2, potato);
            checkBox3.Enabled = checkBox2.Checked;
            if (!checkBox3.Enabled && checkBox3.Checked) {
                checkBox3.Checked = checkBox3.Enabled;
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e) {
            recalculation(checkBox3, sauсe);
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e) {
            recalculation(checkBox4, cocaCola);
        }

        void recalculation(CheckBox checkBox, double price) {
            if (checkBox.Checked) {
                if (label2.Text == "") {
                    label2.Text = "" + 0;
                }

                label2.Text = (double.Parse(label2.Text) + price).ToString();
            } else {
                label2.Text = (double.Parse(label2.Text) - price).ToString();
                if (label2.Text == "0") {
                    label2.Text = "";
                }
            }
        }

        private void button1_Click(object sender, EventArgs e) {
            if (checkBox1.Checked && checkBox2.Checked && checkBox3.Checked && checkBox4.Checked) {
                MessageBox.Show("Вам предоставляется скидка 10% Платить: " + double.Parse(label2.Text) * 0.9, "Заказ");
            } else {
                MessageBox.Show("Платить: " + label2.Text, "Заказ");
            }
        }
    }
}
