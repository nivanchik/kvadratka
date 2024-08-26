#include <TXLib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#define MICRO 10e-6
//#define INF //1000
//#define NAN

struct StructTest
    {
    int nomTest;
    double a, b, c;
    double x1Good, x2Good;
    int nRootsGood;
    };

typedef enum
    {
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    IN_FINITY = 1000
    } NumbRoots;

typedef enum
    {
    NO,
    YES
    }Logic;

void input (double* a, double* b, double* c);

int Calculetion (double a, double b, double c,
                 double* x1, double* x2);

void output (int nRoots, double x1, double x2);

int SolveLine (double a, double b, double c,
               double* x1);

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2);
int IS_ZERO (double y);

int IS_comparison (double n, double m);

int RunTest (double a, double b, double c, double x1good, double x2good, int nRootsgood);
//int RunTest (struct StructTest);

void CleanBufer ();

int testing ();

int main () /*Квадратка*/
    {
    char ch = 0;
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int i = 1;

    int testing ();

    if (testing ()  == YES)
        {
        printf ("Тест прошёл успешно!\n\n");

        printf ("Для запуска программы нажмите [Enter]\nДля выхода нажмите [Ctrl/Z], затем дважды [Enter]\n");

        while ((ch = getchar()) != EOF)
            {
            printf ("Запуск номер %d\n", i++);

            input (&a, &b, &c);

            assert (isfinite (a)); //возможно перенести
            assert (isfinite (b));
            assert (isfinite (c));

            int nRoots = Calculetion (a, b, c, &x1, &x2);

            output (nRoots, x1, x2);

            CleanBufer ();

            printf ("\n\nДля запуска программы нажмите [Enter]\nДля выхода нажмите [Ctri/Z], затем дважды [Enter]\n");
            }
        }
    else
        printf ("Переписывай программу");
    return 0;
    }

void input (double* a, double* b, double* c)
    {
    assert (a != 0);
    assert (b != 0);
    assert (c != 0);
    printf ("Введите значения коэффииентов квадратного уравнения по порядку\n");

    int vvod = scanf ("%lg %lg %lg", a, b, c);

    if (vvod < 3)
        {
        int i = 0;

        for (i; vvod < 3; i++)
            {
            if (i == 5)
                break;

            printf ("Неверный ввод данных! \n Введите числа\n ");

            CleanBufer ();

            vvod = scanf ("%lg %lg %lg", a, b, c);
            }
        }
    }

int Calculetion (double a, double b, double c,
                 double* x1, double* x2)
    {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1 != 0);
    assert (x2 != 0);
    assert (x1 != x2);

    if (IS_ZERO (a) == YES)
        return SolveLine (a, b, c, x1);
    else /* if (a != 0) */
        return SolveSquare (a, b, c, x1, x2);
    }

int SolveLine (double a, double b, double c,
               double* x1)
    {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1 != 0);

    if (IS_ZERO (b) == YES)
        {
        if (IS_ZERO (c) == YES)
            return IN_FINITY;
        else /* if (c != 0)*/
            return NO_ROOTS;
        }
    else /* if (b != 0) */
        {
        *x1 = -c / b;
        return ONE_ROOT;
        }
    }
void output (int nRoots, double x1, double x2)
    {
    switch (nRoots)
        {
        case NO_ROOTS:
            printf ("Нет корней\n");
            break;

        case ONE_ROOT:
            printf ("Один корень \n x = %lg\n", x1);
            break;

        case TWO_ROOTS:
            printf ("Корни квадратного уравнения: \n x1 = %lg, x2 = %lg\n", x1, x2);
            break;

        case IN_FINITY:
            printf ("Бесконечно много корней\n");
            break;
        }
    }

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2)
    {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1 != 0);
    assert (x2 != 0);
    assert (x1 != x2);

    double d = b * b - 4 * a * c;

    if (d < 0)
        return NO_ROOTS;
    else if (IS_ZERO (d) == YES)
        {
        *x1 = -b / (2 * a);
        return ONE_ROOT;
        }
    else
        {
        double sqrt_d = sqrt (d);

        *x1 = (-b + sqrt_d) / (2 * a);
        *x2 = (-b - sqrt_d) / (2 * a);

        return TWO_ROOTS;
        }
    }

