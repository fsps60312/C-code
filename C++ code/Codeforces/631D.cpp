#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
void Read(vector<pair<char,LL> >&s,const int len)
{
	s.clear();
	for(int i=0;i<len;i++)
	{
		int l;char c;
		scanf("%d-%c",&l,&c);
		const int n=s.size();
		if(n==0||s[n-1].first!=c)s.push_back(make_pair(c,l));
		else s[n-1].second+=l;
	}
}
void BuildFail(const vector<pair<char,LL> >&s,vector<int>&fail)
{
	fail.clear(),fail.resize(3,1);
	for(int i=2;i+1<(int)s.size();i++)
	{
		int f=fail[i];
		while(f>1&&s[f]!=s[i])f=fail[f];
		if(s[f]==s[i])f++;
		fail.push_back(f);
	}
}
vector<pair<char,LL> >A,B;
LL Solve3()
{
	assert((int)B.size()>=3);
	vector<int>fail;
	BuildFail(B,fail);
	int u=1;
	LL ans=0LL;
	for(int i=1;i+1<(int)A.size();i++)
	{
		while(u>1&&A[i]!=B[u])u=fail[u];
		if(A[i]==B[u])u++;
		if(u==(int)B.size()-1)
		{
			if(A[i+1].first==B[u].first&&A[i+1].second>=B[u].second)
			{
				const pair<char,LL>&pa=A[i+1-((int)B.size()-1)],&pb=B[0];
				if(pa.first==pb.first&&pa.second>=pb.second)ans++;
			}
			u=fail[u];
		}
	}
	return ans;
}
LL Solve2()
{
	assert((int)B.size()==2);
	LL ans=0LL;
	for(int i=1;i<(int)A.size();i++)
	{
		if(A[i-1].first==B[0].first&&A[i-1].second>=B[0].second)
		{
			if(A[i].first==B[1].first&&A[i].second>=B[1].second)
			{
				ans++;
			}
		}
	}
	return ans;
}
LL Solve1()
{
	assert((int)B.size()==1);
	LL ans=0LL;
	for(const auto &p:A)
	{
		if(p.first==B[0].first&&p.second>=B[0].second)
		{
			ans+=p.second-B[0].second+1LL;
		}
	}
	return ans;
}
LL Solve()
{
	switch(B.size())
	{
		case 1:return Solve1();
		case 2:return Solve2();
		default:return Solve3();
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int alen,blen;scanf("%d%d",&alen,&blen)==2;)
	{
		Read(A,alen);Read(B,blen);
		printf("%lld\n",Solve());
	}
	return 0;
}
