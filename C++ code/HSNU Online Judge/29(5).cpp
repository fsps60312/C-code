#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,P,Q,X,Y;
char S[1000001];
int LOW[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d%d%s",&N,&P,&Q,&X,&Y,S);
	int l=N,r=N,low=N;
	for(int i=0;i<N;i++)
	{
		if(S[i]=='+')r++;
		else r--;
		LOW[i]=low=min(low,r);
	}
	int adjust=Q-(P+(r-N));
	adjust/=2;
	int ans=INF,cyc=0;
	low=INF;
	for(int i=N-1,mn,opes,v,a,b;;i--,cyc++)
	{
		mn=P+((min(low,LOW[i])-N)-(l-N));
		if(mn>0)mn=0;
		opes=(-mn+1)/2;
		a=b=opes;
		if(adjust>=0)
		{
			if(b>=adjust)b-=adjust;
			else a+=adjust-b,b=0;
		}
		else
		{
			b+=-adjust;
		}
		v=Y*cyc+X*(a+b);
		ans=min(ans,v);
		if(!i)break;
		if(S[i]=='+')r--,l--;
		else r++,l++;
		low=min(low,l);
	}
	printf("%d\n",ans);
	return 0;
}
