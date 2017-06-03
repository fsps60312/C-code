#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
int N,M;
int S[2000000],CNT[1000000];
int ReadInput()
{
	for(int i=0;i<N;i++)CNT[i]=0;
	int *cnt=new int[M];
	int ans=0;
	for(int i=0;i<M;i++)
	{
		scanf("%d",&cnt[i]),ans+=cnt[i];
		if(ans>N)return -1;
	}
	for(int i=0,c;i<M;i++)scanf("%d",&c),CNT[--c]=cnt[i];
	delete[]cnt;
	for(int i=0;i<N;i++)scanf("%d",&S[i]),S[i]--;
	return ans;
}
int Solve()
{
	const int sum=ReadInput();
	if(sum==-1)return 0;
	for(int i=0;i<sum;i++)S[N+i]=S[i];
	for(int i=0;i<sum;i++)CNT[S[i]]--;
	int dif=0;
	for(int i=0;i<N;i++)if(CNT[i]!=0)dif++;
	int ans=0;
	for(int i=sum;i<N+sum;i++)
	{
		if(dif==0)ans++;
		if(CNT[S[i-sum]]==0)dif++;
		if(CNT[S[i]]==0)dif++;
		CNT[S[i-sum]]++,CNT[S[i]]--;
		if(CNT[S[i-sum]]==0)dif--;
		if(CNT[S[i]]==0)dif--;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	printf("%d\n",Solve());
	return 0;
}
