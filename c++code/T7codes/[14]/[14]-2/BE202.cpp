#include <bits/stdc++.h>
using namespace std;
struct uu {
	int t, b;
};
int main () {
	int z;
	cin >> z;
	while (z--) {
		int n, num;
		cin >> n >> num;
		vector<uu> p (n);
		for (int i = 0; i < n; ++i) { cin >> p[i].t >> p[i].b; }
		vector<uu> v, o;
		for (auto &uu : p) {
			if (uu.b >= 0) {
				v.push_back (uu);
			} else {
				o.push_back (uu);
			}
		}
		sort (v.begin (), v.end (), [] (const uu &a, const uu &b) { return a.t < b.t; });
		sort (o.begin (), o.end (), [] (const uu &a, const uu &b) { return a.t + a.b > b.t + b.b; });
		vector<uu> sum;
		sum.insert (sum.end (), v.begin (), v.end ());
		sum.insert (sum.end (), o.begin (), o.end ());
		bool f = true;
		for (auto &uu : sum) {
			if (num <= uu.t) {
				f = false;
				break;
			}
			num += uu.b;
			if (num <= 0) {
				f = false;
				break;
			}
		}
		cout << (f ? "+1s" : "-1s") << endl;
	}
	return 0;
}