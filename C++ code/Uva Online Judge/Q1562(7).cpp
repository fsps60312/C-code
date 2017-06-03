#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
#include<algorithm>
#define debug(...) //__VA_ARGS__
#define debug2(...) __VA_ARGS__
using namespace std;
typedef long long LL;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');}
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
	Matrix(const Matrix &m,const vector<LL>&select)
	{
		resize(m.r,select.size());
		for(LL i=0,idx=0;i<r;i++,idx++)
		{
			LL tmp=0LL;
			for(LL j=0;j<c;j++)tmp|=(s[i][j]=m.s[idx][select[j]]);
			if(tmp==0LL){i--,r--;s.pop_back();continue;}
			s[i][c]=m.s[idx][m.c];
		}
	}
	void RemoveFirstColumn(const LL v)
	{
		debug(puts("Removing");Print(););
		for(LL i=0;i<r;i++)
		{
			s[i][c]-=s[i][0]*v;
			for(LL j=0;j<c;j++)s[i][j]=s[i][j+1];
			s[i].pop_back();
		}
		c--;
		debug(puts("Removed");Print(););
	}
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
	void Print()
	{
		for(LL i=0;i<r;i++)
		{
			for(LL j=0;j<=c;j++)printf(" %d",s[i][j]);puts("");
		}
		puts("");
	}
};
LL RowOperation(Matrix &m)
{
	if(m.r<m.c)return 2;
	debug(puts("RowOperating");m.Print(););
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
	debug(puts("RowOperated");m.Print(););
	for(LL i=0;i<m.c;i++)if(!m.s[i][i])return m.s[i][m.c]==0?2:0;
	for(LL i=m.c;i<m.r;i++)if(m.s[i][m.c])return 0;
	return 1;
}
void Print(const vector<LL>&up,const vector<LL>&down){for(int i=0;i<up.size();i++)printf(" %lld/%lld",up[i],down[i]);puts("");}
bool Solve(Matrix &m,vector<LL>&up,vector<LL>&down);
bool GetFractionSolution(Matrix &m,vector<LL>&up,vector<LL>&down)
{
	Matrix tmp=m;
	debug(puts("GetFractionSolution");tmp.Print(););
	int result=RowOperation(tmp);
	debug(printf("result=%d\n",result););
	if(result==0)
	{
		debug2(puts("Result for");m.Print(););
		debug2(puts("Is");puts("No solution"););
		return false;
	}
	else if(result==1)
	{
		up.clear(),down.clear();
		for(LL i=0;i<tmp.c;i++)
		{
			LL a=tmp.s[i][tmp.c],b=tmp.s[i][i];
			if(b<0)a*=-1,b*=-1;
			if(a<0)return false;
			LL g=Gcd(a,b);
			a/=g,b/=g;
			up.push_back(a),down.push_back(b);
		}
		debug2(puts("Result for");m.Print(););
		debug2(puts("Is");Print(up,down););
		return true;
	}
	else if(result==2)
	{
		debug2(puts("Result for");m.Print(););
		debug2(puts("Is");puts("Multiple solutions"););
		m.RemoveFirstColumn(1);
		if(!Solve(m,up,down))return false;
		up.push_back(-1LL),down.push_back(-1LL);
		for(int i=(int)up.size()-1;i>=0;i--)up[i+1]=up[i],down[i+1]=down[i];
		up[0]=down[0]=1LL;
		return true;
	}
	assert(0);
}
struct Dj
{
	vector<int>s;
	Dj(const int n){s.clear();for(int i=0;i<n;i++)s.push_back(i);}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	void Merge(const int a,const int b){s[Find(a)]=Find(b);}
};
bool Solve(Matrix &m,vector<LL>&up,vector<LL>&down)
{
	Dj dj=Dj(m.c);
	for(int i=0;i<m.r;i++)
	{
		int j=0;
		while(m.s[i][j]==0&&j<=m.c)j++;
		if(j==m.c)return false;
		else if(j==m.c+1)continue;
		for(int k=j+1;k<m.c;k++)if(m.s[i][k])dj.Merge(j,k);
	}
	vector<bool>vis;
	up.resize(m.c),down.resize(m.c);
	vis.resize(m.c);
	for(int i=0;i<m.c;i++)vis[i]=false;
	for(LL i=0;i<m.c;i++)if(!vis[i])
	{
		vector<LL>select,tup,tdown;
		for(LL j=i;j<m.c;j++)if(dj.Find(j)==dj.Find(i))select.push_back(j),vis[j]=true;
		Matrix tmp=Matrix(m,select);
		debug(puts("Split:");m.Print();tmp.Print(););
		if(!GetFractionSolution(tmp,tup,tdown))return false;
		for(int i=0;i<tup.size();i++)up[select[i]]=tup[i],down[select[i]]=tdown[i];
	}
	return true;
}
void Check()
{
	int cnt_check=1;
	for(int i=0;INPUT[i];i++)if(INPUT[i]=='+'||INPUT[i]=='=')cnt_check++;
	assert(cnt_check==E.size());
	vector<char>rebuild;
	for(int i=0,sign=1,idx=0;i<E.size();i++)
	{
		if(E[i][0].cnt<0&&sign==1)sign=-1,assert(INPUT[idx++]=='=');
		else if(i)assert(INPUT[idx++]=='+');
		for(int j=0;j<E[i].size();j++)
		{
			const Atom &atom=E[i][j];
			const LL type=RI[atom.type];
			assert(INPUT[idx++]==type/256);
			if(type%256)assert(INPUT[idx++]==type%256);
			LL v=atom.cnt*sign;
			assert(v>0);
			if(!Digit(INPUT[idx])){assert(v==1LL);continue;}
			vector<int>tmp;
			while(v)tmp.push_back(v%10),v/=10;
			for(int i=tmp.size()-1;i>=0;i--)assert(INPUT[idx++]=='0'+tmp[i]);
		}
	}
}
int main()
{
	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",&INPUT);
		Initialize();
		Check();
		Matrix m=Matrix(IDX.size(),E.size());
		for(LL i=0;i<IDX.size();i++)for(LL j=0;j<=E.size();j++)m.s[i][j]=0;
		for(LL c=0;c<E.size();c++)for(const auto &atom:E[c])m.s[atom.type][c]+=atom.cnt;
		m.RemoveFirstColumn(1);
		vector<LL>up,down;
		if(!Solve(m,up,down))
		{
			puts(INPUT);
			puts("IMPOSSIBLE");
		}
		else
		{
			LL lca=1;
			for(int i=0;i<down.size();i++)lca=lca/Gcd(lca,down[i])*down[i];
			printf("%lld",lca);
			for(LL i=0;i<up.size();i++)printf(" %lld",lca/down[i]*up[i]);
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
