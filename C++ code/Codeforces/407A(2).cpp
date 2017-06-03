#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<cmath>
using namespace std;
int Gcd(const int a,const int b){return b==0?a:Gcd(b,a%b);}
void Dissolve(const int c,vector<pair<int,int> >&output)
{
	output.clear();
	for(int a=1;a<c;a++)
	{
		const int b=sqrt(c*c-a*a)+0.5;
		if(a*a+b*b==c*c)output.push_back(make_pair(a,b));
	}
}
int A,B;
bool Solve(vector<pair<int,int> >&ans)
{
	const int g=Gcd(A,B);
	vector<pair<int,int> >ps;
	Dissolve(g,ps);
//	printf("g=%d,ps.size()=%d\n",g,(int)ps.size());
	if(ps.empty())return false;
	auto p=ps[0];
	if(A==B&&p.first==p.second)return false;
	if(A/g*p.first==B/g*p.second)swap(p.first,p.second);
	assert(A/g*p.first!=B/g*p.second);
	ans.push_back(make_pair(0,0));
	ans.push_back(make_pair(A/g*p.first,A/g*p.second));
	ans.push_back(make_pair(B/g*p.second,-B/g*p.first));
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
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
