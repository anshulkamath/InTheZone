using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Vex_Auton_Select
{
    public partial class Form1 : Form
    {
        private AutonAction[] actions;
        public Form1()
        {
            InitializeComponent();
            actions = new AutonAction[0];
        }

        private void addAction(int x, int y)
        {
            Button temp = new Button();
            temp.AutoSize = true;
            temp.Location = new System.Drawing.Point(x, y);
            temp.Name = "Auton Action " + (actions.Length+1);
            temp.Size = new System.Drawing.Size(35, 13);
            temp.TabIndex = 1;
            temp.Text = "Auton Action " + (actions.Length + 1);
            temp.Enabled = true;
            temp.Visible = true;
            temp.Show();

            //pictureBox1.Enabled = false;
            this.Controls.Add(temp);
            temp.BringToFront();
            AutonAction[] tempActions = new AutonAction[actions.Length + 1];
            for(int i = 0; i<actions.Length; i++)
            {
                tempActions[i] = actions[i];
            }
            tempActions[actions.Length] = new AutonAction(temp);
            actions = tempActions;

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
             var relativePoint = this.PointToClient(Cursor.Position);
            addAction(relativePoint.X, relativePoint.Y);

        }


    }
    public class AutonAction
    {
        public Label marker;
        private Button temp;

        public AutonAction(Button temp)
        {
            this.temp = temp;
        }
    }
}
