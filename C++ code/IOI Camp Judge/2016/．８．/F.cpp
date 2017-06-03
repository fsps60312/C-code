#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Deq
{
	int data[2000002],l,r;
	void clear(){l=0,r=-1;}
	int front()const{return data[l];}
	int back()const{return data[r];}
	void push_back(const int v){data[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	bool empty(){return r<l;}
}DEQ;
void BuildZ(const char *s,int *z)
{
	z[0]=0;
	for(int i=1,mx=0;s[i];i++)
	{
		if(mx+z[mx]>=i)z[i]=min(z[i-mx],mx+z[mx]-i);
		else z[i]=0;
		while(s[i+z[i]]==s[z[i]])z[i]++;
		if(i+z[i]>=mx+z[mx])mx=i;
	}
}
int N;
char A[1000001],B[1000001],S[2000002];
int Z1[2000002],Z2[2000002],Z3[2000002];
int DP[2000002];
void Solve(int &ans1,int &ans2)
{
	for(int i=N*2+2-Z2[N+1];i<N*2+2;i++)if(DP[i]!=-1)
	{
		if(Z3[N+1+(N*2+2-i)]>=DP[i]-N)
		{
			ans1=N*2+1-i,ans2=N-(i-DP[i]);
			return;
		}
	}
	ans1=ans2=-1;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s%s",A,B);
		N=-1;while(A[++N]);
		if(true)
		{
			int n=-1;while(B[++n]);
			if(N!=n){puts("-1,-1");continue;}
		}
		
		for(int i=0;i<N;i++)S[i]=A[N-1-i];
		S[N]=1;
		for(int i=0;i<N;i++)S[N+1+i]=B[i];
		S[N+1+N]=0;
		BuildZ(S,Z1);
		
		for(int i=0;i<N;i++)S[i]=B[N-1-i];
		S[N]=1;
		for(int i=0;i<N;i++)S[N+1+i]=A[i];
		S[N+1+N]=0;
		BuildZ(S,Z2);
		
		for(int i=0;i<N;i++)S[i]=B[i];
		S[N]=1;
		for(int i=0;i<N;i++)S[N+1+i]=A[i];
		S[N+1+N]=0;
		BuildZ(S,Z3);
		
		DEQ.clear();
		for(int i=0;i<N*2+2;i++)
		{
			if(DEQ.empty()||i+Z1[i]>DEQ.back()+Z1[DEQ.back()])DEQ.push_back(i);
			while(!DEQ.empty()&&DEQ.front()+Z1[DEQ.front()]<i)DEQ.pop_front();
			if(DEQ.empty())DP[i]=-1;
			else DP[i]=DEQ.front();
		}
		int ans1,ans2;
		Solve(ans1,ans2);
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
