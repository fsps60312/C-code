#include<cstdio>
#include<cassert>
using namespace std;
int R,C;
char S[4000][4001];
bool Dfs(const int r,const int c,const int d)
{
	if(r==-1)return false;
	if(c==-1||c==C)return false;
	if(d==0)
	{
		if(r==R-1)return true;
		if(S[r+1][c]=='/')
		{
			if(c-1>=0)
			{
				if(S[r+1][c-1]=='/')return Dfs(r+1,c-1,0);
				else if(S[r+1][c-1]=='\\')return Dfs(r,c-1,1);
				else assert(0);
			}
			else return false;
		}
		else if(S[r+1][c]=='\\')
		{
			if(c+1<C)
			{
				if(S[r+1][c+1]=='/')return Dfs(r,c+1,1);
				else if(S[r+1][c+1]=='\\')return Dfs(r+1,c+1,0);
				else assert(0);
			}
			else return false;
		}
		else assert(0);
	}
	else if(d==1)
	{
		if(S[r][c]=='/')
		{
			if(c+1<C)
			{
				if(S[r][c+1]=='/')return Dfs(r-1,c+1,1);
				else if(S[r][c+1]=='\\')return Dfs(r,c+1,0);
				else assert(0);
			}
			else return false;
		}
		else if(S[r][c]=='\\')
		{
			if(c-1>=0)
			{
				if(S[r][c-1]=='/')return Dfs(r,c-1,0);
				else if(S[r][c-1]=='\\')return Dfs(r-1,c-1,1);
				else assert(0);
			}
			else return false;
		}
		else assert(0);
	}
	assert(0);return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&C,&R)==2)
	{
		for(int i=0;i<R;i++)assert(scanf("%s",S[i])==1);
		int ans=0;
		for(int i=0;i<C;i++)
		{
			int c=i;
			bool valid=true;
			switch(S[0][i])
			{
				case'/':
				{
					--c;
					if(c<0||S[0][c]=='\\')valid=false;
				}break;
				case'\\':
				{
					++c;
					if(c==C||S[0][c]=='/')valid=false;
				}break;
				default:assert(0);break;
			}
			if(!valid)continue;
			if(Dfs(0,c,0))++ans;
		}
		if(!ans)puts("I can't escape.");
		else printf("%d\n",ans);
	}
	return 0;
}
