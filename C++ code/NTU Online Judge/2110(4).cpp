#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
const int INF=2147483647;
//void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(a<b)a=b;}
struct Bit
{
	int S[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Update(int i,const int val){for(++i;i<=N;i+=(i&(-i)))getmax(S[i],val);}
	int Query(int i){int ans=0;for(++i;i;i-=(i&(-i)))getmax(ans,S[i]);return ans;}
}BIT;
int N,A[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)A[i]=(i+1)-A[i];
		map<int,vector<int> >s;
		for(int i=0;i<N;i++)if(0<=A[i]&&A[i]<=i)s[i-A[i]].push_back(i);
		//j-A[j]<i-A[i]<=i-A[j]
		//A[j]<=A[i]
		//j<i
		static int ans[100000];
		for(int i=0;i<N;i++)ans[i]=0;
		BIT.Clear(N);
		for(const auto &p:s)
		{
			for(const int v:p.second)getmax(ans[v],BIT.Query(A[v])+1);
			for(const int v:p.second)BIT.Update(A[v],ans[v]);
		}
		int res=0;
		for(int i=0;i<N;i++)getmax(res,ans[i]);
		printf("%d\n",res);
	}
	return 0;
}
