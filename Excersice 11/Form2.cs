using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form2 : Form
    {
        bool spaceEnabled = false;
        int numOperations = 0;
        int result;
        public Form2()
        {
            InitializeComponent();
        }

        private static int EvaluatePostfix(string postfix)
        {
            // System.Windows.Forms.MessageBox.Show("'"+postfix+"'");
            Stack<int> stack = new Stack<int>();
            string[] tokens = postfix.Split(' ');

            foreach (string token in tokens)
            {
                if (int.TryParse(token, out int number))
                {
                    stack.Push(number);
                }
                else
                {
                    int operand2 = stack.Pop();
                    int operand1 = stack.Pop();

                    switch (token)
                    {
                        case "+":
                            stack.Push(operand1 + operand2);
                            break;
                        case "-":
                            stack.Push(operand1 - operand2);
                            break;
                        case "*":
                            stack.Push(operand1 * operand2);
                            break;
                        case "/":
                            stack.Push(operand1 / operand2);
                            break;
                    }
                }
            }

            return stack.Pop();
        }

        private void button17_Click(object sender, EventArgs e)
        {
            string postfix = textBox1.Text;
            string lastChar = postfix.Substring(postfix.Length - 1);
            // System.Windows.Forms.MessageBox.Show(lastChar);
            // System.Windows.Forms.MessageBox.Show(numOperations.ToString());
            if (numOperations == 1)
            {
                postfix = postfix.TrimEnd();
                result = EvaluatePostfix(postfix);
                textBox1.Text = result.ToString();
            }
            else 
            {
                if (lastChar != " ")
                {
                    result = EvaluatePostfix(postfix);
                    textBox1.Text = result.ToString();
                }
                else 
                {
                    System.Windows.Forms.MessageBox.Show("The number of Operators and Numbers is not congruent.");
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text += "1";
            spaceEnabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text += "2";
            spaceEnabled = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBox1.Text += "3";
            spaceEnabled = true;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox1.Text += "4";
            spaceEnabled = true;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            textBox1.Text += "5";
            spaceEnabled = true;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            textBox1.Text += "6";
            spaceEnabled = true;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            textBox1.Text += "7";
            spaceEnabled = true;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            textBox1.Text += "8";
            spaceEnabled = true;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            textBox1.Text += "9";
            spaceEnabled = true;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            textBox1.Text += "0";
            spaceEnabled = true;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (spaceEnabled)
            {
                textBox1.Text += " ";
                spaceEnabled = false;
                numOperations++;
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("You cannot enter more Spaces.");
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            spaceEnabled = false;
            numOperations = 0;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            if (!spaceEnabled)
            {
                textBox1.Text += "+ ";
                numOperations--;
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Enter a Number or other Symbol.");
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            if (!spaceEnabled)
            {
                textBox1.Text += "- ";
                numOperations--;
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Enter a Number or other Symbol.");
            }
        }

        private void button15_Click(object sender, EventArgs e)
        {
            if (!spaceEnabled)
            {
                textBox1.Text += "* ";
                numOperations--;
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Enter a Number or other Symbol.");
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            if (!spaceEnabled)
            {
                textBox1.Text += "/ ";
                numOperations--;
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Enter a Number or other Symbol.");
            }
        }
    }
}
