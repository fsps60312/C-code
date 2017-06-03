#include<cstdio>
#include<string>
#include<set>
#include<vector>
using namespace std;
set<string>S;
char LINE[10000];
int T,M,N;
vector<string>A,B;
int main()
{
	gets(LINE);sscanf(LINE,"%d",&T);
	int kase=1;
	while(T--)
	{
		A.clear(),B.clear();S.clear();
		gets(LINE);sscanf(LINE,"%d%d",&M,&N);
		for(int i=0;i<M;i++){gets(LINE);A.push_back(LINE);}
		for(int i=0;i<N;i++){gets(LINE);B.push_back(LINE);}
		for(int i=0;i<M;i++)for(int j=0;j<N;j++)S.insert(A[i]+B[j]);
		printf("Case %d: %d\n",kase++,S.size());
	}
}
