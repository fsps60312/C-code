#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,Q;
int A[1000001];
LL _SUM[1000001];
inline LL Sum(const int id)
{
	if(id<=N)return _SUM[id];
	else if(id<=N*2)return _SUM[N]+_SUM[id-N];
	else if(id<=N*3)return _SUM[N]*2LL+_SUM[id-N*2];
	else assert(0);
	return -1LL;
}
int Solve(const LL d)
{
	vector<int>s;
	s.push_back(0);
	while(s.back()<N)
	{
		const int preb=s.back();
		s.push_back(preb);
		while(Sum(s.back()+1)-Sum(preb)<=d)++s.back();
	}
	assert((int)s.size()>=2);
	int ans=(int)s.size()-1;
	for(int limit=s[1];s[0]<=limit;++s[0])
	{
		for(int i=1;i<(int)s.size();i++)
		{
			if(Sum(s[i]+1)-Sum(s[i-1])<=d)
			{
				while(Sum(s[i]+1)-Sum(s[i-1])<=d)++s[i];
			}
			else break;
		}
		while(s.back()<N+s[0])
		{
			const int preb=s.back();
			s.push_back(preb+1);
			while(Sum(s.back()+1)-Sum(preb)<=d)++s.back();
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
		_SUM[0]=0LL;
		for(int i=1;i<=N;i++)_SUM[i]=_SUM[i-1]+A[i];
		for(LL d;Q--;)
		{
			scanf("%lld",&d);
			if(d<mx)puts("NIE");
			else if(d>=_SUM[N])puts("1");
			else printf("%d\n",Solve(d));
		}
	}
	return 0;
}
