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
    printf ("# (c) RTCupid, 2024\n");

    printf ("Verification tests...\n");

    if (!RunTests ())
        return 0;

    printf ("# Enter a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    int inpTrue = Input (&a, &b, &c);

    if (inpTrue == 0)
        return 0;

    double x1 = NAN, x2 = NAN;

    int nAnsw = SolveSquare (a, b, c, &x1, &x2);

    Output (nAnsw, x1, x2);

    return 0;
}


void Output (int nAnsw, double x1, double x2)
{
    switch (nAnsw)
    {
        case 0:
            printf ("\nNo solutions");
            break;
        case 1:
            printf ("\nx = %lg", x1);
            break;
        case 2:
            printf ("\nx1 = %lg, x2 = %lg", x1, x2);
            break;
        case SS_INF_nAnsw:
            printf ("\nx = Any number");
            break;
        default:
            printf("\nansw = %d", nAnsw);
    }
}

int SolveSquare (double a, double b, double c, double *x1, double *x2)
{
    assert (x1 != x2);
    assert (!isnan (a));
    assert (!isnan (b));
    assert (!isnan (c));

    if (IsZero(a) && IsZero(b) && IsZero(c))
        return SS_INF_nAnsw;

    else if (IsZero(a) && IsZero(b))
        return 0;

    else if (IsZero(a))
    {
        *x1 = (-c) / b;
        return 1;
    }

    else if ((IsZero(a) or IsZero(b)) && IsZero(c))
    {
        *x1 = 0;
        return 1;
    }
    else
    {
        double d = (b * b) - (4 * a * c);
        if (d < 0)
            return 0;

        else if (IsZero(d))
        {
            *x1 = (-b) / (2 * a);
            return 1;
        }

        else
        {
            double s = sqrt (d);

            *x1 = (-b - s) / (2 * a);
            *x2 = (-b + s) / (2 * a);
            return 2;
        }
    }
}

int Input (double *a, double *b, double *c)
{
    int count = scanf ("%lg %lg %lg", a, b, c);
    int nTries = 2;
    while (count != 3)
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

        count = scanf ("%lg %lg %lg", a, b, c);
        nTries--;
    }

    if (count != 3)
        return 0;
    else
        return 1;
}

void CleanBuf ()
{

    while (true)
    {
        int ch = getchar ();

        if (ch == '\n' || ch == EOF)
            break;
    }
}

int IsZero (double a)
{
    return fabs (a) < Accuracy;
}

int AreEqual (double a, double b)
{
    return fabs (a - b) < Accuracy;
}
