#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
vector<int> a_;
int zsd() {
    int x = 0 , flag = 0;
    char a = getchar ();
    while ( a > '9' || a < '0' ) {
        if ( a == '-' ) flag = 1;
        a = getchar ();}
    while ( a >= '0' && a <= '9' ) {
        x = x * 10 + a - '0';
        a = getchar ();}
    return flag ? - x : x;}
void zsx(int x) {
    if ( x < 0 ) {
        putchar ('-');
        x = - x;}
    if ( x > 9 ) zsx (x / 10);
    putchar (x % 10 + '0');}
bool zhishu(int a) {
    if ( a == 1 || a == 0 ) return false;
    if (a == 2) return true;
    for ( int i = 2 ; i * i < a ; i ++ ) {
        if ( a % i == 0 ) return false;}
    return true;}
int erfen(int x) {
    int l = 1 , r = a_ . size ();
    while ( l < r ) {
        int mid = l + (r - l) / 2;
        if ( a_[mid] >= x ) r = mid;
        else l = mid + 1;}
    if ( a_[l] == x ) return l;
    else return - 1;}
string jzh(int n,string s,int m) {
    __int128 num = 0 , temp , sum = 1;
    int len = s . size ();
    for ( int i = len - 1 ; i >= 0 ; i -- ) {
        if ( s[i] > '9' ) temp = s[i] - 55;
        else temp = s[i] - '0';
        num += temp * sum;
        sum *= n;}
    len = 0;
    string ans;
    for ( int i = 0 ; i < 100 ; i ++ ) ans += '0';
    while ( num > 0 ) {
        temp = num % m;
        ans[++ len] = temp + '0';
        if ( ans[len] > '9' ) ans[len] += 7;
        num /= m;}
    return ans;}
struct INT {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector < int > s;
    int sign;
    INT () : sign (1) { }
    INT (long long num) {*this = num;}
    INT (const string & str) {*this = str;}
    INT operator= (long long num) {
        s . clear ();
        sign = num < 0 ? - 1 : 1;
        num = std::abs (num);
        do {
            s . push_back (num % BASE);
            num /= BASE;
        } while ( num );
        return *this;}
    INT operator= (const string & str) {
        s . clear ();
        sign = (str[0] == '-') ? - 1 : 1;
        int start = (str[0] == '-') ? 1 : 0;
        int len = (str . length () - start - 1) / WIDTH + 1;
        for ( int i = 0 ; i < len ; i ++ ) {
            int end = str . length () - i * WIDTH;
            int start = max (0 , end - WIDTH);
            s . push_back (stoi (str . substr (start , end - start)));}
        return *this;}
    bool operator< (const INT & b) const {
        if ( sign != b . sign ) return sign < b . sign;
        if ( s . size () != b . s . size ()) return s . size () * sign < b . s . size () * b . sign;
        for ( int i = s . size () - 1 ; i >= 0 ; i -- )
            if ( s[i] != b . s[i] ) return s[i] * sign < b . s[i] * b . sign;
        return false;}
    bool operator> (const INT & b) const { return b < *this; }
    bool operator<= (const INT & b) const { return ! (b < *this); }
    bool operator>= (const INT & b) const { return ! (*this < b); }
    bool operator!= (const INT & b) const { return *this < b || b < *this; }
    bool operator== (const INT & b) const { return ! (*this < b) && ! (b < *this); }
    INT operator+ (const INT & b) const {
        if ( sign != b . sign ) return *this - (- b);
        INT c;
        c . sign = sign;
        c . s . resize (max (s . size () , b . s . size ()));
        int carry = 0;
        for ( size_t i = 0 ; i < c . s . size () ; i ++ ) {
            carry += (i < s . size () ? s[i] : 0) + (i < b . s . size () ? b . s[i] : 0);
            c . s[i] = carry % BASE;
            carry /= BASE;}
        if ( carry ) c . s . push_back (carry);
        return c;}
    INT operator- (const INT & b) const {
        if ( sign != b . sign ) return *this + (- b);
        if ((*this) . abs () < b . abs ()) return - (b - *this);
        INT c;
        c . sign = sign;
        c . s . resize (s . size ());
        int carry = 0;
        for ( size_t i = 0 ; i < s . size () ; i ++ ) {
            carry = s[i] - (i < b . s . size () ? b . s[i] : 0) - carry;
            c . s[i] = carry < 0 ? carry + BASE : carry;
            carry = carry < 0;}
        while ( c . s . size () > 1 && c . s . back () == 0 ) c . s . pop_back ();
        return c;}
    INT operator* (const INT & b) const {
        INT c;
        c . sign = sign * b . sign;
        c . s . resize (s . size () + b . s . size ());
        for ( size_t i = 0 ; i < s . size () ; i ++ )
            for ( size_t j = 0 ; j < b . s . size () ; j ++ ) {
                long long mul = (long long) s[i] * b . s[j];
                int k = i + j;
                while ( mul ) {
                    mul += c . s[k];
                    c . s[k] = mul % BASE;
                    mul /= BASE;
                    k ++;}}
        while ( c . s . size () > 1 && c . s . back () == 0 ) c . s . pop_back ();
        return c;}
    INT operator/ (const INT & b) const {
        INT c , d = 0;
        c . sign = sign * b . sign;
        for ( int i = s . size () - 1 ; i >= 0 ; i -- ) {
            d = d * BASE + s[i];
            int l = 0 , r = BASE - 1;
            while ( l < r ) {
                int mid = (l + r + 1) / 2;
                if ( b * mid <= d ) l = mid;
                else r = mid - 1;}
            c . s . push_back (l);
            d = d - b * l;}
        reverse (c . s . begin () , c . s . end ());
        while ( c . s . size () > 1 && c . s . back () == 0 )c . s . pop_back ();
        return c;}
    INT operator% (const INT & b) const {
        INT c = *this - *this / b * b;
        c . sign = 1;
        return c;}
    INT operator- () const {
        INT c = *this;
        c . sign = - sign;
        return c;}
    INT abs () const {
        INT c = *this;
        c . sign = 1;
        return c;}
    friend istream & operator>> (istream & in , INT & x) {
        string s;
        in >> s;
        x = s;
        return in;}
    friend ostream & operator<< (ostream & out , const INT & x) {
        if ( x . sign == - 1 )out << '-';
        out << (x . s . empty () ? 0 : x . s . back ());
        for ( int i = x . s . size () - 2 ; i >= 0 ; i -- )out << setw (WIDTH) << setfill ('0') << x . s[i];
        return out;}
    INT operator++ () {return *this = *this + 1;}
    INT operator++ (int) {INT old = *this;++ (*this);return old;}
    INT operator-- () {return *this = *this - 1;}
    INT operator-- (int) {INT old = *this;-- (*this);return old;}
    INT operator+= (const INT & b) {*this = *this + b;return *this;}
    INT operator-= (const INT & b) {*this = *this - b;return *this;}
    INT operator*= (const INT & b) {*this = *this * b;return *this;}
    INT operator/= (const INT & b) {*this = *this / b;return *this;}
    INT operator%= (const INT & b) {*this = *this % b;return *this;}
};
int main(){
    ios::sync_with_stdio(false);
    INT a,ans=1;
    cin>>a;
    for(INT I;I<a;I++) ans*=2;
    cout<<ans-1;
    return 0;
}
