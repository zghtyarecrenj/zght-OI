#include <bits/stdc++.h>

typedef long long ll;
const int N = 305;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

int n, m, p, t, vis[N];
ll d[N][N];

void dfs(int u, int fa) {
    vis[u] = -1;
    for (int i = 1; i <= n; ++i) if (i != u && d[u][i] != inf) {
        dfs(v, u);
        
    }

}

int main() {
    scanf("%d%d%d%d", &n, &m, &p, &t);
    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= m; ++i) {
        int x, y, l; scanf("%d%d%d", &x, &y, &l);
        d[x][y] = d[y][x] = l;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                d[j][k] = std::min(d[j][k], d[j][i] + d[i][k]);
    for (int i = 1; i <= n; ++i) {
        int tmp = 0;
    }
    return 0;
}