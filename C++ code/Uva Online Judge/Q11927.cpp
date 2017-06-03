#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,M,SG[1000];
vector<int> TO[1000];
int getSG(int u)
{
	int &sg=SG[u];
	if(sg!=-1)return sg;
	if(!TO[u].size())return sg=0;
	vector<int> ch;
	for(int i=0;i<TO[u].size();i++)
	{
		int &t=TO[u][i];
		ch.push_back(getSG(t));
	}
	sort(ch.begin(),ch.end());
	sg=0;
	for(int i=0;i<ch.size();i++)
	{
		if(ch[i]==sg)sg++;
		else if(ch[i]>sg) break;
	}
	return sg;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			SG[i]=-1;
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			TO[a].push_back(b);
		}
		int sg=0;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			if(v&1)sg^=getSG(i);
		}
		printf(sg?"First\n":"Second\n");
	}
	return 0;
}
