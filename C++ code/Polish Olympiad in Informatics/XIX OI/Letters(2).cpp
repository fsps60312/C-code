#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
struct Bit
{
	int DATA[1000001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)DATA[i]=0;}
	void Add(int i){i++;while(i<=N)DATA[i]++,i+=(i&(-i));}
	int Query(int i){i++;int ans=0;while(i)ans+=DATA[i],i-=(i&(-i));return ans;}
}BIT;
int N;
char A[1000001],B[1000001];
int S[1000000];
void BuildS()
{
	vector<int>locs[26];
	for(int i=0;i<26;i++)locs[i].clear();
	for(int i=N-1;i>=0;i--)locs[A[i]-'A'].push_back(i);
	long long ans=0;
	for(int i=0;i<N;i++)ans+=S[locs[B[i]-'A'].back()]=i,locs[B[i]-'A'].pop_back();
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	scanf("%s%s",A,B);
	BuildS();
	BIT.Clear(N);
	long long ans=0;
	for(int i=N-1;i>=0;i--)
	{
		ans+=BIT.Query(S[i]);
		BIT.Add(S[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
