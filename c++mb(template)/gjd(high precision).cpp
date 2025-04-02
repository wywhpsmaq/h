//高精度
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
struct INT {
    static const int BASE = 10000000;
    static const int WIDTH = 8;
    vector<int> s;
    int sign;
    INT() : sign(1) {}
    INT(long long num) { *this = num; }
    INT(const string& str) { *this = str; }
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
        INT operator/ (const INT& b) const {
            if (b.s.size() == 1 && b.s[0] == 0) 
                throw runtime_error("Division by zero");
            if (s.size() == 1 && s[0] == 0) 
                return INT(0);
            if (this->abs() < b.abs())
                return INT(0);
                
            INT c;
            c.sign = sign * b.sign;
            INT temp = this->abs();
            INT divisor = b.abs();
            vector<int> result;
            while (temp >= divisor) {
                int current_width = temp.s.size() - divisor.s.size();
                if (current_width < 0) break;
                INT trial = divisor;
                for (int i = 0; i < current_width; i++)
                    trial.s.insert(trial.s.begin(), 0);
                    
                int q = 0;
                while (temp >= trial) {
                    temp -= trial;
                    q++;
                }
                result.push_back(q);
                while (temp.s.size() > 1 && temp.s.back() == 0)
                    temp.s.pop_back();
            }
            reverse(result.begin(), result.end());
            c.s = result;
            if (c.s.empty())
                c.s.push_back(0);
                
            return c;
        }
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
    INT operator<< (const int n) const {
        if (n == 0) return *this;
        if (n < 0) return *this >> (-n);
        INT result = *this;
        for (int i = 0; i < n; i++) {
            result *= 2;
        }
        return result;
    }
    INT operator>> (const int n) const {
        if (n == 0) return *this;
        if (n < 0) return *this << (-n);
        INT result = *this;
        for (int i = 0; i < n; i++) {
            result /= 2;
        }
        return result;
    }
    INT operator& (const INT& b) const {
        INT result;
        result.sign = sign & b.sign;
        string bin1 = this->toBinary();
        string bin2 = b.toBinary();
        int maxLen = max(bin1.length(), bin2.length());
        bin1 = string(maxLen - bin1.length(), '0') + bin1;
        bin2 = string(maxLen - bin2.length(), '0') + bin2;
        string resultBin;
        for (int i = 0; i < maxLen; i++) {
            resultBin += ((bin1[i] - '0') & (bin2[i] - '0')) + '0';
        }
        return INT(binaryToDecimal(resultBin));
    }
    INT operator| (const INT& b) const {
        INT result;
        result.sign = sign | b.sign;
        string bin1 = this->toBinary();
        string bin2 = b.toBinary();
        int maxLen = max(bin1.length(), bin2.length());
        bin1 = string(maxLen - bin1.length(), '0') + bin1;
        bin2 = string(maxLen - bin2.length(), '0') + bin2;
        string resultBin;
        for (int i = 0; i < maxLen; i++) {
            resultBin += ((bin1[i] - '0') | (bin2[i] - '0')) + '0';
        }
        return INT(binaryToDecimal(resultBin));
    }
    INT operator^ (const INT& b) const {
        INT result;
        result.sign = sign ^ b.sign;
        string bin1 = this->toBinary();
        string bin2 = b.toBinary();
        int maxLen = max(bin1.length(), bin2.length());
        bin1 = string(maxLen - bin1.length(), '0') + bin1;
        bin2 = string(maxLen - bin2.length(), '0') + bin2;
        string resultBin;
        for (int i = 0; i < maxLen; i++) {
            resultBin += ((bin1[i] - '0') ^ (bin2[i] - '0')) + '0';
        }
        return INT(binaryToDecimal(resultBin));
    }
    private:
    string toBinary() const {
        INT num = this->abs();
        if (num == INT(0)) return "0";
        string result;
        while (num > INT(0)) {
            result = (char)((num % INT(2)).s[0] + '0') + result;
            num /= 2;
        }
        return result;
    }
    static string binaryToDecimal(const string& binary) {
        INT result = 0;
        INT power = 1;
        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary[i] == '1') {
                result += power;
            }
            power *= 2;
        }
        return result.toString();
    }
    public:
    string toString() const {
        stringstream ss;
        ss << *this;
        return ss.str();
    }
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
int main() {
    ios::sync_with_stdio(false);
    return 0;
}