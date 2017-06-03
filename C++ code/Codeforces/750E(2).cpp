#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int FindBefore(const vector<int>&s,const int v)
{
	return (int)(upper_bound(s.begin(),s.end(),v)-s.begin())-1;
}
int N,Q;
char S[200001];
vector<int>L[10];
int Track201(int v)
{
	int i=FindBefore(L[1],v);
	if(i==-1)return -1;
	v=L[1][i];
	i=FindBefore(L[0],v);
	if(i==-1)return -1;
	v=L[0][i];
	i=FindBefore(L[2],v);
	if(i==-1)return -1;
	return L[2][i];
}
int Solve(const int a,const int b)
{
	int i=FindBefore(L[7],b);
	if(i==-1||Track201(L[7][i])<a)return -1;
	
	if(Track201(L[7][i])==-1)return -1;
	int answer=0;
	i=FindBefore(L[6],b);
	while(true)
	{
		if(i==-1||Track201(L[6][i])<a)return answer;
		i--,answer++;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		scanf("%s",S);
		for(int i=0;i<10;i++)L[i].clear();
		for(int i=0;i<N;i++)L[S[i]-'0'].push_back(i);
		for(int querycount=0,a,b;querycount<Q;querycount++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			printf("%d\n",Solve(a,b));
		}
	}
	return 0;
}
