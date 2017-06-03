#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
int N,TYPE[100000],COLOR[100000];
vector<int>ET[100000];
int TagType(const int u,const int parent,const int type)
{
	TYPE[u]=type;
	int ans=(type==0?1:0);
	for(const int nxt:ET[u])if(nxt!=parent)ans+=TagType(nxt,u,type^1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("bicoloring.in","r",stdin);
	freopen("bicoloring.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<N-1;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	if(TagType(0,-1,0)>N)
	{
		for(int i=0;i<N;i++)TYPE[i]^=1;
	}
	for(int i=0;i<N;i++)COLOR[i]=-1;
	set<int>color_used,available;
	for(int i=1;i<=N+1;i++)available.insert(i);
	for(int i=0;i<N;i++)if(TYPE[i]==0)
	{
		set<int>restrict;
		for(const int nxt:ET[i])restrict.insert(COLOR[nxt]);
		int &color=COLOR[i];assert(color==-1);
		for(const int v:available)if(restrict.find(v)==restrict.end()){color=v;break;}
		assert(color!=-1);
		available.erase(color);
		auto it1=color_used.begin(),it2=available.begin();
		for(const int nxt:ET[i])if(COLOR[nxt]==-1)
		{
			int &ans=COLOR[nxt];
			for(;ans==-1&&it1!=color_used.end();it1++)if(restrict.find(*it1)==restrict.end())
			{
				restrict.insert(ans=*(it1++));break;
			}
			for(;ans==-1&&it2!=available.end();it2++)if(restrict.find(*it2)==restrict.end())
			{
				restrict.insert(ans=*(it2++));break;
			}
			assert(ans!=-1);
		}
		color_used.insert(color);
	}
	for(int i=0;i<N;i++)
	{
		if(i)putchar(' ');
		printf("%d",COLOR[i]);
	}
	puts("");
	return 0;
}
