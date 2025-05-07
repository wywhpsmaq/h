#include <bits/stdc++.h>
#pragma GCC optimize(2)
typedef long long ll;
using namespace std;
// 快读快写
template <typename T>
inline T read()
{
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
// 超级快读
/*template<typename T>
inline T fastread() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar_unlocked();
    }
    return x * f;
}
*/
template <typename T>
inline void write(T x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
// 刷新输出缓冲区
inline void flush()
{
    fflush(stdout);
}
// 高精度
struct INT
{
    static const int BASE = 100000000; // 1e8
    static const int WIDTH = 8;
    vector<int> s;
    int sign;
    INT() : sign(1) {}
    INT(long long num) { *this = num; }
    INT(const string &str) { *this = str; }
    INT operator=(long long num)
    {
        s.clear();
        sign = num < 0 ? -1 : 1;
        num = std::abs(num);
        do
        {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num);
        return *this;
    }
    INT operator=(const string &str)
    {
        s.clear();
        sign = (str[0] == '-') ? -1 : 1;
        int start = (str[0] == '-') ? 1 : 0;
        int len = (str.length() - start - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++)
        {
            int end = str.length() - i * WIDTH;
            int start2 = max(0, end - WIDTH);
            s.push_back(stoi(str.substr(start2, end - start2)));
        }
        return *this;
    }
    bool operator<(const INT &b) const
    {
        if (sign != b.sign)
            return sign < b.sign;
        if (s.size() != b.s.size())
            return s.size() * sign < b.s.size() * b.sign;
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i])
                return s[i] * sign < b.s[i] * b.sign;
        return false;
    }
    bool operator>(const INT &b) const { return b < *this; }
    bool operator<=(const INT &b) const { return !(b < *this); }
    bool operator>=(const INT &b) const { return !(*this < b); }
    bool operator!=(const INT &b) const { return *this < b || b < *this; }
    bool operator==(const INT &b) const { return !(*this < b) && !(b < *this); }
    INT operator+(const INT &b) const
    {
        if (sign != b.sign)
            return *this - (-b);
        INT c;
        c.sign = sign;
        c.s.resize(max(s.size(), b.s.size()));
        int carry = 0;
        for (size_t i = 0; i < c.s.size(); i++)
        {
            carry += (i < s.size() ? s[i] : 0) + (i < b.s.size() ? b.s[i] : 0);
            c.s[i] = carry % BASE;
            carry /= BASE;
        }
        if (carry)
            c.s.push_back(carry);
        return c;
    }
    INT operator-(const INT &b) const
    {
        if (sign != b.sign)
            return *this + (-b);
        if ((*this).abs() < b.abs())
            return -(b - *this);
        INT c;
        c.sign = sign;
        c.s.resize(s.size());
        int carry = 0;
        for (size_t i = 0; i < s.size(); i++)
        {
            carry = s[i] - (i < b.s.size() ? b.s[i] : 0) - carry;
            if (carry < 0)
            {
                c.s[i] = carry + BASE;
                carry = 1;
            }
            else
            {
                c.s[i] = carry;
                carry = 0;
            }
        }
        while (c.s.size() > 1 && c.s.back() == 0)
            c.s.pop_back();
        return c;
    }
    INT operator*(const INT &b) const
    {
        INT c;
        c.sign = sign * b.sign;
        c.s.resize(s.size() + b.s.size());
        for (size_t i = 0; i < s.size(); i++)
            for (size_t j = 0; j < b.s.size(); j++)
            {
                long long mul = (long long)s[i] * b.s[j] + c.s[i + j];
                c.s[i + j] = mul % BASE;
                c.s[i + j + 1] += mul / BASE;
            }
        while (c.s.size() > 1 && c.s.back() == 0)
            c.s.pop_back();
        return c;
    }
    INT operator/(const INT &b) const
    {
        if (b.s.size() == 1 && b.s[0] == 0)
            throw runtime_error("Division by zero");
        INT a = this->abs(), d = b.abs(), res, cur;
        res.s.resize(a.s.size());
        for (int i = a.s.size() - 1; i >= 0; i--)
        {
            cur.s.insert(cur.s.begin(), a.s[i]);
            while (cur.s.size() > 1 && cur.s.back() == 0)
                cur.s.pop_back();
            int x = 0, l = 0, r = BASE - 1;
            while (l <= r)
            {
                int m = (l + r) / 2;
                INT t = d * m;
                if (t <= cur)
                {
                    x = m;
                    l = m + 1;
                }
                else
                    r = m - 1;
            }
            res.s[i] = x;
            cur = cur - d * x;
        }
        while (res.s.size() > 1 && res.s.back() == 0)
            res.s.pop_back();
        res.sign = sign * b.sign;
        if (res.s.size() == 1 && res.s[0] == 0)
            res.sign = 1;
        return res;
    }
    INT operator%(const INT &b) const
    {
        INT a = *this, d = b;
        INT q = a / d;
        INT r = a - q * d;
        if (r.sign < 0)
            r.sign = 1;
        return r;
    }
    INT operator-() const
    {
        INT c = *this;
        if (c.s.size() == 1 && c.s[0] == 0)
            c.sign = 1;
        else
            c.sign = -sign;
        return c;
    }
    INT abs() const
    {
        INT c = *this;
        c.sign = 1;
        return c;
    }
    INT operator<<(const int n) const
    {
        if (n == 0)
            return *this;
        if (n < 0)
            return *this >> (-n);
        INT result = *this;
        for (int i = 0; i < n; i++)
            result = result * 2;
        return result;
    }
    INT operator>>(const int n) const
    {
        if (n == 0)
            return *this;
        if (n < 0)
            return *this << (-n);
        INT result = *this;
        for (int i = 0; i < n; i++)
            result = result / 2;
        return result;
    }
    INT operator&(const INT &b) const
    {
        // 仅支持非负数
        INT a = this->abs(), bb = b.abs();
        INT res;
        size_t n = max(a.s.size(), bb.s.size());
        res.s.resize(n, 0);
        for (size_t i = 0; i < n; ++i)
        {
            int av = i < a.s.size() ? a.s[i] : 0;
            int bv = i < bb.s.size() ? bb.s[i] : 0;
            res.s[i] = av & bv;
        }
        while (res.s.size() > 1 && res.s.back() == 0)
            res.s.pop_back();
        res.sign = 1;
        return res;
    }
    INT operator|(const INT &b) const
    {
        INT a = this->abs(), bb = b.abs();
        INT res;
        size_t n = max(a.s.size(), bb.s.size());
        res.s.resize(n, 0);
        for (size_t i = 0; i < n; ++i)
        {
            int av = i < a.s.size() ? a.s[i] : 0;
            int bv = i < bb.s.size() ? bb.s[i] : 0;
            res.s[i] = av | bv;
        }
        while (res.s.size() > 1 && res.s.back() == 0)
            res.s.pop_back();
        res.sign = 1;
        return res;
    }
    INT operator^(const INT &b) const
    {
        INT a = this->abs(), bb = b.abs();
        INT res;
        size_t n = max(a.s.size(), bb.s.size());
        res.s.resize(n, 0);
        for (size_t i = 0; i < n; ++i)
        {
            int av = i < a.s.size() ? a.s[i] : 0;
            int bv = i < bb.s.size() ? bb.s[i] : 0;
            res.s[i] = av ^ bv;
        }
        while (res.s.size() > 1 && res.s.back() == 0)
            res.s.pop_back();
        res.sign = 1;
        return res;
    }

public:
    string toString() const
    {
        stringstream ss;
        if (sign == -1)
            ss << '-';
        ss << (s.empty() ? 0 : s.back());
        for (int i = s.size() - 2; i >= 0; i--)
            ss << setw(WIDTH) << setfill('0') << s[i];
        return ss.str();
    }
    friend istream &operator>>(istream &in, INT &x)
    {
        string s;
        in >> s;
        x = s;
        return in;
    }
    friend ostream &operator<<(ostream &out, const INT &x)
    {
        if (x.sign == -1)
            out << '-';
        out << (x.s.empty() ? 0 : x.s.back());
        for (int i = x.s.size() - 2; i >= 0; i--)
            out << setw(WIDTH) << setfill('0') << x.s[i];
        return out;
    }
    INT operator++() { return *this = *this + 1; }
    INT operator++(int)
    {
        INT old = *this;
        ++(*this);
        return old;
    }
    INT operator--() { return *this = *this - 1; }
    INT operator--(int)
    {
        INT old = *this;
        --(*this);
        return old;
    }
    INT operator+=(const INT &b)
    {
        *this = *this + b;
        return *this;
    }
    INT operator-=(const INT &b)
    {
        *this = *this - b;
        return *this;
    }
    INT operator*=(const INT &b)
    {
        *this = *this * b;
        return *this;
    }
    INT operator/=(const INT &b)
    {
        *this = *this / b;
        return *this;
    }
    INT operator%=(const INT &b)
    {
        *this = *this % b;
        return *this;
    }
};
// 快速排序
template <typename T>
int partition(T arr[], int low, int high)
{
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}
template <typename T>
void fastsort(T arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        fastsort(arr, low, pi - 1);
        fastsort(arr, pi + 1, high);
    }
}
// 快速幂,求a^b%m
ll fast_pow(ll a, ll b, ll m)
{
    ll result = 1;
    a %= m;
    while (b > 0)
    {
        if (b & 1)
        {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return result;
}
// 归并排序
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *leftArr = new int[n1];
    int *rightArr = new int[n2];
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    delete[] leftArr;
    delete[] rightArr;
}
void mergesort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
// 二分查找
int erfen(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
// Miller-Rabin素数测试
bool zs(int n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    ll d = n - 1;
    int r = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        r++;
    }
    ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll a : bases)
    {
        if (a >= n)
            break;
        ll x = fast_pow(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++)
        {
            x = (x * x) % n;
            if (x == n - 1)
            {
                composite = false;
                break;
            }
        }
        if (composite)
            return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== gj ===" << endl;
    INT a("123123123");
    INT b("987987987");
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "b / a = " << b / a << endl;
    cout << "b % a = " << b % a << endl;
    cout << "a << 2 = " << (a << 2) << endl;
    cout << "b >> 2 = " << (b >> 2) << endl;
    cout << "a & b = " << (a & b) << endl;
    cout << "a | b = " << (a | b) << endl;
    cout << "a ^ b = " << (a ^ b) << endl;

    cout << "\n=== px ===" << endl;
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    fastsort(arr1, 0, n1 - 1);
    cout << "h: ";
    for (int i = 0; i < n1; i++)
        cout << arr1[i] << " ";
    cout << endl;

    cout << "\n=== m ===" << endl;
    ll x = 2, y = 10, m = 1000000007;
    cout << x << "^" << y << " mod " << m << " = " << fast_pow(x, y, m) << endl;

    cout << "\n=== px ===" << endl;
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    mergesort(arr2, 0, n2 - 1);
    cout << "h: ";
    for (int i = 0; i < n2; i++)
        cout << arr2[i] << " ";
    cout << endl;

    cout << "\n=== cz ===" << endl;
    int target = 34;
    int result = erfen(arr2, 0, n2 - 1, target);
    cout << "cz " << target << " ans: " << (result == -1 ? "no" : "on " + to_string(result)) << endl;

    cout << "\n=== Miller-Rabin ===" << endl;
    int primes[] = {2, 17, 19, 97, 100};
    for (int p : primes)
    {
        cout << p << " ?: " << (zs(p) ? "y" : "n") << endl;
    }

    return 0;
}