#include<cstdio>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,S[1000000];
bool VIS[1000000];
int MaxSpan()
{
	int ans=0;
	for(int i=0;i<N;i++)VIS[i]=false;
	for(int i=0;i<N;i++)VIS[(S[i]+N-i)%N]=true;
	for(int i=0,cnt=0;i<N*2;i++)
	{
		getmax(ans,++cnt);
		if(VIS[i%N])cnt=0;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d",&N)==1);
	for(int i=0;i<N;i++)assert(scanf("%d",&S[i])==1),S[i]--;
	int maxspan=MaxSpan();
	for(int i=0;i<N;i++)S[i]=N-1-S[i];
	getmax(maxspan,MaxSpan());
	printf("%d\n",(N-maxspan+1)/2); 
	return 0;
}
