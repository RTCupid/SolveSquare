
const double Accuracy = 1e-08;                  // точность округления до нуля

struct OneTest
    {
    double a, b, c;
    double x1Correct, x2Correct;
    int nanswCorrect;
    };

const int SS_INF_nansw = 8;

//{
//! @brief   SolveSquare - решает квадратное уравнение
//!
//! @param   a     а   -   первый коэффициент квадратного уравнения
//! @param   b     b   -   второй коэффициент квадратного уравнения
//! @param   c     c   -   третий коэффициент квадратного уравнения
//! @param   &x1   &x1 -   адрес для возврата первого (меньшего) корня квадратного уравнения
//! @param   &x2   &x2 -   адрес для возврата второго корня квадратного уравнения
//!
//! @return  количество корней уравнения, 0, 1, 2 или 8 в случае, если бесконечное количество корней
//!
//! @code
//!     SolveSquare (1, 3, 4, &x1, &x2);
//! @endcode
//}

int SolveSquare (double a, double b, double c,  // коэффициенты квадратного уравнения
                 double *x1, double *x2);       // адреса для корней квадратного уравнения

//{
//! @brief   функция ввода
//! @param   double *a - адрес для возврата первого коэффициента квадратного уравнения
//! @param   double *b - адрес для возврата второго коэффициента квадратного уравнения
//! @param   double *c - адрес для возврата третьего коэффициента квадратного уравнения
//! @return  0, если ввод не удачный
//!          1, если ввод удачный
//! @code
//!     Input (&a, &b, &c);
//! @endcode
//}

int Input (double *a, double *b, double *c);    // функция ввода

void CleanBuf ();                               //!< функция очистки буфера

void RunTests ();                               //!< функция для прогонки тестов

void CheckTest (int nTest, OneTest data, int *prov); //!< функция проверки теста

int CloseZero (double a);                       //!< функция для сравнения с нулём

int Compare (double a, double b);               //!< функция для сравнений двух чисел с точностью Accuracy



void output (int nansw, double x1, double x2);  //!< функция вывода ответа взависимости от количества корней

