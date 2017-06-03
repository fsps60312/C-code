#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,N;
int X[1000000],Y[1000000];
inline bool Digit(const int &c){static int c0='0',c9='9';return c>=c0&&c<=c9;}
inline void GetInt(int &v)
{
	static int c,c0='0',dash='-';
	static bool nega;
	nega=false;
	while(!Digit(c=getchar()))nega=(c==dash);
	v=c-c0;
	while(Digit(c=getchar()))v*=10,v+=c-c0;
	if(nega)v=-v;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			GetInt(X[i]),GetInt(Y[i]);
		}
		nth_element(X,X+N/2,X+N),nth_element(Y,Y+N/2,Y+N);
		LL x=X[N/2],y=Y[N/2];
		LL ans=0LL;
		for(int i=0;i<N;i++)ans+=abs(x-X[i])+abs(y-Y[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
