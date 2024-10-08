#include <stdio.h>
#include "TXLib.h"
#include "SolveSquare.h"

// �������, ������� ��������� �������� ������ � ������� �������� �������.............................

void RunTests ()
    {
    const int countTests = 12;

    int prov = 1;

    double n = NAN;
                                      //a       b        c   x1Correct x2Correct nAnswCorrect
    struct OneTest data[countTests] = {{0,      0,       0,  n,        n,        SS_INF_nAnsw   },  //0  ����
                                       {0,      0,       1,  n,        n,        0              },  //1  ����
                                       {0,      1,       0,  0,        n,        1              },  //2  ����
                                       {0,      1,       1, -1,        n,        1              },  //3  ����
                                       {1,      0,       0,  0,        n,        1              },  //4  ����
                                       {1,      0,       1,  n,        n,        0              },  //5  ����
                                       {1,      1,       0, -1,        0,        2              },  //6  ����
                                       {1,      1,       1,  n,        n,        0              },  //7  ����
                                       {5,      7,       2, -1,       -0.4,      2              },  //8  ����
                                       {2.5,    7,       4, -2,       -0.8,      2              },  //9  ����
                                       {5,     -7,       2,  0.4,      1,        2              },  //10 ����
                                       {1e-10,  1,      -2,  2,        n,        1              }}; //11 ����


    for (int i = 0; i < countTests; i++)
        CheckTest (i, data[i], &prov);


    if (prov == 1)
            printf("Verification completed successfully!\n\n");
    }

// �������, ������� ��������� ���� ����..............................................................

void CheckTest (int nTest, OneTest data, int *prov)
    {
    double x1 = NAN, x2 = NAN;
    int nAnsw = SolveSquare (data.a, data.b, data.c, &x1, &x2);

    if (!isnan (x1) && !isnan (x2))
        {
        if (!AreEqual (nAnsw, data.nAnswCorrect) || !AreEqual(x1, data.x1Correct) || !AreEqual (x2, data.x2Correct))
            {
            txSetConsoleAttr (0x0E);

            printf ("ERROR TEST %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nansw = %d\n"
                    "CORRECT: x1 = %lg, x2 = %lg, nansw = %d\n\n",
                    nTest, data.a, data.b, data.c, x1, x2, nAnsw,
                    data.x1Correct, data.x2Correct, data.nAnswCorrect);

                    *prov = 0;

            txSetConsoleAttr (0x07);
            }
        }

    else if (isnan (x1) && isnan (x2) && AreEqual (nAnsw, data.nAnswCorrect))
        ;

    else if ((isnan (x1) && !AreEqual (x2, data.x2Correct)) ||
             (isnan (x2) && !AreEqual (x1, data.x1Correct)))
        {
        txSetConsoleAttr (0x4E);

        printf ("ERROR TEST %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nAnsw = %d\n"
                    "CORRECT: x1 = %lg, x2 = %lg, nAnsw = %d\n\n",
                    nTest, data.a, data.b, data.c, x1, x2, nAnsw,
                    data.x1Correct, data.x2Correct, data.nAnswCorrect);

                    *prov = 0;

        txSetConsoleAttr (0x07);
        }
    }

// ������� ������� "verification tests..."..............................................................

void StartVerification ()
    {
    printf ("Verification tests...\n");
    }


