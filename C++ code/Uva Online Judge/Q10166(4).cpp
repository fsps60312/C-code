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
vector<int> CITY[100];
struct Rail{int to,st,et;};
vector<Rail>RAIL;
bool VIS[100][2400];
int Q[100][2400];
int query(int u,int st)
{
    if(VIS[u][st])return Q[u][st];
    VIS[u][st]=true;
    if(u==SP)return Q[u][st]=st;
    int ans=-1;
    for(int i=0;i<CITY[u].size();i++)
    {
        int j=CITY[u][i];
        if(RAIL[j].et>st)continue;
        ans=max(ans,query(RAIL[j].to,RAIL[j].st));
    }
    return Q[u][st]=ans;
}
Rail solve()
{
	int ans=-1;
    for(int i=0;i<CITY[EP].size();i++)
    {
        int j=CITY[EP][i];
        ans=max(ans,query(RAIL[j].to,RAIL[j].st));
        if(i+1<CITY[EP].size()&&RAIL[CITY[EP][i+1]].et==RAIL[j].et)continue;
        //if(i+1<CITY[EP].size())printf("ans.et==%d:%d\n",RAIL[CITY[EP][i+1]].et,RAIL[j].et);
        if(ans>=ST)return (Rail){0,ans,RAIL[j].et};
    }
    return (Rail){0,0,-1};
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    while(scanf("%d",&N)==1&&N)
    {
        char tstr[21];
        RAIL.clear();
        IDX.clear();
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<2400;j++)VIS[i][j]=false;
            CITY[i].clear();
            scanf("%s",tstr);
            int sz=IDX.size();
            IDX[tstr]=sz;
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
                for(int i=CITY[nowc].size()-1;i>0;i--)
                {
                    Rail &r1=RAIL[CITY[nowc][i]],&r2=RAIL[CITY[nowc][i-1]];
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
        //for(int i=0;i<CITY[EP].size()-1;i++)printf("ans.et==%d:%d\n",RAIL[CITY[EP][i]].et,RAIL[CITY[EP][i+1]].et);
        Rail ans=solve();
        if(ans.et==-1)printf("No connection\n");
        else printf("%04d %04d\n",ans.st,ans.et);
    }
    return 0;
}
