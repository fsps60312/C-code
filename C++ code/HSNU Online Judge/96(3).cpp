#include<cstdio>
#include<queue>
#include<cassert>
#include<set>
using namespace std;
int N,M,DT[40000],DF[40000];
bool VIS[40000];
vector<int>ET[40000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b);
		a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	queue<int>q;
	for(int i=0;i<N;i++)VIS[i]=false,DT[i]=4;
	q.push(0),VIS[0]=true;
	DT[0]=0;
	for(int d=1;d<=3;d++)
	{
		for(int cnt=q.size();cnt>=1;cnt--)
		{
			const int u=q.front();q.pop();
			for(int i=0;i<ET[u].size();i++)
			{
				const int nxt=ET[u][i];
				if(VIS[nxt])continue;
				VIS[nxt]=true;
				DT[nxt]=d;
				q.push(nxt);
			}
		}
	}
	while(!q.empty())q.pop();
	for(int i=0;i<N;i++)VIS[i]=false,DF[i]=4;
	q.push(1),VIS[1]=true;
	DF[1]=0;
	for(int d=1;d<=3;d++)
	{
		for(int cnt=q.size();cnt>=1;cnt--)
		{
			const int u=q.front();q.pop();
			for(int i=0;i<ET[u].size();i++)
			{
				const int nxt=ET[u][i];
				if(VIS[nxt])continue;
				VIS[nxt]=true;
				DF[nxt]=d;
				q.push(nxt);
			}
		}
	}
//	for(int i=0;i<N;i++)printf("%d:DT=%d,DF=%d\n",i,DT[i],DF[i]);
	int ans=0,to,from;
	for(int i=0;i<=4;i++)
	{
		to=from=0;
//		vector<int>a,b;
		for(int j=0;j<N;j++)
		{
			if(DT[j]==i)to++;
			if(DT[j]>i&&DF[j]>=4-i)from++;
		}
//		printf("from:");for(int i=0;i<a.size();i++)printf(" %d",a[i]);puts("");
//		printf("to  :");for(int i=0;i<b.size();i++)printf(" %d",b[i]);puts("");
//		printf("add(%d,%d)\n",to*from,to*(to-1)/2);
		ans+=to*from;
		ans+=to*(to-1)/2;
	}
//	printf("ans=%d\n",ans);
	printf("%d\n",ans-M); 
	return 0;
}