int IS_ZERO (double y) /*Проверяем равенство нулю некоторой переменной*/
    {
    if (fabs(y) < MICRO)
        return YES;
    else
        return NO;
    }

int IS_comparison (double n, double m) /*Проверяем равенство вещественных переменных*/
    {
    if (fabs (m - n) < MICRO)
        return YES;
    else
        return NO;
    }

int RunTest (double a, double b, double c, double x1Good, double x2Good, int nRootsGood)
    {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (isfinite (x1Good));
    assert (isfinite (x2Good));
    assert (isfinite (nRootsGood));

    double x1 = 0, x2 = 0;

    int nRoots = Calculetion (a, b, c, &x1, &x2);

    if (nRoots != nRootsGood || IS_comparison(x1, x1Good) == NO || IS_comparison(x2, x2Good) == NO)
        {
        printf ("Тест не пройден: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n"
                "Должно быть так: x1 = %lg, x2 = %lg, nRoots = %d\n",
                a, b, c, x1, x2, nRoots, x1Good, x2Good, nRootsGood);
        return NO;
        }
    else
        return YES;
    }

/*int RunTest (struct StructTest)
    {
    assert (isfinite (StructTest.a));
    assert (isfinite (StructTest.b));
    assert (isfinite (StructTest.c));

    assert (isfinite (StructTest.x1Good));
    assert (isfinite (StructTest.x2Good));
    assert (isfinite (StructTest.nRootsGood));

    double x1 = 0, x2 = 0;

    int nRoots = Calculetion (StructTest.a, StructTest.b, StructTest.c, &x1, &x2);

    if (nRoots != StructTest.nRootsGood || IS_comparison(x1, StructTest.x1Good) == NO || IS_comparison(x2, StructTest.x2Good) == NO)
        {
        printf ("Тест не пройден: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n"
                "Должно быть так: x1 = %lg, x2 = %lg, nRoots = %d\n",
                StructTest.a, StructTest.b, StructTest.c, x1, x2, nRoots, StructTest.x1Good, StructTest.x2Good, StructTest.nRootsGood);
        return NO;
        }
    else
        return YES;
    }     */

void CleanBufer ()
    {
    while (getchar() != '\n') {}
    }

int testing ()
{
int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;

a = RunTest (1, 2, -3, 1, -3, 2);
b = RunTest (1.1, 2.2, -3.3, 1, -3, 2);
c = RunTest (1, -4, 4, 2, 0, 1);
d = RunTest (0, 0, 0, 0, 0, IN_FINITY);
e = RunTest (0, 2, -3, 1.5, 0, 1);
f = RunTest (7, 7, 7, 0, 0, 0);
g = RunTest (0, 0, 7, 0, 0, 0);

if (a == NO || b == NO || c == NO || d == NO || e == NO || f == NO || g == NO)
    return NO;
else
    return YES;

/*const int N = 7;
StructTest test1 = {1, 1, 2, -3, 1, -3, 2};
StructTest test2 = {2, 1.5, 2.5, -3.5, 0.906718, -2.57338, 2};
StructTest test3 = {3, 1, -4, 4, 2, 0, 1};
StructTest test4 = {4, 0, 0, 0, 0, 0, IN_FINITY};
StructTest test5 = {5, 0, 2, -3, 1.5, 0, 1};
StructTest test6 = {6, 7, 7, 7, 0, 0, 0};
StructTest test7 = {7, 0, 0, 7, 0, 0, 0};

/*for (int i = 0, .nomRoots < N, i++)
{
RunTest (*/

/*RunTest (struct StructTest);

if (RunTest(test1) == NO || RunTest(test2) == NO || RunTest(test3) == NO ||
 RunTest(test4) == NO || RunTest(test5) == NO || RunTest(test6) == NO || RunTest(test7) == NO)
    return NO;
else
    return YES;  */

}
