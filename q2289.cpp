#include <bits/stdc++.h>

typedef long long ll;
const int N = 305;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

int n, m, p, t, vis[N];
ll d[N][N], dp[N], mxd[N];
std::vector<std::tuple<int, int, int>> G[N]; 
std::vector<std::pair<int, int>> edges;
std::vector<std::pair<ll, ll>> a;
std::vector<int> v;

void dfs(int u, int d) {
    vis[u] = 1;
    for (auto &[v, w, i] : G[u]) {
        if (v == d) edges.emplace_back(u, i);
        else if (!vis[v]) dfs(v, d);
    }
}

void dfs2(int u, int id) {
    vis[u] = 1, v.push_back(u);
    for (auto &[v, w, i] : G[u])
        if (i != id && !vis[v]) dfs2(v, id);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &p, &t);
    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= n; ++i) d[i][i] = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y, l; scanf("%d%d%d", &x, &y, &l);
        d[x][y] = d[y][x] = l;
        G[x].emplace_back(y, l, i), G[y].emplace_back(x, l, i);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                d[j][k] = std::min(d[j][k], d[j][i] + d[i][k]);
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; ++i) if (G[i].size() == 1) dp[i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) if (d[i][j] != inf)
            mxd[i] = std::max(mxd[i], d[i][j]);
    for (int i = 1; i <= n; ++i) if (dp[i] == -1) a.emplace_back(-mxd[i], i);
    std::sort(a.begin(), a.end());
    for (auto &[x, y] : a) {
        for (int i = 1; i <= n; ++i)
            if (mxd[y] == d[y][i]) {
                if (dp[i] == -1) dp[y] = inf;
                else dp[y] = std::min(inf, std::max(dp[y], mxd[y] + dp[i]));
            }
    }
    dfs(p, t);
    ll res = inf;
    for (auto &[x, id] : edges) {
        memset(vis, 0, sizeof(int) * (n + 1));
        v.clear(); dfs2(t, id);
        ll mxd = 0, cur = 0;
        for (int y : v) mxd = std::max(mxd, d[t][y]);
        for (int y : v) if (mxd == d[t][y]) cur = std::max(cur, mxd + dp[y]);
        res = std::min(res, d[p][t] + cur);
    }
    if (res < inf) printf("%lld\n", res); else puts("impossible");
    return 0;
}