#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct List
{
	vector<int>L,R,S;
	int BEGIN,END,SZ;
	List()
	{
		L.clear(),R.clear(),S.clear();
		L.push_back(-1),R.push_back(-1),S.push_back(-1);
		BEGIN=END=0,SZ=1;
	}
	void Expand(){L.push_back(-1),R.push_back(-1),S.push_back(-1),++SZ;}
	void PushBack(const int v)
	{
		Expand();
		S[END]=v;
		R[END]=SZ-1;
		L[SZ-1]=END;
		END=SZ-1;
	}
};
int Sks(const int n)
{
	int ans=0;
	int d=0;
	while((1<<(d+1))<=n)d++;
	if(d==0)return 1;
	ans+=(1<<d)-(d-1);
	if(n&(1<<(d-1)))ans+=(1<<(d-1))-1;
	else ans+=n&((1<<(d-1))-1);
//	printf("ans=%d\n",ans);
	for(int i=d-2,v=0;i>=0;i--)
	{
		if((n&((1<<(i+2))-1))>=(1<<i))ans+=v+1;
		else ans+=v;
		v=(v<<1)+((n>>(i+1))&1);
	}
	return ans;
}
int N,S[1000000],LOC[1000000];
int main()
{
	freopen("in.txt","r",stdin);
	for(;scanf("%d",&N)==1;)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int sum=0;
		for(int i=N-1;i>=0;i--)LOC[i]=(sum+=S[i]);
		if(sum==1){printf("1\n1\n");continue;}
		vector<List>anses;
		int adjust=0;
		if(true)
		{
			List s;
			s.PushBack(1);
			s.PushBack(sum-1);
			anses.push_back(s);
			adjust-=(sum-2);
		}
		if(S[0]>=2)
		{
			if(sum>2)
			{
				List s;
				s.PushBack(sum-2);
				anses.push_back(s);
			}
		}
		else
		{
			if(N>=3)
			{
				List s;
				for(int i=2;i<N;i++)s.PushBack(S[i]);
				anses.push_back(s);
			}
		}
		for(int i=0;i<N;i+=2)
		{
			List s;
			s.PushBack(S[i]);
			s.PushBack(LOC[i]-S[i]+1);
			adjust-=(S[i]-1);
		}
		
	}
	return 0;
}
