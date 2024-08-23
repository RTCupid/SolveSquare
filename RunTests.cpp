// �������, ������� ��������� �������� ������ � ������� �������� �������.............................

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
