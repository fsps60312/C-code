#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
inline void getmax(int &a,const int b){if(a<b)a=b;}
typedef vector<int>::const_iterator Iter;
int N,K;
vector<int>LOCS[1000000],X,Y;
vector<pair<int,int> >GetHome(const int *colors)
{
	static pair<int,int>ts[1000000];
	static bool vis[1000000];
	for(int i=0;i<K;i++)vis[i]=false;
	for(int i=0,cur=0;i<N;i++)
	{
		const int c=colors[i];
		if(!vis[c])vis[c]=true,ts[cur++]=make_pair(LOCS[c].front(),LOCS[c].back());
	}
	vector<pair<int,int> >ans;
	for(int i=0,mx=-1;i<K;i++)
	{
		if(ts[i].second<=mx)continue;
		else ans.push_back(ts[i]),getmax(mx,ts[i].second);
	}
	return ans;
}
int MaintainLeftPath(vector<pair<Iter,Iter> >&s,vector<bool>&vis,const int start)
{
	if(s.back().first==s.back().second)return N;
	int l=start;
	for(int i=0;i<(int)s.size();i++)
	{
		pair<Iter,Iter>&si=s[i];
		if(vis[i]&&*si.first>l)return *s.back().first;
		vis[i]=true;
		while(si.first!=si.second&&*si.first<=l)++si.first;
		if(si.first==si.second)
		{
			s.back().first=s.back().second;
			return N;
		}
		l=*si.first;
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
	const vector<int>&locs=LOCS[X.back()];
	for(int i=0,cur=0;i<(int)ta.size();i++)
	{
		while(locs[cur]<ta[i].first)cur++;
		assert(locs[cur]==ta[i].first);
		while(cur<(int)locs.size()&&locs[cur]<=ta[i].second)ans.push_back(locs[cur++]);
	}
	return ans;
}
int TRANS[1000001];
int COLORS[1000000];
inline char ReadChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
void GetInt(int &v)
{
	char c=ReadChar();
	while(c<'0'||'9'<c)c=ReadChar();
	v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=ReadChar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N),GetInt(K);
	for(int i=1;i<=K;i++)TRANS[i]=-1;
	for(int i=0;i<N;i++)GetInt(COLORS[i]),TRANS[COLORS[i]]=-2;
	for(int k=K,i=1,&cnt=K=0;i<=k;i++)if(TRANS[i]==-2)TRANS[i]=cnt++;
	for(int i=0;i<K;i++)LOCS[i].clear();
	for(int i=0;i<N;i++)LOCS[COLORS[i]=TRANS[COLORS[i]]].push_back(i);
	bool impossible=false;
	if(true)
	{
		int m,l;GetInt(m),GetInt(l);
		X.resize(m),Y.resize(l);
		for(int i=0;i<m;i++)
		{
			int &v=X[i];
			GetInt(v);
			if(TRANS[v]==-1)impossible=true;
			else v=TRANS[v];
		}
		for(int i=0;i<l;i++)
		{
			int &v=Y[i];
			GetInt(v);
			if(TRANS[v]==-1)impossible=true;
			else v=TRANS[v];
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
	return 0;
}
