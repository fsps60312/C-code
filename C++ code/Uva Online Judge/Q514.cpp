#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<cassert>
using namespace std;
int N;
queue<int>C,TARGET;
bool Input()
{
	static int v;scanf("%d",&v);
	if(v==0)return false;
	while(!C.empty())C.pop();
	while(!TARGET.empty())TARGET.pop();
	TARGET.push(v),C.push(1);
	for(int i=2;i<=N;i++)scanf("%d",&v),TARGET.push(v),C.push(i);
	return true;
}
stack<int>STK;
int Pop(queue<int>&q){int ans=q.front();q.pop();return ans;}
bool Solve()
{
	while(!STK.empty())STK.pop();
	for(int i=0;i<N;i++)
	{
		STK.push(Pop(C));
		while(!STK.empty()&&STK.top()==TARGET.front())STK.pop(),TARGET.pop();
	}
	return TARGET.empty();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N){while(Input())
	{
		puts(Solve()?"Yes":"No");
	}puts("");}
	return 0;
}
