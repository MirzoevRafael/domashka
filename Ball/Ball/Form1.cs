using System.ComponentModel;
using System.Reflection;
using System.Security.Cryptography.X509Certificates;

namespace Ball
{
    public delegate void BallStopped(Animator a);
    public delegate void SquareAppeared(Square s);
    public partial class GameForm : Form
    {
        private object locker = new();
        private Painter p;
        bool flag = false;
        private BindingList<Square> squares = new();

        public GameForm()
        {
            InitializeComponent();
        }
        public void NewSquare(Square s)
        {
            //try
            //{
                if (InvokeRequired) Invoke(NewSquare, s);
                else
                {
                    squares.Add(s);
                    p.DB.NewSquare(s);
                    dataGridView1.Rows[s.Id - 1].Cells[1].Style.BackColor = s.COLOR;
                }
            //}
            //catch { }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            flag = true;
        }

        private void mainPanel_Resize(object sender, EventArgs e)
        {
            if (p != null)
                p.MainGraphics = mainPanel.CreateGraphics();
        }

        private void mainPanel_MouseClick(object sender, MouseEventArgs e)
        {
            if (flag)
            {
                p.AddSquare(e);
                flag = false;
            }
        }
        public void DataUpdate()
        {
            if (InvokeRequired) Invoke(DataUpdate);
            else dataGridView1.Refresh(); 
        }

        private void GameForm_Load(object sender, EventArgs e)
        {
            p = new Painter(mainPanel.CreateGraphics());
            p.ShowCircle();
            p.squareAppeared += NewSquare;
            dataGridView1.DataSource = squares;
            dataGridView1.Columns["X"].Visible = false;
            dataGridView1.Columns["Y"].Visible = false;
            dataGridView1.Columns["Width"].Visible = false;
            Thread t = new Thread(() =>
                {
                    while (true)
                    {
                        lock (locker)
                        {
                            DataUpdate();
                            Thread.Sleep(1000);
                        }
                    }
                });
            t.IsBackground = true;
            t.Start();
        }
    }
}