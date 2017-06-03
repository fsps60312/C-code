#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
typedef unsigned long long ULL;
int N,L;
struct Matrix
{
	ULL s[26][26];
	Matrix operator*(const Matrix &m)const
	{
		Matrix ans;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			ULL &v=ans.s[i][j]=0;
			for(int k=0;k<N;k++)v+=s[i][k]*m.s[k][j];
		}
		return ans;
	}
	Matrix operator+(const Matrix &m)const
	{
		Matrix ans;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.s[i][j]=s[i][j]+m.s[i][j];
		return ans;
	}
};
struct AC_Automaton
{
	int ch[26][26],sz;
	bool is_end[26];
	void Clear(){sz=0;Expand();}
	void Expand(){for(int i=0;i<26;i++)ch[sz][i]=0;is_end[sz++]=false;}
	int GetNxt(const int u,const int c)
	{
		if(ch[u][c]==0){Expand();ch[u][c]=sz-1;}
		return ch[u][c];
	}
	int GetID(const char c){return c-'a';}
	void Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,GetID(str[i]));
		is_end[u]=true;
	}
	int fail[101];
	void BuildFail()
	{
		fail[0]=0;
		queue<int>q;
		for(int i=0;i<26;i++)if(ch[0][i])fail[ch[0][i]]=0,q.push(ch[0][i]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<26;i++)if(ch[u][i])
			{
				int &f=fail[ch[u][i]]=fail[u];
				while(f&&ch[f][i]==0)f=fail[f];
				f=ch[f][i];
				is_end[ch[u][i]]|=is_end[f];
				q.push(ch[u][i]);
			}
		}
	}
	Matrix GetMatrix()
	{
		Matrix ans;
		N=sz;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)ans.s[i][j]=0;
			for(int c=0;c<26;c++)
			{
				int u=i;
				while(u&&ch[u][c]==0)u=fail[u];
				u=ch[u][c];
				if(is_end[u])continue;
				ans.s[i][u]++;
			}
		}
		return ans;
	}
}AC;
Matrix I()
{
	Matrix ans;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.s[i][j]=(i==j?1:0);
	return ans;
}
Matrix Pow(Matrix a,int p)
{
	Matrix ans=I();
	for(;p;a=a*a,p>>=1)if(p&1)ans=ans*a;
	return ans;
}
Matrix GetSum(const Matrix &m,const int n)
{
	if(n==0)return I();
	const int mid=((long long)n+1)/2;//notice n=2147483647
	const Matrix &ans=GetSum(m,mid-1)*(I()+Pow(m,mid));
	if(n&1)return ans;
	else return ans+Pow(m,n);
}
//  S=26^0+26^1+26^2+26^3+...+26^n
//26S=26^1+26^2+26^3+26^4+...+26^(n+1)
//25S=26^(n+1)-1
ULL Pow26(int p)
{
	ULL ans=1,a=26;
	for(;p;a*=a,p>>=1)if(p&1)ans*=a;
	return ans;
}
ULL GetSum(const int n)
{
	if(n==0)return 1;
	const int mid=((long long)n+1)/2;//notice n=2147483647
	const ULL &ans=GetSum(mid-1)*(1+Pow26(mid));
	if(n&1)return ans;
	else return ans+Pow26(n);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&L)==2)
	{
		AC.Clear();
		for(int i=0;i<N;i++)
		{
			static char word[11];scanf("%s",word);
			AC.Insert(word);
		}
		AC.BuildFail();
		const Matrix &m=GetSum(AC.GetMatrix(),L);
		ULL ans=GetSum(L);
		for(int i=0;i<N;i++)ans-=m.s[0][i];
		printf("%llu\n",ans);
	}
	return 0;
}
