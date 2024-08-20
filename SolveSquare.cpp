#include <stdio.h>
#include <TXLib.h>

int SolveSquare (double a, double b, double c,  // коэффициенты
                 double *x1, double *x2);       // адреса для решений

void SolveLine (double a, double b, double c,
                double *x1);

void input (double *a, double *b, double *c);

void CleanBuf ();

int main ()
    {
    printf ("# Эта программа решает квадратные уравнения\n");
    printf ("# (с) RTCupid, 2024\n");
    printf ("# Введите a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    input (&a, &b, &c);       // функция не написана
    /*double a = NAN, b = NAN, c = NAN;         // это функция
                                                // ввода
    scanf ("%lg %lg %lg", &a, &b, &c);*/

    double x1 = NAN, x2 = NAN;                  // решения квадратного уравнения

    int answ = SolveSquare (a, b, c, &x1, &x2); // answ считает количество корней

    switch (answ)                               // вывожу ответ в зависимости от количества решений
        {
        case 0:
            printf ("нет решений");
            break;
        case 1:
            printf ("x = %lg", x1);
            break;
        case 2:
            printf ("x1 = %lg, x2 = %lg", x1, x2);
            break;
        case 8: // вариант: бесконечное кол-во решений, бесконечность = 8 повернуть на 90 градусов
            printf ("x = любое число");
            break;
        default:
            printf("answ = %d", answ);
        }
    }

// функция квадратного уравнения.....................................................................

int SolveSquare (double a, double b, double c, double *x1, double *x2)  // решение квадратки
    {
    assert (x1 != x2);

    if (a == 0 and b == 0 and c == 0)           // все коэф==0, беск кол-во решений
        return 8;
    else if (a == 0 or c == 0 and a != c)       // если преобразуется в линейное уравнение
        {
        SolveLine (a, b, c, x1);
        return 1;
        }
    else                                        // норм квадратное
        {
        float d = b*b - 4*a*c;                  // d = дискриминант
        if (d < 0)                              // дискриминант < 0, нет решений
            return 0;
        else if (d == 0)                        // дискриминант = 0, одно решение
            {
            *x1 = -b/(2*a);
            return 1;
            }
        else                                    // всё норм, два корня
            {
            double s = sqrt (d);                // s = корень из дискриминанта
            *x1 = (-b + s)/(2*a);
            *x2 = (-b - s)/(2*a);
            return 2;
            }
        }
    }

// функция линейного уравнения.......................................................................

void SolveLine (double a, double b, double c, double *x1)
    {
    if (a == 0)
        *x1 = -c/b;
    else                                        // с == 0
        *x1 = -b/a;
    }

// функция ввода.....................................................................................

void input (double *a, double *b, double *c)
    {
    int kol = scanf ("%lg %lg %lg", a, b, c);   // kol считает количество введённых чисел

    int nTries = 2;
    while (kol != 3)
        {
        if (nTries == 0)
            {
            printf ("Превышено количество попыток!\n");
            printf ("Неправильный ввод");
            break;
            }
        CleanBuf ();

        printf ("Неверный формат ввода!\n");
        printf ("Введите три числа, используя цифры на клавиатуре\n");
        printf ("осталось %d попытки\n", nTries);

        kol = scanf ("%lg %lg %lg", a, b, c);
        nTries--;
        }

    assert (kol == 3);                          // неправильный формат входных данных
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
