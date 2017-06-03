#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int T;
char INPUT[201];
map<int,int>IDX;
vector<int>RI;
LL Gcd(const LL a,const LL b){return b?Gcd(b,a%b):a;}
int GetIdx(const int v)
{
	auto it=IDX.find(v);
	if(it==IDX.end())
	{
		const int sz=IDX.size();
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
	int type,cnt;
	Atom(){}
	Atom(const int _t,const int _c):type(_t),cnt(_c){}
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
struct Fraction
{
	LL up,down;
	Fraction():up(0LL),down(1LL){}
	Fraction(const LL _v):up(_v),down(1LL){}
	Fraction(const LL _u,const LL _d):up(_u),down(_d){Reduce();}
	void Reduce()
	{
		if(down<0)up*=-1LL,down*=-1LL;
		LL g=Gcd(abs(up),abs(down));
		up/=g,down/=g;
	}
	bool operator==(const Fraction &f)const{return up==f.up&&down==f.down;}
	bool operator!=(const Fraction &f)const{return up!=f.up||down!=f.down;}
	Fraction operator*(const Fraction &f)const{return Fraction(up*f.up,down*f.down);}
	Fraction operator/(const Fraction &f)const{return Fraction(up*f.down,down*f.up);}
	Fraction operator-(const Fraction &f)const{return Fraction(up*f.down-f.up*down,down*f.down);}
	Fraction operator+(const Fraction &f)const{return Fraction(up*f.down+f.up*down,down*f.down);}
	Fraction &operator-=(const Fraction &f){return (*this)=(*this)-f;}
	Fraction &operator+=(const Fraction &f){return (*this)=(*this)+f;}
	void Print(){if(down==1LL)printf("%lld",up);else printf("%lld/%lld",up,down);}
};
struct Matrix
{
	int r,c;
	vector<vector<Fraction> >s;
	void resize(const int _r,const int _c){r=_r,c=_c;s.resize(r);for(auto &v:s)v.resize(c+1);}
	Matrix(const int _r,const int _c){resize(_r,_c);}
	void Swap(const int r1,const int r2){for(int i=0;i<=c;i++)swap(s[r1][i],s[r2][i]);}
	void Sub(const int r1,const int r2,const Fraction &ratio){for(int i=0;i<=c;i++)s[r1][i]-=s[r2][i]*ratio;}
	bool Empty(const int _r,const int _c=-1){for(int i=0;i<c;i++)if(i!=_c&&s[_r][i]!=0)return false;return true;}
	void Print()
	{
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<=c;j++)putchar(' '),s[i][j].Print();
			puts("");
		}
		puts("");
	}
};
int RowOperation(Matrix &m)
{
//	m.Print();
	if(m.c>m.r)return 2;
//	m.Print();
	for(int i=0;i<m.c;i++)
	{
		if(m.s[i][i]==0)
		{
			bool found=false;
			for(int j=i+1;j<m.r;j++)if(m.s[j][i]!=0){m.Swap(i,j),found=true;break;}
			if(!found)continue;
		}
		for(int j=i+1;j<m.r;j++)m.Sub(j,i,m.s[j][i]/m.s[i][i]);
	}
//	m.Print();
	for(int i=m.c-1;i>=0;i--)if(m.s[i][i]!=0)for(LL j=i-1;j>=0;j--)m.Sub(j,i,m.s[j][i]/m.s[i][i]);
//	m.Print();
	bool found=false;
	for(int i=0;i<m.c;i++)if(m.Empty(i)&&m.s[i][m.c]!=0)return 0;
	for(int i=m.c;i<m.r;i++)
	{
		assert(m.Empty(i));
		if(m.s[i][m.c]!=0)return 0;
	}
	for(int i=0;i<m.c;i++)
	{
		if(m.s[i][i]==0)return 2;
		if(!m.Empty(i,i))return 2;
	}
	return 1;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",&INPUT);
		Initialize();
		Matrix m=Matrix(IDX.size(),E.size()-1);
		for(int i=0;i<E.size();i++)for(const auto &a:E[i])
		{
			if(i)m.s[a.type][i-1]+=a.cnt;
			else m.s[a.type][m.c]-=a.cnt;
		}
		int result=RowOperation(m);
		if(result==0)puts("Impossible");
		else if(result==2)puts("Multiple Solutions");
		else
		{
			vector<Fraction>ans;
			for(int i=0;i<m.c;i++)ans.push_back(m.s[i][m.c]/m.s[i][i]);
			LL lcm=1LL;
			for(int i=0;i<ans.size();i++)lcm=lcm/Gcd(lcm,ans[i].down)*ans[i].down;
			printf("%lld",lcm);
			for(int i=0;i<ans.size();i++)
			{
				printf(" %lld",lcm/ans[i].down*ans[i].up);
			}
			puts("");
		}
	}
	return 0;
}
/*
6
HCl+CaO2H2=CaCl2+H2O
HCl+NaOH=NaCl+H2O
HCl+H2SO4=NaCl
AcF3+Li=LiF+Ac
Al+HCl+OH+H2O=AlCl3+H2O
K2Cr2O7+C2H5OH+H2SO4=Cr2S3O12+CH3COOH+K2SO4+H2O
*/
