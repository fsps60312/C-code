#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
struct Big
{
	vector<char>s;
	Big(){}
	Big(const int v){s.clear(),s.push_back(v);}
	void operator+=(const Big &a)
	{
		while(s.size()<a.s.size())s.push_back(0);
		for(int i=0;i<a.s.size();i++)s[i]+=a.s[i];
		for(int i=0;i<s.size();i++)if(s[i]>=10)
		{
			if(i+1==s.size())s.push_back(0);
			s[i+1]+=s[i]/10,s[i]%=10;
		}
	}
	void Print(){for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
};
Big DP[502][501];
int T,M;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&M);
		assert(M%2==0);
		for(int i=0;i<=M;i++)DP[0][i]=0;
		DP[0][0]=1;
		for(int i=0;i<=M;i++)DP[1][i]=0;
		for(int i=0;i<=M;i+=2)DP[1][i]=1;
		for(int cnt=1;cnt<=M;cnt++)
		{
			for(int i=0;i<=M;i+=2)
			{
				DP[cnt+1][i]=0;
				if(i-2>=cnt)DP[cnt+1][i]+=DP[cnt][i-2];
				if(i>=cnt)DP[cnt+1][i]+=DP[cnt][i];
			}
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		DP[M+1][M].Print();puts("");
	}
	return 0;
}
