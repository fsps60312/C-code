#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,V,E,K[100],VAL[100],SG[100];
vector<int> TO[100];
int cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int getSG(int u)
{
	int &sg=SG[u];
	if(sg!=-1)return sg;
	int sz=TO[u].size(),&k=K[u];
	if(!sz)return sg=0;
	vector<int> forSG;
	for(int i=0,limit=(1<<sz),v=0;i<limit;i++,v=0)
	{
		if(cntbits(i)!=k)continue;
		for(int j=0;j<sz;j++)if(i&(1<<j))v^=getSG(TO[u][j]);
		forSG.push_back(v);
	}
	sort(forSG.begin(),forSG.end());
	sg=0;
	for(int i=0;i<forSG.size();i++)
	{
		if(forSG[i]==sg)sg++;
		else if(forSG[i]>sg)break;
	}
	return sg;
}
bool solve()
{
	int ans=0;
	for(int i=0;i<V;i++)
	{
		if(VAL[i]&1)ans^=getSG(i);
	}
	return ans==0;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&V,&E);
		for(int i=0;i<V;i++)
		{
			TO[i].clear();
			SG[i]=-1;
		}
		for(int i=0,a,b;i<E;i++)
		{
			scanf("%d%d",&a,&b);
			TO[a].push_back(b);
		}
		for(int i=0;i<V;i++)scanf("%d",&K[i]);
		int R;scanf("%d",&R);
		printf("Game#%d:\n",kase++);
		int roundn=1;
		while(R--)
		{
			for(int i=0;i<V;i++)scanf("%d",&VAL[i]);
			printf("Round#%d: %s\n",roundn++,solve()?"LOSING":"WINNING");
		}
		printf("\n");
	}
	return 0;
}
