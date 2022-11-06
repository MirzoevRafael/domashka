using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Matrices
{
    internal class InvMatrix : SqMatrix
    {
        //FIELDS AND PROPERTIES
        private double det;
        public double Determinant { get { return det; } }

        //CONSTRUCTORS
        public InvMatrix(SqMatrix other) : base(other)
        {
            this.det = other.Det();
        }

        //METHODS
        public InvMatrix FindInv()
        {
            InvMatrix transp = new InvMatrix(this.Transp().ConvertToSquare());
            SqMatrix res = new SqMatrix(this.line);
            for (int i = 0; i < this.line; i++)
            {
                for (int j = 0; j < this.column; j++)
                {
                    res[i, j] = transp.AlgAdd(i, j);
                }
            }
            return ((res / (this.Determinant)).ConvertToSquare()).ConvertToInv();
        }
    }
}
