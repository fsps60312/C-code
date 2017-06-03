#include<stdio.h>
#include<map>
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
}LINE[300001];
bool CmpR(const Pair &a,const Pair &b){return a.r!=b.r?a.r<b.r:a.l>b.l;}
struct Bit
{
	int mx[300002],n;
	inline void clear(const int _n){n=_n;for(int i=0;i<=n;i++)mx[i]=-1;}
	inline void Update(int i,const int v){while(i<=n)getmax(mx[i],v),i+=(i&(-i));}
	inline int Query(int i){if(i>n)i=n;int ans=-1;while(i)getmax(ans,mx[i]),i-=(i&(-i));return ans;}
}BIT;
inline int Solve()
{
	DP[0]=1;
	for(int i=2,mx=0;i<N;i+=2)
	{
		int &dp=DP[i];
		if(mx+DP[mx]-1>i)dp=min(DP[mx-(i-mx)],mx+DP[mx]-i);
		else dp=1;
		while(i-dp>=0&&i+dp<N&&S[i-dp]==S[i+dp])dp+=2;
	}
	int line_sz=0;
	map<int,int>idx;
	for(int i=0,l,r;i<N;i+=2)if(DP[i]>=3)
	{
		l=(i-DP[i]+1)/2+1,r=(i+DP[i]-1)/2+1;
		LINE[line_sz++]=Pair(l,r);
		idx[l]=-1;
	}
	sort(LINE,LINE+line_sz,CmpR);
//	printf("line_sz=%d\n",line_sz);
	int cnt=0;
	for(auto &it:idx)it.second=++cnt;
	BIT.clear(cnt);
	int ans=0;
	for(int i=0;i<line_sz;i++)
	{
		const Pair &line=LINE[i];
		const int mid=(line.l+line.r)/2;
		if(DP[(mid-1)*2]>=5)
		{
			auto it=idx.upper_bound(mid);
			if(it!=idx.begin())getmax(ans,BIT.Query((--it)->second)-mid);
		}
		BIT.Update(idx[line.l],mid);
	}
	return ans*4;
}
inline void GetS()
{
	char c=getchar();
	N=0;
	while(c!='\n'&&c!='\0')S[++N]=c,++N,c=getchar();
}
int main()
{
	freopen("in.txt","r",stdin);
	static char tmp[100];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
//	printf("T=%d\n",T);
	auto start=clock();
	while(T--)
	{
		GetS();
		printf("%d\n",Solve());
//		assert(T>=20);
	}
//	printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}
