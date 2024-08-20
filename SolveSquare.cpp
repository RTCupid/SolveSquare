#include <stdio.h>
#include <TXLib.h>

int SolveSquare (double a, double b, double c,  // ������������
                 double *x1, double *x2);       // ������ ��� �������

void SolveLine (double a, double b, double c,
                double *x1);

void input (double *a, double *b, double *c);

void CleanBuf ();

int main ()
    {
    printf ("# ��� ��������� ������ ���������� ���������\n");
    printf ("# (�) RTCupid, 2024\n");
    printf ("# ������� a, b, c\n");

    double a = NAN, b = NAN, c = NAN;
    input (&a, &b, &c);       // ������� �� ��������
    /*double a = NAN, b = NAN, c = NAN;         // ��� �������
                                                // �����
    scanf ("%lg %lg %lg", &a, &b, &c);*/

    double x1 = NAN, x2 = NAN;                  // ������� ����������� ���������

    int answ = SolveSquare (a, b, c, &x1, &x2); // answ ������� ���������� ������

    switch (answ)                               // ������ ����� � ����������� �� ���������� �������
        {
        case 0:
            printf ("��� �������");
            break;
        case 1:
            printf ("x = %lg", x1);
            break;
        case 2:
            printf ("x1 = %lg, x2 = %lg", x1, x2);
            break;
        case 8: // �������: ����������� ���-�� �������, ������������� = 8 ��������� �� 90 ��������
            printf ("x = ����� �����");
            break;
        default:
            printf("answ = %d", answ);
        }
    }

// ������� ����������� ���������.....................................................................

int SolveSquare (double a, double b, double c, double *x1, double *x2)  // ������� ���������
    {
    assert (x1 != x2);

    if (a == 0 and b == 0 and c == 0)           // ��� ����==0, ���� ���-�� �������
        return 8;
    else if (a == 0 or c == 0 and a != c)       // ���� ������������� � �������� ���������
        {
        SolveLine (a, b, c, x1);
        return 1;
        }
    else                                        // ���� ����������
        {
        float d = b*b - 4*a*c;                  // d = ������������
        if (d < 0)                              // ������������ < 0, ��� �������
            return 0;
        else if (d == 0)                        // ������������ = 0, ���� �������
            {
            *x1 = -b/(2*a);
            return 1;
            }
        else                                    // �� ����, ��� �����
            {
            double s = sqrt (d);                // s = ������ �� �������������
            *x1 = (-b + s)/(2*a);
            *x2 = (-b - s)/(2*a);
            return 2;
            }
        }
    }

// ������� ��������� ���������.......................................................................

void SolveLine (double a, double b, double c, double *x1)
    {
    if (a == 0)
        *x1 = -c/b;
    else                                        // � == 0
        *x1 = -b/a;
    }

// ������� �����.....................................................................................

void input (double *a, double *b, double *c)
    {
    int kol = scanf ("%lg %lg %lg", a, b, c);   // kol ������� ���������� �������� �����

    int nTries = 2;
    while (kol != 3)
        {
        if (nTries == 0)
            {
            printf ("��������� ���������� �������!\n");
            printf ("������������ ����");
            break;
            }
        CleanBuf ();

        printf ("�������� ������ �����!\n");
        printf ("������� ��� �����, ��������� ����� �� ����������\n");
        printf ("�������� %d �������\n", nTries);

        kol = scanf ("%lg %lg %lg", a, b, c);
        nTries--;
        }

    assert (kol == 3);                          // ������������ ������ ������� ������
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
