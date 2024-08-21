#include <stdio.h>
#include <TXLib.h>

int SolveSquare (double a, double b, double c,  // коэффициенты
                 double *x1, double *x2);       // адреса для решений

void SolveLine (double a, double b, double c,
                double *x1);

void input (double *a, double *b, double *c);

void CleanBuf ();

int CheckTest (int nTest, double a, double b, double c, double x1Correct, double x2Correct, int nanswCorrect );

void RunTests ();

int main ()
    {
    printf ("# Эта программа решает квадратные уравнения\n");
    printf ("# (с) RTCupid, 2024\n");

    RunTests ();                           // программа запускает тесты и проверяет их

    printf ("# Введите a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    input (&a, &b, &c);       // функция написана

    double x1 = NAN, x2 = NAN;                  // решения квадратного уравнения

    int answ = SolveSquare (a, b, c, &x1, &x2); // answ считает количество корней

    //assert (std:(!isNAN (x1)));               // выдаст ошибку, если значение x1 не назначается

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
    /*assert (std: !isNAN (a));
    assert (std: !isNAN (b));
    assert (std: !isNAN (c));*/

    if (a == 0 && b == 0 && c == 0)           // все коэф==0, беск кол-во решений
        return 8;

    else if (a == 0 && b == 0)
        return 0;

    else if (a == 0)       // если преобразуется в линейное уравнение
        {
        SolveLine (a, b, c, x1);
        return 1;
        }

    else if ((a == 0 or b == 0) && c == 0)
        {
        *x1 = 0;
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

            *x1 = (-b - s)/(2*a);
            *x2 = (-b + s)/(2*a);
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

// функция, которая проверяет один тест..............................................................

int CheckTest (int nTest, double a,double b, double c, double x1Correct, double x2Correct, int nanswCorrect, int *prov)
    {
    double x1 = NAN, x2 = NAN;
    int nansw = SolveSquare (a, b, c, &x1, &x2);

    if (!isnan (x1) && !isnan (x2))
        {
        if (nansw != nanswCorrect || x1 != x1Correct || x2 != x2Correct)
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

    if (isnan (x1) && isnan (x2) && nansw == nanswCorrect)
        ;

    else if ((isnan (x1) && x2 != x2Correct) ||
        (isnan (x2) && x1 != x1Correct) ||
        (nansw != nanswCorrect))
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







// функция, которая запускает проверку тестов с разными входными данными.............................

void RunTests ()
        {

        int prov = 1;

        int nTest = 0;
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

        if (prov == 1)
            printf("Проверка пройдена успешно\n\n");
        //assert (prov == 1);
        }

