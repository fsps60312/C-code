#include<cstdio>
#include<cstdlib>
#include<queue>
#include<stack>
using namespace std;
int n;
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1)
	{
		stack<int> s;
		queue<int> q;
		priority_queue<int> p;
		bool iss=true,isq=true,isp=true;
		for(int i=0,j,k;i<n;i++)
		{
			scanf("%d%d",&j,&k);
			if(j==1)
			{
				s.push(k);q.push(k);p.push(k);
			}
			else
			{
				if(s.empty()||s.top()!=k) iss=false;
				else s.pop();
				if(q.empty()||q.front()!=k) isq=false;
				else q.pop();
				if(p.empty()||p.top()!=k) isp=false;
				else p.pop();
			}
		}
		int ans=0;
		if(iss) ans++;
		if(isq) ans++;
		if(isp) ans++;
		if(ans==0) printf("impossible\n");
		else if(ans>=2) printf("not sure\n");
		else if(iss) printf("stack\n");
		else if(isq) printf("queue\n");
		else printf("priority queue\n");
	}
	return 0;
}
