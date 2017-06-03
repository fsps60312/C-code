#include<cstdio>
#include<vector>
#include<bitset>
using namespace std;
const int MAXP=2000000000;
bitset<MAXP+1>ISP;
vector<int>P;
int T,A,B,K,S;
int Solve()
{
	int l=0,r=P.size();
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(P[mid]<A)l=mid+1;
		else r=mid;
	}
	if(l==P.size())return 0;
	int ans=0;
	for(;l+K<=P.size()&&P[l+K-1]<=B;l++)if(P[l+K-1]-P[l]==S)ans++;
	return ans;
}
int main()
{
	for(int i=0;i<=MAXP;i++)ISP[i]=(i&1?true:false);
	ISP[1]=false,ISP[2]=true;
	for(int i=3;i<=MAXP;i++)if(ISP[i])for(int j=3;j<=MAXP/i;j+=2)ISP[i*j]=false;
	for(int i=0;i<=MAXP;i++)if(ISP[i])P.push_back(i);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&A,&B,&K,&S);
		printf("%d\n",Solve());
	}
	return 0;
}
