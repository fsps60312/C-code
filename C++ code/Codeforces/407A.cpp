#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<cmath>
using namespace std;
int A,B;
void Dissolve(const int c,vector<pair<int,int> >&output)
{
	output.clear();
	for(int a=1;a<c;a++)
	{
		const int b=sqrt(c*c-a*a)+0.5;
		if(a*a+b*b==c)output.push_back(make_pair(a,b));
	}
}
bool Solve(vector<pair<int,int> >&ans)
{
	vector<pair<int,int> >sa,sb;
	Dissolve(A,sa),Dissolve(B,sb);
	int d[3][2]={{0,0},{0,1},{1,0}};
	for(int i=0;i<3;i++)
	{
		const int a=d[i][0],b=d[i][1];
		if(a<(int)sa.size()&&b<(int)sb.size()&&sa[a].first!=sb[b].first)
		{
			ans.push_back(make_pair(0,0));
			ans.push_back(make_pair(sa[a].first,sa[a].second));
			ans.push_back(make_pair(sb[b].first,-sb[b].second));
		}
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&A,&B)==2)
	{
		vector<pair<int,int> >ans;
		if(!Solve(ans))puts("NO");
		else
		{
			puts("YES");
			for(const auto &p:ans)printf("%d %d\n",p.first,p.second);
		}
	}
	return 0;
}
