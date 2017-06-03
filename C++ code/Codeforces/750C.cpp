#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return a>b?(a=b,true):false;}
int N,C[200000],D[200000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&C[i],&D[i]);
		int upper=INF,lower=-INF;
		for(int i=N-2;i>=0;i--)C[i]+=C[i+1];
		for(int i=0;i<N;i++)
		{
			switch(D[i])
			{
				case 1:
				{
					getmax(lower,1900+C[i]);
				}break;
				case 2:
				{
					getmin(upper,1899+C[i]);
				}break;
				default:assert(0);break;
			}
		}
		if(lower>upper)puts("Impossible");
		else if(upper==INF)puts("Infinity");
		else printf("%d\n",upper);
	}
	return 0;
}
