#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
#include<functional>
using namespace std;
void bssert(bool valid){if(!valid)for(;;);}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
const int MAX_N=10000,INF=2147483647;
int N;
vector<int>ET[MAX_N];
namespace QDist
{
	int DEPTH[MAX_N];
	vector<int>PA[MAX_N];
	void Dfs(const int u,const int pa,const int depth)
	{
		DEPTH[u]=depth;
		PA[u].clear();
		if(pa!=-1)
		{
			for(int cur=pa,i=0;;cur=PA[cur][i++])
			{
				PA[u].push_back(cur);
				if(i>=(int)PA[cur].size())break;
			}
		}
		for(const int nxt:ET[u])if(nxt!=pa)Dfs(nxt,u,depth+1);
	}
	void Build()
	{
		Dfs(0,-1,0);
	}
	int GetLCA(int a,int b)
	{
		if(DEPTH[a]<DEPTH[b])swap(a,b);
		bssert(DEPTH[a]>=DEPTH[b]);
		for(int dis=DEPTH[a]-DEPTH[b],i=0;(1<<i)<=dis;i++)if(dis&(1<<i))a=PA[a][i];
		bssert(DEPTH[a]==DEPTH[b]);
		if(a==b)return a;
		for(int i=30;i>=0;i--)if(i<(int)PA[a].size()&&PA[a][i]!=PA[b][i])a=PA[a][i],b=PA[b][i];
		bssert(a!=b&&PA[a][0]==PA[b][0]);
		return PA[a][0];
	}
	int Get(const int a,const int b){return DEPTH[a]+DEPTH[b]-2*DEPTH[GetLCA(a,b)];}
}
class Color
{
	vector<int>VR,VC,VT;
  public:
	void clear(const int time_stamp)
	{
		VR.clear(),VC.clear(),VT.clear();
		push_back(INF,1,time_stamp);
	}
	void push_back(const int r,const int c,const int t)
	{
		VR.push_back(r),VC.push_back(c),VT.push_back(t);
	}
	void pop_back()
	{
		VR.pop_back(),VC.pop_back(),VT.pop_back();
	}
	void Cover(const int r,const int c,const int t)
	{
		while(!VR.empty()&&VR.back()<=r)pop_back();
		assert(!VR.empty());
		push_back(r,c,t);
	}
	pair<int,int>Get(const int r)const
	{
		const auto &i=upper_bound(VR.begin(),VR.end(),r,greater<int>())-VR.begin()-1;
		assert(0<=i&&i<(int)VR.size()&&(i+1==(int)VR.size()||VR[i+1]<r)&&r<=VR[i]);
		return make_pair(VT[i],VC[i]);
	}
};
namespace CD
{
	bool VIS[MAX_N];
	int PA[MAX_N];
	int DfsCD(const int u,const int pa,int &ansu,int &ansn,const int n)
	{
		if(VIS[u])return 0;
		int sz=1;
		int mxsz=0;
		for(const int nxt:ET[u])if(nxt!=pa)
		{
			const int chsz=DfsCD(nxt,u,ansu,ansn,n);
			sz+=chsz;
			getmax(mxsz,chsz);
		}
		getmax(mxsz,n-sz);
		if(n>0&&mxsz<ansn)ansn=mxsz,ansu=u;
		return sz;
	}
	int GetCD(const int u)
	{
		int ansu=-1,ansn=INF;
		const int n=DfsCD(u,-1,ansu,ansn,0);
		bssert(n>0&&n==DfsCD(u,-1,ansu,ansn,n));
		bssert(ansu!=-1&&ansn*2<=n);
		return ansu;
	}
	void DfsBuild(const int u,const int pa)
	{
		bssert(!VIS[u]);
		VIS[u]=true;
		PA[u]=pa;
		for(const int nxt:ET[u])if(!VIS[nxt])DfsBuild(GetCD(nxt),u);
	}
	static int time_stamp;
	vector<Color>COLOR;
	void Build()
	{
		time_stamp=0;
		COLOR.resize(N);
		for(int i=0;i<N;i++)VIS[i]=false,COLOR[i].clear(time_stamp);
		DfsBuild(GetCD(0),-1);
		QDist::Build();
	}
	void Draw(const int u,const int c,const int r)
	{
		++time_stamp;
		for(int cur=u;cur!=-1;cur=PA[cur])
		{
			COLOR[cur].Cover(r-QDist::Get(cur,u),c,time_stamp);
		}
	}
	int GetColor(const int u)
	{
		auto ans=make_pair(-1,-1);
		for(int cur=u;cur!=-1;cur=PA[cur])
		{
			getmax(ans,COLOR[cur].Get(QDist::Get(cur,u)));
		}
		assert(ans.first!=-1);
//		printf("u=%d, find (%d,%d)\n",u,ans.first,ans.second);
		return ans.second;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;
		scanf("%d%d",&N,&querycount);
		bssert(1<=N&&N<=MAX_N&&1<=querycount&&querycount<=10000);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			bssert(0<=a&&a<N&&0<=b&&b<N);
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		CD::Build();
		for(int type,s,d,x;querycount--;)
		{
			scanf("%d",&type);
			switch(type)
			{
				case 1:
				{
					scanf("%d%d%d",&s,&d,&x),--s;
					bssert(0<=s&&s<N);
					CD::Draw(s,x,d);
				}break;
				case 2:
				{
					scanf("%d",&s),--s;
					bssert(0<=s&&s<N);
					printf("%d\n",CD::GetColor(s));
				}break;
				default:assert(0);break;
			}
		}
	}
	return 0;
}
