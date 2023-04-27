using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Threading.Tasks;

namespace Ball
{
    public class Animator
    {
        private Circle c;
        public int a = 100;
        private Color _color;
        public Color COLOR { get { return _color; } }
        public Circle C => c;
        private int _id;
        public int Id { get { return _id; } }


        private Thread? t = null;
        public bool IsAlive => t == null || t.IsAlive;
        public Size ContainerSize { get; set; }
        public event BallStopped _ballStopped;

        public Animator(Size containerSize, int x, int y, Color color, int id)
        {
            int d = 50;
            Random rnd = new Random();
            _color = color;
            c = new Circle(d, x, y, color);
            _id = id;

            ContainerSize = containerSize;
        }

        public void Start()
        {
            Random rnd = new Random();
            t = new Thread(() =>
            {
                c.Dx = rnd.Next(-5, 6);
                int sign = rnd.Next(0, 2);
                if (sign == 0) { sign = -1; }
                c.Dy = sign * Convert.ToInt32(Math.Sqrt(25 - c.Dx * c.Dx));
                while (c.Dx == 0 && c.Dy == 0)
                {
                    c.Dx = rnd.Next(-1, 1);
                    c.Dy = rnd.Next(-1, 1);
                }
                while (true)
                {
                    Thread.Sleep(30);
                    c.Move();
                    if (WallCheck()) break;
                }
                _ballStopped(this);
            });
            t.IsBackground = true;
            t.Start();
        }

        public bool WallCheck()
        {
            if (c.X + c.Diam >= ContainerSize.Width || c.X <= 0 || c.Y + c.Diam >= ContainerSize.Height || c.Y <= 0)
            {
                return true;
            }
            return false;
        }

        public void PaintCircle(Graphics g)
        {
            c.Paint(g);
        }
    }
}
