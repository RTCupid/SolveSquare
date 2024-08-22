#include <stdio.h>
#include <TXLib.h>

#define Accuracy 1e-08                          // точность округления до нуля

int SolveSquare (double a, double b, double c,  // коэффициенты
                 double *x1, double *x2);       // адреса для решений

int Input (double *a, double *b, double *c);    // функция ввода

void CleanBuf ();                               // функция очистки буфера

void RunTests ();                               // функция для прогонки тестов

void CheckTest (int nTest, double a, double b, double c, double x1Correct, double x2Correct, int nanswCorrect, int *prov); // функция проверки теста

int CloseZero (double a);                       // функция для сравнения с нулём

int Compare (double a, double b);               // функция для сравнений двух чисел с точностью Accuracy

int main ()
    {
    printf ("# Program for Solve Square equation\n");
    printf ("# (с) RTCupid, 2024\n");

    RunTests ();                                // программа запускает тесты и проверяет их

    printf ("# Enter a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    int inpTrue = Input (&a, &b, &c);           // функция написана

    if (inpTrue == 0)
        return 0;

    double x1 = NAN, x2 = NAN;                  // решения квадратного уравнения

    int answ = SolveSquare (a, b, c, &x1, &x2); // answ считает количество корней

    //assert (std:(!isNAN (x1)));               // выдаст ошибку, если значение x1 не назначается

    switch (answ)                               // вывожу ответ в зависимости от количества решений
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
        case 8: // вариант: бесконечное кол-во решений, бесконечность = 8 повернуть на 90 градусов
            printf ("x = Any number");
            break;
        default:
            printf("answ = %d", answ);
        }
    return 0;
    }

// функция квадратного уравнения.....................................................................

