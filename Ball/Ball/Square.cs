using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ball
{
    public class Square
    {
        private Random _r = new();
        private int _width;
        private Color _color;
        private int _x, _y;
        [DisplayName("Номер игрока")]
        public int Id { get; set; }
        [DisplayName("Цвет")]
        public Color COLOR { get { return _color; } }
        [DisplayName("Очки")]
        public int Score { get; set; } = 0;

        public int Width { get { return _width; } set { _width = value; } }
        public int X { get { return _x; } set { _x = value; } }
        public int Y { get { return _y; } set { _y = value; } }

        public Square(int x, int y, int id, int width = 50) { 
            _x = x;
            _y = y;
            _width = width;
            Id = id;
            _color = Color.FromArgb(_r.Next(255), _r.Next(255), _r.Next(255));
        }

        public void Paint(Graphics g)
        {
            var brush = new SolidBrush(_color);
            var pen = new Pen(Color.Black);
            g.FillRectangle(brush, X - _width/2, Y - _width / 2, _width, _width);
            g.DrawRectangle(pen, X - _width / 2, Y - _width / 2, _width, _width);
        }

    }
}
