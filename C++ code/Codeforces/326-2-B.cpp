#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
LL N;
vector<LL>P,F;
void GetF(LL n)
{
	for(int i=0,cnt=0;P[i]*P[i]<=n;i++,cnt=0)
	{
		while(n%P[i]==0LL)cnt++,n/=P[i];
		if(cnt>=1)F.push_back(P[i]);
	}
	if(n>1LL)F.push_back(n);
}
int main()
{
	P.push_back(2LL),P.push_back(3LL);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2LL;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j]!=0LL;j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]>=1000000LL)break;
	}
	scanf("%I64d",&N);
	GetF(N);
	LL ans=1LL;
	for(int i=0;i<F.size();i++)ans*=F[i];
	printf("%I64d\n",ans);
	return 0;
}
