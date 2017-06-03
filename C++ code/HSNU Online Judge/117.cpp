#include<cstdio>
#include<cassert>
#include<set>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,S[24],SUM[1<<24];
set<int>DP[1<<24];
int LowBit(const int s){return s&(-s);}
set<int>&GetDP(const int s)
{
	set<int>&ans=DP[s];
	if(!ans.empty())return ans;
	const set<int>&a=GetDP(LowBit(s)),&b=GetDP(s-LowBit(s));
	for(const int v1:a)for(const int v2:b)ans.insert(v1+v2);
	return ans;
}
int GetSUM(const int s)
{
	int &sum=SUM[s];
	if(sum!=-1)return sum;
	return sum=GetSUM(LowBit(s))+GetSUM(s-LowBit(s));
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<(1<<N);i++)SUM[i]=-1,DP[i].clear();
	SUM[0]=0,DP[0].insert(0);
	for(int i=0;i<N;i++)scanf(1,"%d",&S[i]),DP[1<<i].insert(0),DP[1<<i].insert(S[i]),SUM[1<<i]=S[i];
	int ans=INF;
	const int all=(1<<N)-1;
	for(int s=0;s<(1<<N);s++)
	{
		const int sum1=GetSUM(s),sum2=GetSUM(all^s);
		const auto it=GetDP(s).lower_bound(sum1/2);
		const int a=sum1-(*it),b=sum1-a,c=sum2;
		getmin(ans,max(abs(a-b),max(abs(a-c),abs(b-c))));
	}
	printf("%d\n",ans);
	return 0;
}
