#include<cstdio>
#include<map>
#include<vector>
//#include<cassert>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
int T;
char INPUT[201];
map<int,int>IDX;
int Gcd(const int a,const int b){return b?Gcd(b,a%b):a;}
int GetIdx(const int v)
{
	auto it=IDX.find(v);
	if(it==IDX.end())
	{
		const int sz=IDX.size();
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
	void resize(const int _r,const int _c){r=_r,c=_c;s.resize(r);for(auto &v:s)v.resize(c+1);}
	Matrix(const int _r,const int _c){resize(_r,_c);}
	Matrix(const Matrix &m,const vector<int>&select)
	{
		resize(m.r,select.size());
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<c;j++)s[i][j]=m.s[i][select[j]];
			s[i][c]=m.s[i][m.c];
		}
	}
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
	void Reduce(const int _r)
	{
		int g=0;
		for(int i=0;i<=c;i++)g=Gcd(g,abs(s[_r][i]));
		if(g)for(int i=0;i<=c;i++)s[_r][i]/=g;
	}
	void Eliminate(const int r1,const int r2,const int _c)
	{
		assert(s[r1][_c]);
		if(s[r2][_c]==0)return;
		int g=Gcd(abs(s[r1][_c]),abs(s[r2][_c])),v1=s[r1][_c]/g,v2=s[r2][_c]/g;
		for(int i=0;i<=c;i++)s[r2][i]=s[r2][i]*v1-s[r1][i]*v2;
		Reduce(r2);
		assert(!s[r2][_c]);
	}
	void Print()
	{
		puts("");
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<=c;j++)printf(" %d",s[i][j]);puts("");
		}
	}
};
int RowOperation(Matrix &m)
{
//	m.Print();
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
	for(int i=m.c-1;i>=0;i--)if(m.s[i][i])for(int j=i-1;j>=0;j--)
	{
		m.Eliminate(i,j,i);
	}
//	m.Print();
	for(int i=0;i<m.c;i++)if(!m.s[i][i])return m.s[i][m.c]==0?2:0;
	for(int i=m.c;i<m.r;i++)if(m.s[i][m.c])return 0;
	return 1;
}
bool GetIntergerSolution(Matrix &m,vector<int>&ans)
{
	Matrix tmp=m;
	int result=RowOperation(tmp);
	assert(result>=1);
	if(result==1)return false;
	vector<int>up,down;
	while(result==2)
	{
		up.push_back(1),down.push_back(1);
		m.RemoveFirstColumn(1);
		result=RowOperation(tmp=m);
	}
	assert(result==1);
	for(int i=0;i<tmp.c;i++)
	{
		int a=tmp.s[i][tmp.c],b=tmp.s[i][i];
		if(b<0)a*=-1,b*=-1;
		if(a<0)return false;
		int g=Gcd(a,b);
		a/=g,b/=g;
		up.push_back(a),down.push_back(b);
	}
	int lca=down[0];
	for(int i=1;i<down.size();i++)lca=lca/Gcd(lca,down[i])*down[i];
	ans.clear();
	for(int i=0;i<up.size();i++)ans.push_back(up[i]*(lca/down[i]));
	return true;
}
vector<int>DJ;
int FindDJ(const int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
vector<int>ANS;
vector<bool>VIS;
bool Solve(Matrix &m)
{
	ANS.resize(E.size());
	for(int i=0;i<E.size();i++)if(!VIS[i])
	{
		vector<int>select,ans;
		for(int j=i;j<E.size();j++)if(FindDJ(j)==FindDJ(i))select.push_back(j),VIS[j]=true;
		Matrix tmp=Matrix(m,select);
		if(!GetIntergerSolution(tmp,ans))return false;
		for(int i=0;i<ans.size();i++)ANS[select[i]]=ans[i];
	}
	for(int i=0;i<ANS.size();i++)
	{
		if(ANS[i]<1||ANS[i]>9)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",&INPUT);
		Initialize();
		Matrix m=Matrix(IDX.size(),E.size());
		for(int i=0;i<IDX.size();i++)for(int j=0;j<=E.size();j++)m.s[i][j]=0;
		for(int c=0;c<E.size();c++)for(const auto &atom:E[c])m.s[atom.type][c]=atom.cnt;
		DJ.clear(),VIS.clear();
		for(int i=0;i<E.size();i++)DJ.push_back(i),VIS.push_back(false);
		for(int i=0;i<IDX.size();i++)
		{
			int j=0;
			while(m.s[i][j]==0)j++;
			for(int k=j+1;k<E.size();k++)if(m.s[i][k])DJ[FindDJ(j)]=FindDJ(k);
		}
		if(!Solve(m))puts("IMPOSSIBLE");
		else
		{
			for(int i=0;i<ANS.size();i++)
			{
				if(i)putchar(' ');
				printf("%d",ANS[i]);
			}
			puts("");
		}
	}
	return 0;
}
/*
A2B+AB+C=AB2
*/
