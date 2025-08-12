#include <bits/stdc++.h>
using namespace std;
#define itn int

// io板块
namespace io {
template <typename T> inline T read () {
	if constexpr (is_same<T, int>::value || is_same<T, long long>::value || is_same<T, unsigned long long>::value) {
		T x = 0, f = 1;
		char ch = getchar ();
		while (!isdigit (ch)) {
			if (ch == '-') f = -1;
			ch = getchar ();
		}
		while (isdigit (ch)) {
			x = x * 10 + ch - '0';
			ch = getchar ();
		}
		return x * f;
	} else if constexpr (is_same<T, char>::value) {
		char ch = getchar ();
		while (ch == '\n' || ch == ' ' || ch == '\r') { ch = getchar (); }
		return ch;
	} else if constexpr (is_same<T, string>::value) {
		string s;
		char ch = getchar ();
		while (ch == '\n' || ch == ' ' || ch == '\r') { ch = getchar (); }
		while (ch != '\n' && ch != ' ' && ch != '\r') {
			s += ch;
			ch = getchar ();
		}
		return s;
	} else if constexpr (is_same<T, double>::value || is_same<T, float>::value) {
		T x = 0, f = 1, div = 1;
		char ch = getchar ();
		while (!isdigit (ch) && ch != '-' && ch != '.') { ch = getchar (); }
		if (ch == '-') f = -1, ch = getchar ();
		while (isdigit (ch)) {
			x = x * 10 + ch - '0';
			ch = getchar ();
		}
		if (ch == '.') {
			ch = getchar ();
			while (isdigit (ch)) {
				x = x * 10 + ch - '0';
				div *= 10;
				ch = getchar ();
			}
		}
		return x * f / div;
	}
}
template <typename T> inline void write (T x) {
	if constexpr (is_same<T, int>::value || is_same<T, long long>::value || is_same<T, unsigned long long>::value) {
		if (x < 0) putchar ('-'), x = -x;
		if (x > 9) write (x / 10);
		putchar (x % 10 + '0');
	} else if constexpr (is_same<T, string>::value) {
		for (char c : x) putchar (c);
	} else if constexpr (is_same<T, char>::value) {
		putchar (x);
	} else if constexpr (is_same<T, double>::value || is_same<T, float>::value) {
		printf ("%.10lf", x);
	}
}
} // namespace io

