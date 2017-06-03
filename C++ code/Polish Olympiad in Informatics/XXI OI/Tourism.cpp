#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
int N,M;
vector<int>ET[20000];
int C[20000],DEPTH[20000];
void BuildDepth(const int u,const int depth)
{
	assert(DEPTH[u]==-1);
	DEPTH[u]=depth;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(DEPTH[nxt]==-1)printf("%d->%d\n",u+1,nxt+1),BuildDepth(nxt,depth+1);
	}
}
inline void Add(int &a,const int b)
{
	if(a==INF||b==INF){a=INF;return;}
	a+=b;
}
//typedef long long LL;
void GetDP(const int u,int *dp,int *put)
{
	vector<int*>ch_dps,ch_puts;
	vector<int>parents;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(DEPTH[nxt]==DEPTH[u]+1)
		{
			int *ch_dp=new int[1<<DEPTH[nxt]],*ch_put=new int[1<<DEPTH[nxt]];
			printf("%d->%d\n",u+1,nxt+1);
			GetDP(nxt,ch_dp,ch_put);
			ch_dps.push_back(ch_dp);
			ch_puts.push_back(ch_put);
		}
		else if(DEPTH[nxt]<DEPTH[u])parents.push_back(nxt);
	}
	for(int s=0;s<(1<<DEPTH[u]);s++)
	{
		int no_put=0,min_dif=INF;
		for(int i=0;i<(int)ch_dps.size();i++)Add(no_put,ch_dps[i][s]),getmin(min_dif,ch_puts[i][s]-ch_dps[i][s]);
		for(int i=0;i<(int)parents.size();i++)if(s&(1<<DEPTH[parents[i]])){min_dif=0;break;}
		Add(no_put,min_dif);
		dp[s]=no_put;
		int put_val=C[u];
		for(int i=0;i<(int)ch_dps.size();i++)Add(put_val,ch_dps[i][s+(1<<DEPTH[u])]);
		getmin(dp[s],put_val),put[s]=put_val;
	}
	for(int i=0;i<(int)ch_dps.size();i++)
	{
		delete[]ch_dps[i];
		delete[]ch_puts[i];
	}
	vector<int*>().swap(ch_dps);
	vector<int*>().swap(ch_puts);
	vector<int>().swap(parents);
	printf("DEPTH[%d]=%d, dp=",u+1,DEPTH[u]);
	switch(u+1)
	{
		case 2:
		case 8:
		case 7:
		case 9:printf("%d\n",dp[1<<0]);break;
		case 10:
		case 6:
		case 3:
		case 11:
		case 5:
		case 4:printf("%d\n",dp[(1<<0)+(1<<4)]);break;
		case 1:printf("%d\n",dp[0]);break;
		default:assert(0);break;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)DEPTH[i]=-1;
		int ans=0;
		for(int i=0;i<N;i++)if(DEPTH[i]==-1)
		{
			puts("a");
			BuildDepth(i,0);
			puts("b");
			int *dp=new int[1],*put=new int[1];
			GetDP(i,dp,put);
			Add(ans,dp[0]);
		}
		printf("%d\n",ans);
		assert(ans!=INF);
	}
	return 0;
}
