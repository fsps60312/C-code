#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,S[50][50],ANS[50];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)scanf("%d",&S[i][j]);
		}
		int repeat=0;
		for(int i=0;i<N;i++)
		{
			int mx=0;
			for(int j=0;j<N;j++)getmax(mx,S[i][j]),getmax(mx,S[j][i]);
			if(mx==N-1)
			{
				ANS[i]=N-1+(repeat++);
			}
			else
			{
				assert(0<mx&&mx<N-1);
				ANS[i]=mx;
			}
		}
		assert(repeat==2);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
