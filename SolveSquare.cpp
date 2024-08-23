
//{
//! @file    SolveSquare.cpp
//! @brief   ���������, ������� �������� ������������
//!          ��� ������� ���������� ���������
//}

#include <stdio.h>
#include <TXLib.h>

const double Accuracy = 1e-08;                  // �������� ���������� �� ����

struct OneTest
    {
    double a, b, c;
    double x1Correct, x2Correct;
    int nanswCorrect;
    };

//{
//! @brief   SolveSquare - ������ ���������� ���������
//!
//! @param   a     �   -   ������ ����������� ����������� ���������
//! @param   b     b   -   ������ ����������� ����������� ���������
//! @param   c     c   -   ������ ����������� ����������� ���������
//! @param   &x1   &x1 -   ����� ��� �������� ������� (��������) ����� ����������� ���������
//! @param   &x2   &x2 -   ����� ��� �������� ������� ����� ����������� ���������
//!
//! @return  ���������� ������ ���������, 0, 1, 2 ��� 8 � ������, ���� ����������� ���������� ������
//!
//! @code
//!     SolveSquare (1, 3, 4, &x1, &x2);
//! @endcode
//}

int SolveSquare (double a, double b, double c,  // ������������ ����������� ���������
                 double *x1, double *x2);       // ������ ��� ������ ����������� ���������

//{
//! @brief   ������� �����
//! @param   double *a - ����� ��� �������� ������� ������������ ����������� ���������
//! @param   double *b - ����� ��� �������� ������� ������������ ����������� ���������
//! @param   double *c - ����� ��� �������� �������� ������������ ����������� ���������
//! @return  0, ���� ���� �� �������
//!          1, ���� ���� �������
//! @code
//!     Input (&a, &b, &c);
//! @endcode
//}

int Input (double *a, double *b, double *c);    // ������� �����

void CleanBuf ();                               //!< ������� ������� ������

void RunTests ();                               //!< ������� ��� �������� ������

void CheckTest (int nTest, OneTest data, int *prov); // ������� �������� �����

int CloseZero (double a);                       //!< ������� ��� ��������� � ����

int Compare (double a, double b);               //!< ������� ��� ��������� ���� ����� � ��������� Accuracy

int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (�) RTCupid, 2024\n");

    RunTests ();                                // ��������� ��������� ����� � ��������� ��

    printf ("# Enter a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    int inpTrue = Input (&a, &b, &c);           // ������� ��������

    if (inpTrue == 0)
        return 0;

    double x1 = NAN, x2 = NAN;                  // ������� ����������� ���������

    int answ = SolveSquare (a, b, c, &x1, &x2); // answ ������� ���������� ������

    switch (answ)                               // ������ ����� � ����������� �� ���������� �������
        {
        case 0:
            printf ("No solutions");
            break;
        case 1:
            printf ("x = %lg", x1);
            break;
        case 2:
            printf ("x1 = %lg, x2 = %lg", x1, x2);
            break;
        case 8: // �������: ����������� ���-�� �������, ������������� = 8 ��������� �� 90 ��������
            printf ("x = Any number");
            break;
        default:
            printf("answ = %d", answ);
        }
    return 0;
    }

// ������� ����������� ���������.....................................................................

int SolveSquare (double a, double b, double c, double *x1, double *x2)  // ������� ���������
    {
    assert (x1 != x2);
    assert (!isnan (a));
    assert (!isnan (b));
    assert (!isnan (c));

    if (CloseZero(a) && CloseZero(b) && CloseZero(c))    // ��� ����==0, ���� ���-�� �������
        return 8;                                        // magick: rotated infinity

    else if (CloseZero(a) && CloseZero(b))
        return 0;

    else if (CloseZero(a))                               // ���� ������������� � �������� ���������
        {
        *x1 = -c / b;
        return 1;
        }

    else if ((CloseZero(a) or CloseZero(b)) && CloseZero(c))
        {
        *x1 = 0;
        return 1;
        }
    else                                        // ���� ����������
        {
        double d = (b * b) - (4 * a * c);       // d = ������������
        if (d < 0)                              // ������������ < 0, ��� �������
            return 0;

        else if (CloseZero(d))                        // ������������ = 0, ���� �������
            {
            *x1 = -b / (2 * a);
            return 1;
            }

        else                                    // �� ����, ��� �����
            {
            double s = sqrt (d);                // s = ������ �� �������������

            *x1 = (-b - s) / (2 * a);
            *x2 = (-b + s) / (2 * a);
            return 2;
            }
        }
    }

// ������� �����.....................................................................................

int Input (double *a, double *b, double *c)
    {
    int kol = scanf ("%lg %lg %lg", a, b, c);   // kol ������� ���������� �������� �����

    int nTries = 2;
    while (kol != 3)
        {
        if (nTries == 0)
            {
            printf ("Number of attempts exceeded!\n");
            printf ("Incorrect input!");
            break;
            }
        CleanBuf ();

        printf ("Invalid input format!\n");
        printf ("Enter three numbers using the numbers on the keyboard\n");
        printf ("%d attempts left\n", nTries);

        kol = scanf ("%lg %lg %lg", a, b, c);
        nTries--;
        }

    if (kol != 3)
        return 0;
    else
        return 1;                               // ������������ ������ ������� ������
    }

