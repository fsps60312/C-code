#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct ZValue
{
	char str[3000001];
	int z[3000001];
	void Build(const int n)
	{
		z[0]=0;
		for(int i=1,mx=0;i<n;i++)
		{
			if(mx+z[mx]-1>=i)z[i]=min(mx+z[mx]-1-i+1,z[i-mx]);
			else z[i]=0;
			while(str[i+z[i]]==str[z[i]])z[i]++;
			if(i+z[i]>=mx+z[mx])mx=i;
		}
	}
}POSI,NEGA;
int N;
char A[1000001],B[1000001];
void Solve(vector<int>&ans)
{
	ans.clear();
	if(N==1)
	{
		if(A[0]!=B[0])ans.push_back(0);
		return;
	}
	else if(N==2)
	{
		int cnt0=0,cnt1=0;
		for(int i=0;i<2;i++)
		{
			if(A[i]!=B[i])cnt0++;
			if(A[i]!=B[i^1])cnt1++;
		}
		if(cnt0==1)ans.push_back(0);
		if(cnt1==1)ans.push_back(1);
		return;
	}
	for(int i=0;i<N;i++)
	{
		POSI.str[i]=A[i];
		POSI.str[N+i]=POSI.str[N*2+i]=B[i];
		NEGA.str[i]=A[N-1-i];
		NEGA.str[N+i]=NEGA.str[N*2+i]=B[N-1-i];
	}
	POSI.str[N*3]=NEGA.str[N*3]='\0';
	POSI.Build(N*3),NEGA.Build(N*3);
	for(int i=N;i>0;i--)if(POSI.z[N+i]+NEGA.z[N*2-i]==N-1)ans.push_back(N-i);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s%s",&N,A,B)==3)
	{
		static vector<int>ans;
		Solve(ans);
		if(ans.empty())puts("NIE");
		else
		{
			puts("TAK");
			for(int i=0;i<(int)ans.size();i++)
			{
				if(i)putchar(' '),assert(ans[i-1]<ans[i]);
				printf("%d",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
