#include<cstdio>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
typedef long long LL;
int T,N;
LL P;
char S[1000001];
LL Pow(LL a,int b)
{
	LL ans=1LL;
	while(b)
	{
		if(b&1)(ans*=a)%=P;
		(a*=a)%=P;
		b>>=1;
	}
	return ans;
}
vector<int>IDX;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%lld",S,&P);
		IDX.clear();
		for(int i=0;i<P;i++)IDX.push_back(-2);
		N=-1;while(S[++N]);
		int idx=INF,len=INF;
		if(P==2LL||P==5LL)
		{
			for(int i=0;i<N;i++)if((S[i]-'0')%P==0LL){idx=i-1,len=1;break;}
		}
		else
		{
			IDX[0]=-1;
			LL now=0LL;
			for(int i=0;i<N;i++)
			{
				now=(now*10LL+(S[i]-'0'))%P;
				LL tmp=(now*Pow(10LL,N-i))%P;
				if(IDX[tmp]!=-2)
				{
					int tlen=i-IDX[tmp];
					if(tlen<len||(tlen==len&&IDX[tmp]<idx))idx=IDX[tmp],len=tlen;
				}
				IDX[tmp]=i;
			}
		}
		if(idx==INF)puts("-1");
		else printf("%d %d\n",idx+2,idx+len+1);
	}
	return 0;
}
