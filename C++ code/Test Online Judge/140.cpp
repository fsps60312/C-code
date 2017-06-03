#include<cstdio>
#include<cassert>
using namespace std;
const int MOD=1000007;
int ANS[100000];
int DP[100000][3][3];
void AddTo(int &a,const int b){(a+=b)%=MOD;}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<9;i++)DP[0][i/3][i%3]=0;
	for(int i=0;i<3;i++)DP[0][i][i]=1;
	ANS[0]=3;
	for(int i=1;i<100000;i++)
	{
		for(int j=0;j<9;j++)DP[i][j/3][j%3]=0;
		for(int lcolor=0;lcolor<3;lcolor++)
		{
			for(int rcolor=0;rcolor<3;rcolor++)
			{
				for(int newcolor=0;newcolor<3;newcolor++)
				{
					if((rcolor==1&&newcolor==2)||(rcolor==2&&newcolor==1))continue;
					AddTo(DP[i][lcolor][newcolor],DP[i-1][lcolor][rcolor]);
				}
			}
		}
		ANS[i]=0;
		for(int lc=0;lc<3;lc++)for(int rc=0;rc<3;rc++)if(!(lc==1&&rc==2)&&!(lc==2&&rc==1))AddTo(ANS[i],DP[i][lc][rc]);
	}
	static int casenumber;scanf("%d",&casenumber);
	while(casenumber--)
	{
		static int n;scanf("%d",&n);
		assert(n>=1&&n<=100000);
		printf("%d\n",ANS[n-1]);
	}
	return 0;
}
