#include <iostream>

using namespace std;

struct Node {
    int value, next, pre;
    bool invalid;
} a[6000005];

struct Operator {
    int op, x;
    char c;
} Op[6000005];

int n, m, ans[6000005];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i].value);
        a[i].next = i + 1;
        a[i].pre = i - 1;
        a[i].invalid = 0;
    }
    a[1].pre = n;
    a[n].next = 1;
    int t;
    scanf("%d", &m);
    for (int j = 1; j <= m; ++j) {
        scanf("%d", &Op[j].op);
        switch (Op[j].op) {
            case 0:
                scanf("%d", &Op[j].x);
                t = Op[j].x;
                if (a[t].invalid) continue;
                a[a[t].pre].next = a[t].next;
                a[a[t].next].pre = a[t].pre;
                a[t].invalid = 1;
                break;
            case 1:
                getchar();
                Op[j].c = getchar();
                scanf("%d", &Op[j].x);
                t = Op[j].x;
                if (a[t].invalid) ans[j] = -1;
                else ans[j] = ((Op[j].c == 'P') ? a[t].pre : a[t].next);
        }
    }
    int maxn = -1;
    for (int i = 1; i <= n; ++i)
        if (!a[i].invalid)
            if (a[i].value > maxn) maxn = a[i].value;
    for (int j = m; j >= 1; --j) {
        if (Op[j].op == 2) {
            ans[j] = maxn;
        }
        else if (Op[j].op == 0) {
            if (a[Op[j].x].invalid) {
                a[Op[j].x].invalid = 0;
                if (a[Op[j].x].value > maxn)
                    maxn = a[Op[j].x].value;
            }
        }
    }
    for (int j = 1; j <= m; ++j)
        if (Op[j].op != 0) {
            if (ans[j] == -1) printf("Invalid.\n");
            else
                printf("%d\n", ans[j]);
        }
}