#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
struct nodetype
{
	int mom;
	vector<int> ch;
	void removech(int a)
	{
		if(ch[ch.size()-1]!=a) printf("error\n");
		ch.pop_back();
	}
};
int bfs[1001],dfs[1001],n;
nodetype S[1001];
void shows()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<S[i].ch.size();j++) printf("%d",S[i].ch[j]);printf(" ");
	}
	printf("\n");
}
void changemom(int a,int b)
{
	S[S[a].mom].removech(a);
	S[a].mom=S[b].mom;
	S[S[b].mom].ch.push_back(a);
	//printf("connect %d to %d\n",a,b);
}
bool check()
{
	queue<int> node;
	node.push(bfs[1]);
	int now=1;
	while(!node.empty())
	{
		int a=node.front();node.pop();
		for(int i=0;i<S[a].ch.size();i++)
		{
			int j=S[a].ch[i];
		//printf("%d,",j);
			if(j!=bfs[++now])
			{
				//shows();
				changemom(bfs[now],bfs[now-1]);
				return true;
			}
			else node.push(j);
		}
	}
	return false;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1)
	{
		for(int i=1;i<=n;i++) scanf("%d",&bfs[i]);
		for(int i=1;i<=n;i++) scanf("%d",&dfs[i]);
		for(int i=0;i<=n;i++)
		{
			S[i].ch.clear();
		}
		for(int i=1;i<n;i++)
		{
			S[dfs[i]].ch.push_back(dfs[i+1]);
			S[dfs[i+1]].mom=dfs[i];
		}
		while(check());
		for(int i=1;i<=n;i++)
		{
			printf("%d:",i);
			for(int j=0;j<S[i].ch.size();j++)
			{
				printf(" %d",S[i].ch[j]);
			}
			printf("\n");
		}
	}
	return 0;
}
