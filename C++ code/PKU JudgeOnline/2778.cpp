#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
typedef long long LL;
const LL MOD=100000;
int N,M;
struct Matrix
{
	int s[101][101];
	Matrix operator*(const Matrix &m)const
	{
		Matrix ans;
		for(int i=0;i<M;i++)for(int j=0;j<M;j++)
		{
			int &v=ans.s[i][j]=0;
			for(int k=0;k<M;k++)v=(v+(LL)s[i][k]*m.s[k][j])%MOD;
		}
		return ans;
	}
};
struct AC_Automaton
{
	int ch[101][4],sz;
	bool is_end[101];
	void Clear(){sz=0;Expand();}
	void Expand(){for(int i=0;i<4;i++)ch[sz][i]=0;is_end[sz++]=false;}
	int GetNxt(const int u,const int c)
	{
		if(ch[u][c]==0){Expand();ch[u][c]=sz-1;}
		return ch[u][c];
	}
	int GetID(const char c)
	{
		switch(c)
		{
			case'A':return 0;
			case'C':return 1;
			case'G':return 2;
			case'T':return 3;
			default:assert(0);return -1;
		}
	}
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
		for(int i=0;i<4;i++)if(ch[0][i])fail[ch[0][i]]=0,q.push(ch[0][i]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<4;i++)if(ch[u][i])
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
		M=sz;
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<M;j++)ans.s[i][j]=0;
			for(int c=0;c<4;c++)
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
Matrix Pow(Matrix a,int p)
{
	Matrix ans;
	for(int i=0;i<M;i++)for(int j=0;j<M;j++)ans.s[i][j]=(i==j?1:0);
	for(;p;a=a*a,p>>=1)if(p&1)ans=ans*a;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&M,&N);
	AC.Clear();
	for(int i=0;i<M;i++)
	{
		static char dna[11];scanf("%s",dna);
		AC.Insert(dna);
	}
	AC.BuildFail();
	const Matrix &m=Pow(AC.GetMatrix(),N);
	int ans=0;
	for(int i=0;i<M;i++)(ans+=m.s[0][i])%=MOD;
	printf("%d\n",ans);
	return 0;
}
