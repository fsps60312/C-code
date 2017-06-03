#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int N,A[20],C[20];
bool Valid(const int x)
{
	for(int i=1;i<N;i++)
	{
		if((A[i-1]/x==A[i]/x)!=(C[i-1]==C[i]))return false;
	}
	return true;
}
struct State
{
	int loc,val;
	State(){}
	State(const int _loc,const int _val):loc(_loc),val(_val){}
	bool operator<(const State &a)const{return val/loc<a.val/a.loc;}
};
int Solve()
{
	for(int i=0;i<N;i++)for(int j=i+2;j<N;j++)if(C[i]==C[j])
	{
		for(int k=i+1;k<j;k++)if(C[k]!=C[i])return 0;
	}
	//A[i]/x
	vector<int>s;
//	puts("c");
	for(int i=0;i<N;i++)
	{
		for(int x=1;;)
		{
			s.push_back(x);
//			const int v=A[i]/x;
			if(x>=A[i])break;
//			puts("a");
			assert(A[i]/(x+1));
			const int pre_x=x;
			x=A[i]/(A[i]/(x+1));
//			puts("b");
			assert(A[i]/pre_x!=A[i]/x);
			assert(A[i]/pre_x!=A[i]/(pre_x+1));
		}
	}
	s.push_back(0);
//	puts("d");
	sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
	if(Valid(s.back()+1))return -1;
	else
	{
		int ans=0;
		for(int i=1;i<(int)s.size();i++)
		{
			if(Valid(s[i]))ans+=s[i]-s[i-1];
		}
		return ans;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&A[i],&C[i]),--A[i];
		printf("%d\n",Solve());
	}
	return 0;
}