int SolveSquare (double a, double b, double c, double *x1, double *x2)  // решение квадратки
    {
    assert (x1 != x2);
    /*assert (std: !isNAN (a));
    assert (std: !isNAN (b));
    assert (std: !isNAN (c));*/

    if (CloseZero(a) && CloseZero(b) && CloseZero(c))    // все коэф==0, беск кол-во решений
        return 8;                                        // magick: rotated infinity

    else if (CloseZero(a) && CloseZero(b))
        return 0;

    else if (CloseZero(a))                               // если преобразуется в линейное уравнение
        {
        *x1 = -c / b;;
        return 1;
        }

    else if ((CloseZero(a) or CloseZero(b)) && CloseZero(c))
        {
        *x1 = 0;
        return 1;
        }
    else                                        // норм квадратное
        {
        double d = (b * b) - (4 * a * c);       // d = дискриминант
        if (d < 0)                              // дискриминант < 0, нет решений
            return 0;

        else if (CloseZero(d))                        // дискриминант = 0, одно решение
            {
            *x1 = -b / (2 * a);
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
    int kol = scanf ("%lg %lg %lg", a, b, c);   // kol считает количество введённых чисел

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

// функция, которая запускает проверку тестов с разными входными данными.............................

void RunTests ()
    {

    int prov = 1;

    int nTest = -1;

    nTest = 0;
    CheckTest (nTest, 0, 0, 0, NAN, NAN, 8, &prov);

    nTest = 1;
    CheckTest (nTest, 0, 0, 1, NAN, NAN, 0, &prov);

    nTest = 2;
    CheckTest (nTest, 0, 1, 0, 0, NAN, 1, &prov);

    nTest = 3;
    CheckTest (nTest, 0, 1, 1, -1, NAN, 1, &prov);

    nTest = 4;
    CheckTest (nTest, 1, 0, 0, 0, NAN, 1, &prov);

    nTest = 5;
    CheckTest (nTest, 1, 0, 1, NAN, NAN, 0, &prov);

    nTest = 6;
    CheckTest (nTest, 1, 1, 0, -1, 0, 2, &prov);

    nTest = 7;
    CheckTest (nTest, 1, 1, 1, NAN, NAN, 0, &prov);

    nTest = 8;
    CheckTest (nTest, 5, 7, 2, -1, -0.4, 2, &prov);

    nTest = 9;
    CheckTest (nTest, 2.5, 7, 4, -2, -0.8, 2, &prov);

    nTest = 10;
    CheckTest (nTest, 5, -7, 2, 0.4, 1, 2, &prov);

    nTest = 11;
    CheckTest (nTest, 0.0000000000000000001, 1, -2, 2, NAN, 1, &prov);

    if (prov == 1)
        printf("Verification completed successfully!\n\n");
    //assert (prov == 1);
    }

/*   Runtest версия Деда (более компактно и понятно)
void RunTests ()
        {

        int prov = 1;

        double n = NAN;

        CheckTest ( 0, 0,    0, 0,  n,   n,   8, &prov);
        CheckTest ( 1, 0,    0, 1,  n,   n,   0, &prov);
        CheckTest ( 2, 0,    1, 0,  0,   n,   1, &prov);
        CheckTest ( 3, 0,    1, 1, -1,   n,   1, &prov);
        CheckTest ( 4, 1,    0, 0,  0,   n,   1, &prov);
        CheckTest ( 5, 1,    0, 1,  n,   n,   0, &prov);
        CheckTest ( 6, 1,    1, 0, -1,   0,   2, &prov);
        CheckTest ( 7, 1,    1, 1,  n,   n,   0, &prov);
        CheckTest ( 8, 5,    7, 2, -1,  -0.4, 2, &prov);
        CheckTest ( 9, 2.5,  7, 4, -2,  -0.8, 2, &prov);
        CheckTest (10, 5,   -7, 2,  0.4, 1,   2, &prov);
        CheckTest (11, 0.0000000000000000001, 1, -2, 2, NAN, 1, &prov);

        if (prov == 1)
            printf("Verification completed successfully!\n\n");
        //assert (prov == 1);
        }

*/

// функция, которая проверяет один тест..............................................................

void CheckTest (int nTest, double a,double b, double c, double x1Correct, double x2Correct, int nanswCorrect, int *prov)
    {
    double x1 = NAN, x2 = NAN;
    int nansw = SolveSquare (a, b, c, &x1, &x2);

    if (!isnan (x1) && !isnan (x2))
        {
        if (!Compare (nansw, nanswCorrect) || !Compare(x1, x1Correct) || !Compare (x2, x2Correct))
            {
            txSetConsoleAttr (0x0E);

            printf ("ERROR TEST %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nansw = %d\n"
                    "CORRECT: x1 = %lg, x2 = %lg, nansw = %d\n\n",
                    nTest, a, b, c, x1, x2, nansw,
                    x1Correct, x2Correct, nanswCorrect);

                    *prov = 0;

            txSetConsoleAttr (0x07);
            }
        }

    if (isnan (x1) && isnan (x2) && Compare (nansw, nanswCorrect))
        ;

    else if ((isnan (x1) && !Compare (x2, x2Correct)) ||
             (isnan (x2) && !Compare (x1, x1Correct)) ||
             (!Compare (nansw, nanswCorrect)))
        {
        txSetConsoleAttr (0x4E);

        printf ("ERROR TEST %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nansw = %d\n"
                    "CORRECT: x1 = %lg, x2 = %lg, nansw = %d\n\n",
                    nTest, a, b, c, x1, x2, nansw,
                    x1Correct, x2Correct, nanswCorrect);

                    *prov = 0;

        txSetConsoleAttr (0x07);
        }
    }

// функция обнуляет очень близкие к нулю значения....................................................

int CloseZero (double a)
    {
    double epsilonPoz =  Accuracy;
    double epsilonNeg = -Accuracy;

    if ((a < epsilonPoz) && (a > epsilonNeg))

        return 1;
    else
        return 0;
    }

// функция, которая сравнивает два числа с определённой точностью....................................

int Compare (double a, double b)
    {
    if (a - b >= Accuracy)
        return 0;
    else
        return 1;
    }





