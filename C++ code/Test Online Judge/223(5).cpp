#include<cstdio>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int T,N,P;
char S[1000001];
int POW[1000000];
vector<int>IDX;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d",S,&P);
		IDX.clear();
		for(int i=0;i<P;i++)IDX.push_back(-2);
		N=-1;while(S[++N]);
		POW[0]=1;
		for(int i=1;i<N;i++)POW[i]=(POW[i-1]*10)%P;
		int idx=INF,len=INF;
		if(P==2||P==5)
		{
			for(int i=0;i<N;i++)if((S[i]-'0')%P==0){idx=i-1,len=1;break;}
		}
		else
		{
			IDX[0]=-1;
			int now=0;
			for(int i=0;i<N;i++)
			{
				now=(now*10+(S[i]-'0'))%P;
				int tmp=((long long)now*POW[N-1-i])%P;
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
