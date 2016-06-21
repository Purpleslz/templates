#define uLL unsigned long long

const int MAXN = 410;
struct bign
{
    static const int TEN = 10;
	int len, s[MAXN];
	bign ()
	{
		memset(s, 0, sizeof(s));
		len = 1;
	}
	bign (int num) { *this = num; }
	bign (const char *num) { *this = num; }
	bign operator = (const int num)
	{
		char s[MAXN];
		sprintf(s, "%d", num);
		*this = s;
		return *this;
	}
	bign operator = (const char *num)
	{
		for(int i = 0; num[i] == '0'; num++) ;  //???0
		len = strlen(num);
		for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0';
		return *this;
	}
	bign operator + (const bign &b) const //+
	{
		bign c;
		c.len = 0;
		for(int i = 0, g = 0; g || i < max(len, b.len); i++)
		{
			int x = g;
			if(i < len) x += s[i];
			if(i < b.len) x += b.s[i];
			c.s[c.len++] = x % TEN;
			g = x / TEN;
		}
		return c;
	}
	bign operator += (const bign &b)
	{
		*this = *this + b;
		return *this;
	}
	void clean()
	{
		while(len > 1 && !s[len-1]) len--;
	}
	bign operator * (const bign &b) //*
	{
		bign c;
		c.len = len + b.len;
		for(int i = 0; i < len; i++)
		{
			for(int j = 0; j < b.len; j++)
			{
				c.s[i+j] += s[i] * b.s[j];
			}
		}
		for(int i = 0; i < c.len; i++)
		{
			c.s[i+1] += c.s[i]/TEN;
			c.s[i] %= TEN;
		}
		c.clean();
		return c;
	}
	bign operator *= (const bign &b)
	{
		*this = *this * b;
		return *this;
	}
	bign operator - (const bign &b)
	{
		bign c;
		c.len = 0;
		for(int i = 0, g = 0; i < len; i++)
		{
			int x = s[i] - g;
			if(i < b.len) x -= b.s[i];
			if(x >= 0) g = 0;
			else
			{
				g = 1;
				x += TEN;
			}
			c.s[c.len++] = x;
		}
		c.clean();
		return c;
	}
	bign operator -= (const bign &b)
	{
		*this = *this - b;
		return *this;
	}
	bign operator / (const bign &b)
	{
		bign c, f = 0;
		for(int i = len-1; i >= 0; i--)
		{
			f = f*TEN;
			f.s[0] = s[i];
			while(f >= b)
			{
				f -= b;
				c.s[i]++;
			}
		}
		c.len = len;
		c.clean();
		return c;
	}
	bign operator /= (const bign &b)
	{
		*this  = *this / b;
		return *this;
	}
	bign operator % (const bign &b)
	{
		bign r = *this / b;
		r = *this - r*b;
		return r;
	}
	bign operator %= (const bign &b)
	{
		*this = *this % b;
		return *this;
	}
	bool operator < (const bign &b)
	{
		if(len != b.len) return len < b.len;
		for(int i = len-1; i >= 0; i--)
		{
			if(s[i] != b.s[i]) return s[i] < b.s[i];
		}
		return false;
	}
	bool operator > (const bign &b)
	{
		if(len != b.len) return len > b.len;
		for(int i = len-1; i >= 0; i--)
		{
			if(s[i] != b.s[i]) return s[i] > b.s[i];
		}
		return false;
	}
	bool operator == (const bign &b)
	{
		return !(*this > b) && !(*this < b);
	}
	bool operator != (const bign &b)
	{
		return !(*this == b);
	}
	bool operator <= (const bign &b)
	{
		return *this < b || *this == b;
	}
	bool operator >= (const bign &b)
	{
		return *this > b || *this == b;
	}
	string str() const
	{
		string res = "";
		for(int i = 0; i < len; i++) res = char(s[i]+'0') + res;
		return res;
	}
};
bign len, A, B;
bign zero;
istream& operator >> (istream &in, bign &x)
{
	string s;
	in >> s;
	x = s.c_str();
	return in;
}
ostream& operator << (ostream &out, const bign &x)
{
	out << x.str();
	return out;
}
bign gcd(bign a,bign b)
{
	bign temp;
	if(a<b)	swap(a, b);
	while(!(b.len == 1 && b.s[0] == 0))
	{/*?????,??b?0??*/
		temp=a%b;
		a=b;	
		b=temp;
	}
	return a;
}

