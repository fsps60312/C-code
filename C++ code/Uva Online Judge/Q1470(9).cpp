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
struct Sparser
{
	int sparse[21][600001],type,n;
	void Build(const int *s,const int _n,const int _type)
	{
		n=_n,type=_type;
		for(int i=0;i<n;i++)sparse[0][i]=s[i];
		for(int d=1;(1<<d)<=n;d++)
		{
			assert(d<21);
			for(int i=0;i+(1<<d)<=n;i++)
			{
				if(type==-1)sparse[d][i]=min(sparse[d-1][i],sparse[d-1][i+(1<<(d-1))]);
				else if(type==1)sparse[d][i]=max(sparse[d-1][i],sparse[d-1][i+(1<<(d-1))]);
				else printf("type=%d\n",type),assert(0);
			}
		}
	}
	int Query(const int a,const int b)const
	{
		assert(a>=0&&a<n&&b>=0&&b<n);
		int d=0;
		while((1<<(d+1))<=b-a+1)d++;
		if(type==-1)return min(sparse[d][a],sparse[d][b-(1<<d)+1]);
		else if(type==1)return max(sparse[d][a],sparse[d][b-(1<<d)+1]);
		else{assert(0);return -1;}
	}
}MXP;
struct StringMatcher
{
	Sparser sparser;
	int sa[300000],rank[300000],height[300000],n;
	void Build(const char *str,const int _n)
	{
		n=_n;
		BuildSa(str,n,sa);
		BuildHeight(str,n,sa,rank,height);
		sparser.Build(height,n,-1);
	}
	int Match(const int a,const int b)const
	{
		assert(a!=b);
		if(a>=n||b>=n)return 0;
		assert(a>=0&&b>=0);
		int ra=rank[a],rb=rank[b];
		if(ra>rb)swap(ra,rb);
		return sparser.Query(ra+1,rb);
	}
}LSM,RSM;
bool Solve(const int n,const int h)
{
	if(!h)return true;
	assert(h%2==0);
	for(int i=0;i+h*2<=n;i+=h)
	{
		const int lspan=LSM.Match(n-1-(i+h*2-1),n-1-(i+h-1)),rspan=RSM.Match(i+h,i+h*2);
		if(lspan+rspan>=h)
		{
			const int from=((i+h-1-lspan+1)*2+1)+(h*2)-1;
			const int to=((i+h*2+rspan-1)*2+1)-(h*2)+1;
			if(MXP.Query(from,to)>=h*2+1)return true;
		}
	}
	return false;
}
#include<ctime>
int main()
{
	freopen("in.txt","r",stdin);
	static char str[300002];
	static int caseremain,dp[600001];
	assert(fgets(str,INF,stdin)&&sscanf(str,"%d",&caseremain)==1);
	while(caseremain--)
	{
		static int n;
		auto start=clock();
		for(int i=0;i<100000000;i++);
		printf("Runtime for 1e8: %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
		start=clock();
		GetS(str,n);
		printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
		start=clock();
		BuildPalindrome(str,n,dp);
		printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
		start=clock();
		MXP.Build(dp,n*2+1,1);
		printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
		start=clock();
		RSM.Build(str,n);
		printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
		start=clock();
		for(int i=0;i<n-1-i;i++)swap(str[i],str[n-1-i]);
		LSM.Build(str,n);
		printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
		start=clock();
		for(int ans=n/2-n/2%2;;ans-=2)if(Solve(n,ans))
		{
			printf("%.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
			printf("%d\n",ans*2);
			break;
		}
	}
	return 0;
}
