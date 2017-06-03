#include<cstdio>
#include<cassert>
using namespace std;
int N,S[100];
bool VIS[100];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]),VIS[i]=false;
		int cnt=1,remain=N,cur=-1;
		for(;remain>1;cnt++)
		{
			cur=(cur+1)%N;
			while(VIS[cur])
			{
				cur=(cur+1)%N;
			}
//			printf("cur=%d\n",cur);
			for(int i=0;i<N;i++)if(i!=cur&&!VIS[i]&&cnt%S[i]==0)VIS[i]=true,--remain;
		}
		if(cur==-1)cur++;
		printf("%d\n",cur+1);
	}
	return 0;
}
