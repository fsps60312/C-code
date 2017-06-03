#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
using namespace std;
int N;
map<string,int> IDX;
double MAT[30][30];
void getmax(double &a,double b){if(b>a)a=b;}
bool solve()
{
	for(int k=2;k<=N;k++)
	{
		for(int i1=0;i1<N;i1++)
		{
			for(int i2=0;i2<N;i2++)
			{
				for(int j=0;j<N;j++)
				{
					getmax(MAT[i1][i2],MAT[i1][j]*MAT[j][i2]);
				}
			}
			if(MAT[i1][i1]>1)return true;
		}
	}
	return false;
}
int main()
{
	char tstr1[1000],tstr2[1000];
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		IDX.clear();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)MAT[i][j]=0;
			scanf("%s",tstr1);
			IDX[tstr1]=i;
		}
		int m;scanf("%d",&m);//printf("m=%d\n",m);
		while(m--)
		{
			double d;
			scanf("%s%lf%s",tstr1,&d,tstr2);
			MAT[IDX[tstr1]][IDX[tstr2]]=d;
		}
		if(solve())printf("Case %d: Yes\n",kase++);
		else printf("Case %d: No\n",kase++);
	}
	return 0;
}
