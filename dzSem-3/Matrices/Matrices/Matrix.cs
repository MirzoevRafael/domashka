using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Matrices
{
    internal class Matrix
    {
        //FIELDS AND PROPERTIES
        protected int line, column;
        protected double[,] matr;
        public int Line { get { return line; } }
        public int Column { get { return column; } }

        //INDEXING
        public double? this[int i, int j]
        {
            get
            {
                if (i >= 0 && i < this.line && j >= 0 && j < this.column)
                {
                    return this.matr[i, j];
                }
                return null;
            }
            set
            {
                if (value != null)
                {
                    if (i >= 0 && i < this.line && j >= 0 && j < this.column)
                    {
                        this.matr[i, j] = (double)value;
                    }
                }
            }
        }

        //CONSTRUCTORS
        public Matrix(int line = 2, int column = 3)
        {
            this.line = line;
            this.column = column;
            this.matr = new double[line, column];
            for (int i = 0; i < line; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    this[i, j] = 0;
                }
            }
        }
        public Matrix(int line, int column, bool rand)
        {
            this.line = line;
            this.column = column;
            this.matr = new double[line, column];
            if (rand)
            {
                this.FillRand();
            }
            else
            {
                this.FillByLine();
            }
        }
        public Matrix(int line, int column, StreamReader file)
        {
            this.line = line;
            this.column = column;
            this.matr = new double[line, column];
            this.FillWFile(file);
        }
        public Matrix(Matrix other)
        {
            this.line = other.line;
            this.column = other.column;
            this.matr = new double[this.line, this.column];
            this.FillCopy(other);
        }

        //METHODS
        public void FillCopy(Matrix other)
        {
            if (this.line != other.line || this.column != other.column)
            {
                Console.WriteLine("Количество строк и/или столбцов матриц не совпадают");
                return;
            }
            for (int i = 0; i < line; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    this[i, j] = other[i, j];
                }
            }
        }
        public void FillByLine()
        {
            Console.WriteLine("Введите элементы массива построчно через пробел:");
            for (int i = 0; i < this.line; i++)
            {
                string line = Console.ReadLine();
                if (line != null && line != "")
                {
                    double[] newLine = line.Split(' ').Select(double.Parse).ToArray();
                    int len = newLine.Length;
                    if (len <= this.column)
                    {
                        for (int j = 0; j < len; j++)
                        {
                            this[i, j] = newLine[j];

                        }
                        for (int j = len; j < this.column; j++)
                        {
                            this[i, j] = 0;

                        }
                    }
                    else
                    {
                        for (int j = 0; j < this.column; j++)
                        {
                            this[i, j] = newLine[j];

                        }
                    }
                }
                else
                {
                    for (int j = 0; j < this.column; j++)
                    {
                        this[i, j] = 0;
                    }
                }
            }
        }
        public void FillRand()
        {
            Random x = new Random();
            for (int i = 0; i < line; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    this[i, j] = Convert.ToDouble(x.Next(-10, 11));
                }
            }
        }
        public void FillWFile(StreamReader file)
        {
            for (int i = 0; i < this.line; i++)
            {
                string line = file.ReadLine();
                if (line != null && line != "")
                {
                    double[] newLine = line.Split(' ').Select(double.Parse).ToArray();
                    int len = newLine.Length;
                    if (len <= this.column)
                    {
                        for (int j = 0; j < len; j++)
                        {
                            this[i, j] = newLine[j];

                        }
                        for (int j = len; j < this.column; j++)
                        {
                            this[i, j] = 0;

                        }
                    }
                    else
                    {
                        for (int j = 0; j < this.column; j++)
                        {
                            this[i, j] = newLine[j];

                        }
                    }
                }
                else
                {
                    for (int j = 0; j < this.column; j++)
                    {
                        this[i, j] = 0;
                    }
                }
            }
            file.Close();
        }
        public Matrix Transp()
        {
            Matrix transposed = new Matrix(this.column, this.line);
            for (int i = 0; i < this.line; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    transposed[j, i] = this[i, j];
                }
            }
            return transposed;
        }
        public void PrintMatrix()
        {
            for (int i = 0; i < this.line; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    Console.Write("{0}\t", this[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
        public SqMatrix? ConvertToSquare()
        {
            if (this.line == this.column)
            {
                SqMatrix res = new SqMatrix(this.column);
                for (int i = 0; i < this.line; i++)
                {
                    for (int j = 0; j < this.column; j++)
                    {
                        res[i, j] = this[i, j];
                    }
                }
                return res;
            }
            return null;
        }

        //OPERATORS
        public static Matrix? operator +(Matrix fst, Matrix snd)
        {
            if (fst.line == snd.line && fst.column == snd.Column)
            {
                Matrix sum = new Matrix(fst.line, fst.column);
                for (int i = 0; i < fst.line; i++)
                {
                    for (int j = 0; j < fst.column; j++)
                    {
                        sum[i, j] = fst[i, j] + snd[i, j];
                    }
                }
                return sum;
            }
            Console.WriteLine("Количество строк и/или столбцов не совпадает");
            return null;
        }
        public static Matrix? operator -(Matrix fst, Matrix snd)
        {
            if (fst.line == snd.line && fst.column == snd.Column)
            {
                Matrix diff = new Matrix(fst.line, fst.column);
                for (int i = 0; i < fst.line; i++)
                {
                    for (int j = 0; j < fst.column; j++)
                    {
                        diff[i, j] = fst[i, j] - snd[i, j];
                    }
                }
                return diff;
            }
            Console.WriteLine("Количество строк и/или столбцов не совпадает");
            return null;
        }
        public static Matrix operator *(double k, Matrix matr)
        {
            Matrix prod = new Matrix(matr.line, matr.column);
            for (int
                i = 0; i < matr.line; i++)
            {
                for (int j = 0; j < matr.column; j++)
                {
                    prod[i, j] = k * matr[i, j];
                }
            }
            return prod;
        }
        public static Matrix operator *(Matrix matr, double k)
        {
            Matrix prod = new Matrix(matr.line, matr.column);
            for (int i = 0; i < matr.line; i++)
            {
                for (int j = 0; j < matr.column; j++)
                {
                    prod[i, j] = k * matr[i, j];
                }
            }
            return prod;
        }
        public static Matrix operator /(Matrix matr, double k)
        {
            Matrix quot = new Matrix(matr.line, matr.column);
            for (int i = 0; i < matr.line; i++)
            {
                for (int j = 0; j < matr.column; j++)
                {
                    quot[i, j] = matr[i, j] / k;
                }
            }
            return quot;
        }
        public static Matrix? operator *(Matrix fst, Matrix snd)
        {
            if (fst.column == snd.line)
            {
                Matrix prod = new Matrix(fst.line, snd.column);
                for (int i = 0; i < fst.line; i++)
                {
                    for (int j = 0; j < snd.column; j++)
                    {
                        prod[i, j] = 0;
                        for (int k = 0; k < fst.column; k++)
                        {
                            prod[i, j] += fst[i, k] * snd[k, j];
                        }
                    }
                }
                return prod;
            }
            Console.WriteLine("Количество столбцов 1 матрицы и строк 2 не совпадает");
            return null;
        }
    }
}
