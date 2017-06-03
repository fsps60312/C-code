#include<cstdio>
#include<set>
#include<queue>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
inline void getmax(int &a,const int b){if(b>a)a=b;}
int T,N;
vector<char>S;
vector<int>DP;
struct Pair
{
	int l,r;
	Pair(){}
	Pair(const int _l,const int _r):l(_l),r(_r){}
};
bool CmpR(const Pair &a,const Pair &b){return a.r!=b.r?a.r<b.r:a.l>b.l;}
vector<Pair>LINE;
struct Bit
{
	int mx[300002],n;
	inline void clear(const int _n){n=_n;for(int i=0;i<=n;i++)mx[i]=-1;}
	inline int lowbit(const int v){return v&(-v);}
	inline void Update(int i,const int v){while(i<=n)getmax(mx[i],v),i+=lowbit(i);}
	inline int Query(int i){int ans=-1;while(i)getmax(ans,mx[i]),i-=lowbit(i);return ans;}
}BIT;
//#include<ctime>
inline int Solve()
{
	DP[0]=1;
	for(int i=1,mx=0;i<N;i++)
	{
		int &dp=DP[i];
		if(mx+DP[mx]-1>i)dp=min(DP[mx-(i-mx)],mx+DP[mx]-i);
		else dp=1;
		while(i-dp>=0&&i+dp<N&&S[i-dp]==S[i+dp])dp++;
	}
	LINE.clear();
	for(int i=0;i<N;i+=2)if(DP[i]>1)
	{
		const Pair p=Pair((i-DP[i]+1)/2+1,(i+DP[i]-1)/2+1);
		LINE.push_back(p);
	}
	sort(LINE.begin(),LINE.end(),CmpR);
	assert((N-1)/2+1<300002);
	BIT.clear((N-1)/2+1);
	int ans=0;
	for(const auto &line:LINE)
	{
		const int v=BIT.Query((line.l+line.r)/2)-(line.l+line.r)/2;
		getmax(ans,v);
		BIT.Update(line.l,(line.l+line.r)/2);
	}
	sort(LINE.begin(),LINE.end(),CmpR);
	return ans*4;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[300002];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
//	auto start=clock();
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
//	printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}
