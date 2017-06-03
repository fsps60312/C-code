#include<cstdio>
#include<vector>
using namespace std;
int R,C,N,KM_TO[1001],T1[1001],T2[1001],KM_FROM[1001];
vector<int> TO[1001];
bool check_paired(int u)
{
	T1[u]=1;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(T2[j])continue;
		T2[j]=1;
		if(KM_TO[j]==-1||check_paired(KM_TO[j]))
		{
			KM_TO[j]=u;
			return true;
		}
	}
	return false;
}
void clear_T1T2()
{
	for(int i=1;i<=R;i++)T1[i]=0;
	for(int i=1;i<=C;i++)T2[i]=0;
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%d%d%d",&R,&C,&N)==3&&(R||C||N))
	{
		for(int i=1;i<=R;i++)
		{
			TO[i].clear();
		}
		for(int i=1;i<=C;i++)
		{
			KM_TO[i]=-1;
		}
		while(N--)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
		}
		int edge_find=0;
		for(int i=1;i<=R;i++)
		{
			clear_T1T2();
			if(check_paired(i))edge_find++;
		}
		printf("%d",edge_find);
		clear_T1T2();
		for(int i=1;i<=R;i++)KM_FROM[i]=-1;
		for(int i=1;i<=C;i++)
		{
			if(KM_TO[i]!=-1)
			{
				KM_FROM[KM_TO[i]]=i;
			}
		}
		for(int i=1;i<=R;i++)
		{
			if(KM_FROM[i]==-1)
			{
				check_paired(i);
			}
		}
		for(int i=1;i<=R;i++)
		{
			if(T1[i]==0)printf(" r%d",i);
		}
		for(int i=1;i<=C;i++)
		{
			if(T2[i]==1)printf(" c%d",i);
		}
		puts("");
	}
	return 0;
}
