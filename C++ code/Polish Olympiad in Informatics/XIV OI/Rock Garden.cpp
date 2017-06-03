#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
template<class T>inline void get_min_max(T&a,T&b,const T&c){getmin(a,c),getmax(b,c);}
template<class T>inline bool In(const T&o,const T&a,const T&b){return a<=o&&o<=b;}
struct Stone
{
	int X,Y,M;
};
int N;
Stone S[1000000];
char ANS[2][1000001];
int Solve(const int type,const int x1,const int x2,const int y1,const int y2)
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		if(!In(S[i].X,x1,x2)||!In(S[i].Y,y1,y2))ans+=S[i].M,ANS[type][i]='1';
		else ANS[type][i]='0';
	}
	ANS[type][N]='\0';
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d%d",&S[i].X,&S[i].Y,&S[i].M);
		int X1,X2,Y1,Y2;
		X1=Y1=INF,X2=Y2=-INF;
		for(int i=0;i<N;i++)get_min_max(X1,X2,min(S[i].X,S[i].Y)),get_min_max(Y1,Y2,max(S[i].X,S[i].Y));
		const int ans0=Solve(0,X1,X2,Y1,Y2),ans1=Solve(1,Y1,Y2,X1,X2);
		printf("%lld %d\n%s\n",2*((long long)(X2-X1)+(Y2-Y1)),min(ans0,ans1),ANS[ans0<ans1?0:1]);
	}
	return 0;
}
