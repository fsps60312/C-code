#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int N,M,DT[4],DF[4];
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
	for(int i=0;i<N;i++)VIS[i]=false;
	queue<int>q;
	q.push(0),VIS[0]=true;
	DT[0]=1;
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
				q.push(nxt);
			}
		}
		DT[d]=q.size();
	}
	for(int i=0;i<N;i++)VIS[i]=false;
	q.push(1),VIS[1]=true;
	DF[0]=1;
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
				q.push(nxt);
			}
		}
		DF[d]=q.size();
	}
	int ans=0;
	ans+=DT[0]*(N-DF[0]-DF[1]-DF[2]-DF[3]);
	ans+=DT[1]*(N-DF[0]-DF[1]-DF[2]);
	ans+=DT[2]*(N-DF[0]-DF[1]);
	ans+=DT[3]*(N-DF[0]);
	ans+=(N-DT[0]-DT[1]-DT[2]-DT[3])*N;
	assert(ans%2==0);
	ans/=2;ans-=N;
	printf("%d\n",ans-M); 
	return 0;
}
