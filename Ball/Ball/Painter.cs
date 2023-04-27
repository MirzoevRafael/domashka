using System.Security.Cryptography.X509Certificates;

namespace Ball
{
    public class Painter
    {
        private object locker = new();
        private List<Animator> _animators = new();
        private List<Square> _squares = new();
        private Size _containerSize;
        private Thread t;
        private Thread sqT;
        private Graphics _mainGraphics;
        private BufferedGraphics _bg;
        private int _id = 1;
        public event SquareAppeared squareAppeared;
        public event ScoreUpdate squareScoreUpdate;
        private Database db;

        private volatile int objectsPainted = 0;
        public Thread PainterThread => t;
        public Graphics MainGraphics
        {
            get => _mainGraphics;
            set
            {
                lock (locker)
                {
                    _mainGraphics = value;
                    ContainerSize = _mainGraphics.VisibleClipBounds.Size.ToSize();
                    _bg = BufferedGraphicsManager.Current.Allocate(
                        _mainGraphics, new Rectangle(new Point(0, 0), ContainerSize)
                    );
                    objectsPainted = 0;
                }
            }
        }

        public Size ContainerSize
        {
            get => _containerSize;
            set
            {
                _containerSize = value;
                foreach (var animator in _animators)
                {
                    animator.ContainerSize = ContainerSize;
                }
            }
        }

        public Painter(Graphics mainGraphics)
        {
            MainGraphics = mainGraphics;
            db = new();
        }


        public void AddSquare(MouseEventArgs e)
        {
            Square square = new Square(e.X, e.Y, _id++);
            //Circle c = new Circle(50, e.X - 25, e.Y - 25, Color.FromArgb(250, 210, 210));
            //try
            //{
                if (e.X - 30 >= 0 && e.X + 30 <= _containerSize.Width && e.Y - 30 >= 0 && 
                    e.Y + 30 <= _containerSize.Height && CheckSqs(e))
                {
                    db.NewSquare(square);
                    lock (locker)
                    {
                        //c.Paint(MainGraphics);
                        _squares.Add(square);
                        squareAppeared(square);
                        square.Paint(_mainGraphics);
                        AddCircle(e, square.COLOR, square.Id);
                    }
                }
            //}
            //catch { }
        }
        public bool CheckSqs(MouseEventArgs e)
        {
            foreach (var square in _squares)
            {
                if (Math.Sqrt((square.X - e.X) * (square.X - e.X) + (square.Y - e.Y) * (square.Y - e.Y)) <= 75) return false;
            }
            return true;
        }

        public void AddCircle(MouseEventArgs e, Color color, int id)
        {
            sqT = new Thread(() =>
            {
                try
                {
                    while (true)
                    {
                        var a = new Animator(ContainerSize, e.X - 25, e.Y - 25, color, id);
                        lock (locker)
                        {
                            _animators.Add(a);
                            a.Start();
                            a._ballStopped += StopBall;
                        }
                        Thread.Sleep(3000);
                    }

                }
                catch { }
                
            });
            
            sqT.IsBackground = true;
            sqT.Start();
                //return 1;
            
        }
        
        private void StopBall(Animator a)
        {
            lock(locker)
            {
                _animators.Remove(a);
            }
        }
        public void ShowCircle()
		{
            t = new Thread(() =>
            {
            try
            {
                while (true)
                {
                    lock (locker)
                    {
                        if (PaintOnBuffer())
                            {
                                _bg.Render(MainGraphics);
                            }
                        }
                    }
                }
                catch (ArgumentException e) { }
            });
            t.IsBackground = true;
            t.Start();

        }
   

        public void Stop()
        {
            t.Interrupt();
        }

        private double Dist(Circle A, Circle B)
        {
            return Math.Sqrt((A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y));
        }

        private Animator[]? CheckCrash(Animator animator1)
        {
            lock (locker)
            {
                //foreach (var animator1 in _animators)
                //{
                    foreach (var animator2 in _animators)
                    {
                        if (!(animator1.Id == animator2.Id))
                        {
                            if (Dist(animator1.C, animator2.C) <= animator1.C.Diam)
                            {
                                var r = new Random();
                                if (r.Next(2) == 1) return new Animator[2] { animator1, animator2 };
                                return new Animator[2] { animator2, animator1 }; ;
                            }
                        }
                    }
                    return null;
                //}
            }
        }
        

        private bool PaintOnBuffer()
        {
            Thread.Sleep(10);
            objectsPainted = 0;
            var objectsCount = _animators.Count + _squares.Count;
            _bg.Graphics.Clear(Color.White);
            lock (locker)
            {
                foreach (var animator in _animators)
                {
                    var crashedBalls = CheckCrash(animator);
                    if (!(crashedBalls == null))
                    {
                        StopBall(crashedBalls[0]);
                        foreach (var square in _squares)
                        {
                            if (square.Id == crashedBalls[1].Id)
                            { 
                                square.Score++;
                                squareScoreUpdate(square.Id);
                                db.NewScore(square);
                                break;
                            }
                        }
                        break;
                    }
                    animator.PaintCircle(_bg.Graphics);
                    objectsPainted++;
                }

                foreach (var square in _squares)
                {
                    square.Paint(_bg.Graphics);
                    objectsPainted++;
                }
            }
            return objectsPainted == objectsCount;
        }
    }
}
