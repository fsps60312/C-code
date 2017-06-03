#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,S[1001][1001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			int &v=S[i][j];
			scanf("%d",&v),v--,v=(v-i+N)%N;
		}
		int ans=INF;
		for(int i=0;i<N;i++)
		{
			int ta=0;
			for(int p=0;p<N;p++)
			{
				int cost=(S[p][0]-i+N)%N;
				for(int j=1;j<N;j++)cost+=(S[p][j]-S[p][j-1]+N)%N;
				getmax(ta,cost);
			}
			getmin(ans,ta);
		}
		printf("%d\n",ans);
	}
	return 0;
}
