#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
typedef vector<int>::const_iterator Iter;
int N,K;
vector<int>LOCS[1000000],X,Y;
vector<pair<int,int> >GetHome()
{
	vector<pair<int,int> >ts,ans;
	for(int i=0;i<K;i++)ts.push_back(make_pair(LOCS[i].front(),LOCS[i].back()));
	sort(ts.begin(),ts.end());
	assert((int)ts.size()==K);
	for(int i=0,mx=-1;i<K;i++)
	{
		if(ts[i].second<=mx)continue;
		else ans.push_back(ts[i]),getmax(mx,ts[i].second);
	}
	return ans;
}
int MaintainLeftPath(vector<pair<Iter,Iter> >&s,const int start)
{
	if(s.back().first==s.back().second)return N;
	int l=start;
	for(int i=0;i<(int)X.size();i++)
	{
		if(*s[i].first>l)return *s.back().first;
		while(s[i].first!=s[i].second&&*s[i].first<=l)++s[i].first;
		if(s[i].first==s[i].second)
		{
			s.back().first=s.back().second;
			return N;
		}
		l=*s[i].first;
	}
	return l;
}
Iter Prev(Iter it){return --it;}
int MaintainRightPath(vector<pair<Iter,Iter> >&s,const int start)
{
	int r=start;
	for(int i=0;i<(int)Y.size();i++)
	{
		if()
		if(s[i].first!=LOCS[Y[i]].begin()&&(s[i].first==s[i].second||*s[i].first>=l))
		while(s[i].first!=s[i].second&&*s[i].first<l)++s[i].first;
		
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<K;i++)LOCS[i].clear();
		for(int i=0,c;i<N;i++)
		{
			scanf("%d",&c),--c;
			LOCS[c].push_back(i);
		}
		if(true)
		{
			int m,l;scanf("%d%d",&m,&l);
			X.resize(m),Y.resize(l);
			for(int i=0;i<m;i++)scanf("%d",&X[i]),--X[i];
			for(int i=0;i<l;i++)scanf("%d",&Y[i]),--Y[i];
		}
		const vector<pair<int,int> >&home=GetHome();
		vector<pair<Iter,Iter> >lpath,rpath;
		for(int i=0;i<(int)X.size();i++)lpath.push_back(make_pair(LOCS[X[i]].begin(),LOCS[X[i]].end()));
		for(int i=0;i<(int)Y.size();i++)rpath.push_back(make_pair(LOCS[Y[i]].begin(),LOCS[Y[i]].end()));
		for(int i=0,r=home[0].second;i<(int)Y.size();i++)
		{
			Iter it=lower_bound(LOCS[Y[i]].begin(),LOCS[Y[i]].end(),r);
			rpath[i]=make_pair(it,LOCS[Y[i]].begin());
			if(it!=LOCS[Y[i]].begin())r=*--it;
			else r=-1;
		}
		vector<pair<int,int> >ans_seg;
		for(int i=0,l,r;i<(int)home.size();i++)
		{
			if((l=MaintainLeftPath(lpath,home[i].first))<=(r=MaintainRightPath(rpath,home[i].second)))ans_seg.push_back(make_pair(l,r));
		}
	}
	return 0;
}
