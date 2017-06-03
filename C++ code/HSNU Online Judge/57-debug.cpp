#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
#define N 1005
struct P
{
	int v;
	double c;
};
vector<P>s[N];
queue<int>que;
int val[N],in[N],add[N],is=0,pre[N]={0},dfs_cnt=0;
double dis[N];
char arr[10];
void dfs(int u)
{
	int i;
	pre[u]=++dfs_cnt;
	for(i=0;i<s[u].size();i++){
		int v=s[u][i].v;
		if(pre[v]==0){
			dfs(v);
		}
		else if(pre[v]<pre[u]) is=1;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int n,m,i,j,x,y,flag;
	double z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&val[i]);
	for(i=0;i<m;i++)
	{
		scanf("%d%d%lf",&x,&y,&z);
		s[x].push_back((P){y,z});
	}
	for(i=1;i<=n;i++)if(pre[i]==0)dfs(i);
	if(is==0)
	{
		puts("0");
		return 0;
	}
	double l=0,r=1000000000,M;
	while(r-l>=0.0000001)
	{
		M=(l+r)/2;
		memset(dis,0,sizeof(dis));
		memset(in,0,sizeof(in));
		memset(add,0,sizeof(add));
		flag=0;
		while(que.size())que.pop();
		for(i=1;i<=n;i++)
		{
			que.push(i);
			in[i]=1;
		}
		while(que.size())
		{
			int u=que.front();
			que.pop();
			in[u]=0;
			if(add[u]==n+1)
			{
				flag=1;
				break;
			}
			for(i=0;i<s[u].size();i++)
			{
				P v=s[u][i];
				if(dis[u]+v.c*M-val[v.v]<dis[v.v])
				{
					dis[v.v]=dis[u]+v.c*M-val[v.v];
					if(in[v.v]==0)
					{
						in[v.v]=1;
						add[v.v]++;
						que.push(v.v);
					}
				}
			}
		}
		if(flag)l=M;
		else r=M;
	}
	printf("%.2f",r);
}
