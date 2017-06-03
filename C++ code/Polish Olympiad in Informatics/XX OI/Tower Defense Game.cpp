#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
int N,M,K;
vector<int>ET[500000];
bool VIS[500000],DELETED[500000];
set<int>S;
void Cover(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	if(!DELETED[u])S.erase(u),DELETED[u]=true;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(!DELETED[nxt])S.erase(nxt),DELETED[nxt]=true;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	S.clear();
	for(int i=0;i<N;i++)VIS[i]=DELETED[i]=false,S.insert(i);
	vector<int>ans;
	while(!S.empty())
	{
		const int u=*S.begin();
		Cover(u);
		for(int i=0;i<(int)ET[u].size();i++)Cover(ET[u][i]);
		ans.push_back(u+1);
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)
	{
		if(i)putchar(' ');
		printf("%d",ans[i]);
	}
	puts("");
	return 0;
}
