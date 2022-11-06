using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Matrices
{
    internal class SqMatrix : Matrix
    {
        //CONSTRUCTORS
        public SqMatrix(int n = 2) : base(n, n)
        {
        }
        public SqMatrix(int n, bool rand) : base(n, n, rand)
        {
        }
        public SqMatrix(int n, StreamReader file) : base(n, n, file)
        {
        }
        public SqMatrix(SqMatrix other) : base(other)
        {
        }

        //METHODS
        public double Det()
        {
            if (this.line == 1)
            {
                return (double)this[0, 0];
            }
            if (this.line == 2)
            {
                return (double)this[0, 0] * (double)this[1, 1] - (double)this[0, 1] * (double)this[1, 0];
            }
            double res = 0;
            SqMatrix next = new SqMatrix(this.line - 1);
            for (int i = 0; i < this.line; i++)
            {
                double coef = (double)this[i, 0];
                for (int j = 0; j < this.line; j++)
                {
                    for (int k = 1; k < this.line; k++)
                    {
                        if (i > j)
                        {
                            next[j, k - 1] = (double)this[j, k];
                        }
                        else if (i < j)
                        {
                            next[j - 1, k - 1] = (double)this[j, k];
                        }
                    }
                }
                res += Math.Pow(-1, i) * coef * next.Det();
            }
            return res;
        }
        public double AlgAdd(int i, int j)
        {
            SqMatrix sq = new SqMatrix(this.line - 1);
            for (int k = 0; k < this.line; k++)
            {
                for (int l = 0; l < this.column; l++)
                {
                    if (k < i)
                    {
                        if (l < j)
                        {
                            sq[k, l] = this[k, l];
                        }
                        else if (l > j)
                        {
                            sq[k, l - 1] = this[k, l];
                        }
                    }
                    else if (k > i)
                    {
                        if (l < j)
                        {
                            sq[k - 1, l] = this[k, l];
                        }
                        else if (l > j)
                        {
                            sq[k - 1, l - 1] = this[k, l];
                        }
                    }
                }
            }
            return Math.Pow(-1, i + j) * sq.Det();
        }
        public InvMatrix? ConvertToInv()
        {
            if (this.line == this.column && this.Det() != 0)
            {
                InvMatrix res = new InvMatrix(this);
                return res;
            }
            return null;
        }
    }
}
