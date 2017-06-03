#include<cstdio>
#include<vector>
#include<map>
using namespace std;
int N,M;
int DJ[10];
int FindDJ(const int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool Merge(int a,int b){if((a=FindDJ(a))==(b=FindDJ(b)))return false;DJ[a]=b;return true;}
int ET[10][10],TET[10][10];
bool Merge()
{
	for(int i=0;i<N;i++)DJ[i]=i;
	int tn=N;
	bool result=false;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(ET[i][j]>1)if(Merge(i,j))tn--,result=true;
	if(!result)return false;
	map<int,int>idx;
	for(int i=0;i<N;i++)idx[FindDJ(i)]=-1;
	int cnt=0;
	for(auto &it:idx)it.second=cnt++;
	for(int i=0;i<N;i++)DJ[i]=idx[DJ[i]];
	for(int i=0;i<tn*tn;i++)TET[i/tn][i%tn]=0;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(DJ[i]!=DJ[j])
	{
		TET[DJ[i]][DJ[j]]+=ET[i][j];
		TET[DJ[j]][DJ[i]]+=ET[i][j];
	}
	N=tn;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ET[i][j]=TET[i][j];
	return true;
}

int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int i=0;i<N*N;i++)ET[i/N][i%N]=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			if(a!=b)ET[a][b]++,ET[b][a]++;
		}
		while(Merge());
		
	}
	return 0;
}
