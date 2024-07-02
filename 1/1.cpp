#include <iostream>
#include <time.h>
using namespace std;
bool simple(long long int a)
{
    int i;
    for (i = 2; i < sqrt(a); i++)
    {
        if (a % i == 0)
            return false;
    }
    return true;
}

long long int pow_mod(long long int a, long long int n, long long int p)
{
    long long int i, k, n2 = 0, res = 1, * N2;
    if (!simple(p))
    {
        cout << " p не простое.\n";
        return 0;
    }
    for (i = 1, n2 = 1; i * 2 < n; i *= 2, n2++);
    N2 = new long long int[n2 + 1];
    for (i = 0, k = n; i <= n2; i++, k /= 2)
        N2[i] = k % 2;

    for (i = 0; i <= n2; i++)
    {
        if (i > 0)
            k = ((k % p) * (k % p)) % p;
        else
            k = a % p;
        if (N2[i] > 0)
            res = ((res % p) * (k % p)) % p;
    }
    delete[] N2;
    return res;
}

int evk(long long int a, long long int b, long long int& x, long long int& y)
{
    int i;
    long long int obm, q, U[3] = { a, 1, 0 }, V[3] = { b, 0, 1 }, T[3];
    if (a < b)
    {
        obm = a;
        a = b;
        b = obm;
    }
    while (V[0] != 0)
    {
        q = U[0] / V[0];
        for (i = 0; i < 3; i++)
        {
            if (i > 0)
                T[i] = U[i] - q * V[i];
            else
                T[i] = U[i] % V[i];
            U[i] = V[i];
            V[i] = T[i];
        }
    }
    x = U[1];
    y = U[2];
    return U[0];
}

void dh()
{
    long long int p, q = 0, g, X[2], Y[2], Z[2];
    while (!simple(q) || (q == 0) || !simple(p))
    {
        q = rand() % (long long int)pow(10, 9);
        p = 2 * q + 1;
    }
    do
    {
        g = 2 + rand() % (p - 2);
    } while (pow_mod(g, q, p) == 1);
    X[0] = 2 + rand() % (p - 2);
    X[1] = 2 + rand() % (p - 2);
    Y[0] = pow_mod(g, X[0], p);
    Y[1] = pow_mod(g, X[1], p);
    Z[0] = pow_mod(Y[1], X[0], p);
    Z[1] = pow_mod(Y[0], X[1], p);
    cout << " p = " << p << ", Ya = " << Y[0] << ", Yb = " << X[1] << ", Za = " << Z[0] << " = Zb = " << Z[1] << endl;
}

void shmshv(long long int a, long long int p, long long int y)
{
    long long int i, j, m = sqrt(p) + 1, k = m, * Ay, * A;
    if (!simple(p))
    {
        cout << " p не простое.\n";
        return;
    }
    Ay = new long long int[m];
    A = new long long int[k];
    for (i = 0; i < m; i++)
        Ay[i] = (pow_mod(a, i, p) * (y % p)) % p;

    for (i = 0; i < k; i++)
    {
        A[i] = pow_mod(a, m * (i + 1), p);
        for (j = 0; j < m; j++)
        {
            if (A[i] == Ay[j])
            {
                cout << " i = " << i + 1 << ", j = " << j << ", x = " << (i + 1) * m - j << " (" << pow_mod(a, (i + 1) * m - j, p) << ")\n";
                break;
            }
        }
    }
    delete[] Ay;
    delete[] A;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    /*long long int a = rand() % (long long int)pow(10, 9), n = rand() % (long long int)pow(10, 9), p = 0, a2 = 28, b = 19, x = 0, y = 0;
    while (!simple(p) || (p == 0))
        p = rand() % (long long int)pow(10, 9);
    cout << " 1) " << a << " ^ " << n << " mod " << p << " = " << pow_mod(a, n, p) << endl;
    cout << " 2) " << evk(a2, b, x, y);
    cout << " = " << a2 << " * " << x << " + " << b << " * " << y << endl;
    cout << " 3)";
    dh();
    cout << " 4)";
    shmshv(a, p, pow_mod(a, n, p));*/
    long long int a = 0, b = 0, x = 0, y = 0;
    while (!((a != 0) && simple(a) && (b != 0) && simple(b) && (evk(a, b, x, y) == 1)))
    {
        a = rand() % (long long int)pow(10, 9);
        b = rand() % (long long int)pow(10, 9);
    }
    cout << " 1) a = " << a << ", b = " << b << ", НОД = " << evk(a, b, x, y) << " = " << a << " * " << x << " + " << b << " * " << y << " = " << a * x + b * y << endl;
    a = 0;
    b = 0;
    x = 0;
    y = 0;
    while (!((a != 0) && !simple(a) && (b != 0) && !simple(b) && (evk(a, b, x, y) == 1)))
    {
        a = rand() % (long long int)pow(10, 9);
        b = rand() % (long long int)pow(10, 9);
    }
    cout << " 2) a = " << a << ", b = " << b << ", НОД = " << evk(a, b, x, y) << " = " << a << " * " << x << " + " << b << " * " << y << " = " << a * x + b * y << endl;
    a = 0;
    b = 0;
    x = 0;
    y = 0;
    while (!((a != 0) && (b != 0) && (evk(a, b, x, y) != 1)))
    {
        a = rand() % (long long int)pow(10, 9);
        b = rand() % (long long int)pow(10, 9);
    }
    cout << " 3) a = " << a << ", b = " << b << ", НОД = " << evk(a, b, x, y) << " = " << a << " * " << x << " + " << b << " * " << y << " = " << a * x + b * y << endl;
    return 0;
}