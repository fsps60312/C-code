#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,S[200000];
int DEG[200000];
bool VIS[200000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)DEG[i]=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),++DEG[--S[i]],VIS[i]=false;
		queue<int>q;
		for(int i=0;i<N;i++)if(!DEG[i])q.push(i);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			assert(!VIS[u]);
			VIS[u]=true;
			if(!--DEG[S[u]])q.push(S[u]);
		}
		int self=-1,ans=0;
		vector<int>loop;
		for(int i=0;i<N;i++)if(!VIS[i])
		{
			if(S[i]==i)
			{
				if(self==-1)self=i;
				else S[i]=self,++ans;
			}
			else
			{
				int cur=i;
				for(;!VIS[cur];cur=S[cur])VIS[cur]=true;
				assert(cur==i);
				loop.push_back(cur);
			}
		}
		if(self!=-1)
		{
			for(int i=0;i<(int)loop.size();i++)S[loop[i]]=self,++ans;
		}
		else
		{
			assert(!loop.empty());
			S[loop[0]]=loop[0],++ans;
			for(int i=1;i<(int)loop.size();i++)S[loop[i]]=loop[0],++ans;
		}
		printf("%d\n",ans);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",S[i]+1);
		}
		puts("");
	}
	return 0;
}
