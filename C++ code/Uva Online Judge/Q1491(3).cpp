#include<bits/stdc++.h>
using namespace std;
void massert(bool valid){if(valid)return;for(;;)puts("E");}
int N,LIMIT[5],L,NOW[5];
char S[501];
vector<vector<char> >STATE[5];
int IDX;
vector<char>TREE[5];
bool Dfs(char &dep)
{
	if(dep<1||dep>N)
	{
		if(dep)return S[IDX++]==dep;
		dep=S[IDX++];
		return dep>0;
	}
	vector<char>&v=TREE[dep];
	for(int i=0;i<v.size();i++)if(!Dfs(v[i]))return false;
	return true;
}
bool Solve(int dep)
{
	if(dep==0)
	{
		for(int i=1;i<=N;i++)
		{
			TREE[i].clear();
			vector<char>&v=STATE[i][NOW[i]];
			for(int j=0;j<v.size();j++)TREE[i].push_back(v[j]);
		}
		IDX=0;
		char root=N;
		return Dfs(root)&&IDX==L;
	}
	for(int &i=NOW[dep]=0;i<STATE[dep].size();i++)if(Solve(dep-1))return true;
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&LIMIT[i]);
		int n=0;
		for(int i=1;i<=N;i++)if(LIMIT[i]>1)LIMIT[++n]=LIMIT[i];
		N=n;
		for(int i=1;i<=N;i++)
		{
			STATE[i].clear();
			for(int cnt=2;cnt<=LIMIT[i];cnt++)
			{
				int limit=1;
				for(int j=0;j<cnt;j++)limit*=i;
				for(int s=0;s<limit;s++)
				{
					vector<char>v;
					for(int j=0,k=s;j<cnt;j++,k/=i)v.push_back(k%i);
					STATE[i].push_back(v);
				}
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			printf("i=%d\n");
//			for(int j=0;j<STATE[i].size();j++)
//			{
//				vector<int>&v=STATE[i][j];
//				for(int k=0;k<v.size();k++)printf(" %d",v[k]);puts("");
//			}
//		}
		scanf("%s",S);
		L=-1;while(S[++L]);
		if(!N)puts(L==1?"Yes":"No");
		else puts(L==1||Solve(N)?"Yes":"No");
	}
	return 0;
}

