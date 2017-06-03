#include<cstdio>
#include<map>
#include<string>
#include<vector>
using namespace std;
map<string,int> IDX;
int get_IDX(string a)
{
	if(IDX.find(a)!=IDX.end())return IDX[a];
	int sz=IDX.size();
	IDX[a]=sz;
	return sz;
}
char NAME1[101],NAME2[101];
vector<int> GETO[200];
int DP[200][2];
bool UNIQUE[200][2];
int max(int a,int b){return a>b?a:b;}
int get_ANS(int u,int sct)
{
	int &ans=DP[u][sct];
	bool &uni=UNIQUE[u][sct];
	if(ans!=-1)return ans;
	if(!GETO[u].size())return ans=(sct?1:0);
	if(sct)
	{
		ans=1;
		for(int i=0;i<GETO[u].size();i++)
		{
			ans+=get_ANS(GETO[u][i],0);
			uni&=UNIQUE[GETO[u][i]][0];
		}
		return ans;
	}
	else
	{
		ans=0;
		for(int i=0;i<GETO[u].size();i++)
		{
			int &j=GETO[u][i];
			int a1=get_ANS(j,0),a2=get_ANS(j,1);
			if(a1==a2)ans+=a1,uni=false;
			else if(a1>a2)
			{
				ans+=a1;
				uni&=UNIQUE[j][0];
			}
			else
			{
				ans+=a2;
				uni&=UNIQUE[j][1];
			}
		}
		return ans;
	}
}
int N;
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		IDX.clear();
		for(int i=0;i<N;i++)
		{
			GETO[i].clear();
			DP[i][0]=DP[i][1]=-1;
			UNIQUE[i][0]=UNIQUE[i][1]=true;
		}
		scanf("%s",NAME1);
		IDX[NAME1]=0;
		for(int i=1;i<N;i++)
		{
			scanf("%s%s",NAME1,NAME2);
			GETO[get_IDX(NAME2)].push_back(get_IDX(NAME1));
		}
		bool unique=true;
		int ans1=get_ANS(0,0),ans2=get_ANS(0,1);
		if(ans1>ans2)unique&=UNIQUE[0][0];
		else if(ans2>ans1)unique&=UNIQUE[0][1];
		else unique=false;
		printf("%d ",ans1>ans2?ans1:ans2);
		if(unique)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