// 高精度板块
struct INT {
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;
	int sign;
	INT () : sign (1) {
	}
	INT (long long num) {
		*this = num;
	}
	INT (const string &str) {
		*this = str;
	}
	INT operator= (long long num) {
		s.clear ();
		sign = num < 0 ? -1 : 1;
		num = std::abs (num);
		do {
			s.push_back (num % BASE);
			num /= BASE;
		} while (num);
		return *this;
	}
	INT operator= (const string &str) {
		s.clear ();
		sign = (str[0] == '-') ? -1 : 1;
		int start = (str[0] == '-') ? 1 : 0;
		int len = (str.length () - start - 1) / WIDTH + 1;
		for (int i = 0; i < len; i++) {
			int end = str.length () - i * WIDTH;
			int start2 = max (0, end - WIDTH);
			s.push_back (stoi (str.substr (start2, end - start2)));
		}
		return *this;
	}
	bool operator< (const INT &b) const {
		if (sign != b.sign) return sign < b.sign;
		if (s.size () != b.s.size ()) return s.size () * sign < b.s.size () * b.sign;
		for (int i = s.size () - 1; i >= 0; i--)
			if (s[i] != b.s[i]) return s[i] * sign < b.s[i] * b.sign;
		return false;
	}
	bool operator> (const INT &b) const {
		return b < *this;
	}
	bool operator<= (const INT &b) const {
		return !(b < *this);
	}
	bool operator>= (const INT &b) const {
		return !(*this < b);
	}
	bool operator!= (const INT &b) const {
		return *this < b || b < *this;
	}
	bool operator== (const INT &b) const {
		return !(*this < b) && !(b < *this);
	}
	INT operator+ (const INT &b) const {
		if (sign != b.sign) return *this - (-b);
		INT c;
		c.sign = sign;
		c.s.resize (max (s.size (), b.s.size ()));
		int carry = 0;
		for (size_t i = 0; i < c.s.size (); i++) {
			carry += (i < s.size () ? s[i] : 0) + (i < b.s.size () ? b.s[i] : 0);
			c.s[i] = carry % BASE;
			carry /= BASE;
		}
		if (carry) c.s.push_back (carry);
		return c;
	}
	INT operator- (const INT &b) const {
		if (sign != b.sign) return *this + (-b);
		if ((*this).abs () < b.abs ()) return -(b - *this);
		INT c;
		c.sign = sign;
		c.s.resize (s.size ());
		int carry = 0;
		for (size_t i = 0; i < s.size (); i++) {
			carry = s[i] - (i < b.s.size () ? b.s[i] : 0) - carry;
			if (carry < 0) {
				c.s[i] = carry + BASE;
				carry = 1;
			} else {
				c.s[i] = carry;
				carry = 0;
			}
		}
		while (c.s.size () > 1 && c.s.back () == 0) c.s.pop_back ();
		return c;
	}
	INT operator* (const INT &b) const {
		INT c;
		c.sign = sign * b.sign;
		c.s.resize (s.size () + b.s.size ());
		for (size_t i = 0; i < s.size (); i++)
			for (size_t j = 0; j < b.s.size (); j++) {
				long long mul = (long long)s[i] * b.s[j] + c.s[i + j];
				c.s[i + j] = mul % BASE;
				c.s[i + j + 1] += mul / BASE;
			}
		while (c.s.size () > 1 && c.s.back () == 0) c.s.pop_back ();
		return c;
	}
	INT operator/ (const INT &b) const {
		if (b.s.size () == 1 && b.s[0] == 0) throw runtime_error ("Division by zero");
		INT a = this->abs (), d = b.abs (), res, cur;
		res.s.resize (a.s.size ());
		for (int i = a.s.size () - 1; i >= 0; i--) {
			cur.s.insert (cur.s.begin (), a.s[i]);
			while (cur.s.size () > 1 && cur.s.back () == 0) cur.s.pop_back ();
			int x = 0, l = 0, r = BASE - 1;
			while (l <= r) {
				int m = (l + r) / 2;
				INT t = d * m;
				if (t <= cur) {
					x = m;
					l = m + 1;
				} else r = m - 1;
			}
			res.s[i] = x;
			cur = cur - d * x;
		}
		while (res.s.size () > 1 && res.s.back () == 0) res.s.pop_back ();
		res.sign = sign * b.sign;
		if (res.s.size () == 1 && res.s[0] == 0) res.sign = 1;
		return res;
	}
	INT operator% (const INT &b) const {
		INT a = *this, d = b;
		INT q = a / d;
		INT r = a - q * d;
		if (r.sign < 0) r.sign = 1;
		return r;
	}
	INT operator- () const {
		INT c = *this;
		if (c.s.size () == 1 && c.s[0] == 0) c.sign = 1;
		else c.sign = -sign;
		return c;
	}
	INT abs () const {
		INT c = *this;
		c.sign = 1;
		return c;
	}
	INT operator<< (const int n) const {
		if (n == 0) return *this;
		if (n < 0) return *this >> (-n);
		INT result = *this;
		for (int i = 0; i < n; i++) result = result * 2;
		return result;
	}
	INT operator>> (const int n) const {
		if (n == 0) return *this;
		if (n < 0) return *this << (-n);
		INT result = *this;
		for (int i = 0; i < n; i++) result = result / 2;
		return result;
	}
	INT operator& (const INT &b) const {
		INT a = this->abs (), bb = b.abs ();
		INT res;
		size_t n = max (a.s.size (), bb.s.size ());
		res.s.resize (n, 0);
		for (size_t i = 0; i < n; ++i) {
			int av = i < a.s.size () ? a.s[i] : 0;
			int bv = i < bb.s.size () ? bb.s[i] : 0;
			res.s[i] = av & bv;
		}
		while (res.s.size () > 1 && res.s.back () == 0) res.s.pop_back ();
		res.sign = 1;
		return res;
	}
	INT operator| (const INT &b) const {
		INT a = this->abs (), bb = b.abs ();
		INT res;
		size_t n = max (a.s.size (), bb.s.size ());
		res.s.resize (n, 0);
		for (size_t i = 0; i < n; ++i) {
			int av = i < a.s.size () ? a.s[i] : 0;
			int bv = i < bb.s.size () ? bb.s[i] : 0;
			res.s[i] = av | bv;
		}
		while (res.s.size () > 1 && res.s.back () == 0) res.s.pop_back ();
		res.sign = 1;
		return res;
	}
	INT operator^ (const INT &b) const {
		INT a = this->abs (), bb = b.abs ();
		INT res;
		size_t n = max (a.s.size (), bb.s.size ());
		res.s.resize (n, 0);
		for (size_t i = 0; i < n; ++i) {
			int av = i < a.s.size () ? a.s[i] : 0;
			int bv = i < bb.s.size () ? bb.s[i] : 0;
			res.s[i] = av ^ bv;
		}
		while (res.s.size () > 1 && res.s.back () == 0) res.s.pop_back ();
		res.sign = 1;
		return res;
	}

