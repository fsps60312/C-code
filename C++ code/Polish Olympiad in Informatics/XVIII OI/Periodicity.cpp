#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
void GetZ(const int n,const char *s,int *z)
{
	z[0]=0;
	for(int i=1,mx=0;i<n;i++)
	{
		if(mx+z[mx]-1>=i)z[i]=min(mx+z[mx]-1-i+1,z[i-mx]);
		else z[i]=0;
		while(s[z[i]]==s[i+z[i]]&&i+z[i]<n)++z[i];
		if(i+z[i]>=mx+z[mx])mx=i;
	}
}
int N;
char S[200001];
bool Find(vector<int>&s,const int v)
{
	vector<int>::iterator it=lower_bound(s.begin(),s.end(),v);
	if(it==s.end())return false;
	return (*it)==v;
}
bool Solve(vector<char>&ans)
{
	static int z[200000];
	GetZ(N,S,z);
	vector<int>periods;
	for(int i=0;i<N;i++)if(i+z[i]==N)periods.push_back(i),printf(" %d",i);puts("");
	periods.push_back(N);
	ans.clear();
	for(int i=0;i<(int)periods.size();i++)
	{
		const int n=(int)ans.size();
		if(periods[i]<=n*2)
		{
			for(int j=n;j<periods[i];j++)ans.push_back(ans[j-(periods[i]-n)]);
		}
		else
		{
			for(int j=periods[i]-n*2;j--;)ans.push_back('0');
			for(int j=0;j<n;j++)ans.push_back(ans[j]);
			GetZ(periods[i],&ans[0],z);
			for(int j=0;j<periods[i];j++)if(j+z[j]==periods[i])
			{
				if(!Find(periods,j))
				{
					ans[periods[i]-n-1]='1';
					break;
				}
			}
		}
		assert((int)ans.size()==periods[i]);
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		N=-1;while(S[++N]);
		vector<char>ans;
		if(Solve(ans))
		{
			ans.push_back('\0');
			printf("%s\n",&ans[0]);
			static int z[200000];GetZ(N,&ans[0],z);
			for(int i=0;i<N;i++)if(i+z[i]==N)printf(" %d",i);puts("");
		}
		else puts("XXX");
	}
	return 0;
}
