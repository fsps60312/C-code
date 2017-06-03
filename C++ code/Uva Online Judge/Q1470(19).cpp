#include<cstdio>
#include<vector>
#include<cassert>
#include<ctime>
#include<algorithm>
using namespace std;
const int INF=2147483647;
inline void getmax(int &a,const int b){if(b>a)a=b;}
inline void getmin(int &a,const int b){if(b<a)a=b;}
int T,N;
char S[600001];
int DP[600001];
struct Pair
{
	int l,r;
	Pair(){}
	Pair(const int _l,const int _r):l(_l),r(_r){}
	int M2()const{return (l+r)/2;}
	int M3()const{return (l+r*3)/4;}
	int Length()const{return (r-l)/2;}
};
struct Bit
{
	int mx[300002],n;
	inline void clear(const int _n){n=_n;assert(n<=300001);for(int i=0;i<=n;i++)mx[i]=-1;}
	inline void Update(int i,const int v){assert(i>0&&i<=n&&"U");while(i<=n)getmax(mx[i],v),i+=(i&(-i));}
	inline int Query(int i){assert(i>0&&i<=n&&"Q");int ans=-1;while(i)getmax(ans,mx[i]),i-=(i&(-i));return ans;}
}BIT;
vector<Pair>SMALL,LARGE;
bool CmpM2(const Pair &a,const Pair &b){return a.M2()<b.M2();}
bool CmpM3(const Pair &a,const Pair &b){return a.M3()<b.M3();}
inline int Solve()
{
	DP[0]=1;
	for(int i=1,mx=0;i<N;i++)
	{
		int &dp=DP[i];
		if(mx+DP[mx]-1>=i)dp=min(DP[mx-(i-mx)],mx+DP[mx]-i);
		else dp=1;
		while(i-dp>=0&&i+dp<N&&S[i-dp]==S[i+dp])dp++;
		if(i+dp>mx+DP[mx])mx=i;
	}
//	for(int i=0;i<N;i++)printf(" %d",DP[i]);puts("");
	SMALL.clear(),LARGE.clear();
	for(int i=0,l,r;i<N;i+=2)
	{
		assert(DP[i]&1);
		l=(i-DP[i]+1)/2+1,r=(i+DP[i]-1)/2+1;
		if(l<r)
		{
			assert((r-l)%2==0);
			SMALL.push_back(Pair(l,r));
			LARGE.push_back(Pair(l,r));
		}
	}
	sort(SMALL.begin(),SMALL.end(),CmpM2);
	sort(LARGE.begin(),LARGE.end(),CmpM3);
//	for(const auto v:LARGE)printf("(%d,%d,%d)\n",v.l,(v.l+v.r)/2,v.r);
	BIT.clear(N+1);
	int ans=0;
	for(int i=0,j=0;i<LARGE.size();i++)
	{
		for(;j<SMALL.size()&&SMALL[j].M2()<=LARGE[i].M3();j++)BIT.Update(SMALL[j].l,SMALL[j].M2());
//		printf("%d\n",LARGE[i].Length()/2);
		getmax(ans,BIT.Query(LARGE[i].M2())-LARGE[i].M2());
	}
	return ans*4;
}
inline void GetS()
{
	char c=getchar();
	N=-1;
	S[++N]='\0';
	while(c!='\n'&&c!='\0')S[++N]=c,S[++N]='\0',c=getchar();
	N++;
	assert(N<=600001);
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[100];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
//	printf("T=%d\n",T);
//	auto start=clock();
	while(T--)
	{
		GetS();
		printf("%d\n",Solve());
//		assert(T>=20);
	}
//	printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}
/*
1
AAaAaaAaaAaaAaAaaAaAaAaAaaAaaaAaAaAaaAaAAAAaaAAAaAaaAAAaaAaaAAaAAaaAaaAaaaAAaaaaAaaAAaAaAaaAaaaAAaAA
*/
