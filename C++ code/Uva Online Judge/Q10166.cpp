#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<queue>
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int N,ST,SP,EP;
map<string,int> IDX;
map<int,string> NAME;
vector<int> CITY[100];
struct Rail{int to,st,et;};
vector<Rail>RAIL;
bool VIS[100][100];
Rail Q[100][100];
Rail query(int u,int pre,int st)
{
    if(VIS[u][pre])return Q[u][pre];
    VIS[u][pre]=true;
    if(u==SP)return Q[u][pre]=(Rail){0,0,st};
    Rail ans=(Rail){0,0,-1};
    for(int i=0;i<CITY[u].size();i++)
    {
        int j=CITY[u][i];
        if(RAIL[j].et>st)continue;
        ans.et=max(ans.et,query(RAIL[j].to,u,RAIL[j].st).et);
    }
    return Q[u][pre]=ans;
}
Rail solve()
{
    for(int i=0;i<CITY[EP].size();i++)
    {
        int j=CITY[EP][i];
        Rail ans=query(RAIL[j].to,EP,RAIL[j].st);
        //printf("ans.et==%d\n",ans.et);
        if(ans.et>=ST)return (Rail){0,ans.et,RAIL[j].et};
    }
    return (Rail){0,0,-1};
}
int main()
{
    while(scanf("%d",&N)==1&&N)
    {
        char tstr[21];
        RAIL.clear();
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)VIS[i][j]=false;
            CITY[i].clear();
            scanf("%s",tstr);
            int sz=IDX.size();
            IDX[tstr]=sz;
            NAME[sz]=tstr;
        }
        int m;scanf("%d",&m);
        while(m--)
        {
            int t;scanf("%d",&t);
            int pret,prec;
            scanf("%d%s",&pret,tstr);
            prec=IDX[tstr];
            while(--t)
            {
                int nowt,nowc;scanf("%d%s",&nowt,tstr);
                nowc=IDX[tstr];
                CITY[nowc].push_back(RAIL.size());
                RAIL.push_back((Rail){prec,pret,nowt});
                for(int i=CITY[prec].size()-1;i>0;i--)
                {
                    Rail &r1=RAIL[CITY[prec][i]],&r2=RAIL[CITY[prec][i-1]];
                    if(r1.et>r2.et)break;
                    Rail tr=r1;
                    r1=r2;
                    r2=tr;
                }
                prec=nowc,pret=nowt;
            }
        }
        scanf("%d%s",&ST,tstr);SP=IDX[tstr];
        scanf("%s",tstr);EP=IDX[tstr];
        Rail ans=solve();
        if(ans.et==-1)printf("No connection\n");
        else printf("%04d %04d\n",ans.st,ans.et);
    }
    return 0;
}
