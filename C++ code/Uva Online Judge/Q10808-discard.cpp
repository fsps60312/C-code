#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <vector>  
using namespace std;  
  
typedef long long ll;  
  
struct Frac {  
  
    ll a, b;  
  
    Frac() {a = 0; b = 1;}  
    Frac(ll a, ll b) {this->a = a; this->b = b; deal();}  
  
    void init() {a = 0; b = 1;}  
  
    ll gcd(ll a, ll b) {  
    while (b) {  
        ll tmp = a % b;  
        a = b;  
        b = tmp;  
    }  
    return a;  
    }  
  
    void deal() {  
    ll d = gcd(a, b);  
    a /= d; b /= d;  
    if (b < 0) {  
        a = -a;  
        b = -b;  
    }  
    }  
  
    Frac operator + (Frac c) {  
    Frac ans;  
    ans.a = a * c.b + b * c.a;  
    ans.b = b * c.b;  
    ans.deal();  
    return ans;  
    }  
  
    Frac operator - (Frac c) {  
    Frac ans;  
    ans.a = a * c.b - b * c.a;  
    ans.b = b * c.b;  
    ans.deal();  
    return ans;  
  
    }  
  
    Frac operator * (Frac c) {  
    Frac ans;  
    ans.a = a * c.a;  
    ans.b = b * c.b;  
    ans.deal();  
    return ans;  
    }  
  
    Frac operator / (Frac c) {  
    Frac ans;  
    ans.a = a * c.b;  
    ans.b = b * c.a;  
    ans.deal();  
    return ans;  
    }  
  
    void operator += (Frac c) {*this = *this + c;}  
    void operator -= (Frac c) {*this = *this - c;}  
    void operator *= (Frac c) {*this = *this * c;}  
    void operator /= (Frac c) {*this = *this / c;}  
  
    bool operator > (Frac c) {return a * c.b > b * c.a;}  
    bool operator == (Frac c) { return a * c.b == b * c.a;}  
    bool operator < (Frac c) {return !(*this < c && *this == c);}  
    bool operator >= (Frac c) {return !(*this < c);}  
    bool operator <= (Frac c) {return !(*this > c);}  
    bool operator != (Frac c) {return !(*this == c);}  
    bool operator != (ll c) {return *this != Frac(c, 1);}  
      
    void operator = (ll c) {this->a = c; this->b = 1;}  
};  
  
const int N = 20;  
  
int t, n, m, parent[N], node[N];  
Frac g[N][N], A[N][N];  
  
int find(int x) {  
    return x == parent[x] ? x : parent[x] = find(parent[x]);  
}  
  
Frac gauss(int n, int u, int v) {  
    for (int i = 0; i < n; i++) {  
    int r;  
    for (r = i; r < n; r++)  
        if (A[r][i] != 0)  
        break;  
    if (r == n) continue;  
    for (int j = 0; j <= n; j++) swap(A[i][j], A[r][j]);  
    for (int j = n; j > i; j--) A[i][j] /= A[i][i];  
    A[i][i] = 1;  
    for (int j = 0; j < n; j++) {  
        if (i == j) continue;  
        if (A[j][i] != 0) {  
        for (int k = n; k > i; k--)  
            A[j][k] -= A[j][i] * A[i][k];  
        A[j][i] = 0;  
        }  
    }  
    }  
    return A[u][n] / A[u][u] - A[v][n] / A[v][v];  
}  
  
Frac solve(int u, int v) {  
    int tu, tv, tn = 0;  
    for (int i = 0; i < n; i++) {  
    if (i == u) tu = tn;  
    if (i == v) tv = tn;  
    if (find(u) == find(i)) node[tn++] = i;  
    }  
    tn++;  
    for (int i = 0; i < tn; i++)  
    for (int j = 0; j <= tn; j++)  
        A[i][j].init();  
    for (int i = 0; i < tn - 1; i++) {  
    for (int j = 0; j < tn - 1; j++) {  
        if (i == j) continue;  
        int u = node[i], v = node[j];  
        A[i][i] += g[u][v];  
        A[i][j] -= g[u][v];  
    }  
    }  
    A[tu][tn] = 1;  
    A[tv][tn] = -1;  
    A[tn - 1][0] = 1;  
    return gauss(tn, tu, tv);  
}  
  
int main() {
//	freopen("in.txt","r",stdin);
    int cas = 0;  
    scanf("%d", &t);  
    while (t--) {  
    scanf("%d%d", &n, &m);  
    for (int i = 0; i < n; i++) {  
        parent[i] = i;  
        for (int j = 0; j < n; j++)  
        g[i][j].init();  
    }  
    int u, v;  
    ll r;  
    while (m--) {  
        scanf("%d%d%lld", &u, &v, &r);  
        if (u == v) continue;  
        g[u][v] += Frac(1, r);  
        g[v][u] += Frac(1, r);  
        int pu = find(u);  
        int pv = find(v);  
        if (pu != pv)  
        parent[pu] = pv;  
    }  
    scanf("%d", &m);  
    printf("Case #%d:\n", ++cas);  
    while (m--) {  
        scanf("%d%d", &u, &v);  
        int pu = find(u);  
        int pv = find(v);  
        printf("Resistance between %d and %d is ", u, v);  
        if (pu != pv) printf("1/0\n");  
        else {  
        Frac ans = solve(u, v);  
        printf("%lld/%lld\n", ans.a, ans.b);  
        }  
    }  
    printf("\n");  
    }  
    return 0;  
} 

