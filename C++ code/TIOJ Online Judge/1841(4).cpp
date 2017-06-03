#include<cstdio>
#include<vector>
#include<stack>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
LL SUM[1000002];
//vector<int>UP,DOWN;
vector<int>FA[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%lld",&SUM[i]),SUM[i]+=SUM[i-1];
//		UP.clear(),DOWN.clear();
//		for(int i=0;i<=N;i++)
//		{
//			const int cmpl=(i==0||SUM[i-1]==SUM[i]?0:(SUM[i-1]<SUM[i]?-1:1));
//			const int cmpr=(i==N||SUM[i]==SUM[i+1]?0:(SUM[i+1]<SUM[i]?-1:1));
//			if(cmpl<=0&&cmpr<=0)UP.push_back(i);
//			if(cmpl>=0&&cmpr>=0)DOWN.push_back(i);
//		}
		for(int i=0;i<=1000000;i++)FA[i].clear(),vector<int>().swap(FA[i]);
		int ans=0;
		stack<int>stk;
		SUM[N+1]=INF,stk.push(N+1);
		for(int i=N;i>=0;i--)
		{
			while(SUM[i]>SUM[stk.top()])stk.pop();
			for(int cur=stk.top(),d=0;;cur=FA[cur][d++])
			{
				FA[i].push_back(cur);
				if(d>=(int)FA[cur].size())break;
			}
			stk.push(i);
		}
		while(!stk.empty())stk.pop();
		SUM[N+1]=-INF,stk.push(N+1);
		for(int i=N;i>=0;i--)
		{
			while(SUM[i]<=SUM[stk.top()])stk.pop();
			int cur=i;
			for(int d=30;d>=0;d--)if(d<(int)FA[cur].size()&&FA[cur][d]<stk.top())cur=FA[cur][d];
			getmax(ans,cur-i);
			stk.push(i);
		}
		stack<int>().swap(stk);
		printf("%d\n",ans);
	}
	return 0;
}
