using System.ComponentModel;
using System.Reflection;

namespace Ball
{
    public delegate void BallStopped(Animator a);
    public delegate void SquareAppeared(Square s);
    public delegate void ScoreUpdate(int Id);
    public partial class GameForm : Form
    {
        private Painter p;
        bool flag = false;
        private BindingList<Square> squares = new();

        public GameForm()
        {
            InitializeComponent();
        }
        public void NewSquare(Square s)
        {
            if (InvokeRequired) Invoke(NewSquare, s);
            else
            {
                squares.Add(s);
                dataGridView1.Rows[s.Id - 1].Cells[1].Style.BackColor = s.COLOR;
            }
        }

        public void NewScore(int id)
        {
            try
            {
                if (InvokeRequired) Invoke(NewScore, id);
                else dataGridView1.UpdateCellValue(2, id - 1);
            }
            catch { }
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

        private void GameForm_Load(object sender, EventArgs e)
        {
            p = new Painter(mainPanel.CreateGraphics());
            p.ShowCircle();
            p.squareAppeared += NewSquare;
            p.squareScoreUpdate += NewScore;
            dataGridView1.DataSource = squares;
            dataGridView1.Columns["X"].Visible = false;
            dataGridView1.Columns["Y"].Visible = false;
            dataGridView1.Columns["Width"].Visible = false;
        }
    }
}