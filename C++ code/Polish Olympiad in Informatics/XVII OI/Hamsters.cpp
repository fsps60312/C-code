#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
struct AC_Automaton
{
	vector<int>CH[26],END;
	int SZ;
	void Expand()
	{
		for(int i=0;i<26;i++)CH[i].push_back(0);
		END.push_back(0);
		++SZ;
	}
	void Clear()
	{
		for(int i=0;i<26;i++)CH[i].clear();
		END.clear();
		SZ=0;
		Expand();
	}
	int GetNxt(const int u,const int c)
	{
		assert(0<=c&&c<26);
		if(CH[c][u])return CH[c][u];
		CH[c][u]=SZ;
		Expand();
		return CH[c][u];
	}
	void InsertFromStandardInput()
	{
		static char str[100001];
		scanf("%s",str);
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]-'a');
		++END[u];
	}
	void BuildFail()
	{
		vector<int>fail;
		fail.resize(SZ,0);
		queue<int>q;
		for(int c=0;c<26;c++)if(CH[0][c])q.push(CH[0][c]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int c=0;c<26;c++)
			{
				if(CH[u][c])
				{
					int f=fail[u];
					while(f&&CH[f][c]==0)f=fail[f];
					const int nxt=CH[u][c];
					END[nxt]+=END[fail[nxt]=CH[f][c]];
					q.push(nxt);
				}
				else
				{
					int f=fail[u];
					while(f&&CH[f][c]==0)f=fail[f];
					CH[u][c]=CH[f][c];
				}
			}
		}
		vector<int>().swap(fail);
	}
}AC;
int main()
{
	freopen("in.txt","r",stdin);
	for(int n,m;scanf("%d%d",&n,&m)==2;)
	{
		AC.Clear();
		for(int i=0;i<n;i++)AC.InsertFromStandardInput();
		
	}
	return 0;
}
