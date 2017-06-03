#include<cstdio>
#include<string>
#include<set>
using namespace std;
const int INF=2147483647;
static char S[101];
int N;
set<string>W[101];
string SubStr(const int a,const int len)
{
	string ans;
	for(int i=0;i<len;i++)ans.push_back(S[a+i]);
	return ans;
}
int Solve()
{
	N=0;while(S[N++])W[N].clear();N--;
	for(int i=0;i<N;i++)
	{
		for(int len=1;len<=i+1;len++)
		{
			for(int j=0;j+len-1<=i;j++)
			{
				W[len].insert(SubStr(j,len));
				if(W[len].size()>len+1)return i+1;
			}
		}
	}
	return INF;
}
int main()
{
	while(scanf("%s",S)==1)
	{
		int ans=Solve();
		if(ans==INF)puts("YES");
		else printf("NO:%d\n",ans);
	}
	return 0;
}
