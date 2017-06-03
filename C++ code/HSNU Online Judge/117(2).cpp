#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,S[24],SUM[1<<24];
int LowBit(const int s){return s&(-s);}
int GetSUM(const int s)
{
	int &sum=SUM[s];
	if(sum!=-1)return sum;
	return sum=GetSUM(LowBit(s))+GetSUM(s-LowBit(s));
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<(1<<N);i++)SUM[i]=-1;
	SUM[0]=0;
	for(int i=0;i<N;i++)scanf(1,"%d",&S[i]),SUM[1<<i]=S[i];
	for(int i=0;i<(1<<N);i++)GetSUM(i);
	int ans=INF;
	const int all=(1<<N)-1;
	for(int s1=0;s1<(1<<N);s1++)
	{
		for(int s2=s1;s2;s2=(s2-1)&s1)
		{
			const int a=SUM[s2],b=SUM[s1^s2],c=SUM[all^s1];
			getmin(ans,max(max(abs(a-b),abs(a-c)),abs(b-c)));
		}
	}
	printf("%d\n",ans);
	return 0;
}
