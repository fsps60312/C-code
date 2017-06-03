#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,P,Q,X,Y;
char S[1000001];
struct Bit
{
	int v[2000001];
	void Clear(){for(int i=1;i<=N*2;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i){while(i<=N*2){v[i]++;i+=lowbit(i);}}
	int Query(int i){int a=0;while(i){a+=v[i];i-=lowbit(i);}return a;}
}BIT;
int main()
{
	scanf("%d%d%d%d%d%s",&N,&P,&Q,&X,&Y,S);
	BIT.Clear();
	int now=N;
	for(int i=0;i<N;i++)
	{
		if(S[i]=='+')now++;
		else now--;
		BIT.Add(now);
	}
	int ans=INF;
	for(int i=N-1;i>=0;i--)
	{
		ans=min(ans,)
	}
	return 0;
}
