#include <algorithm>
    using namespace std;
struct activity {
    int id, start, end;
};
bool compare(activity a, activity b) { return a.end < b.end; }
int schedule(int n, activity *p) {
    sort(p, p + n, compare);
    int cnt = 0, end = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].start >= end) {
            end = p[i].end;
            cnt++;
        }
    }
    return cnt;
}
