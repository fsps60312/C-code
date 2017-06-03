#include<cstdio>
#include<vector>
using namespace std;
int N,K,M;
vector<int>ET[1000000],REC[1000000];
bool KILL[1000000];
bool Dfs(const int u,const int remain)
{
	if(remain<0)return false;
	if(u>=N)return true;
	if(KILL[u]||ET[u].empty())return Dfs(u+1,remain);
	for(auto nxt:ET[u])
	{
		if(KILL[nxt])continue;
		KILL[u]=true;
		if(Dfs(u+1,remain-1))return true;
		KILL[u]=false;
		break;
	}
	vector<int>rec;
	for(auto nxt:ET[u])
	{
		if(KILL[nxt])continue;
		KILL[nxt]=true,rec.push_back(nxt);
	}
	if(Dfs(u+1,remain-(int)rec.size()))return true;
	for(auto i:rec)KILL[i]=false;
	rec.clear();
	vector<int>(rec).swap(rec);
	return false;
}
bool Check(const int cnt)
{
	for(int i=0;i<N;i++)KILL[i]=false;
	return Dfs(0,cnt);
}
void GetInt(int &v)
{
	const int zero='0',nine='9';
	static int c;c=getchar();
	while(c<zero||c>nine)c=getchar();
	v=0;
	while(c>=zero&&c<=nine)v=v*10+(c-zero),c=getchar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N),GetInt(K),GetInt(M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		GetInt(a),GetInt(b);
		a--,b--;
		ET[a].push_back(b);
		ET[b].push_back(a);
	}
	int l=0,r=N-K,mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(Check(mid))r=mid;
		else l=mid+1;
	}
	if(!Check(l))puts("NIE");
	else
	{
		printf("%d\n",N-l);
		bool printed=false;
		for(int i=0;i<N;i++)
		{
			if(KILL[i])continue;
			if(printed)printf(" ");
			printf("%d",i+1);
			printed=true;
		}
		puts("");
	}
	return 0;
}
