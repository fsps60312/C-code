#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
bool ET[5000][5000];
int TYPE[5000],ECNT[5000];//0:no edge,1:all edge
bool Dfs(const int u,vector<int>&rec)
{
	rec.push_back(u);
	if(TYPE[u]==0)
	{
		for(int i=0;i<N;i++)if(i!=u&&ET[u][i])
		{
			if(TYPE[i]==0)return false;
			if(TYPE[i]==1)continue;
			TYPE[i]=1;
			if(!Dfs(i,rec))return false;
		}
		return true;
	}
	else if(TYPE[u]==1)
	{
		for(int i=0;i<N;i++)if(i!=u&&!ET[u][i])
		{
			if(TYPE[i]==1)return false;
			if(TYPE[i]==0)continue;
			TYPE[i]=0;
			if(!Dfs(i,rec))return false;
		}
		return true;
	}
	else assert(0);
}
bool Check()
{
	int u=-1;
	for(int i=0;i<N;i++)if(TYPE[i]==-1){u=i;break;}
	if(u==-1)return true;
	vector<int>rec;
	rec.clear();
	TYPE[u]=0;
	if(Dfs(u,rec)&&Check())return true;
	for(int i=0;i<rec.size();i++)TYPE[rec[i]]=-1;
	rec.clear();
	TYPE[u]=1;
	if(Dfs(u,rec)&&Check())return true;
	for(int i=0;i<rec.size();i++)TYPE[rec[i]]=-1;
	rec.clear();
	return false;
}
int Solve()
{
	if(!Check())return 0;
	int ans=1,cnt[2]={0,0};
	for(int i=0;i<N;i++)cnt[TYPE[i]]++;
//	printf("CNT(%d,%d)\n",cnt[0],cnt[1]);
//	for(int i=0;i<N;i++)printf("TYPE[%d]=%d\n",i,TYPE[i]);
	for(int i=0;i<N;i++)
	{
//		printf("ECNT[%d]=%d\n",i,ECNT[i]);
		if(TYPE[i]==0)
		{
			if(ECNT[i]==cnt[1]&&cnt[0]>1)ans++;
			if(ECNT[i]==cnt[1]-1)
			{
				int u=-1;
				for(int j=0;j<N;j++)if(!ET[i][j]&&TYPE[j]==1){u=j;break;}
				assert(u!=-1);
				if(ECNT[u]==cnt[1]-1)ans++;
			}
		}
		else if(TYPE[i]==1)
		{
			if(ECNT[i]==cnt[1]-1&&cnt[1]>1)ans++;
			if(ECNT[i]==cnt[1])
			{
				int u=-1;
				for(int j=0;j<N;j++)if(ET[i][j]&&TYPE[j]==0){u=j;break;}
				assert(u!=-1);
				if(ECNT[u]==cnt[1])ans++;
			}
		}
		else assert(0);
	}
	return ans;
}
inline void GetInt(int &v)
{
	const int zero='0',nine='9';
	static int c;c=getchar();
	while(c<zero||c>nine)c=getchar();
	v=0;
	for(;c>=zero&&c<=nine;c=getchar())v*=10,v+=c-zero;
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)ET[i][j]=false;
		TYPE[i]=-1,ECNT[i]=0;
		static int cnt;
		GetInt(cnt);
		for(;cnt--;)
		{
			static int v;
			GetInt(v);
			v--;
			if(!ET[i][v])ET[i][v]=true,ECNT[i]++;
		}
	}
	printf("%d\n",Solve());
	return 0;
}
/*
4
2 2 3
2 1 3
3 1 2 4
1 3
*/
