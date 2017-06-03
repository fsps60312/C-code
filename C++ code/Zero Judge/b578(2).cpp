#include<bits/stdc++.h>
using namespace std;
unsigned long long S[3][2],A[3][2];
int Solve()
{
	int cnt=-1;
	for(int i=0;i<3;i++)
	{
		for(int j=i+1;j<3;j++)
		{
			cnt++;
			A[cnt][0]=S[i][0]+S[j][0];
			A[cnt][1]=S[i][1]+S[j][1];
			if(A[cnt][1]<S[i][1]||A[cnt][1]<S[j][1])A[cnt][0]++;
			int k=3-i-j;
			if(A[cnt][0]==S[k][0]&&A[cnt][1]==S[k][1])return 1;
			if(A[cnt][0]<S[k][0]||(A[cnt][0]==S[k][0]&&A[cnt][1]<S[k][1]))return 2;
		}
	}
	return 0;
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		for(int i=0;i<3;i++)
		{
			scanf("%llu",&S[i][1]);
			S[i][0]=A[i][0]=A[i][1]=0;
			S[i][1]*=S[i][1];
			if(S[i][1]==0)S[i][0]=1;
		}
		int ans=Solve();
		if(ans==0)puts("acute triangle");
		else if(ans==1)puts("right triangle");
		else puts("obtuse triangle");
	}
	return 0;
}
