#include<cstdio>
#include<cassert>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
struct Ans
{
	int a,b,c;
	Ans(){}
	Ans(const int _a,const int _b,const int _c):a(_a),b(_b),c(_c){}
};
vector<Ans>ANS;
int N;
bool EDGE[1<<12][1<<12];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N),N=1<<N;
		for(int i=1;i<N;i++)for(int j=1;j<N;j++)EDGE[i][j]=(i!=j);
		ANS.clear();
		for(int i=1;i<N;i++)for(int j=i+1;j<N;j++)if(EDGE[i][j])
		{
			for(int k=1;k<N;k++)if(EDGE[i][k]&&EDGE[j][k])
			{
				ANS.push_back(Ans(i,j,k));
				EDGE[i][j]=EDGE[j][i]=false;
				EDGE[i][k]=EDGE[k][i]=false;
				EDGE[j][k]=EDGE[k][j]=false;
				break;
			}
		}
		for(const Ans &a:ANS)printf("%d %d %d\n",a.a,a.b,a.c);
//		puts("");
	}
	return 0;
}
