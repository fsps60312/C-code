#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
LL N;
vector<LL>P;
bool NumOfFactor()
{
	for(int i=0;P[i]*P[i]<=N;i++)
	{
		int cnt=0;
		while(N%P[i]==0LL)N/=P[i],cnt++;
		if((cnt+1)%2==0)return false;
	}
	return N==1LL;
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
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]*P[i]>=4294967296LL)break;
	}
	while(scanf("%lld",&N)==1&&N!=0LL)puts(NumOfFactor()?"yes":"no");
	return 0;
}
