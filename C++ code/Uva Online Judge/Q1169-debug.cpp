#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <math.h>  
#include <queue>  
using namespace std;  
const int N = 100005;  
  
int t, w, n, sumw[N], sumd[N], dp[N];  
struct Point {  
    int x, y, w, d;  
    Point() {x = 0; y = 0; w = 0; d = 0;}  
} p[N], zero;;  
  
int dis(Point a, Point b) {  
    return abs(a.x - b.x) + abs(a.y - b.y);  
}  
  
int func(int j) {  
    return dp[j] - sumd[j + 1] + p[j + 1].d;  
}  
  
int solve() {  
    deque<int> Q;  
    Q.push_front(0);  
    for (int i = 1; i <= n; i++) {  
        while (!Q.empty() && sumw[i] - sumw[Q.front()] > w) {Q.pop_front();}  
        dp[i] = func(Q.front()) + sumd[i] + p[i].d;  
        while (!Q.empty() && func(i) <= func(Q.back())) {Q.pop_back();}  
        Q.push_back(i);  
    }  
    return dp[n];  
}  
  
int main() {  
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    scanf("%d", &t);  
    while (t--) {  
        scanf("%d%d", &w, &n);  
        for (int i = 1; i <= n; i++) {  
            scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].w);  
            sumw[i] = sumw[i - 1] + p[i].w;  
            sumd[i] = sumd[i - 1] + dis(p[i], p[i - 1]);  
            p[i].d = dis(p[i], zero);  
        }  
        printf("%d\n", solve());  
        if (t) printf("\n");  
    }  
    return 0;  
} 

