#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<cassert>
#include<algorithm>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');}
typedef long long LL;
int N;
vector<int>S,P;
LL Gcd(const LL &a,const LL &b){return b?Gcd(b,a%b):a;}
struct Matrix
{
	vector<vector<LL> >s;
	vector<int>w;
	int r,c;
	Matrix(const int _r,const int _c):r(_r),c(_c){}//max of r is 25+1
	void Resize(const int _r,const int _c)
	{
		r=_r,c=_c;
		s.resize(r);
		for(auto &v:s)v.resize(c+1);
	}
	void SwapRow(const int r1,const int r2){for(int i=0;i<=c;i++)swap(s[r1][i],s[r2][i]);}
	void SwapColumn(const int c1,const int c2){swap(w[c1],w[c2]);for(int i=0;i<r;i++)swap(s[i][c1],s[i][c2]);}
	void Eliminate(const int r1,const int r2,const int _c)
	{
		assert(s[r1][_c]);
		if(s[r2][_c]==0LL)return;
		LL g=Gcd(labs(s[r1][_c]),labs(s[r2][_c]));
		LL v1=s[r1][_c]/g,v2=s[r2][_c]/g;
		for(int i=0;i<=c;i++)s[r2][i]=s[r2][i]*v1-s[r1][i]*v2;
		assert(s[r2][_c]==0LL);
	}
//	void Print()
//	{
//		for(int i=0;i<r;i++)
//		{
//			for(int j=0;j<=c;j++)printf("%3lld",s[i][j]);
//			puts("");
//		}
//		puts("");
//	}
	bool EmptyRow(const int _r,const int _c,const int mxc){for(int i=0;i<mxc;i++)if(i!=_c&&s[_r][i]!=0LL)return false;return true;}
	void ResetW()
	{
		assert(c==N&&S.size()==N);
		w.clear();
		for(int i=0;i<N;i++)w.push_back(S[i]);
	}
	void RemoveRow(const int _r)
	{
		for(int i=_r+1;i<r;i++)for(int j=0;j<=c;j++)s[i-1][j]=s[i][j];
		s.pop_back();
		r--;
	}
	bool Solve(vector<int>&ans)
	{
		for(int i=0;i<min(r,c);i++)
		{
//			printf("i=%d\n",i);
//			Print();
			if(s[i][i]==0LL)
			{
				bool found=false;
				for(int j=i+1;j<r;j++)if(s[j][i]!=0LL){SwapRow(i,j);found=true;break;}
				if(!found)
				{
					for(int j=i+1;j<c;j++)if(s[i][j]!=0LL){SwapColumn(i,j);found=true;break;}
					if(!found)
					{
						if(s[i][c])return false;
						RemoveRow(i--);
						continue;
					}
				}
			}
			for(int j=i+1;j<r;j++)Eliminate(i,j,i);
		}
		for(int i=min(r,c)-1;i>=0;i--)for(int j=i-1;j>=0;j--)assert(s[i][i]&&EmptyRow(i,i,min(r,c))),Eliminate(i,j,i);
		for(int i=c;i<r;i++)
		{
			assert(EmptyRow(i,-1,c));
			if(s[i][c])return false;
		}
//		puts("");
//		printf("min(%d,%d)\n",r,c);
//		Print();
		for(int i=0;i<min(r,c);i++)assert(s[i][i]&&EmptyRow(i,i,min(r,c)));
//		LL lcm=labs(s[0][0]);
//		for(int i=1;i<min(r,c);i++)lcm=lcm/Gcd(lcm,labs(s[i][i]))*labs(s[i][i]);
		vector<int>up,down;
		for(int i=0;i<min(r,c);i++)
		{
			if(s[i][c]%s[i][i]!=0LL)return false;
			LL cnt=s[i][c]/s[i][i];
//			printf("cnt=%lld",cnt);
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
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
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
//				LL up=a,down=b;
				for(int i=0;i<ans.size();i+=2)
				{
					printf(" %d:%d",ans[i],ans[i+1]);
//					up*=ans[i+1],down*=ans[i];
//					LL g=Gcd(up,down);
//					up/=g,down/=g;
				}
				puts("");
//				assert(up==1LL&&down==1LL);
			}
		}
		puts("");
	}
	return 0;
}
