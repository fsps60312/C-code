#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef __int64 LL;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
void MergeSegments(vector<pair<int,int> >&s)
{
	assert(!s.empty());
	sort(s.begin(),s.end());
	pair<int,int>now=s[0];
	vector<pair<int,int> >ans;
	for(const pair<int,int>&p:s)
	{
		if(now.second<p.first)ans.push_back(now),now=p;
		else getmax(now.second,p.second);
	}
	ans.push_back(now);
	s.clear(),ans.swap(s);
}
struct Bit
{
	int n;
	vector<int>s;
	vector<LL>cnt;
	void clear(const int _n){n=_n;s.clear(),cnt.clear();s.resize(n,0),cnt.resize(n,0LL);}
	void Add(int i,const int v,const int ratio)
	{
		if(!ratio)return;
		assert(i<n&&(cnt[i]+=ratio)>=0);
		if(ratio<0){if(cnt[i])return;}
		if(ratio>0){if(cnt[i]>ratio)return;}
		while(i<n)s[i]+=(ratio<0?-v:v),i+=(i&(-i));
	}
	int Query(int i)
	{
		int ans=0;
		while(i)ans+=s[i],i-=(i&(-i));
		return ans;
	}
}BIT;
int Id(const vector<int>&y,const int val)
{
	const int ans=lower_bound(y.begin(),y.end(),val)-y.begin();
	assert(y[ans]==val);
	return ans;
}
LL Solve(const map<int,vector<pair<int,int> > >&mv,const map<int,vector<pair<int,int> > >&mh)
{
	map<int,map<int,int> >endpoints;
	vector<int>y;
	for(const auto &it:mh)
	{
		y.push_back(it.first),y.push_back(it.first+1);
		for(const pair<int,int>&p:it.second)
		{
			endpoints[p.first][it.first]++,endpoints[p.second][it.first]--;
		}
	}
	for(const auto &it:mv)for(const pair<int,int>&p:it.second)
	{
		y.push_back(p.first),y.push_back(p.second);
	}
	sort(y.begin(),y.end()),y.resize(unique(y.begin(),y.end())-y.begin());
	BIT.clear(y.size());
	int ynow=-1000000000;
	LL ans=0LL;
	auto eps=endpoints.begin();
	for(const auto &vsegs:mv)
	{
		for(;eps!=endpoints.end()&&eps->first<=vsegs.first;eps++)
		{
			ans+=(LL)((eps->first)-ynow)*BIT.Query((int)y.size()-1);
			ynow=eps->first;
			for(const auto &ep:eps->second)BIT.Add(Id(y,ep.first)+1,1,ep.second);
		}
		for(const pair<int,int>&vseg:vsegs.second)
		{
			ans-=BIT.Query(Id(y,vseg.second))-BIT.Query(Id(y,vseg.first));
			ans+=vseg.second-vseg.first;
		}
	}
	for(;eps!=endpoints.end();eps++)
	{
		ans+=(LL)((eps->first)-ynow)*BIT.Query((int)y.size()-1);
		ynow=eps->first;
		for(const auto &ep:eps->second)BIT.Add(Id(y,ep.first)+1,1,ep.second);
	}
	assert(y.empty()||BIT.Query((int)y.size()-1)==0);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		map<int,vector<pair<int,int> > >mv,mh;
		for(int i=0,x1,y1,x2,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x1==x2)mv[x1].push_back(make_pair(min(y1,y2),max(y1,y2)+1));
			else assert(y1==y2),mh[y1].push_back(make_pair(min(x1,x2),max(x1,x2)+1));
		}
		for(auto &it:mv)MergeSegments(it.second);
		for(auto &it:mh)MergeSegments(it.second);
		printf("%I64d\n",Solve(mv,mh));
	}
	return 0;
}
