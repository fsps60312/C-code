#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int min(const int a,const int b,const int c,const int d){return min(min(a,b),min(c,d));}
int CntBit(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
struct Hungary
{
	int N,EDGE[10][10],WA[10],WB[10],MATCH[10],LOW[10];
	bool VA[10],VB[10];
	void Update()
	{
		int low=INF;
		for(int i=0;i<N;i++)getmin(low,LOW[i]);
		for(int i=0;i<N;i++)if(VA[i])WA[i]+=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]-=low;
	}
	bool Match(const int u)
	{
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(!VB[nxt])
		{
			if(WA[u]+WB[nxt]==EDGE[u][nxt])
			{
				VB[nxt]=true;
				if(MATCH[nxt]==-1||Match(MATCH[nxt]))
				{
					MATCH[nxt]=u;
					return true;
				}
			}
			else assert(EDGE[u][nxt]>WA[u]+WB[nxt]),getmin(LOW[nxt],EDGE[u][nxt]-WA[u]-WB[nxt]);
		}
		return false;
	}
	int Solve()
	{
		for(int i=0;i<N;i++)MATCH[i]=-1,WA[i]=WB[i]=0;
		for(int i=0;i<N;i++)
		{
			for(;;)
			{
				for(int j=0;j<N;j++)LOW[j]=INF,VA[j]=VB[j]=false;
				if(Match(i))break;
				else Update();
			}
		}
		int ans=0;
		for(int i=0;i<N;i++)ans+=EDGE[MATCH[i]][i];
		return ans;
	}
}HUNGARY;
int R,C,N;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&R,&C,&N);
		static int r[20],c[20];
		for(int i=0;i<N;i++)scanf("%d%d",&r[i],&c[i]);
		const int half=(N+1)/2;
		int ans=INF;
		for(int s=0;s<(1<<N);s++)if(CntBit(s)==half)
		{
			vector<int>a,b;
			for(int i=0;i<N;i++)(s&(1<<i)?a:b).push_back(i);
			HUNGARY.N=half;
			for(int i=0;i<(int)a.size();i++)for(int j=0;j<(int)b.size();j++)
			{
				HUNGARY.EDGE[i][j]=abs(r[a[i]]-r[b[j]])+abs(c[a[i]]-c[b[j]]);
			}
			if(N&1)for(int i=0;i<half;i++)
			{
				HUNGARY.EDGE[i][half-1]=min(r[a[i]],R+1-r[a[i]],c[a[i]],C+1-c[a[i]]);
			}
			getmin(ans,HUNGARY.Solve());
		}
		printf("%d\n",ans);
	}
	return 0;
}
