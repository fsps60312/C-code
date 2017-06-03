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
	while(N<3)ANS[N++]=0;
	if(ANS[0]==2)ANS[1]++,ANS[0]=0;
	if(ANS[0]==3)ANS[0]=0,ANS[2]++;
	if(ANS[1]==2)ANS[0]++,ANS[1]=0,ANS[2]++;
	for(int i=N-1;i>=2;i--)
	{
		while(i+1<N&&ANS[i]&&ANS[i+1])
		{
			if(i+2==N)ANS[N++]=0;
			ANS[i+2]++;
			ANS[i+1]--;
			ANS[i]--;
		}
		if(ANS[i]==3)
		{
			if(i+1==N)ANS[N++]=0;
			if(i+2==N)ANS[N++]=0;
			ANS[i+2]++,ANS[i-2]++;
			ANS[i]=0;
		}
		if(ANS[i]==2)
		{
			if(i+1==N)ANS[N++]=0;
			ANS[i+1]++,ANS[i-2]++;
			ANS[i]=0;
		}
	}
	for(int i=0;i+1<N;i++)
	{
		if(ANS[i]&&ANS[i+1])
		{
			if(i+2==N)ANS[N++]=0;
			ANS[i]--,ANS[i+1]--,ANS[i+2]++;
		}
	}
	int mx=-1;
	for(int i=0;i<N;i++)if(ANS[i])mx=i;
	printf("%d",mx+1);
	for(int i=0;i<=mx;i++)printf(" %d",ANS[i]);
	puts("");
	return 0;
}
