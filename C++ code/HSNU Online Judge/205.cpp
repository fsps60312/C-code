#include<bits/stdc++.h>
using namespace std;
const int MOD=12345;
int N,S[1500],DP[1500][2];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	DP[0][0]=DP[0][1]=1;
	int ans=0;
	for(int i=1;i<N;i++)
	{
		DP[i][0]=DP[i][1]=1;
		for(int j=0;j<i;j++)
		{
			if(S[j]<S[i])DP[i][0]+=DP[j][1];
			if(S[j]>S[i])DP[i][1]+=DP[j][0];
		}
//		printf("%d: %d %d\n",i,DP[i][0]-1,DP[i][1]-1);
		ans+=DP[i][0]+DP[i][1]-2;
		ans%=MOD;
		DP[i][0]%=MOD;
		DP[i][1]%=MOD;
	}
	vector<int>vv,vc;
	sort(S,S+N);
	int v=S[0],c=0;
	for(int i=0;i<N;i++)
	{
		if(S[i]==v)c++;
		else
		{
			vv.push_back(v),vc.push_back(c);
			v=S[i],c=1;
		}
	}
	vv.push_back(v),vc.push_back(c);
	for(int i=0;i<vv.size();i++)
	{
		for(int j=i+1;j<vv.size();j++)ans-=vc[i]*vc[j];
	}
	printf("%d\n",(ans%MOD+MOD)%MOD);
	return 0;
}
