#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 20010;

int n, m;
int val[MAXN], fa[MAXN];

int find(int x) {
  if (x != fa[x]) {
    int tmp = fa[x];
    fa[x] = find(fa[x]);
    val[x] ^= val[tmp];
  }
  return fa[x];
}

int Union(int x, int y, int v) {
  int fx = find(x);
  int fy = find(y);
  if (fx == fy)
    return (val[x]^val[y]) == v;
  if (fx == n)
    swap(fx, fy);
  fa[fx] = fy;
  val[fx] = val[x]^v^val[y];
  return 1;
}

int main() {
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
  char str[MAXN];
  int p, q, v, k, x;
  int cas = 1;
  while (scanf("%d%d", &n, &m) != EOF && n+m) {
    for (int i = 0; i <= n; i++) {
      val[i] = 0;
      fa[i] = i;
    }
    printf("Case %d:\n", cas++);
    int facts = 0;
    int err = 0;
    while (m--) {
      scanf("%s", str);
      if (str[0] == 'I') {
        gets(str);
        facts++;
        if (err)
          continue;
        int cnt = sscanf(str, "%d%d%d", &p, &q, &v);
        if (cnt == 2) {
          v = q;
          q = n;
        }
        if (!Union(p, q, v)) {
          err = true;
          printf("The first %d facts are conflicting.\n", facts++);
        }
      } else {
        scanf("%d", &k);
        int ans = 0;
        int is = 1;
        map<int, int> mp;
        for (int i = 0; i < k; i++) {
          scanf("%d", &x);
          if (err)
            continue;
          int f = find(x);
          ans ^= val[x];
          mp[f]++;
        }
        if (err)
          continue;
        map<int, int>::iterator it;
        for (it = mp.begin(); it != mp.end(); it++) {
          if (it->second % 2) {
            if (it->first != n) {
              is = 0;
              break;
            }
            else ans ^= val[it->first];
          }
        }
        if (is)
          printf("%d\n", ans);
        else printf("I don't know.\n");
      }
    }
    printf("\n");
  }
  return 0;
}
