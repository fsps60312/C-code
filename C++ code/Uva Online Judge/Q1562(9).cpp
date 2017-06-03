#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
LL T;
char INPUT[201];
map<LL,LL>IDX;
vector<LL>RI;
LL Gcd(const LL a,const LL b){return b?Gcd(b,a%b):a;}
LL GetIdx(const LL v)
{
	auto it=IDX.find(v);
	if(it==IDX.end())
	{
		const LL sz=IDX.size();
		RI.push_back(v);
		return IDX[v]=sz;
	}
	return it->second;
}
bool Upper(const char c){return c>='A'&&c<='Z';}
bool Lower(const char c){return c>='a'&&c<='z';}
bool Digit(const char c){return c>='0'&&c<='9';}
struct Atom
{
	LL type,cnt;
	Atom(){}
	Atom(const LL _t,const LL _c):type(_t),cnt(_c){}
};
vector<vector<Atom> >E;
void Initialize()
{
	IDX.clear(),RI.clear(),E.clear();
	vector<Atom>molecule;
	for(LL i=0,sign=1;;i++)
	{
		switch(INPUT[i])
		{
			case'+':
			case'=':
			case'\0':E.push_back(molecule),molecule.clear();break;
		}
		if(INPUT[i]=='\0')break;
		else if(INPUT[i]=='=')assert(sign==1),sign=-1;
		else if(Upper(INPUT[i]))
		{
			LL type=(int)INPUT[i]*256;
			if(Lower(INPUT[i+1]))type+=INPUT[++i];
			LL cnt=1;
			if(Digit(INPUT[i+1]))
			{
				cnt=0;
				while(Digit(INPUT[i+1]))cnt=cnt*10+(INPUT[++i]-'0');
			}
			molecule.push_back(Atom(GetIdx(type),cnt*sign));
		}
	}
}
struct Matrix
{
	LL r,c;
	vector<vector<LL> >s;
	void resize(const LL _r,const LL _c){r=_r,c=_c;s.resize(r);for(auto &v:s)v.resize(c+1);}
	Matrix(const LL _r,const LL _c){resize(_r,_c);}
	void Swap(const LL r1,const LL r2){for(LL i=0;i<=c;i++)swap(s[r1][i],s[r2][i]);}
	void Reduce(const LL _r)
	{
		LL g=0;
		for(LL i=0;i<=c;i++)g=Gcd(g,abs(s[_r][i]));
		if(g)for(LL i=0;i<=c;i++)s[_r][i]/=g;
	}
	void Eliminate(const LL r1,const LL r2,const LL _c)
	{
		assert(s[r1][_c]);
		if(s[r2][_c]==0)return;
		LL g=Gcd(abs(s[r1][_c]),abs(s[r2][_c])),v1=s[r1][_c]/g,v2=s[r2][_c]/g;
		assert(s[r1][_c]*v2==s[r2][_c]*v1);
		for(LL i=0;i<=c;i++)s[r2][i]=s[r2][i]*v1-s[r1][i]*v2;
		Reduce(r2);
		assert(!s[r2][_c]);
	}
	bool Empty(const LL r){for(LL i=0;i<c;i++)if(s[r][i])return false;return true;}
	void Print()
	{
		for(LL i=0;i<r;i++)
		{
			for(LL j=0;j<=c;j++)printf(" %d",s[i][j]);puts("");
		}
//		puts("");
	}
};
LL RowOperation(Matrix &m)
{
	if(m.c>m.r)return 2;
	for(LL i=0;i<m.c;i++)
	{
		if(!m.s[i][i])
		{
			bool found=false;
			for(LL j=i+1;j<m.r;j++)if(m.s[j][i]){m.Swap(i,j),found=true;break;}
			if(!found)continue;
		}
		for(LL j=i+1;j<m.r;j++)m.Eliminate(i,j,i);
	}
	for(LL i=m.c-1;i>=0;i--)if(m.s[i][i])for(LL j=i-1;j>=0;j--)m.Eliminate(i,j,i);
//	m.Print();
	bool found=false;
	for(LL i=0;i<m.c;i++)if(m.Empty(i)&&m.s[i][m.c])return 0;
//	puts("a");
	for(LL i=m.c;i<m.r;i++)
	{
		assert(m.Empty(i));
		if(m.s[i][m.c])return 0;
	}
//	puts("b");
	for(LL i=0;i<m.c;i++)
	{
		if(!m.s[i][i])return 2;
		const LL v=m.s[i][i];m.s[i][i]=0;
		if(!m.Empty(i))return 2;
		m.s[i][i]=v;
		if(m.s[i][m.c]%m.s[i][i]!=0)return 0;
		else
		{
			const LL v=m.s[i][m.c]/m.s[i][i];
			if(v<1||v>9)return 0;
		}
	}
//	puts("c");
	return 1;
}
vector<LL>ANS;
bool Dfs(const LL dep)
{
	const LL column=E.size()-1-dep;
	Matrix m=Matrix(IDX.size(),column);
	for(LL &ans=ANS[dep]=1;ans<=9;ans++)
	{
		for(LL i=0;i<IDX.size();i++)for(LL j=0;j<=column;j++)m.s[i][j]=0LL;
		for(LL i=0;i<=dep;i++)for(const Atom &a:E[i])m.s[a.type][column]-=a.cnt*ANS[i];
		for(LL i=dep+1;i<E.size();i++)for(const Atom &a:E[i])m.s[a.type][i-1-dep]+=a.cnt;
//		m.Print();
		LL result=RowOperation(m);
//		printf("result=%d\n",result);
		if(result==0)continue;
		else if(result==1)
		{
			for(LL i=0;i<column;i++)ANS[dep+1+i]=m.s[i][column]/m.s[i][i];
			return true;
		}
		else if(Dfs(dep+1))return true;
	}
	return false;
}
int main()
{
//	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%s",&INPUT);
		Initialize();
		ANS.resize(E.size());
		if(!Dfs(0))puts("IMPOSSIBLE");
		else
		{
			for(LL i=0;i<E.size();i++)
			{
				if(i)putchar(' ');
				printf("%lld",ANS[i]);
			}
			puts("");
		}
	}
	return 0;
}
/*
1
AcF3+Li=LiF+Ac
Al+HCl+OH+H2O=AlCl3+H2O
Al+3HCl+3OH+H2O=AlCl3+4H2O
1 3 3 1 1 4
*/
