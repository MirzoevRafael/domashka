using Matrices;

StreamReader file = new StreamReader("C:\\Users\\Rafae\\source\\repos\\Matrices\\Matrices\\file.txt");
SqMatrix sq1 = new SqMatrix(4, false);
SqMatrix sq2 = new SqMatrix(4, file);
Matrix m1 = new Matrix(4, 1, true);
Matrix m2 = new Matrix(1, 4, true);
sq1.PrintMatrix();
sq2.PrintMatrix();
SqMatrix sq3 = (sq1 + sq2).ConvertToSquare();
sq3.PrintMatrix();
sq1.Transp().PrintMatrix();
Console.WriteLine(sq1.Det());
Console.WriteLine(sq2.Det());
Console.WriteLine(sq3.Det());
Console.WriteLine();
(sq1 + sq2).PrintMatrix();
(sq1 - sq2).PrintMatrix();
(sq1 / 3.25).PrintMatrix();
(2 * sq2).PrintMatrix();
m1.PrintMatrix();
m2.PrintMatrix();
(m1 * m2).PrintMatrix();
(m2 * sq2).PrintMatrix();

if (sq2.Det() != 0)
{
    InvMatrix inv1 = new InvMatrix(sq2);
    inv1.PrintMatrix();
    inv1.FindInv().PrintMatrix();
}
else
{
    Console.WriteLine("NO");
}
