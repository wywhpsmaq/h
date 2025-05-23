#include <iostream>
    using namespace std;
int main() {
    int cnt = 0;
    for (int x = 0; x <= 10; x++)
        for (int y = 0; y <= 10; y++)
            for (int z = 0; z <= 10; z++)
                if (x + y + z == 15) cnt++;
    cout << cnt << endl;
    return 0;
}
