#include<bits/stdc++.h>
using namespace std;
int T,N,S[101];
bool TAG[101];
bool All4()
{
	int sum=0;
	for(int i=1;i<=N;i++)
	{
		if(TAG[i]==mx)
		{
			if(sum%4)return false;
			sum=0;
		}
		else sum+=mx-S[i];
	}
	return sum%4==0;
}
struct Ans
{
	int type,column;
	Ans(){}
	Ans(const int &t,const int &c):type(t),column(c){}
};
vector<int>ANS;
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			ANS.clear();
			for(int i=1;i<=N;i++)
			{
				scanf("%d",&S[i]);
				TAG[i]=false;
			}
			for(int i=2;i<N;i++)
			{
				while(S[i-1]-S[i]>=3&&S[i+1]-S[i]>=3)
				{
					printf("1 %d\n",i);
					S[i]+=4;
				}
			}
			int mx=0;
			for(int i=1;i<=N;i++)mx=max(mx,S[i]);
			if(All4())
			{
				for(int l=1,r;;)
				{
					while(l<=N&&TAG[l])l++;
					if(l>N)break;
					for(r=l;r<=N&&!TAG[r];r++);r--;
					for(int i=l;i<=r;i++)
					{
						
					}
				}
			}
			printf("-1 -1");
		}
	}
	return 0;
}
