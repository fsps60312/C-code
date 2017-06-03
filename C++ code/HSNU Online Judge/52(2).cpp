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
	for(int i=N;i<M;i++)ANS[i]=0;
	N=max(N,M);
	for(int i=0,v;i<M;i++){scanf("%d",&v);ANS[i]+=v;}
	bool changed=true;
	for(int i=0;i<N;)
	{
		if(i==0)
		{
			if(i+1==N)ANS[N++]=0;
			ANS[i+1]+=ANS[i]/2;
			ANS[i]%=2;
			i++;
		}
		else
		{
			if(ANS[i-1]&&ANS[i])
			{
				if(i+1==N)ANS[N++]=0;
				int v=min(ANS[i-1],ANS[i]);
				ANS[i+1]+=v;
				ANS[i-1]-=v,ANS[i]-=v;
				i++;
			}
			else if(ANS[i]/2)
			{
				if(i+1==N)ANS[N++]=0;
				ANS[max(0,i-2)]+=ANS[i]/2;
				ANS[i+1]+=ANS[i]/2;
				ANS[i]%=2;
				i=max(0,i-2);
			}
			else i++;
		}
	}
	int mx=-1;
	for(int i=0;i<N;i++)if(ANS[i])mx=i;
	printf("%d",mx+1);
	for(int i=0;i<=mx;i++)printf(" %d",ANS[i]);
	puts("");
	return 0;
}