  public:
	string toString () const {
		stringstream ss;
		if (sign == -1) ss << '-';
		ss << (s.empty () ? 0 : s.back ());
		for (int i = s.size () - 2; i >= 0; i--) ss << setw (WIDTH) << setfill ('0') << s[i];
		return ss.str ();
	}
	friend istream &operator>> (istream &in, INT &x) {
		string s;
		in >> s;
		x = s;
		return in;
	}
	friend ostream &operator<< (ostream &out, const INT &x) {
		if (x.sign == -1) out << '-';
		out << (x.s.empty () ? 0 : x.s.back ());
		for (int i = x.s.size () - 2; i >= 0; i--) out << setw (WIDTH) << setfill ('0') << x.s[i];
		return out;
	}
	INT operator++ () {
		return *this = *this + 1;
	}
	INT operator++ (int) {
		INT old = *this;
		++(*this);
		return old;
	}
	INT operator-- () {
		return *this = *this - 1;
	}
	INT operator-- (int) {
		INT old = *this;
		--(*this);
		return old;
	}
	INT operator+= (const INT &b) {
		*this = *this + b;
		return *this;
	}
	INT operator-= (const INT &b) {
		*this = *this - b;
		return *this;
	}
	INT operator*= (const INT &b) {
		*this = *this * b;
		return *this;
	}
	INT operator/= (const INT &b) {
		*this = *this / b;
		return *this;
	}
	INT operator%= (const INT &b) {
		*this = *this % b;
		return *this;
	}
};
int main () {
	INT A, B;
	long long a=558, b=1145;
	//cin >> a >> b;
	A = a, B = b;
	auto nn = chrono::system_clock::now ().time_since_epoch ().count ();
	cout << "+ : " << A + B << "----" << a + b << '\n';
	cout << "- : " << A - B << "----" << a - b << '\n';
	cout << "* : " << A * B << "----" << a * b << '\n';
	cout << "/ : " << A / B << "----" << a / b << '\n';
	cout << "% : " << A % B << "----" << a % b << '\n';
	cout << "++ : " << ++A << "----" << ++a << '\n';
	cout << "-- : " << --A << "----" << --a << '\n';
	cout << "== : " << (A == B) << "----" << (a == b) << '\n';
	cout << "!= : " << (A != B) << "----" << (a != b) << '\n';
	cout << "> : " << (A > B) << "----" << (a > b) << '\n';
	cout << "< : " << (A < B) << "----" << (a < b) << '\n';
	cout << ">= : " << (A >= B) << "----" << (a >= b) << '\n';
	cout << "<= : " << (A <= B) << "----" << (a <= b) << '\n';
	cout << "& : " << (A & B) << "----" << (a & b) << '\n';
	cout << "| : " << (A | B) << "----" << (a | b) << '\n';
	cout << "^ : " << (A ^ B) << "----" << (a ^ b) << '\n';
	cout << "<< : " << (A << 1) << "----" << (a << 1) << '\n';
	cout << ">> : " << (A >> 1) << "----" << (a >> 1) << '\n';
	cout << "abs : " << A.abs () << "----" << abs (a) << '\n';
	cout << "toString : " << A.toString () << "----" << to_string (a) << '\n';
	cout << "time:" << (chrono::system_clock::now ().time_since_epoch ().count () - nn)/1e6 << '\n';
	return 0;
}
