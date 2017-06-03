#include<cstdio>
#include<vector>
#include<cassert>
#include<utility>
#include<set>
#include<algorithm>
using namespace std;
int N,M;
vector<int>ET[100000];
set<pair<int,int> >ANS;
bool VIS[100000];
vector<vector<int> >LINK;
void Dfs(const int u,vector<int>link)
{
	assert(!VIS[u]);
	VIS[u]=true;
	link.push_back(u);
	for(const int nxt:ET[u])if(!VIS[nxt]){Dfs(nxt,link);break;}
}
bool Cmp(const vector<int>&a,const vector<int>&b){return a.size()>b.size();}
void AddEdge(const int a,const int b){ANS.insert(make_pair(a,b));}
bool Solve()
{
	if(N<=2)return M==0;
	for(int i=0;i<N;i++)VIS[i]=false;
	LINK.clear();
	for(int i=0;i<N;i++)if(!VIS[i])
	{
		vector<int>s;Dfs(i,s);
		LINK.push_back(s);
	}
	sort(LINK.begin(),LINK.end(),Cmp);
	ANS.clear();
	const int lsz=LINK.size();
	if((int)LINK[0].size()==1)
	{
		if(lsz<3)return false;
		for(int i=0;i<3;i++)AddEdge(LINK[i][0],LINK[(i+1)%3][0]);
		for(int i=0;i<3;i++)LINK.erase(LINK.begin());
	}
	else if(lsz>=2&&LINK[0].size()==LINK[1].size())
	{
		const int n=LINK[0].size();
		AddEdge(LINK[0][0],LINK[1][0]),AddEdge(LINK[0][n-1],LINK[1][n-1]);
		for(int i=0;i+1<n;i++)AddEdge(LINK[0][i],LINK[1][i+1]),AddEdge(LINK[0][i+1],LINK[1][i]);
		for(int i=0;i<2;i++)LINK.erase(LINK.begin());
	}
	else if((int)LINK[0].size()==2)
	{
		if(lsz<=2)return false;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)AddEdge(LINK[0][i],LINK[1+j][0]);
		for(int i=0;i<3;i++)LINK.erase(LINK.begin());
	}
	else if((int)LINK[0].size()==3)
	{
		
	}
	else if((int)LINK[0].size()>=5)
	{
		const int n=LINK[0].size();
		vector<int>tmp;
		int cur=0;
		while(cur<n)tmp.push_back(cur),cur+=2;
		if(cur==n)
		{
			tmp.push_back(1),cur=n-1;
			while(cur>1)tmp.push_back(cur),cur-=2;
		}
		else
		{
			cur=1;
			while(cur<n)tmp.push_back(cur),cur+=2;
		}
		assert((int)tmp.size()==n);
		for(int i=0;i<n;i++)AddEdge(LINK[0][tmp[i]],LINK[0][tmp[(i+1)%n]]);
		tmp.clear(),vector<int>().swap(tmp);
		LINK.erase(LINK.begin());
	}
	for(const auto &s:LINK)
	{
		vector<pair<int,int> >a,b;
		for(auto it=ANS.begin();a.size()<s.size();it++)a.push_back(*it);
		for(int i=0;i<(int)s.size();i++)
		{
			b.push_back(make_pair(a[i].first,s[i]));
			b.push_back(make_pair(s[i],a[i].second));
		}
		for(const auto &v:a)ANS.erase(v);
		for(const auto &v:b)ANS.insert(v);
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(Solve())for(const auto &p:ANS)printf("%d %d\n",p.first+1,p.second+1);
		else puts("-1");
//		break;
	}
	return 0;
}
