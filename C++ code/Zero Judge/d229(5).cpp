#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int NOW[11],ANS[11],RECORD;
struct Backpack
{
	bool vis[4084];
	set<int>elements;
	vector<int>changes,recovery;
	void Clear(){elements.clear(),changes.clear(),recovery.clear();for(int i=0;i<=4083;i++)vis[i]=false;}
	void Cover(const int i)
	{
		if(vis[i])return;
		vis[i]=true;
		elements.insert(i);
		changes.push_back(i);
	}
	void CreateRecoveryPoint(){recovery.push_back(changes.size());}
	void DoRecovery()
	{
		assert(!recovery.empty());
		const int sz=recovery[recovery.size()-1];
		recovery.pop_back();
		for(int i=(int)changes.size()-1;i>=sz;i--,changes.pop_back())
		{
			const int v=changes[i];
			vis[v]=false;
			elements.erase(v);
		}
	}
	void Add(const int item)
	{
		const int sz=changes.size();
		for(int i=0;i<sz;i++)Cover(changes[i]+item);
	}
	bool operator[](const int i)const{return vis[i];}
}VIS[11];
//bool VIS[11][11][4084];
//int BOUND[11][11];
int N,M;
//void Update(bool *from,bool *to,const int item)
//{
//	for(int i=4083-item;i>=0;i--)to[i+item]|=from[i];
//}
void Dfs(const int dep)
{
	if(dep==M)
	{
		int record;
		for(record=NOW[M-1];VIS[N][record+1];record++);
		if(record>RECORD)
		{
			RECORD=record;
			for(int i=0;i<M;i++)ANS[i]=NOW[i];
		}
		return;
	}
	for(int &v=NOW[dep]=NOW[dep-1]+1;v<=100;v++)
	{
		for(int n=N;n>=0;n--)
		{
			VIS[n].CreateRecoveryPoint();
			for(int i=1;i<=n;i++)
			{
				for(const int j:VIS[n-i].elements)VIS[n].Cover(j+i*v);
			}
		}
//		for(int n=0;n<=N;n++)for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)Update(VIS[dep-1][i],VIS[dep][n],j*v);
		Dfs(dep+1);
		for(int n=0;n<=N;n++)VIS[n].DoRecovery();
		if(!VIS[N][v])break;
	}
}
FILE *OUT=stdout;//fopen("out.txt","w");
int main()
{
//	for(N=1;N<=10;N++)for(M=1;M<=10;M++)if(N+M<=12)
	while(scanf("%d%d",&N,&M)==2)
	{
		NOW[0]=1,RECORD=-1;
		for(int i=0;i<=N;i++)VIS[i].Clear();
		for(int i=0;i<=N;i++)for(int j=0;j<=i;j++)VIS[i].Cover(j);
//		printf("processing... N=%d M=%d\n",N,M);
		Dfs(1);
//		fprintf(OUT,"N=%d,M=%d\n",N,M);
		fprintf(OUT,"%d\n",RECORD);
		for(int i=0;i<M;i++)
		{
			if(i)fprintf(OUT," ");
			fprintf(OUT,"%d",ANS[i]);
		}
		fprintf(OUT,"\n");
	}
	return 0;
}
