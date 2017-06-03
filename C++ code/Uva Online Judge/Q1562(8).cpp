#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
#include<algorithm>
#define debug(...) //__VA_ARGS__
#define debug2(...) __VA_ARGS__
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
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
	Matrix(const Matrix &m,const vector<LL>&ans,const LL _c)
	{
		resize(m.r,_c);
		for(int i=0;i<r;i++)s[i][c]=m.s[i][m.c];
		LL i=0,idx=0;
		for(;i<m.c;i++)
		{
			if(ans[i]==INF)
			{
				for(int j=0;j<r;j++)s[j][idx]=m.s[j][i];
				idx++;
			}
			else
			{
				for(int j=0;j<r;j++)s[j][c]-=ans[i]*m.s[j][i];
			}
		}
		assert(idx==_c);
		for(int i=r-1;i>=0;i--)
		{
			bool found=false;
			for(int j=0;j<=c;j++)if(s[i][j]!=0LL){found=true;break;}
			if(!found)
			{
				Swap(i,r-1);
				s.pop_back();
				r--;
			}
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
		for(LL i=0;i<r;i++)
		{
			for(LL j=0;j<=c;j++)printf(" %d",s[i][j]);puts("");
		}
		puts("");
	}
};
int RowOperation(Matrix &m)
{
	for(LL i=0;i<min(m.r,m.c);i++)
	{
		if(!m.s[i][i])
		{
			bool found=false;
			for(LL j=i+1;j<m.r;j++)if(m.s[j][i]){m.Swap(i,j),found=true;break;}
			if(!found)continue;
		}
		for(LL j=i+1;j<m.r;j++)m.Eliminate(i,j,i);
	}
	for(LL i=min(m.r,m.c)-1;i>=0;i--)if(m.s[i][i])for(LL j=i-1;j>=0;j--)m.Eliminate(i,j,i);
	for(LL i=0;i<min(m.r,m.c);i++)if(!m.s[i][i])return m.s[i][m.c]?0:2;
	for(LL i=m.c;i<m.r;i++)if(m.s[i][m.c])return 0;
	return 1;
}
void Print(const vector<LL>&up,const vector<LL>&down){for(int i=0;i<up.size();i++)printf(" %lld/%lld",up[i]==INF?-1:up[i],down[i]==INF?-1:down[i]);puts("");}
void EliminateDown(const vector<LL>&up,const vector<LL>&down,vector<LL>&ans)
{
	LL lca=1;
	for(int i=0;i<down.size();i++)if(up[i]!=INF)lca=lca/Gcd(lca,down[i])*down[i];
	ans.clear();
	for(LL i=0;i<up.size();i++)
	{
		if(up[i]==INF)ans.push_back(INF);
		else ans.push_back(lca/down[i]*up[i]);
	}
}
bool GetIntegerSolution(Matrix &m,vector<LL>&up,vector<LL>&down)
{
	Matrix tmp=m;
	puts("GetIntegerSolution");m.Print();
	int result=RowOperation(tmp);
	tmp.Print();
	printf("result=%d\n",result);
	if(result==0)return false;
	else if(result==1||result==2)
	{
		up.clear(),down.clear();
		LL multiplesolution=0LL;
		LL i=0;
		for(i=0;i<min(tmp.r,tmp.c);i++)
		{
			bool found=false;
			for(int j=0;j<tmp.c;j++)if(j!=i&&tmp.s[i][j]){found=true;break;}
			LL a=tmp.s[i][tmp.c],b=tmp.s[i][i];
			if(found)goto idenasmulsolu;
			if(b<0)a*=-1,b*=-1;
			if(a<0)return false;
			if(b==0)
			{
				assert(a==0);
				idenasmulsolu:;
				up.push_back(INF),down.push_back(INF);
				multiplesolution++;
			}
			else
			{
				LL g=Gcd(a,b);
				a/=g,b/=g;
				up.push_back(a),down.push_back(b);
			}
		}
		while(i++<tmp.c)up.push_back(INF),down.push_back(INF),multiplesolution++;
		debug2(puts("Result for");m.Print(););
		debug2(puts("Is");Print(up,down););
//		printf("mulsol=%lld\n",multiplesolution);
		if(multiplesolution)
		{
			vector<LL>ans;
			EliminateDown(up,down,ans);
//			for(int i=0;i<ans.size();i++)printf(" %lld",ans[i]==INF?-1:ans[i]);puts("");
			Matrix nxt=Matrix(m,ans,multiplesolution);
			debug2(puts("Become");nxt.Print());
			nxt.RemoveFirstColumn(1LL);
			vector<LL>tup,tdown;
			assert(GetIntegerSolution(nxt,tup,tdown));
			debug2(puts("From");Print(up,down););
			for(int i=0,idx=0;i<up.size();i++)if(up[i]==INF)up[i]=tup[idx],down[i]=tdown[idx],idx++;
			debug2(puts("To");Print(up,down););
			return true;
		}
		else return true;
	}
	else if(result==3)
	{
		m.RemoveFirstColumn(1);
		assert(GetIntegerSolution(m,up,down));
		up.push_back(INF),down.push_back(INF);
		for(int i=(int)up.size()-1;i>=0;i--)up[i+1]=up[i],down[i+1]=down[i];
		up[0]=down[0]=1LL;
		return true;
	}
	assert(0);
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
		vector<LL>up,down;
		if(!GetIntegerSolution(m,up,down))
		{
			puts(INPUT);
			puts("IMPOSSIBLE");
		}
		else
		{
			vector<LL>ans;
			EliminateDown(up,down,ans);
			for(int i=0;i<ans.size();i++)
			{
				if(i)putchar(' ');
				printf("%lld",ans[i]);
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
