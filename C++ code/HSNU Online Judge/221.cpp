#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
struct Strategy
{
	int x0,y0,x1,y1,val;
	void Scanf(vector<LL>&x,vector<LL>&y,vector<LL>&v)
	{
		scanf("%d%d%d%d%d",&x0,&y0,&x1,&y1,&val),x0--,y0--;
		x.push_back(x0),x.push_back(x1);
		y.push_back(y0),y.push_back(y1);
		v.push_back(val);
	}
};
void Unique(vector<LL>&s){sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());}
void Idize(int &v,const vector<LL>&vs){v=lower_bound(vs.begin(),vs.end(),v)-vs.begin();}
vector<Strategy>S;
int K;
int X0,Y0;
vector<LL>XS,YS,VS;
void ReIndex()
{
	Unique(XS),Unique(YS),Unique(VS);
	Idize(X0,XS),Idize(Y0,YS);
	for(Strategy &s:S)Idize(s.x0,XS),Idize(s.x1,XS),Idize(s.y0,YS),Idize(s.y1,YS),Idize(s.val,VS);
}
struct Pq
{
	int y,x,val;
	Pq(){}
	Pq(const int _y,const int _x,const int _v):y(_y),x(_x),val(_v){}
	bool operator<(const Pq &p)const
	{
		if(val!=p.val)return val>p.val;
		if(y!=p.y)return y<p.y;
		return x<p.x;
	}
};
LL Solve()
{
	vector<vector<bool> >vis;
	vis.clear(),vis.resize((int)YS.size()-1);
	for(auto &v:vis)v.resize((int)XS.size()-1,false);
	set<Pq>pq;
	pq.insert(Pq(Y0,X0,0));
	LL ans=0LL;
	while(!pq.empty())
	{
		const Pq p=*pq.begin();pq.erase(pq.begin());
		if(vis[p.y][p.x])continue;
		vis[p.y][p.x]=true;
//		printf("(%lld,%lld)(%lld,%lld),val=%lld\n",XS[p.x],YS[p.y],XS[p.x+1],YS[p.y+1],p.val);
		(ans+=VS[p.val]*(YS[p.y+1]-YS[p.y])*(XS[p.x+1]-XS[p.x]))%=MOD;
		for(const Strategy &s:S)if(s.y0<=p.y&&p.y<s.y1&&s.x0<=p.x&&p.x<s.x1)
		{
			for(int y=s.y0;y<s.y1;y++)for(int x=s.x0;x<s.x1;x++)pq.insert(Pq(y,x,s.val));
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		{int n,m;scanf("%d%d%d",&n,&m,&K);}
		XS.clear(),YS.clear(),VS.clear(),S.clear();
		scanf("%d%d",&X0,&Y0);
		XS.push_back(X0),XS.push_back(--X0),YS.push_back(Y0),YS.push_back(--Y0),VS.push_back(0);
		for(int i=0;i<K;i++)
		{
			static Strategy s;
			s.Scanf(XS,YS,VS);
			S.push_back(s);
		}
		ReIndex();
		printf("%lld\n",Solve());
	}
	return 0;
}
