#include<cstdio>
#include<algorithm>
using namespace std; 
int N,M,ANS[1000005];
bool Conseq(const int &i)
{
	if(ANS[i]&&ANS[i-1])
	{
		if(i+1==N)ANS[N++]=0;
		int v=min(ANS[i],ANS[i-1]);
		ANS[i]-=v,ANS[i-1]-=v;
		ANS[i+1]+=v;
		return true;
	}
	return false;
}
bool Two(const int &i)
{
	if(ANS[i]/2)
	{
		if(i+1==N)ANS[N++]=0;
		if(i==0)ANS[i+1]+=ANS[i]/2,ANS[i]%=2;
		else
		{
			if(i+1==N)ANS[N++]=0;
			ANS[i+1]+=ANS[i]/2;
			ANS[max(0,i-2)]+=ANS[i]/2;
			ANS[i]%=2;
		}
		return true;
	}
	return false;
}
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
	while(changed)
	{
		changed=false;
		for(int i=1;i<N;i++)changed|=Conseq(i);
		for(int i=0;i<N;i++)changed|=Two(i);
		for(int i=N-1;i>=1;i--)changed|=Conseq(i);
		for(int i=N-1;i>=0;i--)changed|=Two(i);
	}
	int mx=-1;
	for(int i=0;i<N;i++)if(ANS[i])mx=i;
	printf("%d",mx+1);
	for(int i=0;i<=mx;i++)printf(" %d",ANS[i]);
	puts("");
	return 0;
}
