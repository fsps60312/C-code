#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
int N;
struct Segment
{
	int a,b1,b2;
	Segment(){}
	Segment(const int _a,const int _b1,const int _b2):a(_a),b1(_b1),b2(_b2){}
	bool operator<(const Segment &s)const{return a<s.a;}
};
LL Classify(const int a,const vector<pair<int,int> >&s,vector<Segment>&inc,vector<Segment>&exc)
{
	map<int,int>change;
	for(const auto &p:s)change[p.first]++,change[p.second]--;
	for(auto it=change.begin();it!=change.end();)
	{
		if(it->second==0)
		{
			auto tmp=it++;
			change.erase(tmp);
		}
		else it++;
	}
	auto it=change.begin();
	int now=(it++)->second;
	LL ans=0LL;
	for(;it!=change.end();it++)
	{
		assert(now>=0);
		const int l=((--it)++)->first;
		const int r=it->first;
		if(now==1)inc.push_back(Segment(a,l,r));
		else if(now>1)ans+=r-l,exc.push_back(Segment(a,l,r));
		now+=it->second;
	}
	assert(now==0);
	return ans;
}
LL Classify(const map<int,vector<pair<int,int> > >&m,vector<Segment>&inc,vector<Segment>&exc)
{
	LL ans=0LL;
	for(const auto &it:m)ans+=Classify(it.first,it.second,inc,exc);
	return ans;
}
struct Bit
{
	int s[400001],cnt[400001],n;
	void clear(const int _n){n=_n;for(int i=1;i<n;i++)s[i]=cnt[i]=0;}
	void Add(int i,const int v)
	{
		assert(++i<n&&v!=0);
		if(v>0){if(cnt[i]++)return;}
		else{if(--cnt[i])return;}
		while(i<n)s[i]+=v,i+=(i&(-i));
	}
	int Query(int i)
	{
//		printf("(%d,%d)\n",i,n);
		assert(++i<n);
		int a=0;
		while(i)a+=s[i],i-=(i&(-i));
		return a;
	}
}BIT;
int Id(const vector<int>&y,const int val)
{
	const int ans=lower_bound(y.begin(),y.end(),val)-y.begin();
	assert(y[ans]==val);
	return ans;
}
LL Solve(const vector<Segment>&vert,const vector<Segment>&hori)
{
	if(vert.empty()||hori.empty())return 0LL;
	vector<int>y;
	for(const Segment &seg:hori)y.push_back(seg.a),y.push_back(seg.a+1);
	for(const Segment &seg:vert)y.push_back(seg.b1),y.push_back(seg.b2);
	sort(y.begin(),y.end()),y.resize(unique(y.begin(),y.end())-y.begin());
	map<int,map<int,int> >change;
	for(const Segment &seg:hori)change[seg.b1][Id(y,seg.a)]++,change[seg.b2][Id(y,seg.a)]--;
	auto it=change.begin();
	BIT.clear(y.size());
//	printf("y.size()=%d\n",(int)y.size());
	LL ans=0LL;
	for(const Segment &seg:vert)
	{
		for(;it!=change.end()&&(it->first)<=seg.a;it++)
		{
			for(const auto iu:it->second)if(iu.second)BIT.Add(iu.first,iu.second);
		}
		ans+=BIT.Query(Id(y,seg.b2)-1)-BIT.Query(Id(y,seg.b1)-1);
	}
	for(;it!=change.end();it++)
	{
		for(const auto iu:it->second)if(iu.second)BIT.Add(iu.first,iu.second);
	}
	assert(BIT.Query((int)y.size()-2)==0);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		map<int,vector<pair<int,int> > >mv,mh;
		for(int i=0,x1,y1,x2,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x1==x2)mv[x1].push_back(make_pair(min(y1,y2),max(y1,y2)+1));
			else assert(y1==y2),mh[y1].push_back(make_pair(min(x1,x2),max(x1,x2)+1));
		}
		vector<Segment>include_vert,include_hori,exclude_vert,exclude_hori;
		LL ans=0LL;
		ans+=Classify(mv,include_vert,exclude_vert);
		printf("ans1=%d\n",ans);
		ans+=Classify(mh,include_hori,exclude_hori);
		printf("ans2=%d\n",ans);
		ans+=Solve(include_vert,include_hori);
		printf("ans3=%d\n",ans);
		ans-=Solve(exclude_vert,exclude_hori);
		printf("%lld\n",ans);
	}
	return 0;
}
