#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
void BuildKMP(const char *str,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1;str[i];i++)
	{
		int &f=fail[i+1]=fail[i];
		while(f&&str[f]!=str[i])f=fail[f];
		if(str[f]==str[i])++f;
	}
}
int FAIL[2101];
pair<int,int>Match(const char *a,const char *b)
{
	BuildKMP(b,FAIL);
	int u=0;
	pair<int,int>ans=make_pair(-1,-1);
	int i=0;
	for(;a[i];i++)
	{
		while(u&&b[u]!=a[i])u=FAIL[u];
		if(b[u]==a[i])++u;
		if(u>=abs(ans.second-ans.first)+1)ans=make_pair(i-u+1,i);
	}
	--i,u=0;
	for(;i>=0;i--)
	{
		while(u&&b[u]!=a[i])u=FAIL[u];
		if(b[u]==a[i])++u;
		if(u>=abs(ans.second-ans.first)+1)ans=make_pair(i+u-1,i);
	}
	return ans;
}
int N,M;
char A[2101],B[2101];
vector<pair<int,int> >Solve()
{
	vector<pair<int,int> >ans;
	for(int cur=0;B[cur];)
	{
		const auto &p=Match(A,B+cur);
		if(p.first==-1)
		{
			ans.clear();
			return ans;
		}
		ans.push_back(p);
		cur+=abs(p.first-p.second)+1;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s%s",A,B)==2)
	{
		const vector<pair<int,int> >&ans=Solve();
		if(ans.empty())puts("-1");
		else
		{
			printf("%d\n",(int)ans.size());
			for(const auto &p:ans)printf("%d %d\n",p.first+1,p.second+1);
		}
	}
	return 0;
}
