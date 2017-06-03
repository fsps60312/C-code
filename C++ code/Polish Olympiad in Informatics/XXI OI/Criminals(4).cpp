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
//	printf("ans.size()=%d\n",(int)ans.size());
	return ans;
}
int MaintainLeftPath(vector<pair<Iter,Iter> >&s,vector<bool>&vis,const int start)
{
	if(s.back().first==s.back().second)return N;
	int l=start;
	for(int i=0;i<(int)s.size();i++)
	{
		if(vis[i]&&*s[i].first>l)return *s.back().first;
		vis[i]=true;
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
vector<int>GetLeftPaths(const vector<pair<int,int> >&home)
{
	vector<pair<Iter,Iter> >path;
	vector<bool>vis;
	for(int i=0;i<(int)X.size();i++)path.push_back(make_pair(LOCS[X[i]].begin(),LOCS[X[i]].end())),vis.push_back(false);
	vector<int>ans;
	for(int i=0;i<(int)home.size();i++)
	{
		ans.push_back(MaintainLeftPath(path,vis,home[i].first));
	}
	return ans;
}
void ReverseLocs()
{
	for(int i=0;i<K;i++)
	{
		for(int j=0;j<(int)LOCS[i].size();j++)LOCS[i][j]=N-1-LOCS[i][j];
		reverse(LOCS[i].begin(),LOCS[i].end());
	}
}
vector<int>GetRightPaths(const vector<pair<int,int> >&home)
{
	ReverseLocs();
	vector<pair<Iter,Iter> >path;
	vector<bool>vis;
	for(int i=0;i<(int)Y.size();i++)path.push_back(make_pair(LOCS[Y[i]].begin(),LOCS[Y[i]].end())),vis.push_back(false);
	vector<int>ans;
	for(int i=(int)home.size()-1;i>=0;i--)
	{
		ans.push_back(MaintainLeftPath(path,vis,N-1-home[i].second));
	}
	ReverseLocs();
	for(int i=0;i<(int)ans.size();i++)ans[i]=N-1-ans[i];
	reverse(ans.begin(),ans.end());
	return ans;
}
vector<int>DeDuplicate(vector<pair<int,int> >&a)
{
	vector<pair<int,int> >ta;
	sort(a.begin(),a.end());
	pair<int,int>seg=a[0];
	for(int i=1;i<(int)a.size();i++)
	{
		if(a[i].first<=seg.second)getmax(seg.second,a[i].second);
		else ta.push_back(seg),seg=a[i];
	}
	ta.push_back(seg);
	vector<int>ans;
	const int c=X.back();
	for(int i=0;i<(int)ta.size();i++)
	{
		const int l=(int)(lower_bound(LOCS[c].begin(),LOCS[c].end(),ta[i].first)-LOCS[c].begin());
		const int r=(int)(lower_bound(LOCS[c].begin(),LOCS[c].end(),ta[i].second)-LOCS[c].begin());
		for(int j=l;j<=r;j++)ans.push_back(LOCS[c][j]);
	}
	return ans;
}
vector<int>V;
int COLORS[1000000];
int Id(const vector<int>&s,const int val){return (int)(lower_bound(s.begin(),s.end(),val)-s.begin());}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		V.clear();
		for(int i=0;i<N;i++)scanf("%d",&COLORS[i]),V.push_back(COLORS[i]);
		sort(V.begin(),V.end()),V.resize(unique(V.begin(),V.end())-V.begin());
		K=(int)V.size();
		for(int i=0;i<K;i++)LOCS[i].clear();
		for(int i=0;i<N;i++)LOCS[Id(V,COLORS[i])].push_back(i);
		if(true)
		{
			int m,l;scanf("%d%d",&m,&l);
			X.resize(m),Y.resize(l);
			for(int i=0;i<m;i++)scanf("%d",&X[i]),X[i]=Id(V,X[i]);
			for(int i=0;i<l;i++)scanf("%d",&Y[i]),Y[i]=Id(V,Y[i]);
		}
		const vector<pair<int,int> >&home=GetHome();
		const vector<int>&ls=GetLeftPaths(home);
		const vector<int>&rs=GetRightPaths(home);
		vector<pair<int,int> >ans_seg;
		for(int i=0;i<(int)home.size();i++)
		{
			if(ls[i]<=rs[i])ans_seg.push_back(make_pair(ls[i],rs[i]));
		}
		const vector<int>&ans=DeDuplicate(ans_seg);
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
