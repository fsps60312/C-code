#include<cstdio>
#include<set>
#include<cassert>
#include<algorithm>
using namespace std;
set<int>S[50001];
int IDX[50001];
int Idx(const int &a){return IDX[a]==a?a:(IDX[a]=Idx(IDX[a]));}
bool Merge(int x,int y)
{
	if(x==y)return true; 
	if(S[x].size()>S[y].size())swap(x,y);
	for(auto it=S[x].begin();it!=S[x].end();it++)if(S[y].find(-(*it))!=S[y].end())return false;
	for(auto it=S[x].begin();it!=S[x].end();it++)
	{
		S[y].insert(*it);
		if((*it)>0)assert(S[*it].find(-x)!=S[*it].end()),S[*it].erase(-x),S[*it].insert(-y);
		else assert(S[-(*it)].find(x)!=S[-(*it)].end()),S[-(*it)].erase(x),S[-(*it)].insert(y);
	}
	S[x].clear();
	IDX[x]=y;
	return true;
}
int N,K;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)S[i].clear(),IDX[i]=i;
	int ans=0;
	while(K--)
	{
		static int d,x,y;
		scanf("%d%d%d",&d,&x,&y);
//		printf("%d %d %d\n",d,x,y);
//		int preans=ans;
		if(x>N||y>N)ans++;
		else
		{
			assert(x>=1&&y>=1);
			x=Idx(x),y=Idx(y);
			if(d==1)
			{
				if(!Merge(x,y))ans++;
			}
			else if(d==2)
			{
				if(x==y||S[x].find(-y)!=S[x].end())ans++;
				else S[x].insert(y),S[y].insert(-x);
			}
			else assert(0);
		}
//		if(ans!=preans)puts("lie");
//		else puts("truth");
	}
	printf("%d\n",ans);
	return 0;
}
