#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
int T;
char INPUT[201];
map<int,int>IDX;
int GetIdx(const int v)
{
	auto it=IDX.find(v);
	if(it==IDX.end())
	{
		const int sz=IDX.size();
		return IDX[it]=sz;
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
	IDX.clear(),E.clear();
	vector<Atom>molecule;
	for(int i=0,sign=1;;i++)
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
			int type=(int)INPUT[i]*256;
			if(Lower(INPUT[i+1]))type+=INPUT[++i];
			int cnt=1;
			if(Digit(INPUT[i+1]))cnt=INPUT[++i]-'0';
			assert(!Digit(INPUT[i+1]));
			molecule.push_back(Atom(GetIdx(type),cnt*sign));
		}
	}
}
struct Matrix
{
	int r,c;
	vector<vector<int> >s;
	Matrix(const int _r,const int _c):r(_r),c(_c){s.resize(r);for(auto &v:s)v.resize(c+1);}
	void RemoveFirstColumn(const int v)
	{
		for(int i=0;i<r;i++)
		{
			s[i][c]-=s[i][0]*v;
			for(int j=0;j<c;j++)s[i][j]=s[i][j+1];
			s[i].pop_back();
		}
		c--;
	}
	void Swap(const int r1,const int r2){for(int i=0;i<=c;i++)swap(s[r1][i],s[r2][i]);}
	int Gcd(const int a,const int b){return b?Gcd(b,a%b):a;}
	void Reduce(const int _r)
	{
		int g=0;
		for(int i=0;i<=c;i++)g=Gcd(g,abs(s[_r][i]));
		if(g)for(int i=0;i<=c;i++)s[_r][i]/=g;
		RemoveSame();
	}
	void Eliminate(const int r1,const int r2,const int _c)
	{
		assert(s[r1][_c]);
		if(s[r2][_c]==0)return;
		int g=Gcd(abs(s[r1][_c]),abs(s[r2][_c])),v1=s[r1][_c]/g,v2=s[r2][_c]/g;
		for(int i=0;i<=c;i++)s[r2][i]=s[r2][i]*v1-s[r1][i]*v2;
		Reduce(r2);
		assert(!s[r2][i]);
	}
	bool Same(const int r1,const int r2){for(int i=0;i<=c;i++)if(s[r1][i]!=s[r2][i])return false;return true;}
	void RemoveSame()
	{
		for(int i=0;i<r;i++)Reduce(i);
		bool changed=true;
		while(changed)
		{
			changed=false;
			for(int i=0;i<r;i++)for(int j=i+1;j<r;j++)if(Same(i,j))
			{
				Swap(j,r-1);
				s.pop_back();
				r--;
				changed=true;
				break;
			}
		}
	}
};
int Solve(Matrix &m)
{
	if(m.r<m.c)return 2;
	for(int i=0;i<m.r;i++)
	{
		if(!m.s[i][i])
		{
			bool found=false;
			for(int j=i+1;j<m.r;j++)if(m.s[j][i]){m.Swap(i,j),found=true;break;}
			if(!found)continue;
		}
		for(int j=i+1;j<m.r;j++)m.Eliminate(i,j,i);
	}
	for(int i=m.r-1;i>=0;i--)if(m.s[i][i])for(int j=i-1;j>=0;j--)
	{
		m.Eliminate(i,j,i);
	}
	for(int i=0;i<m.r;i++)if(!m.s[i][i])return m.s[i][m.c]==0?2:0;
	return 1;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",&INPUT);
		Initialize();
		Matrix m=Matrix(IDX.size(),E.size());
		for(int i=0;i<IDX.size();i++)for(int j=0;j<=E.size();j++)m.s[i][j]=0;
		for(int c=0;c<E.size();c++)for(const auto &atom:E[c])m.s[atom.type][c]=atom.cnt;
		m.RemoveSame();
		Matrix tmp=m;
		int result=Solve(tmp);
		if(result==0)puts("IMPOSSIBLE");
		else
		{
			while(result==2)m.RemoveFirstColumn(1),printf(" %d/%d",1,1),result=Solve(tmp=m);
			assert(result==1);
			assert(tmp.r==tmp.c);
			for(int i=0;i<tmp.r;i++)printf(" %d/%d",tmp.s[i][tmp.c],tmp.s[i][i]);
			puts("");
		}
	}
	return 0;
}
