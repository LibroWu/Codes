// targan
#include <iostream>
#include <stack>

using namespace std;

int head[100005] = {0}, Next[100005], vet[100005], head_block[100005] = {0},
        Next_block[100005], vet_block[100005], dfn[100005] = {0}, low[100005] = {0},
        f[100005], col[100005] = {0}, col_max[100005] = {0}, d[100005] = {0},st[100005];
int n, m, cnt = 0, tot = 0, color = 0, tot_block = 0,top=0;
bool visited[1000005];

inline void build(int x, int y) {
    Next[++tot] = head[x];
    head[x] = tot;
    vet[tot] = y;
}

void build_block(int x, int y) {
    Next_block[++tot_block] = head_block[x];
    head_block[x] = tot_block;
    vet_block[tot_block] = y;
}

inline int min(int a, int b) { return ((a < b) ? a : b); }

void targan(int u) {
    dfn[u] = low[u] = ++cnt;
    st[++top]=u;
    int v;
    for (int i = head[u]; i != 0; i = Next[i]) {
        v = vet[i];
        if (dfn[v] == 0) {
            targan(v);
            low[u] = min(low[u], low[v]);
        } else if (col[v] == 0)
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++color;
        int max_num = 0;
        while (st[top] != u) {
            col[st[top]] = color;
            if (st[top] > max_num) max_num = st[top];
            --top;
        }
        col[u] = color;
        if (u > max_num) max_num = u;
        col_max[color] = max_num;
        top--;
    }
}

void dfs(int u) {
    int res = col_max[u];
    int v;
    visited[u] = 1;
    for (int i = head_block[u]; i != 0; i = Next_block[i]) {
        v = vet_block[i];
        if (visited[v] && f[v] > res) res = f[v];
        if (visited[v]) continue;
        dfs(v);
        if (f[v] > res) res = f[v];
    }
    if (res>f[u])
        f[u] = res;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        static int x, y;
        cin >> x >> y;
        build(x, y);
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        top=0;
        if (dfn[i] == 0) targan(i);
    }
    for (int u = 1; u <= n; ++u) {
        static int v;
        for (int i = head[u]; i != 0; i = Next[i]) {
            v = vet[i];
            if (col[v] != col[u]) {
                build_block(col[u], col[v]);
                ++d[col[v]];
            }
        }
    }
    for (int i = 1; i <= color; ++i) {
        f[i] = col_max[i];
        visited[i] = 0;
    }
    for (int i = 1; i <= color; ++i) dfs(i);
    for (int i = 1; i <= n; ++i) cout << f[col[i]] << ' ';
    cout << '\n';
    return 0;
}
