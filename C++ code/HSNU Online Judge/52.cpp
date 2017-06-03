#include<cstdio>
#include<algorithm>
using namespace std; 
int N,M,ANS[1000005];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&ANS[i]);
	scanf("%d",&M);
	for(int i=N;i<max(M,N)+2;i++)ANS[i]=0;
	N=max(N,M);
	for(int i=0,v;i<M;i++){scanf("%d",&v);ANS[i]+=v;}
	bool changed=true;
	while(changed)
	{
		changed=false;
		for(int i=1,v;i<N;i++)
		{
			v=min(ANS[i-1],ANS[i]);
			if(v)
			{
				if(i+1==N)ANS[N++]=0;
				ANS[i-1]-=v,ANS[i]-=v;
				ANS[i+1]+=v;
				changed=true;
			}
		}
		ANS[1]+=ANS[0]/2;
		ANS[0]%=2;
		for(int i=1,v;i<N;i++)
		{
			v=ANS[i]/2;
			if(v)
			{
				if(i+1==N)ANS[N++]=0;
				ANS[i+1]+=v;
				ANS[max(0,i-2)]+=v;
				ANS[i]-=v*2;
				changed=true;
			}
		}
	}
	int mx=-1;
	for(int i=0;i<N;i++)if(ANS[i])mx=i;
	printf("%d",mx+1);
	for(int i=0;i<=mx;i++)printf(" %d",ANS[i]);
	puts("");
	return 0;
}
