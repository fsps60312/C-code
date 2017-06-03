#include<cstdio>
#include<cassert>
#include<set>
#include<map>
using namespace std;
set<char>DP[201][201][201];
int N;
void Merge(set<char>&a,const set<char>&b){for(const char v:b)a.insert(v);}
set<char>GetDP(const int a,const int b,const int c)
{
	set<char>&ans=DP[a][b][c];
	if(!ans.empty())return ans;
	if(a>=2)Merge(ans,GetDP(a-1,b,c));
	if(b>=2)Merge(ans,GetDP(a,b-1,c));
	if(c>=2)Merge(ans,GetDP(a,b,c-1));
	if(a&&b)Merge(ans,GetDP(a-1,b-1,c+1));
	if(a&&c)Merge(ans,GetDP(a-1,b+1,c-1));
	if(b&&c)Merge(ans,GetDP(a+1,b-1,c-1));
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	DP[1][0][0].insert('B');
	DP[0][1][0].insert('G');
	DP[0][0][1].insert('R');
	while(scanf("%d",&N)==1)
	{
		static char str[201];
		scanf("%s",str);
		map<char,int>cnt;
		for(int i=0;i<N;i++)cnt[str[i]]++;
		const set<char>&s=GetDP(cnt['B'],cnt['G'],cnt['R']);
		for(const char c:s)putchar(c);puts("");
	}
	return 0;
}
