#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
typedef vector<int>::const_iterator Iter;
int N,K;
vector<int>LOCS[1000000],X,Y;
vector<pair<int,int> >GetHome(const int *colors)
{
	vector<pair<int,int> >ts,ans;
	static bool vis[1000000];
	for(int i=0;i<K;i++)vis[i]=false;
	for(int i=0;i<N;i++)
	{
		const int c=colors[i];
		if(!vis[c])assert(LOCS[c].front()==i),vis[c]=true,ts.push_back(make_pair(LOCS[c].front(),LOCS[c].back()));
	}
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
	if(a.empty())return vector<int>();
	vector<pair<int,int> >ta;
	pair<int,int>seg=a[0];
	for(int i=1;i<(int)a.size();i++)
	{
		assert(a[i-1].first<=a[i].first);
		if(a[i].first<=seg.second)getmax(seg.second,a[i].second);
		else ta.push_back(seg),seg=a[i];
	}
	ta.push_back(seg);
	vector<int>ans;
	const int c=X.back();
	for(int i=0,cur=0;i<(int)ta.size();i++)
	{
		while(LOCS[c][cur]<ta[i].first)cur++;
		assert(LOCS[c][cur]==ta[i].first);
		while(cur<(int)LOCS[c].size()&&LOCS[c][cur]<=ta[i].second)ans.push_back(LOCS[c][cur++]);
	}
	return ans;
}
int TRANS[1000001];
int COLORS[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=1;i<=K;i++)TRANS[i]=-1;
		for(int i=0;i<N;i++)scanf("%d",&COLORS[i]),TRANS[COLORS[i]]=-2;
		for(int k=K,i=1,&cnt=K=0;i<=k;i++)if(TRANS[i]==-2)TRANS[i]=cnt++;
//		printf("K=%d\n",K);
		for(int i=0;i<K;i++)LOCS[i].clear();
		for(int i=0;i<N;i++)LOCS[COLORS[i]=TRANS[COLORS[i]]].push_back(i);
		bool impossible=false;
		if(true)
		{
			int m,l;scanf("%d%d",&m,&l);
			X.resize(m),Y.resize(l);
			for(int i=0;i<m;i++)scanf("%d",&X[i]);
			for(int i=0;i<l;i++)scanf("%d",&Y[i]);
			for(int i=0;i<m;i++)
			{
				if(TRANS[X[i]]==-1)impossible=true;
				else X[i]=TRANS[X[i]];
			}
			for(int i=0;i<l;i++)
			{
				if(TRANS[Y[i]]==-1)impossible=true;
				else Y[i]=TRANS[Y[i]];
			}
		}
		if(impossible)printf("0\n\n");
		else
		{
			const vector<pair<int,int> >&home=GetHome(COLORS);
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
	}
	return 0;
}
