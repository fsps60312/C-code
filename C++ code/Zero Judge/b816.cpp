#include<cstdio>
#include<cassert>
//#include<algorithm>
using namespace std;
int N,S[500000],MN[500000],MX[500000];
int max(int a,int b)
{
	return a>b?a:b;
}
int min(int a,int b)
{
	return a<b?a:b;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&S[i]);
	}
	MN[0]=S[0];
	for(int i=1;i<N;i++)
	{
		MN[i]=min(MN[i-1],S[i]);
	}
	MX[N-1]=S[N-1];
	for(int i=N-2;i>=0;i--)
	{
		MX[i]=max(MX[i+1],S[i]);
	}
	int ans=0;
	for(int i=1;i+1<N;i++)
	{
		if(MN[i-1]<S[i]&&S[i]<MX[i+1])
		{
			ans=max(ans,(S[i]-MN[i-1])*(MX[i+1]-S[i]));
		}
	}
	printf("%d\n",ans);
	return 0;
}
