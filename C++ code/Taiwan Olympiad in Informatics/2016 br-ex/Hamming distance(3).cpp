#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N;
bool EDGE[80][80];
void getmax(int &a,const int b){if(b>a)a=b;}
int ANS;
int UpBound(const vector<bool>&s)
{
	static bool matched[80];
	for(int i=0;i<N;i++)matched[i]=false;
	int cnt=0;
	for(int i=0;i<N;i++)if(s[i]&&!matched[i])
	{
		for(int j=i+1;j<N;j++)if(s[j]&&EDGE[i][j]&&!matched[j]){matched[i]=matched[j]=true,++cnt;break;}
	}
	return N-cnt;
}
vector<bool>VIS,CHOOSE,REMAIN;
bool AllDisconnected(const int u)
{
	for(int i=0;i<N;i++)if(CHOOSE[i]&&EDGE[u][i])return false;
	return true;
}
int NOW;
void Dfs(const int u)
{
	if(u==N){if(NOW>ANS)ANS=NOW;return;}
	if(NOW+UpBound(REMAIN)<=ANS)return;
	VIS[u]=true,REMAIN[u]=false;
	Dfs(u+1);
	if(AllDisconnected(u))
	{
		CHOOSE[u]=true,++NOW;
		Dfs(u+1);
		CHOOSE[u]=false,--NOW;
	}
	VIS[u]=false,REMAIN[u]=true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		if(true)
		{
			int s[80];
			for(int i=0;i<N;i++)scanf("%d",&s[i]);
			for(int i=0;i<N;i++)for(int j=0;j<N;j++)
			{
				if(i!=j)
				{
					int cnt=0;
					for(int k=0;k<30;k++)if((1<<k)&(s[i]^s[j]))cnt++;
					if(cnt<=4)EDGE[i][j]=true;
					else EDGE[i][j]=false;
				}
				else EDGE[i][j]=false;
			}
//			for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(EDGE[i][j])++DEG[i];
		}
		VIS.clear(),VIS.resize(N,false);
		CHOOSE.clear(),CHOOSE.resize(N,false);
		REMAIN.clear(),REMAIN.resize(N,true);
		ANS=-1,NOW=0;
		Dfs(0);
		printf("%d\n",ANS);
	}
	return 0;
}
