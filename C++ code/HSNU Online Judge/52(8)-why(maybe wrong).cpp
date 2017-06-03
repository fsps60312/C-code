#include<cstdio>
#include<algorithm>
using namespace std; 
int N,M,ANS[1000010];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<1000010;i++)ANS[i]=0;
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&ANS[i]);
	scanf("%d",&M);
	for(int i=0,v;i<M;i++){scanf("%d",&v);ANS[i]+=v;}
	N=1000010;
	if(ANS[0]==2)ANS[1]++,ANS[0]=0;
	if(ANS[0]==3)ANS[0]=0,ANS[2]++;
	if(ANS[1]==2)ANS[0]++,ANS[1]=0,ANS[2]++;
	for(int i=N-2;i>=2;i--)
	{
		while(ANS[i]&&ANS[i+1])
		{
			ANS[i+2]++;
			ANS[i+1]--;
			ANS[i]--;
		}
		if(ANS[i]==3)
		{
			ANS[i+2]++,ANS[i-2]++;
			ANS[i]=0;
		}
		if(ANS[i]==2)
		{
			ANS[i+1]++,ANS[i-2]++;
			ANS[i]=0;
		}
	}
	for(int i=0;i+1<N;i++)
	{
		if(ANS[i]&&ANS[i+1])
		{
			if(ANS[i+2]&&ANS[i+3]==0)continue;
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
