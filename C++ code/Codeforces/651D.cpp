#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,A,B,T;
char S[1000001];
int TIME[1000000];
int Solve()
{
	TIME[N]=(S[N]=='w'?B+1:1);
	for(int i=N;i+1<N*2;i++)TIME[i+1]=TIME[i]+A+(S[i+1]=='w'?B+1:1);
	for(int i=N;i-1>=1;i--)TIME[i-1]=TIME[i]+A+(S[i-1]=='w'?B+1:1);
//	for(int i=1;i<N*2;i++)printf("%d ",TIME[i]);puts("");
	int ans=0;
	for(int i=N;i>=1&&TIME[i]<=T;i--)
	{
		int read=N-i+1;
		int remain=T-TIME[i]-(N-i)*A;
//		printf("i=%d,remain=%d\n",i,remain);
		int l=N,r=N+i-1;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(TIME[mid]-TIME[N]<=remain)l=mid;
			else r=mid-1;
		}
		getmax(ans,read+(r-N));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&A,&B,&T)==4)
	{
		scanf("%s",S);
		for(int i=0;i<N;i++)S[N+i]=S[i];
		int ans=0;
		getmax(ans,Solve());
		for(int l=1,r=N*2-1;l<r;l++,r--)swap(S[l],S[r]);
		getmax(ans,Solve());
		printf("%d\n",ans);
	}
	return 0;
}
