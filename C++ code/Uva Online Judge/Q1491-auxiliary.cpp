#include<bits/stdc++.h>
using namespace std;
int DP[5];
//F4:*3
//F3:0000,000,00,0004,004,04,0044,044,44,0444,444,4444   1+15*3+1+7*3+1+3*3=78
//   1+   1+  1+ 12+  9+  6+ 18+  9+  3+ 12+  3+  3=   78
//none :3
//only4:(15+7+3)*3=75
//sum  :78
//F2:
//none :3
//only4:(15+7+3)*3=75
//only3:(15+7+3)*78=1950
//4,3  :()*78
int Test(int dep)
{
	int &dp=DP[dep];
	if(dp!=-1)return dp;
	if(dep==0)return dp=1;
	dp=0;
	int has[dep];
	for(int cnt=4;cnt>=2;cnt--)
	{
		int limit=1;
		for(int i=0;i<cnt;i++)limit*=dep;
		int now[cnt];
		for(int s=0;s<limit;s++)
		{
			for(int i=0;i<dep;i++)has[i]=0;
			for(int i=s,j=0;j<4;j++,i/=dep)has[i%dep]++;
			int ta=-1;
			for(int i=dep-1;i>=0;i--)if(has[i]){ta=Test(i);break;}
			assert(ta!=-1);
			dp+=ta;
		}
	}
	return dp;
}
int main()
{
	for(int i=0;i<=4;i++)DP[i]=-1;
	Test(4);
	for(int i=0;i<=4;i++)printf("DP[%d]=%d\n",i,DP[i]);
	return 0;
}
