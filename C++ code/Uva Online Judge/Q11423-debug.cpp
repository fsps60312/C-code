#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

const int N = 35;
const int maxn = 1e7 + 5;
#define lowbit(x) ((x)&(-x))

int n;
int Miss[N], Cache[N];
int C[maxn];
char str[N];

void add (int x, int v) {
    while (x < maxn) {

        C[x] += v;
        x += lowbit(x);
    }
}

int sum (int x) {
    int ret = 0;
    while (x > 0) {

        ret += C[x];
        x -= lowbit(x);
    }
    return ret;
}

struct Num {
    int value, pre;
    Num (int value , int pre) {
        this->value = value;
        this->pre = pre;
    }
};
queue<Num> Q;
map<int, int> vis;

void init () {

    int b, y, k;
    memset (Miss, 0, sizeof(Miss));
    vis.clear();
    while (scanf ("%s", str) && str[0] != 'E') {

        if (str[0] == 'R') {
            scanf ("%d%d%d" , &b, &y, &k);
            for (int i = 0; i < k; i++) {
                Q.push(Num(b + y * i, vis[b + y * i]));
                vis[b + y * i] = Q.size();
            }
        } else if (str[0] == 'A') {
            scanf ("%d", &b);
            Q.push(Num (b, vis[b]));
            vis[b] = Q.size();
        } else {
            Q.push(Num (-1, 0));
        }
    }
}

void solve () {

    init();
    memset (C, 0, sizeof (C));
    for (int cnt=0;!Q.empty();cnt++)
	{
		const auto u=Q.front();Q.pop();
        if (u.value >= 0)
		{
            add(cnt + 1, 1);
            if (u.pre > 0)
			{
                int dis = sum(cnt + 1) - sum(u.pre);
                for (int i = 0; i < n; i++)
				{
                    if (Cache[i] < dis)Miss[i]++;
                    else break;
                }    
                add(u.pre, -1);
            }
			else
			{
                for (int i = 0; i < n; i++)Miss[i]++;
            }
        }
		else
		{
            for (int i = 0; i < n - 1; i++)printf ("%d ", Miss[i]);
            printf ("%d\n", Miss[n - 1]);
            memset (Miss, 0, sizeof (Miss));
        }
    }
}

int main () {
	freopen("in.txt","r",stdin);
    scanf ("%d", &n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &Cache[i]);    

    solve();
    return 0;
};
