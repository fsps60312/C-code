#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef unsigned long long ULL;
const int MOD=10000;
void Plus(int &a,const int b){(a+=b)%=MOD;}
struct Matrix
{
	vector<vector<int> >s;
	int n;
	Matrix(const int _n):n(_n){s.clear();s.resize(n,vector<int>(n));}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans=Matrix(n);
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)
		{
			int &v=ans.s[i][j]=0;
			for(int k=0;k<n;k++)Plus(v,s[i][k]*a.s[k][j]);
		}
		return ans;
	}
	void Print()const
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(j)putchar(' ');
				printf("%d",s[i][j]);
			}
			puts("");
		}
		puts("");
	}
};
Matrix Pow(Matrix a,ULL p)
{
	Matrix ans=Matrix(a.n);
	for(int i=0;i<a.n;i++)for(int j=0;j<a.n;j++)ans.s[i][j]=(i==j?1:0);
	while(p)
	{
		if(p&(ULL)1)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
struct A_Solver
{
	int DP[2][1<<7];
	Matrix M=Matrix(0);
	void Initialize()
	{
		M=Matrix(1<<7);
		for(int source=0;source<(1<<7);source++)
		{
			for(int i=0;i<(1<<7);i++)DP[0][i]=DP[1][i]=0;
			int d=0;
			DP[0][source]=1;
			for(int row=0;row<7;row++,d^=1)
			{
				for(int s=0;s<(1<<7);s++)if(DP[d][s])
				{
					const int v=DP[d][s];
//					printf("row=%d,s=%d,v=%d\n",row,s,v);
					if(s&(1<<row))Plus(DP[d^1][s-(1<<row)],v);
					else
					{
						Plus(DP[d^1][s+(1<<row)],v);
						if(row+1<7&&!(s&(1<<(row+1))))Plus(DP[d^1][s+(1<<(row+1))],v);
					}
					DP[d][s]=0;
				}
			}
			for(int target=0;target<(1<<7);target++)M.s[source][target]=DP[d][target];
		}
//		M.Print();
	}
	int Solve(const ULL &n)
	{
		const Matrix result=Pow(M,n);
//		result.Print();
		return result.s[0][0];
	}
}A_SOLVER;
struct BC_Solver
{
	struct State
	{
		int data[8];
		void Replace(const int sou,const int tar){for(int i=0;i<8;i++)if(data[i]==sou)data[i]=tar;}
		void ReIndex()
		{
			map<int,int>idx;
			for(int i=0,cnt=0;i<8;i++){const int v=data[i];if(v>=0&&idx.find(v)==idx.end())idx[v]=cnt++;}
			for(int i=0;i<8;i++)if(data[i]>=0)data[i]=idx[data[i]];
		}
		bool TryMove(State &t,const int row,const bool up,const bool right,const bool down,const bool left,const bool isb)const
		{
//			if(isb)
//			{
//				bool found=false;
//				for(int i=0;i<8;i++)if(data[i]>=0){found=true;break;}
//				if(!found)return false;
//			}
			if((row==0&&up)||(row==6&&down))return false;
			if((up&&data[7]==-1)||(left&&data[row]==-1))return false;
			if((!up&&row&&data[7]>=0)||(!left&&data[row]>=0))return false;
			int type=-2;
			t=(*this);
			if(up&&left)
			{
				assert(data[7]>=0&&data[row]>=0);
				if(data[7]==data[row]){if(isb)return false;}
				else t.Replace(data[7],data[row]);
				type=data[row];
			}
			else if(!up&&left)assert(data[row]>=0),type=data[row];
			else if(up&&!left)assert(data[7]>=0),type=data[7];
			else assert(!up&&!left),type=100;
			assert(type!=-2);
			t.data[row]=(right?type:-1);
			t.data[7]=(down?type:-1);
			t.ReIndex();
			return true;
		}
		void Print()const{for(int i=0;i<8;i++)printf(" %d",data[i]);puts("");}
		bool operator<(const State &s)const{for(int i=0;i<8;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return false;}
	};
	bool ISB;
	Matrix M=Matrix(0);
	vector<int>O;
	map<State,int>DP[2];
	int IDX0,ANS[8];
	void Plus(const int d,const State &s,const int v)
	{
		auto it=DP[d].find(s);
		if(it==DP[d].end())DP[d][s]=v%MOD;
		else ::Plus(it->second,v);
	}
	void TryMove(const int row,const int d)
	{
		assert(DP[d^1].empty());
		for(const auto &it:DP[d])
		{
			const State &s=it.first;
			static State t;
			if(s.TryMove(t,row,true,false,true,false,ISB))Plus(d^1,t,it.second);
			if(s.TryMove(t,row,false,true,false,true,ISB))Plus(d^1,t,it.second);
			if(s.TryMove(t,row,true,true,false,false,ISB))Plus(d^1,t,it.second);
			if(s.TryMove(t,row,false,true,true,false,ISB))Plus(d^1,t,it.second);
			if(s.TryMove(t,row,false,false,true,true,ISB))Plus(d^1,t,it.second);
			if(s.TryMove(t,row,true,false,false,true,ISB))Plus(d^1,t,it.second);
		}
		DP[d].clear();
	}
	void Initialize()
	{
		ANS[0]=1;
		assert(DP[0].empty()&&DP[1].empty());
		State state1;
		for(int i=0;i<8;i++)state1.data[i]=-1;
		state1.data[0]=state1.data[7]=0;
		Plus(0,state1,1);
		State state0;
		for(int i=0;i<8;i++)state0.data[i]=-1;
		state0.data[6]=state0.data[7]=0;
		int d=0;
		map<State,int>idx;
		for(int row=1,col=0;;d^=1)
		{
			if(row==6)
			{
				for(const auto &it:DP[d])idx[it.first]=-1;
				const auto it=DP[d].find(state0);
				if(it==DP[d].end())ANS[col+1]=0;
				else ANS[col+1]=it->second;
//				printf("ANS[%d]=%d\n",col,ANS[col]);
				if(col==6)break;
			}
			TryMove(row,d);
			if(++row==7)row=0,col++;
		}
		vector<State>ridx;
		do{int cnt=0;for(auto &it:idx)it.second=cnt++,ridx.push_back(it.first);}while(0);
		O.clear(),O.resize(idx.size(),0);
		const int tmp=idx.size();
		for(const auto &it:DP[d])O[idx[it.first]]=it.second;
		IDX0=idx[state0];
		assert(tmp==(int)idx.size());
		assert(O[IDX0]==ANS[7]);
		DP[d].clear();
		BuildMatrix(idx,ridx);
	}
	void BuildMatrix(const map<State,int>&idx,const vector<State>&ridx)
	{
//		for(const State &s:ridx)s.Print();
		assert(idx.size()==ridx.size());
		const int n=idx.size();
//		printf("n=%d\n",n);
		M=Matrix(n);
		for(int source=0;source<n;source++)
		{
			assert(DP[0].empty()&&DP[1].empty());
			int d=0;
			Plus(0,ridx[source],1);
			for(int row=6;row<6+7;row++,d^=1)TryMove(row%7,d);
			int cnt=0;
			for(int target=0;target<n;target++)
			{
				const auto it=DP[d].find(ridx[target]);
				if(it!=DP[d].end())cnt++;
				M.s[source][target]=(it==DP[d].end()?0:it->second);
			}
//			printf("(%d,%d)\n",cnt,DP[d].size());
//			for(const auto &it:DP[d])it.first.Print();
			assert(cnt==(int)DP[d].size());
			DP[d].clear();
		}
	}
	int Solve(const ULL &n)
	{
		if(n<=(ULL)7)return ANS[n];
		Matrix result=Pow(M,n-(ULL)7);
		int ans=0;
		assert((int)O.size()==M.n);
		for(int i=0;i<M.n;i++)::Plus(ans,O[i]*result.s[i][IDX0]);
		return ans;
	}
}B_SOLVER,C_SOLVER;
int main()
{
//	freopen("out.txt","w",stdout);
	A_SOLVER.Initialize();
	B_SOLVER.ISB=true,C_SOLVER.ISB=false;
//	puts("C");
	C_SOLVER.Initialize();
//	puts("B");
	B_SOLVER.Initialize();
	puts("Initializing completed");
//	return 0;
	static ULL n;
	while(scanf("%llu",&n)==1)
	{
		const int a=A_SOLVER.Solve(n),b=B_SOLVER.Solve(n),c=C_SOLVER.Solve(n),ans=(a+b+c)%MOD;
//		printf("%04d %04d %04d\n",a,b,c);
		printf("%04d\n",ans);
	}
	return 0;
}
