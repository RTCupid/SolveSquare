
//{
//! @file    SolveSquare.cpp
//! @brief   ���������, ������� �������� ������������
//!          ��� ������� ���������� ���������
//}

#include <stdio.h>
#include "TXLib.h"

#include "SolveSquare.h"

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

    int nansw = SolveSquare (a, b, c, &x1, &x2); // answ ������� ���������� ������

    output (nansw, x1, x2);

    return 0;
    }

// ������� ������� ����� ������������ �� ���������� ������...........................................

void output (int nansw, double x1, double x2)
    {
    switch (nansw)
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
        case SS_INF_nansw:                       // �������: ����������� ���-�� �������
            printf ("x = Any number");
            break;
        default:
            printf("answ = %d", nansw);
        }
    }

// ������� ����������� ���������.....................................................................

int SolveSquare (double a, double b, double c, double *x1, double *x2)  // ������� ���������
    {
    assert (x1 != x2);
    assert (!isnan (a));
    assert (!isnan (b));
    assert (!isnan (c));

    if (CloseZero(a) && CloseZero(b) && CloseZero(c))    // ��� ����==0, ���� ���-�� �������
        return SS_INF_nansw;                                        // magick: rotated infinity

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











