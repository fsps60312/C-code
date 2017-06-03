#include<bits/stdc++.h>
using namespace std;
int N,A[20][20],B[20][20];
int main()
{
	static int x,y,c;
	for(int i=1;i<=19;i++)for(int j=1;j<=19;j++)A[i][j]=B[i][j]=2;
	scanf("%d",&N);
	while(N--)
	{
		scanf("%d%d%d",&x,&y,&c);
		if(c==2)continue;
		A[x][y]=c;
	}
	scanf("%d",&N);
	while(N--)
	{
		scanf("%d%d%d",&x,&y,&c);
		if(c==2)continue;
		B[x][y]=c;
	}
	int ans=0;
	for(int i=1;i<=19;i++)for(int j=1;j<=19;j++)
	{
		int &a=A[i][j],&b=B[i][j];
		if(a==b)continue;
		if(a+b==1)ans+=2;
		else ans++;
	}
	printf("%d\n",ans);
	return 0;
}
