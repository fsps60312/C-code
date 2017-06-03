#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N;
char A[100001],B[100001];
int LP[100001],RP[100001],LCNT[100001],RCNT[100001];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf(1,"%d",&testcount);
	while(testcount--)
	{
		scanf(3,"%d%s%s",&N,A,B);
		LP[0]=0;
		for(int i=1;i<=N;i++)LP[i]=(A[i-1]==B[i-1]?LP[i-1]:i);
		RP[N]=N;
		for(int i=N-1;i>=0;i--)RP[i]=(A[i]==B[i]?RP[i+1]:i);
		LCNT[0]=0,LCNT[1]=1;
		for(int i=2;i<=N;i++)LCNT[i]=LCNT[i-1]+(B[i-1]==B[i-2]?0:1);
		RCNT[N]=0,RCNT[N-1]=1;
		for(int i=N-2;i>=0;i--)RCNT[i]=RCNT[i+1]+(B[i]==B[i+1]?0:1);
		int ans=INF;
		for(int i=0;i<=N;i++)getmin(ans,max(LCNT[LP[i]],RCNT[RP[i]]));
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	return 0;
}
