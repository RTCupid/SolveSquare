
//{
//! @file    SolveSquare.cpp
//! @brief   Программа, которая является инструментом
//!          для решения квадратных уравнений
//}

#include <stdio.h>
#include "TXLib.h"

#include "SolveSquare.h"

int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (с) RTCupid, 2024\n");

    StartVerification ();

    RunTests ();                                // программа запускает тесты и проверяет их

    printf ("# Enter a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    int inpTrue = Input (&a, &b, &c);           // функция написана

    if (inpTrue == 0)
        return 0;

    double x1 = NAN, x2 = NAN;                  // решения квадратного уравнения

    int nAnsw = SolveSquare (a, b, c, &x1, &x2);// nAnsw считает количество корней

    Output (nAnsw, x1, x2);

    return 0;
    }

// функция выводит ответ взависимости от количества корней...........................................

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
        case SS_INF_nAnsw:                       // вариант: бесконечное кол-во решений
            printf ("\nx = Any number");
            break;
        default:
            printf("\nansw = %d", nAnsw);
        }
    }

// функция квадратного уравнения.....................................................................

int SolveSquare (double a, double b, double c, double *x1, double *x2)  // решение квадратки
    {
    assert (x1 != x2);
    assert (!isnan (a));
    assert (!isnan (b));
    assert (!isnan (c));

    if (IsZero(a) && IsZero(b) && IsZero(c))     // все коэф==0, беск кол-во решений
        return SS_INF_nAnsw;

    else if (IsZero(a) && IsZero(b))
        return 0;

    else if (IsZero(a))                           // если преобразуется в линейное уравнение
        {
        *x1 = (-c) / b;
        return 1;
        }

    else if ((IsZero(a) or IsZero(b)) && IsZero(c))
        {
        *x1 = 0;
        return 1;
        }
    else                                        // норм квадратное
        {
        double d = (b * b) - (4 * a * c);       // d = дискриминант
        if (d < 0)                              // дискриминант < 0, нет решений
            return 0;

        else if (IsZero(d))                        // дискриминант = 0, одно решение
            {
            *x1 = (-b) / (2 * a);
            return 1;
            }

        else                                    // всё норм, два корня
            {
            double s = sqrt (d);                // s = корень из дискриминанта

            *x1 = (-b - s) / (2 * a);
            *x2 = (-b + s) / (2 * a);
            return 2;
            }
        }
    }

// функция ввода.....................................................................................

int Input (double *a, double *b, double *c)
    {
    int count = scanf ("%lg %lg %lg", a, b, c);   // count считает количество введённых чисел
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
        return 1;                               // неправильный формат входных данных
    }

// функция очистки буффера...........................................................................

void CleanBuf ()
    {

    while (true)
        {
        int ch = getchar ();

        if (ch == '\n' || ch == EOF)
            break;
        }
    }

// функция обнуляет очень близкие к нулю значения....................................................

int IsZero (double a)
    {
    return fabs (a) < Accuracy;
    }

// функция, которая сравнивает два числа с определённой точностью....................................

int AreEqual (double a, double b)
    {
    return fabs (a - b) < Accuracy;
    }