// ������� ������� �������...........................................................................

void CleanBuf ()
    {

    while (true)
        {
        int ch = getchar ();

        if (ch == '\n' || ch == EOF)
            break;
        }
    }

// �������, ������� ��������� �������� ������ � ������� �������� �������.............................

/*void RunTests ()
        {

        int prov = 1;

        double n = NAN;
        //          nTest  a       b        c   x1Correct x2Correct nansw &prov
        CheckTest ( 0,     0,      0,       0,  n,        n,        8,    &prov);
        CheckTest ( 1,     0,      0,       1,  n,        n,        0,    &prov);
        CheckTest ( 2,     0,      1,       0,  0,        n,        1,    &prov);
        CheckTest ( 3,     0,      1,       1, -1,        n,        1,    &prov);
        CheckTest ( 4,     1,      0,       0,  0,        n,        1,    &prov);
        CheckTest ( 5,     1,      0,       1,  n,        n,        0,    &prov);
        CheckTest ( 6,     1,      1,       0, -1,        0,        2,    &prov);
        CheckTest ( 7,     1,      1,       1,  n,        n,        0,    &prov);
        CheckTest ( 8,     5,      7,       2, -1,       -0.4,      2,    &prov);
        CheckTest ( 9,     2.5,    7,       4, -2,       -0.8,      2,    &prov);
        CheckTest (10,     5,     -7,       2,  0.4,      1,        2,    &prov);
        CheckTest (11,     1e-10,  1,      -2,  2,        n,        1,    &prov);

        if (prov == 1)
            printf("Verification completed successfully!\n\n")
        //assert (prov == 1);
        }
*/


// �������, ������� ��������� ���� ����..............................................................

void CheckTest (int nTest, OneTest data, int *prov)
    {
    double x1 = NAN, x2 = NAN;
    int nansw = SolveSquare (data.a, data.b, data.c, &x1, &x2);

    if (!isnan (x1) && !isnan (x2))
        {
        if (!Compare (nansw, data.nanswCorrect) || !Compare(x1, data.x1Correct) || !Compare (x2, data.x2Correct))
            {
            txSetConsoleAttr (0x0E);

            printf ("ERROR TEST %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nansw = %d\n"
                    "CORRECT: x1 = %lg, x2 = %lg, nansw = %d\n\n",
                    nTest, data.a, data.b, data.c, x1, x2, nansw,
                    data.x1Correct, data.x2Correct, data.nanswCorrect);

                    *prov = 0;

            txSetConsoleAttr (0x07);
            }
        }

    else if (isnan (x1) && isnan (x2) && Compare (nansw, data.nanswCorrect))
        ;

    else if ((isnan (x1) && !Compare (x2, data.x2Correct)) ||
             (isnan (x2) && !Compare (x1, data.x1Correct)))
        {
        txSetConsoleAttr (0x4E);

        printf ("ERROR TEST %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nansw = %d\n"
                    "CORRECT: x1 = %lg, x2 = %lg, nansw = %d\n\n",
                    nTest, data.a, data.b, data.c, x1, x2, nansw,
                    data.x1Correct, data.x2Correct, data.nanswCorrect);

                    *prov = 0;

        txSetConsoleAttr (0x07);
        }
    }

// ������� �������� ����� ������� � ���� ��������....................................................

int CloseZero (double a)
    {
    double epsilonPoz =  Accuracy;
    double epsilonNeg = -Accuracy;

    if ((a < epsilonPoz) && (a > epsilonNeg))

        return 1;
    else
        return 0;
    }

// �������, ������� ���������� ��� ����� � ����������� ���������....................................

int Compare (double a, double b)
    {
    if (a > 0 && b > 0 && (a - b > Accuracy || b - a > Accuracy))
        return 0;
    else if (((a < 0 && b > 0) || (a > 0 && b < 0)) && (fabs(a) > Accuracy || fabs(b) > Accuracy))
        return 0;
    else if (a < 0 && b < 0 && (-a + b > Accuracy))
        return 0;
    else
        return 1;
    }


void RunTests ()
    {
    const int kolTests = 12;

    int prov = 1;

    double n = NAN;
                                    //a       b        c   x1Correct x2Correct nansw
    struct OneTest data[kolTests] = {{0,      0,       0,  n,        n,        8    },  //0  ����
                                     {0,      0,       1,  n,        n,        0    },  //1  ����
                                     {0,      1,       0,  0,        n,        1    },  //2  ����
                                     {0,      1,       1, -1,        n,        1    },  //3  ����
                                     {1,      0,       0,  0,        n,        1    },  //4  ����
                                     {1,      0,       1,  n,        n,        0    },  //5  ����
                                     {1,      1,       0, -1,        0,        2    },  //6  ����
                                     {1,      1,       1,  n,        n,        0    },  //7  ����
                                     {5,      7,       2, -1,       -0.4,      2    },  //8  ����
                                     {2.5,    7,       4, -2,       -0.8,      2    },  //9  ����
                                     {5,     -7,       2,  0.4,      1,        2    },  //10 ����
                                     {1e-10,  1,      -2,  2,        n,        1    }}; //11 ����


    for (int i = 0; i < kolTests; i++)
        CheckTest (i, data[i], &prov);


    if (prov == 1)
            printf("Verification completed successfully!\n\n");
    }










