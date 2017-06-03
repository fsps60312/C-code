#include<cstdio>
#include<cmath>
#include<vector>
const int INF=2147483647;
int N,B;
int GetZero()
{
	int ans=INF;
	int b=B;
	for(int i=2;i*i<=b;i++)
	{
		int cnt=0;
		while(b%i==0)b/=i,cnt++;
		if(cnt>0)
		{
			int n=N,ta=0;
			while(n/=i)ta+=n;
			ta/=cnt;
			if(ta<ans)ans=ta;
		}
	}
	if(b>1)
	{
		int n=N,ta=0;
		while(n/=b)ta+=n;
		if(ta<ans)ans=ta;
	}
	return ans;
}
int GetDigit()
{
	double v=0.0;
	for(int i=1;i<=N;i++)v+=log(i);
	v/=log(B);
	return (int)(v+1e-9)+1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&B)==2)printf("%d %d\n",GetZero(),GetDigit());
	return 0;
}
