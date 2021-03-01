#include <iostream>

using namespace std;

int like[65], dislike[65];
int t, n, m, x, y;
bool flag;

bool check(int x) {
    bool flag;
    for (int i = 0; i < m; ++i) {
       // if (!((like[i]!=0&&(like[i] & x)) || ((dislike[i]!=0) && ((dislike[i] & x) == 0))))
       flag=false;
       if (like[i])
           if (like[i]&x)
               flag= true;
       if (dislike[i])
           if ((dislike[i]&(~x)))
               flag= true;
        if (!flag) return false;
    }
    return true;
}

int main() {
    cin >> t;
    char c;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < m; ++i) like[i] = dislike[i] = 0;
        for (int i = 0; i < m; ++i) {
            do {
                cin >> x;
                if (x > 0) {
                    --x;
                    like[i] ^= 1 << x;
                }
                else {
                    x = abs(x) - 1;
                    dislike[i] ^= 1 << x;
                }
                c = getchar();
            } while (c != '\r' && c != '\n');
        }
        flag = false;
        for (int i = 0; i < (1 << n); ++i)
            if (check(i)) {
                flag = true;
                break;
            }
        cout << (flag ? "Bingo!\n" : "Sigh...\n");
    }
}
