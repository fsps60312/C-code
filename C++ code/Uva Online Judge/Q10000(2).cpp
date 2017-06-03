#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int N;
vector<int> PATH[101];
void insertside()
{
    int a,b;
    while(scanf("%d%d",&a,&b)==2&&(a||b))PATH[a].push_back(b);
}
struct Pair
{
    int x,y;
    bool operator>(Pair a){return x>a.x||(x==a.x&&y<a.y);}
    Pair operator+(int a){x+=a;return *this;}
};
Pair DIS[101];
Pair max(Pair a,Pair b){return a>b?a:b;}
Pair query(int u)
{
    if(DIS[u].x!=-1)return DIS[u];
    if(!PATH[u].size())return DIS[u]=(Pair){0,u};
    Pair ans=(Pair){-1,-1};
    for(int i=0;i<PATH[u].size();i++)
    {
        int tu=PATH[u][i];
        ans=max(ans,query(tu)+1);
    }
    return DIS[u]=ans;
}
int SP;
int main()
{
    int kase=1;
    while(scanf("%d",&N)==1&&N)
    {
        scanf("%d",&SP);
        for(int i=1;i<=N;i++)
        {
            PATH[i].clear();
            DIS[i]=(Pair){-1,-1};
        }
        insertside();
        Pair ans=query(SP);
        printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n",kase++,SP,ans.x,ans.y);
    }
    return 0;
}
