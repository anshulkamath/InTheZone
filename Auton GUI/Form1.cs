using System;
using System.Windows.Forms;
namespace Vex_Auton_Select
{
    public partial class Form1 : Form
    {
        private AutonAction[] actions;
        public Form1()
        {
            ContextMenu cm = new ContextMenu();
            cm.MenuItems.Add("Generate Code", new EventHandler(codeGeneration));

            InitializeComponent();
            pictureBox1.ContextMenu = cm;
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
            ContextMenu cm = new ContextMenu();
            cm.MenuItems.Add("Sent Backwards", new EventHandler(setBackwards));
            temp.ContextMenu = cm;
            //pictureBox1.Enabled = false;
            this.Controls.Add(temp);
            temp.BringToFront();
            AutonAction[] tempActions = new AutonAction[actions.Length + 1];
            for(int i = 0; i<actions.Length; i++)
            {
                tempActions[i] = actions[i];
            }
            tempActions[actions.Length] = new AutonAction(temp, true);
            actions = tempActions;

        }

        private void setBackwards(object sender, EventArgs e)
        {
            MenuItem menuItem = sender as MenuItem;
            ContextMenu menu = menuItem.GetContextMenu();
            Control sourceControl = menu.SourceControl;
            for (int i = 0; i<actions.Length; i++)
                
                if(((Button)sourceControl).Equals(actions[i].button))
                {
                    actions[i].forward = false;
                }
        }

        private void codeGeneration(object sender, EventArgs e)
        {
            String code = "";
            double orentation = 0;
            for (int i = 0; i < actions.Length -1 ; i++)
            {
                if(actions[i+1].forward)
                    orentation = forwardMove(actions[i+1], actions[i], orentation, ref code);
                else
                {
                    orentation = backwardMove(actions[i + 1], actions[i], orentation, ref code);
                }

            }
            MessageBox.Show(code);

        }

        private double forwardMove(AutonAction one, AutonAction two, double orentation, ref String code)
        {
            double angleToMove = Math.Atan2(one.button.Location.Y - two.button.Location.Y,
                one.button.Location.X - two.button.Location.X);
            angleToMove *= (180 / Math.PI);
            angleToMove -= orentation;
            orentation = angleToMove;
            if (angleToMove > 0)
            {
                code += "right(" + (int)angleToMove + ");\n";
            }
            else
            {
                code += "left(" + -(int)angleToMove + ");\n";
            }
            double distance = Math.Pow(inchesToTicks(one.button.Location.Y - two.button.Location.Y, 4), 2)
                + Math.Pow(inchesToTicks(one.button.Location.X - two.button.Location.X, 4), 2);
            distance = Math.Sqrt(distance);
            code += "forward(" + (int)distance + ");\n";
            return orentation;
        }
        private double inchesToTicks(double pixels, double wheelSize)
        {
            double inches = pixelsToInches(pixels, true);
            MessageBox.Show(((inches / (wheelSize * Math.PI)) * 360) + "");
            return (inches/(wheelSize * Math.PI)) * 360;
        }

        private double pixelsToInches(double pixels, bool width)
        {

            int height = System.Windows.Forms.SystemInformation.VirtualScreen.Height;
            int width1 = System.Windows.Forms.SystemInformation.VirtualScreen.Width;
            if(width)
            {
                return ((double)pixels / pictureBox1.Width)*(12*12+2);
            }
            return ((double)pixels / pictureBox1.Height) * (12 * 12 + 2);
        }
        private double backwardMove(AutonAction one, AutonAction two, double orentation, ref String code)
        {
            double angleToMove = Math.Atan2(-one.button.Location.Y + two.button.Location.Y,
                -one.button.Location.X + two.button.Location.X);
            angleToMove *= (180 / Math.PI);
            angleToMove -= orentation;
            orentation = angleToMove;
            if (angleToMove > 0)
            {
                code += "right(" + -(int)angleToMove + ");\n";
            }
            else
            {
                code += "left(" + -(int)angleToMove + ");\n";
            }
            double distance = Math.Pow(inchesToTicks(one.button.Location.Y - two.button.Location.Y, 4), 2)
                + Math.Pow(inchesToTicks(one.button.Location.X - two.button.Location.X, 4), 2);
            distance = Math.Sqrt(distance);
            code += "backward(" + (int)distance + ");\n";
            return orentation;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            MouseEventArgs me = (MouseEventArgs)e;
            switch (me.Button)
            {

                case MouseButtons.Left:
                    var relativePoint = this.PointToClient(Cursor.Position);
                    addAction(relativePoint.X, relativePoint.Y);
                    break;

                case MouseButtons.Right:
                    // Right click
                    break;
            }
 

        }


    }
    public class AutonAction
    {
        public Button button;
        public bool forward;

        public AutonAction(Button temp)
        {
            this.button = temp;
        }

        public AutonAction(Button temp, bool v) : this(temp)
        {
            forward = v;
        }
    }
}
