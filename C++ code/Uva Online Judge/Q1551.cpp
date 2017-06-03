#include<cstdio>
#include<vector>
#include<map>
#include<set>
//#include<cassert>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
typedef long long LL;
int N;
vector<int>S,P;
struct Matrix
{
	vector<vector<LL> >s;
	vector<int>w;
	int r,c;
	Matrix(const int _r,const int _c):r(_r),c(_c){}//max of r is 25
	void Resize(const int _r,const int _c)
	{
		r=_r,c=_c;
		s.resize(r);
		for(auto &v:s)v.resize(c+1);
	}
	void RemoveColumn(const int _c)
	{
		for(int i=_c+1;i<c;i++)w[i-1]=w[i];w.pop_back();
		for(int i=0;i<r;i++)
		{
			for(int j=_c+1;j<=c;j++)s[i][j-1]=s[i][j];
			s[i].pop_back();
		}
		c--;
	}
	void SwapRow(const int r1,const int r2){for(int i=0;i<=c;i++)swap(s[r1][i],s[r2][i]);}
	LL Gcd(const LL &a,const LL &b){return b?Gcd(b,a%b):a;}
	void Eliminate(const int r1,const int r2,const int _c)
	{
		LL g=Gcd(abs(s[r1][_c]),abs(s[r2][_c]));
		LL v1=s[r1][_c]/g,v2=s[r2][_c]/g;
		for(int i=0;i<=c;i++)s[r2][i]=s[r2][i]*v1-s[r1][i]*v2;
	}
	void Print()
	{
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<=c;j++)printf("%3d",s[i][j]);
			puts("");
		}
		puts("");
	}
	bool EmptyRow(const int _r,const int _c=-1){for(int i=0;i<c;i++)if(i!=_c&&s[_r][i]!=0)return false;return true;}
	void ResetW()
	{
		assert(c==N);
		w.clear();
		for(int i=0;i<N;i++)w.push_back(S[i]);
	}
	bool Solve(vector<int>&ans)
	{
//		puts("Before");
//		Print();
		for(int i=0;i<c;i++)
		{
			if(s[i][i]==0LL)
			{
				bool found=false;
				for(int j=i+1;j<r;j++)if(s[j][i]!=0LL){SwapRow(i,j);found=true;break;}
				if(!found)continue;
//				if(!found){RemoveColumn(i--);continue;}
			}
			for(int j=i+1;j<r;j++)Eliminate(i,j,i);
		}
//		puts("After");
//		Print();
		if(c==0)return false;
		for(int i=c-1;i>=0;i--)for(int j=i-1;j>=0;j--)if(s[i][i])Eliminate(i,j,i);
		for(int i=c;i<r;i++)assert(EmptyRow(i));
		for(int i=0;i<r;i++)if(EmptyRow(i)&&s[i][c])return false;
		for(int i=0;i<c;i++)if(!s[i][i]){RemoveColumn(i);return Solve(ans);}
		LL lca=1LL;
		for(int i=0;i<c;i++)lca=lca/Gcd(lca,abs(s[i][i]))*abs(s[i][i]);
		vector<int>up,down;
		for(int i=0;i<c;i++)
		{
			LL cnt=lca/s[i][i]*s[i][c];
			for(;cnt>0LL;cnt--)up.push_back(w[i]);
			for(;cnt<0LL;cnt++)down.push_back(w[i]);
		}
		assert(up.size()==down.size());
		ans.clear();
		for(int i=0;i<up.size();i++)ans.push_back(up[i]),ans.push_back(down[i]);
		return true;
	}
}M=Matrix(0,0);
bool Solve(const int a,const int b,vector<int>&ans)
{
	M.Resize(P.size()+1,N);
	for(int i=0;i<N;i++)
	{
		int n=S[i];
		for(int j=0;j<P.size();j++)
		{
			LL &cnt=M.s[j][i]=0LL;
			while(n%P[j]==0)cnt++,n/=P[j];
		}
	}
	for(int i=0;i<P.size();i++)M.s[i][N]=0LL;
	for(int n=a,p=0;n>1;p++)
	{
		if(p==P.size())return false;
		LL &cnt=M.s[p][N];
		while(n%P[p]==0)cnt++,n/=P[p];
	}
	for(int n=b,p=0;n>1;p++)
	{
		if(p==P.size())return false;
		LL &cnt=M.s[p][N];
		while(n%P[p]==0)cnt--,n/=P[p];
	}
	for(int i=0;i<N;i++)M.s[P.size()][i]=1LL;
	M.s[P.size()][N]=0LL;
	M.ResetW();
	return M.Solve(ans);
}
int main()
{
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]>=100){P.pop_back();break;}
	}
//	printf("%d\n",P.size());
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		static int kase=1;
		printf("Set #%d\n",kase++);
		set<int>duplicate;
		S.clear();
		for(int i=0,w;i<N;i++)
		{
			scanf("%d",&w);
			auto it=duplicate.find(w);
			if(it!=duplicate.end()){i--,N--;continue;}
			duplicate.insert(w);
			S.push_back(w);
		}
		for(int a,b;scanf("%d%d",&a,&b)&&!(a==0&&b==0);)
		{
			printf("Ratio %d:%d:",a,b);
			vector<int>ans;
			if(!Solve(a,b,ans))puts(" Impossible");
			else
			{
				assert(ans.size()%2==0);
				for(int i=0;i<ans.size();i+=2)printf(" %d:%d",ans[i],ans[i+1]);
				puts("");
			}
		}
		puts("");
	}
	return 0;
}
