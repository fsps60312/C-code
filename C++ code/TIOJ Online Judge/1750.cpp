#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<cassert>
using namespace std;
int T,N;
vector<string>W[7];
int LOC[1000][26];
bool USED[26];
bool Dfs(const int len,const int failed,const int success,const vector<int>&remain)
{
	if(remain.empty())return false;
	if(failed>len)return true;
	if(success==len)return false;
	for(int c=0;c<26;c++)
	{
		if(USED[c])continue;
		vector<int>nxt[len+1];
		for(int i=0;i<remain.size();i++)nxt[LOC[remain[i]][c]].push_back(remain[i]);
		if(nxt[len].size()==remain.size())continue;
		USED[c]=true;
		bool win=false;
		for(int i=0;i<len;i++)if(win|=Dfs(len,failed,success+1,nxt[i]))break;
		if(!win)win|=Dfs(len,failed+1,success,nxt[len]);
		USED[c]=false;
		if(!win)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int c=0;c<26;c++)USED[c]=false;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<7;i++)W[i].clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[7];
			scanf("%s",tmp);
			W[strlen(tmp)].push_back(tmp);
		}
		bool ans=false;
		for(int len=1;len<7;len++)
		{
			vector<int>remain;
			for(int i=0;i<W[len].size();i++)
			{
				remain.push_back(i);
				for(int c=0;c<26;c++)LOC[i][c]=len;
				for(int j=0;j<len;j++)LOC[i][W[len][i][j]-'A']=j;
			}
			if(ans|=Dfs(len,0,0,remain))break;
		}
		puts(ans?"Yes":"No");
		for(int i=0;i<26;i++)assert(!USED[i]);
	}
	return 0;
}
