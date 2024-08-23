
const double Accuracy = 1e-08;                  // �������� ���������� �� ����

struct OneTest
    {
    double a, b, c;
    double x1Correct, x2Correct;
    int nanswCorrect;
    };

const int SS_INF_nansw = 8;

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

void CheckTest (int nTest, OneTest data, int *prov); //!< ������� �������� �����

int CloseZero (double a);                       //!< ������� ��� ��������� � ����

int Compare (double a, double b);               //!< ������� ��� ��������� ���� ����� � ��������� Accuracy



void output (int nansw, double x1, double x2);  //!< ������� ������ ������ ������������ �� ���������� ������

