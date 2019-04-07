using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Task1 {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {

        }

        private void textBox1_TextChanged(object sender, EventArgs e) {
            label3.Text = "";
            button4.Enabled = textBox1.Text != "" && textBox2.Text != "" && label1.Text != "";
        }

        private void button4_Click(object sender, EventArgs e) {
            double x = 0, y = 0, result = 0;
            if(!double.TryParse(textBox1.Text, out x) || !double.TryParse(textBox2.Text, out y)) {
                label2.Text = "= Error";
                return;
            }
            switch (label1.Text[0]) {
                case '+':
                    result = x + y;
                    break;
                case '-':
                    result = x - y;
                    break;
                case '*':
                    result = x * y;
                    break;
                case '/':
                    result = x / y;
                    break;
            }

            label3.Text = result.ToString();
        }

        private void button1_Click(object sender, EventArgs e) {
            label1.Text = "+";
            button4.Enabled = textBox1.Text != "" && textBox2.Text != "" && label1.Text != "";
        }

        private void button2_Click(object sender, EventArgs e) {
            label1.Text = "-";
            button4.Enabled = textBox1.Text != "" && textBox2.Text != "" && label1.Text != "";
        }

        private void button3_Click(object sender, EventArgs e) {
            label1.Text = "*";
            button4.Enabled = textBox1.Text != "" && textBox2.Text != "" && label1.Text != "";
        }

        private void button5_Click(object sender, EventArgs e) {
            label1.Text = "/";
            button4.Enabled = textBox1.Text != "" && textBox2.Text != "" && label1.Text != "";
        }

        private void textBox2_TextChanged(object sender, EventArgs e) {
            label3.Text = "";
            button4.Enabled = textBox1.Text != "" && textBox2.Text != "" && label1.Text != "";
        }
    }
}
