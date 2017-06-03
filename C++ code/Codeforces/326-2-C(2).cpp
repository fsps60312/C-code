#include<cstdio>
#include<queue>
using namespace std;
int N,S[1000000];
priority_queue<int,vector<int>,greater<int> >PQ;
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)PQ.push(S[i]);
	int ans=0;
	while(!PQ.empty())
	{
		int u=PQ.top();PQ.pop();
		if(!PQ.empty()&&u==PQ.top())
		{
			PQ.pop();
			PQ.push(u+1);
		}
		else ans++;
	}
	printf("%d\n",ans);
	return 0;
}
