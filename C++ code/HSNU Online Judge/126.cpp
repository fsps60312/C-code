#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct Bit
{
	int s[1000001],n;
	void clear(const int _n){n=_n;for(int i=1;i<=n;i++)s[i]=0;}
	void Add(int i,const int v){while(i<=n)s[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=s[i],i-=(i&(-i));return ans;}
}BIT;
int N,CUR[26];
char A[1000001],B[1000001];
vector<int>LOC[26];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(3,"%d%s%s",&N,A,B);
	for(int i=0;i<26;i++)LOC[i].clear(),CUR[i]=0;
	BIT.clear(N);
	for(int i=0;i<N;i++)LOC[A[i]-'A'].push_back(i+1),BIT.Add(i+1,1);
	long long ans=0LL;
	for(int i=0;i<N;i++)
	{
		const int alpha=B[i]-'A';
		const int loc=LOC[alpha][CUR[alpha]++];
		BIT.Add(loc,-1);
		ans+=BIT.Query(loc);
	}
	printf("%lld\n",ans);
	return 0;
}
