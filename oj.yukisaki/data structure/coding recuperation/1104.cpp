//
// Created by Libro on 2021/3/21.
//

#include <cstdio>

int n, m, a[3005][3005], que[3005], head, tail,pre[3005],ans=0,tmp;

inline int max(const int &a,const int &b) {
    return ((a>b)?a:b);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        a[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            a[i][j] = (a[i][j] == 0) ? 0 : a[i - 1][j] + 1;
        }
        a[i][m + 1] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        head = tail = 0;
        for (int j = 1; j <= m+1; ++j) {
            tmp=j;
            while (head<tail && a[i][que[tail-1]]>=a[i][j]) {
                ans=max(ans,(j-pre[tail-1])*a[i][que[tail-1]]);
                tmp=pre[tail-1];
                --tail;
            }
            pre[tail]=tmp;
            que[tail++]=j;
        }
    }
    printf("%d\n",ans);
}