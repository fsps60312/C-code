#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
using namespace std;
int K;
int main()
{
//	freopen("in.txt","r",stdin);
	vector<string>ans;ans.push_back("*");
	for(K=1;K<=9;K++)
	{
		assert((int)ans.size()==1<<(K-1));
		for(int i=0;i<(1<<(K-1));i++)
		{
			const string &s=ans[i];
			string t;
			for(int j=0;j<(1<<(K-1));j++)
			{
				const char c=s[j/((1<<(K-1))/(int)s.size())];
				t+=(c=='*'?"*+":"+*");
			}
			ans.push_back(t);
		}
	}
	while(scanf("%d",&K)==1)
	{
		for(int i=0;i<(1<<K);i++)
		{
			for(int j=0;j<(1<<K);j++)
			{
				putchar(ans[i][j/((1<<K)/(int)ans[i].size())]);
			}
			puts("");
		}
	}
	return 0;
}
