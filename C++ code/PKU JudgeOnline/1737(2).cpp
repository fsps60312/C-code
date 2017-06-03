#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
__int128 CONNECT[51],UNCONNECT[51],ALL[51],C[51][51];
int main()
{
	for(int i=1;i<=50;i++)
	{
		C[i][0]=C[i][i]=1LL;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	ALL[0]=1LL;
	for(int i=1;i<=50;i++)ALL[i]=((__int128)1LL<<(i*(i-1)/2));
	CONNECT[1]=1LL,UNCONNECT[1]=0LL;
	for(int n=2;n<=50;n++)
	{
		__int128 &ans=UNCONNECT[n]=0LL;
		for(int i=1;i<n;i++)ans+=C[n-1][i-1]*CONNECT[i]*ALL[n-i];
		CONNECT[n]=ALL[n]-ans;
//		printf("%d\t%d\n",(int)CONNECT[n],(int)UNCONNECT[n]);
	}
//	freopen("in.txt","r",stdin);
	for(int n;scanf("%d",&n)==1&&n;)
	{
		__int128 cnt=CONNECT[n];
		vector<int>ans;
		while(cnt)ans.push_back(cnt%10),cnt/=10;
		for(int i=(int)ans.size()-1;i>=0;i--)putchar('0'+ans[i]);puts("");
	}
	return 0;
}
