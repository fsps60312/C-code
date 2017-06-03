#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void GetS(char *str,int &n)
{
	assert(fgets(str,INF,stdin));
	for(n=0;str[n];n++)if(str[n]=='\n'){str[n]='\0';break;}
}
void BuildPalindrome(const char *str,const int n,int *dp)
{
	vector<char>tmp;
	tmp.push_back('\0');
	for(int i=0;i<n;i++)tmp.push_back(str[i]),tmp.push_back('\0');
	dp[0]=1;
	for(int i=1,mx=0;i<n*2+1;i++)
	{
		if(mx+dp[mx]-1>i)dp[i]=min(dp[mx-(i-mx)],mx+dp[mx]-1-i+1);
		else dp[i]=1;
		while(i-dp[i]>=0&&i+dp[i]<n*2+1&&tmp[i-dp[i]]==tmp[i+dp[i]])dp[i]++;
		if(i+dp[i]>mx+dp[mx])mx=i;
	}
}
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][300000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int p=256;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=str[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int idx=0;
		for(int i=n-move;i<n;i++)y[idx++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[idx++]=sa[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0,x[sa[0]]=p++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]])x[sa[i]]=p++;
			else if((sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=p++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?p-1:p++);
		}
		if(p==n)break;
	}
}
void BuildHeight(const char *str,const int n,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)ans--;
		if(rank[i]==0){height[0]=0;continue;}
		int j=sa[rank[i]-1];
		while(str[i+ans]==str[j+ans])ans++;
		height[rank[i]]=ans;
	}
}
bool IsPalindrome(const int *dp,const int idx,const int len)
{
	//idx*2+1, ..., (idx+idx+len-1)+1, ..., (idx+len-1)*2+1
	//((idx+len-1)*2+1)-((idx+idx+len-1)+1)+1
	//=idx+idx+len+len-1-(idx+idx+len)+1
	//=len
	return dp[(idx+idx+len-1)+1]>=len;
}
int T,N;
char S[300002];
int DP[600001];
int SA[300000],RANK[300000],HEIGHT[300000];
bool Solve(const int h)
{
	if(!h)return true;
	assert(h%2==0);
	for(int i=1;i<N;)
	{
		if(HEIGHT[i]<h||!IsPalindrome(DP,SA[i-1],h)){i++;continue;}
		else
		{
			vector<int>idx;
			idx.push_back(SA[i-1]);
			for(;i<N&&HEIGHT[i]>=h;i++)idx.push_back(SA[i]);
			sort(idx.begin(),idx.end());
			for(int j=1;j<(int)idx.size();j++)if(idx[j]-idx[j-1]==h)return true;
		}
	}
	return false;
}
int main()
{
	assert(fgets(S,INF,stdin)&&sscanf(S,"%d",&T)==1);
	while(T--)
	{
		GetS(S,N);
		BuildPalindrome(S,N,DP);
		BuildSa(S,N,SA);
		BuildHeight(S,N,SA,RANK,HEIGHT);
//		for(int i=0;i<N*2+1;i++)printf(" %d",DP[i]);puts("");
//		for(int i=0;i<N;i++)printf(" %d",SA[i]);puts("");
//		for(int i=0;i<N;i++)printf(" %d",HEIGHT[i]);puts("");
//		printf("N=%d\n",N);
		for(int ans=N/2-N/2%2;;ans-=2)if(Solve(ans)){printf("%d\n",ans*2);break;}
	}
	return 0;
}
