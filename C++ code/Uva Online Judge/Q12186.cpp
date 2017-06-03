#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
vector<int> GETO[100001];
int N,T,ANS[100001];
int get_ANS(int u)
{
	int &ans=ANS[u];
	if(ans!=-1)return ans;
	ans=0;
	if(!GETO[u].size())return ans=1;
	priority_queue<int,vector<int>,greater<int> > pq;
	for(int i=0;i<GETO[u].size();i++)
	{
		pq.push(get_ANS(GETO[u][i]));
	}
	for(int i=0;i*100<GETO[u].size()*T;i++)
	{
		ans+=pq.top();pq.pop();
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%d%d",&N,&T)==2&&(N||T))
	{
		for(int i=0;i<=N;i++)
		{
			GETO[i].clear();
			ANS[i]=-1;
		} 
		for(int i=1;i<=N;i++)
		{
			int a;scanf("%d",&a);
			GETO[a].push_back(i);
		}
		printf("%d\n",get_ANS(0));
	}
	return 0;
}
