sigma( (A * i + B) / C )  i = 0 ~ N-1

LL f(int a, int b, int c, int n)
{
    if (a == 0) return (LL)(b / c) * n;
    if (a >= c || b >= c)
    {
        LL ret = 0;
        ret += (LL) (a / c) * (n - 1)  * n / 2;
        ret += (LL) (b / c) * n;
        return ret + f(a % c, b % c, c, n);
    }
    else return f(c, ((LL)a * n + b) % c, a, ((LL)a * n + b) / c);
} 
