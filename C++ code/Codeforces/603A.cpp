#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
int N;
char B[100001];
int Solve()
{
	vector<pair<char,int> >s;
	for(int i=0;i<N;i++)
	{
		if(s.empty()||s.back().first!=B[i])s.push_back(make_pair(B[i],1));
		else ++s.back().second;
	}
	int cnt2=0;
	for(const auto &p:s)
	{
		if(p.second>=3)return (int)s.size()+2;
		else if(p.second==2)++cnt2;
	}
	if(cnt2>=2)return (int)s.size()+2;
	else if(cnt2==1)return (int)s.size()+1;
	else return (int)s.size();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,B)==2)
	{
		printf("%d\n",Solve());
	}
	return 0;
}
