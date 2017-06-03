#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,Q;
int A[1000001];
LL SUM[3000001];
int Solve(const LL d)
{
	vector<int>s;
	s.push_back(0);
	while(s.back()<N)
	{
		const int preb=s.back();
		s.push_back(preb);
		while(SUM[s.back()+1]-SUM[preb]<=d)++s.back();
	}
	assert((int)s.size()>=2);
	int ans=(int)s.size()-1;
	for(int limit=s[1];s[0]<=limit;++s[0])
	{
		for(int i=1;i<(int)s.size();i++)
		{
			if(SUM[s[i]+1]-SUM[s[i-1]]<=d)
			{
				while(SUM[s[i]+1]-SUM[s[i-1]]<=d)++s[i];
			}
			else break;
		}
		while(s.back()<N+s[0])
		{
			const int preb=s.back();
			s.push_back(preb+1);
			while(SUM[s.back()+1]-SUM[preb]<=d)++s.back();
		}
		while((int)s.size()>=2&&s[s.size()-2]>=N+s[0])s.pop_back();
		assert((int)s.size()>=2);
		ans=min(ans,(int)s.size()-1);
//		for(int i=0;i<(int)s.size();i++)printf("%d ",s[i]);puts("");
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		int mx=0;
		for(int i=1;i<=N;i++)scanf("%d",&A[i]),mx=max(mx,A[i]);
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+A[i];
		for(int i=1;i<=N;i++)SUM[N+i]=SUM[N+i-1]+A[i];
		for(int i=1;i<=N;i++)SUM[N+N+i]=SUM[N+N+i-1]+A[i];
		for(LL d;Q--;)
		{
			scanf("%lld",&d);
			if(d<mx)puts("NIE");
			else if(d>=SUM[N])puts("1");
			else printf("%d\n",Solve(d));
		}
	}
	return 0;
}
