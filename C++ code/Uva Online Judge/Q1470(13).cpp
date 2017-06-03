#include<cstdio>
#include<set>
#include<queue>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int T,N;
vector<char>S;
vector<int>DP;
struct Pair
{
	int l,r;
	Pair(){}
	Pair(const int _l,const int _r):l(_l),r(_r){}
};
struct CmpR{bool operator()(const Pair &a,const Pair &b)const{return a.r!=b.r?a.r<b.r:a.l>b.l;}};
vector<Pair>LINE;
struct Seg
{
	int mx[2400000];
	void Build(const int id,const int l,const int r)
	{
		mx[id]=-1;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Modify(const int id,const int l,const int r,const int loc,const int v)
	{
		if(l==r){getmax(mx[id],v);return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,v);
		else Modify(id*2+1,mid+1,r,loc,v);
		mx[id]=max(mx[id*2],mx[id*2+1]);
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return -INF;
		if(bl<=l&&r<=br)return mx[id];
		const int mid=(l+r)/2;
		return max(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
}SEG;
int Solve()
{
	DP[0]=1;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+DP[mx]-1>i)DP[i]=min(DP[mx-(i-mx)],mx+DP[mx]-1-i+1);
		else DP[i]=1;
		while(i-DP[i]>=0&&i+DP[i]<N&&S[i-DP[i]]==S[i+DP[i]])DP[i]++;
	}
	LINE.clear();
	for(int i=0;i<N;i+=2)if(DP[i]>1)
	{
		const Pair p=Pair(i-DP[i]+1,i+DP[i]-1);
		LINE.push_back(p);
	}
	sort(LINE.begin(),LINE.end(),CmpR());
	SEG.Build(1,0,N-1);
	int ans=0;
	for(const auto &line:LINE)
	{
		const int v=SEG.Query(1,0,N-1,0,(line.l+line.r)/2)-(line.l+line.r)/2;
		getmax(ans,v);
		SEG.Modify(1,0,N-1,line.l,(line.l+line.r)/2);
	}
	return ans*2;
}
#include<ctime>
int main()
{
	freopen("in.txt","r",stdin);
	static char tmp[300002];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
	auto start=clock();
	for(int i=0;i<1000000000;i++);
	printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	start=clock();
	while(T--)
	{
		assert(fgets(tmp,INF,stdin));
		S.clear(),S.push_back('\0');
		N=-1;
		while(tmp[++N])
		{
			if(tmp[N]=='\n')break;
			S.push_back(tmp[N]),S.push_back('\0');
		}
		N=S.size();
		DP.resize(N);
		printf("%d\n",Solve());
	}
	printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}
