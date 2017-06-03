#include<cstdio>
#include<map>
#include<vector>
//#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
LL T;
char INPUT[201];
map<LL,LL>IDX;
LL Gcd(const LL a,const LL b){return b?Gcd(b,a%b):a;}
LL GetIdx(const LL v)
{
	auto it=IDX.find(v);
	if(it==IDX.end())
	{
		const LL sz=IDX.size();
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
	IDX.clear(),E.clear();
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
			if(Digit(INPUT[i+1]))cnt=INPUT[++i]-'0';
			assert(!Digit(INPUT[i+1]));
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
		for(LL i=0;i<r;i++)
		{
			for(LL j=0;j<c;j++)s[i][j]=m.s[i][select[j]];
			s[i][c]=m.s[i][m.c];
		}
	}
	void RemoveFirstColumn(const LL v)
	{
		for(LL i=0;i<r;i++)
		{
			s[i][c]-=s[i][0]*v;
			for(LL j=0;j<c;j++)s[i][j]=s[i][j+1];
			s[i].pop_back();
		}
		c--;
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
		puts("");
		for(LL i=0;i<r;i++)
		{
			for(LL j=0;j<=c;j++)printf(" %d",s[i][j]);puts("");
		}
	}
};
LL RowOperation(Matrix &m)
{
	if(m.r<m.c)return 2;
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
	for(LL i=0;i<m.c;i++)if(!m.s[i][i])return m.s[i][m.c]==0?2:0;
	for(LL i=m.c;i<m.r;i++)if(m.s[i][m.c])return 0;
	return 1;
}
bool GetIntergerSolution(Matrix &m,vector<LL>&ans)
{
	Matrix tmp=m;
	LL result=RowOperation(tmp);
//	assert(result>=1);
	if(result==1)return false;
	vector<LL>up,down;
	while(result==2)
	{
		up.push_back(1),down.push_back(1);
		m.RemoveFirstColumn(1);
		result=RowOperation(tmp=m);
	}
//	assert(result==1);
	for(LL i=0;i<tmp.c;i++)
	{
		LL a=tmp.s[i][tmp.c],b=tmp.s[i][i];
		if(b<0)a*=-1,b*=-1;
		if(a<0)return false;
		LL g=Gcd(a,b);
		a/=g,b/=g;
		up.push_back(a),down.push_back(b);
	}
	LL lca=down[0];
	for(LL i=1;i<down.size();i++)lca=lca/Gcd(lca,down[i])*down[i];
	ans.clear();
	for(LL i=0;i<up.size();i++)ans.push_back(up[i]*(lca/down[i]));
	for(int i=0;i<ans.size();i++)assert(ans[i]>=1&&ans[i]<=9);
	return true;
}
vector<LL>DJ;
LL FindDJ(const LL a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
vector<LL>ANS;
vector<bool>VIS;
bool Solve(Matrix &m)
{
	ANS.resize(E.size());
	for(LL i=0;i<E.size();i++)if(!VIS[i])
	{
		vector<LL>select,ans;
		for(LL j=i;j<E.size();j++)if(FindDJ(j)==FindDJ(i))select.push_back(j),VIS[j]=true;
		Matrix tmp=Matrix(m,select);
		if(!GetIntergerSolution(tmp,ans))return false;
		for(LL i=0;i<ans.size();i++)ANS[select[i]]=ans[i];
	}
	return true;
}
int main()
{
//	LL aaa=0LL,bbb=0LL;
//	printf("%lld\n",aaa/bbb);return 0;
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",&INPUT);
		Initialize();
		Matrix m=Matrix(IDX.size(),E.size());
		for(LL i=0;i<IDX.size();i++)for(LL j=0;j<=E.size();j++)m.s[i][j]=0;
		for(LL c=0;c<E.size();c++)for(const auto &atom:E[c])m.s[atom.type][c]=atom.cnt;
		DJ.clear(),VIS.clear();
		for(LL i=0;i<E.size();i++)DJ.push_back(i),VIS.push_back(false);
		for(LL i=0;i<IDX.size();i++)
		{
			LL j=0;
			while(m.s[i][j]==0)j++;
			for(LL k=j+1;k<E.size();k++)if(m.s[i][k])DJ[FindDJ(j)]=FindDJ(k);
		}
		if(!Solve(m))puts("IMPOSSIBLE");
		else
		{
			for(LL i=0;i<ANS.size();i++)
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
