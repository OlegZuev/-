using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Task3 {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e) {
            label3.Text = "Материал: " + (radioButton1.Checked ? radioButton1.Text : radioButton2.Text) + "\n";
            if (!double.TryParse(textBox1.Text, out var height) || !double.TryParse(textBox2.Text, out var width)) {
                label3.Text += "Стоимость: ERROR";
            } else if (radioButton1.Checked) {
                label3.Text += "Стоимость: " + height * width / 5 * 0.95;
            } else if (radioButton2.Checked) {
                label3.Text += "Стоимость: " + height * width / 5 * 0.9;
            }
        }

        private void reaction(object sender, EventArgs e) {
            label3.Text = "";
            button1.Enabled = textBox1.Text != "" && textBox2.Text != "" && (radioButton1.Checked || radioButton2.Checked);
        }
    }
}
