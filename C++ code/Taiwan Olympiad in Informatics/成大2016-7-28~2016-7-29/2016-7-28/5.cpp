#include<cstdio>
#include<cassert>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int M,N,GRID[10][10];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&M,&N);
		for(int i=0;i<M;i++)for(int j=0;j<N;j++)scanf("%d",&GRID[i][j]);
	}
	return 0;
}
