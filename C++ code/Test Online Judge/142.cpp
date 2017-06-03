#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,K,S[1000];
int DP[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	static int casenumber;scanf("%d",&casenumber);
	while(casenumber--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		DP[0]=S[0];
		int ans=S[0];
		for(int i=1;i<N;i++)
		{
			DP[i]=S[i];
			for(int dis=K;i-dis>=0;dis++)getmax(DP[i],DP[i-dis]+S[i]);
			getmax(ans,DP[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
