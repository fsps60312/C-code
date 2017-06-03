#include<cstdio>
#include<cstdlib>
#include<queue>
#include<stack>
using namespace std;
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		priority_queue<int> pq;
		queue<int> q;
		stack<int> s;
		bool ispq=true;
		bool isq=true;
		bool iss=true;
		for(int i=0,a,b;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			if(a==1)
			{
				pq.push(b);
				q.push(b);
				s.push(b);
			}
			else
			{
				if(!pq.size()||(ispq&&pq.top()!=b)) ispq=false;
				if(!q.size()||(isq&&q.front()!=b)) isq=false;
				if(!s.size()||(iss&&s.top()!=b)) iss=false;
				if(pq.size()) pq.pop();
				if(q.size()) q.pop();
				if(s.size()) s.pop();
			}
		}
		int ans=0;
		if(ispq) ans++;
		if(isq) ans++;
		if(iss) ans++;
		if(ans==0) printf("impossible\n");
		else if(ans>=2) printf("not sure\n");
		else if(ispq) printf("priority queue\n");
		else if(isq) printf("queue\n");
		else printf("stack\n");
	}
	return 0;
}
