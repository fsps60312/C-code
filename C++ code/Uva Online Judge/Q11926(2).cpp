#include<cstdio>
#include<queue>
#include<algorithm>
#include<cassert>
using namespace std;
struct Task
{
	int l,r,interval;
	Task(){}
	Task(const int _l,const int _r,const int _i):l(_l),r(_r),interval(_i){}
	bool operator<(const Task &t)const{return l>t.l;}
};
priority_queue<Task>TASK;
bool Solve()
{
	while(!TASK.empty())
	{
		const Task t=TASK.top();TASK.pop();
		assert(t.l<1000000);
		if(t.interval&&t.l+t.interval<1000000)TASK.push(Task(t.l+t.interval,t.r+t.interval,t.interval));
		if(!TASK.empty()&&t.r>TASK.top().l)return false;
	}
	return true;
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		while(!TASK.empty())TASK.pop();
		for(int i=0,a,b;i<N;i++)scanf("%d%d",&a,&b),TASK.push(Task(a,b,0));
		for(int i=0,a,b,c;i<M;i++)scanf("%d%d%d",&a,&b,&c),TASK.push(Task(a,b,c));
		puts(Solve()?"NO CONFLICT":"CONFLICT");
	}
	return 0;
}
