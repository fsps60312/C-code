#include<cstdio>
#include<vector>
#include<stack>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
LL SUM[1000002];
int FA[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%lld",&SUM[i]),SUM[i]+=SUM[i-1];
		int ans=0;
		stack<int>stk;
		SUM[N+1]=INF,stk.push(N+1);
		for(int i=N;i>=0;i--)
		{
			while(SUM[i]>SUM[stk.top()])stk.pop();
			FA[i]=stk.top();
			stk.push(i);
		}
		while(!stk.empty())stk.pop();
		SUM[N+1]=-INF,stk.push(N+1);
		for(int i=N;i>=0;i--)
		{
			while(SUM[i]<=SUM[stk.top()])stk.pop();
			int cur=i;
			while(FA[cur]<stk.top())cur=FA[cur];
			getmax(ans,cur-i);
			stk.push(i);
		}
		stack<int>().swap(stk);
		printf("%d\n",ans);
	}
	return 0;
}
