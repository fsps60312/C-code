#include<cstdio>
#include<cassert>
using namespace std;
int N,S[200000];
int VIS[200000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]),--S[i];
		for(int i=0;i<N;i++)VIS[i]=-1;
		int self=-1;
		for(int i=0;i<N;i++)if(VIS[i]==-1)
		{
			if(S[i]==i)
			{
				VIS[i]=i;
//				printf("i=%d,a\n",i+1);
				index_self_loop:;
				if(self==-1)self=i;
				else S[i]=-1;
			}
			else
			{
//				printf("i=%d,b\n",i+1);
				int cur=i;
				for(;VIS[cur]==-1;cur=S[cur])VIS[cur]=i;
//				printf("cur=%d\n",cur+1);
				if(cur==i)S[i]=-1;
				else if(VIS[cur]==i)
				{
					if(S[cur]==cur)goto index_self_loop;
					else S[cur]=-1;
				}
			}
		}
		int ans=0;
		if(self!=-1)
		{
			for(int i=0;i<N;i++)if(S[i]==-1)S[i]=self,++ans;
		}
		else
		{
			for(int i=0;i<N;i++)if(S[i]==-1)
			{
				if(self==-1)S[i]=i,self=i,++ans;
				else S[i]=self,++ans;
			}
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
