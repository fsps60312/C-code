#include<cstdio>
#include<vector>
using namespace std;
int T,M,K;
void OLE(){while(1)printf("E");}
vector<int>TO[300],RTO[300];
bool solve()
{
	static int CNT[300];
	for(int ir=0;ir<M;ir++)
	{
		for(int i=0;i<M;i++)CNT[i]=0;
		for(int jr=0;jr<RTO[ir].size();jr++)
		{
			int &u=RTO[ir][jr];
			for(int j=0;j<TO[u].size();j++)
			{
				CNT[TO[u][j]]++;
			}
		}
		for(int i=0;i<M;i++)if(CNT[i]&&CNT[i]!=RTO[ir].size())return false;
	}
	return true;
}
int main()
{
	int kase=1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&M,&K);
		if(M>300)OLE();
		for(int i=0;i<M;i++)TO[i].clear(),RTO[i].clear();
		for(int i=0,a,b;i<K;i++)
		{
			scanf("%d%d",&a,&b);
			if(a>=M||b>=M||a<0||b<0)OLE();
			TO[a].push_back(b);
			RTO[b].push_back(a);
		}
		printf("Case #%d: %s\n",kase++,solve()?"Yes":"No");
	}
	return 0;
}
