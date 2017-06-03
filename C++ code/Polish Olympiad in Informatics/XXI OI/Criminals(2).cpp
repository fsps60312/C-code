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
		lpath.resize(X.size()),rpath.resize(Y.size());
		for(int i=0,l=home[0].first;i<(int)X.size();i++)
		{
			Iter it=upper_bound(LOCS[X[i]].begin(),LOCS[X[i]].end(),l);
			lpath[i]=make_pair(it,LOCS[X[i]].end());
			if(it!=LOCS[X[i]].end())l=*it;
			else l=N;
		}
		for(int i=0,r=home[0].second;i<(int)Y.size();i++)
		{
			Iter it=lower_bound(LOCS[Y[i]].begin(),LOCS[Y[i]].end(),r);
			rpath[i]=make_pair(it,LOCS[Y[i]].begin());
			if(it!=LOCS[Y[i]].begin())r=*--it;
			else r=-1;
		}
		vector<pair<int,int> >ans_seg;
		if()
	}
	return 0;
}
