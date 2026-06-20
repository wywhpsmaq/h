#ifndef H_MAIN_H
#define H_MAIN_H

#endif //H_MAIN_H

bool jc(const int x, const int y) { return x >= 0 && y >= 0 && x <= 798 && y <= 1598; }
int gcd_(int x, int y) { return y == 0 ? x : gcd_(y, x % y); }
int lcm_(int x, int y) { return x * y / gcd_(x, y); }
