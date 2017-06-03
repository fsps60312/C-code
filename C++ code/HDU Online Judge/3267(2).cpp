#include<cstdio>
#include<vector>
#include<map>
using namespace std;
int N,M;
int DJ[10];
int FindDJ(const int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool Merge(int a,int b){if((a=FindDJ(a))==(b=FindDJ(b)))return false;DJ[a]=b;return true;}
int ET[30][100],TET[100];
bool Merge(int *et,int &n)
{
	for(int i=0;i<n;i++)DJ[i]=i;
	int tn=n;
	bool result=false;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(et[i*n+j]>1)if(Merge(i,j))tn--,result=true;
	if(!result)return false;
	map<int,int>idx;
	for(int i=0;i<n;i++)idx[FindDJ(i)]=-1;
	int cnt=0;
	for(auto &it:idx)it.second=cnt++;
	for(int i=0;i<n;i++)DJ[i]=idx[DJ[i]];
	for(int i=0;i<tn*tn;i++)TET[i]=0;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(DJ[i]!=DJ[j])
	{
		TET[DJ[i]*tn+DJ[j]]+=et[i*n+j];
		TET[DJ[j]*tn+DJ[i]]+=et[i*n+j];
	}
	n=tn;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)et[i*n+j]=TET[i*n+j];
	return true;
}
bool CutEdge(const int dep,const int n);
bool ColorEdge(const int dep,const int n)
{
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(ET[dep][i*n+j])
	{
		for(int k=0;k<n*n;k++)ET[dep+1][k]=ET[dep][k];
		ET[dep+1][i*n+j]++,ET[dep+1][j*n+i]++;
		int nxtn=n;
		while(Merge(ET[dep+1],nxtn));
		if(!CutEdge(dep+1,nxtn))return true;
	}
	return false;
}
bool CutEdge(const int dep,const int n)
{
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(ET[dep][i*n+j])
	{
		for(int k=0;k<n*n;k++)ET[dep+1][k]=ET[dep][k];
		ET[dep+1][i*n+j]=ET[dep+1][j*n+i]=0;
		if(!ColorEdge(dep+1,n))return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&!(N==-1&&M==-1))
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int i=0;i<N*N;i++)ET[0][i]=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			if(a!=b)ET[0][a*N+b]++,ET[0][b*N+a]++;
		}
		while(Merge(ET[0],N));
		puts(CutEdge(0,N)?"NO":"YES");
	}
	return 0;
}
