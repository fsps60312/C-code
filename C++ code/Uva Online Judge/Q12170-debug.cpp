#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=110;
const LL oo=0x3f3f3f3f3f3f3f3f;

int n, cnt, limit, h[maxn], to[maxn*maxn<<1];
LL d[maxn][maxn*maxn<<1];

void init()
{
    cnt=0;
    for(int i=0; i<n; i++)
        for(int j=i; j>=-i; j--)
            if(h[i]+j*limit>=0)
                to[cnt++]=h[i]+j*limit;
    sort(to, to+cnt);
    cnt=unique(to, to+cnt)-to;
}

LL dp()
{
    memset(d, 0x3f, sizeof d);
    d[0][lower_bound(to, to+cnt, h[0])-to]=0;
    for(int i=1; i<n-1; i++)
    {
        deque<int> q;
        int R=0;
        for(int j=0; j<cnt; j++)
        {
            while(R<cnt && abs(to[R]-to[j])<=limit)
            {
                while(q.size() && d[i-1][R]<=d[i-1][q.back()])
                    q.pop_back();
                q.push_back(R++);
            }
            while(q.size() && abs(to[q.front()]-to[j])>limit)
                q.pop_front();
            if(q.size())
                d[i][j]=d[i-1][q.front()]+abs(to[j]-h[i]);
        }
    }

    LL ans=oo;
    for(int i=0; i<cnt; i++)
        if(to[i]>=h[n-1]-limit && to[i]<=h[n-1]+limit && d[n-2][i]<oo)
            ans=min(ans, d[n-2][i]);
    return ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &limit);
        for(int i=0; i<n; i++)
            scanf("%d", h+i);
        if(abs(h[n-1]-h[0])>limit*(n-1))
        {
            puts("impossible");
            continue ;
        }
        init();
        printf("%lld\n", dp());
    }
    return 0;
}
