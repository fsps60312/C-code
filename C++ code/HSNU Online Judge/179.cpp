#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int CntBits(int v)
{
	v=(v&0x55555555)+((v&0xaaaaaaaa)>>1);
	v=(v&0x33333333)+((v&0xcccccccc)>>2);
	v=(v&0x0f0f0f0f)+((v&0xf0f0f0f0)>>4);
	v=(v&0x00ff00ff)+((v&0xff00ff00)>>8);
	v=(v&0x0000ffff)+((v&0xffff0000)>>16);
	return v;
}
struct Hungary
{
	int N,EDGE[13][13],MATCH[13],WA[13],WB[13],LOW[13];
	bool VA[13],VB[13];
	bool Match(const int u)
	{
		assert(!VA[u]);
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)
		{
			if(WA[u]+WB[nxt]==EDGE[u][nxt])
			{
				if(VB[nxt])continue;
				VB[nxt]=true;
				if(MATCH[nxt]==-1||Match(MATCH[nxt])){MATCH[nxt]=u;return true;}
			}
			else getmin(LOW[nxt],EDGE[u][nxt]-WA[u]-WB[nxt]);
		}
		return false;
	}
	void Update()
	{
		int low=INF;
		for(int i=0;i<N;i++)getmin(low,LOW[i]);
		assert(low<INF&&low>0);
		for(int i=0;i<N;i++)if(VA[i])WA[i]+=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]-=low;
	}
	int Solve()
	{
		assert(N<=13);
		for(int i=0;i<N;i++)WA[i]=WB[i]=0,MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(;;)
			{
				for(int j=0;j<N;j++)VA[j]=VB[j]=false,LOW[j]=INF;
				if(Match(i))break;
				else Update();
			}
		}
		int ans=0;
		for(int i=0;i<N;i++)ans+=WA[i]+WB[i];
		return ans;
	}
}HUNGARY;
int M,DEG[26],DIST[26][26];
int main()
{
	freopen("in.txt","r",stdin);
	static int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&M);
		for(int i=0;i<26;i++)for(int j=0;j<26;j++)DIST[i][j]=INF;
		for(int i=0;i<26;i++)DEG[i]=0,DIST[i][i]=0;
		int sum=0;
		for(int i=0;i<M;i++)
		{
			static char name[11];scanf("%s",name);
			int len=-1;while(name[++len]);
			const int a=name[0]-'a',b=name[len-1]-'a';
			getmin(DIST[a][b],len);
			DEG[a]++,DEG[b]++;
			sum+=len;
		}
		for(int m=0;m<26;m++)
		{
			for(int a=0;a<26;a++)if(DIST[a][m]!=INF)
			{
				for(int b=0;b<26;b++)if(DIST[m][b]!=INF)
				{
					getmin(DIST[a][b],DIST[a][m]+DIST[m][b]);
				}
			}
		}
		for(int i=0;i<26;i++)for(int j=0;j<26;j++)if(i!=j&&DIST[i][j]!=INF)printf("(%d,%d,%d)\n",i,j,DIST[i][j]);
		int mn=INF;
		if(true)
		{
			vector<int>node;
			for(int i=0;i<26;i++)if(DEG[i]&1)node.push_back(i);
			const int n=node.size();
			assert(n%2==0);
			HUNGARY.N=n/2;
			for(int s=0;s<(1<<n);s++)if(CntBits(s)==n/2)
			{
				vector<int>a,b;
				for(int i=0;i<n;i++)(s&(1<<i)?a:b).push_back(node[i]);
				assert((int)a.size()==n/2&&(int)b.size()==n/2);
				for(int i=0;i<n/2;i++)for(int j=0;j<n/2;j++)HUNGARY.EDGE[i][j]=min(DIST[a[i]][b[j]],INF/n);
				getmin(mn,HUNGARY.Solve());
				if(mn==6)
				{
					for(int i=0;i<n/2;i++)
					{
						for(int j=0;j<n/2;j++)printf("%d ",HUNGARY.EDGE[i][j]);
						puts("");
					}
					puts("");
				}
			}
		}
		printf("%d\n",sum-mn);
	}
	return 0;
}
