#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,B;
vector<int>PASSWORD;
vector<vector<int> >PLATE;
int ANS;
int Mod(const int v){return (v%B+B)%B;}
struct Matrix
{
	vector<vector<int> >s;
	int r,c;
	Matrix(const int _r,const int _c){r=_r,c=_c;s.resize(r);for(auto &v:s)v.resize(c+1);}
	void SwapRow(const int r1,const int r2){for(int i=0;i<=c;i++)swap(s[r1][i],s[r2][i]);}
	void Eliminate(const int r1,const int r2,const int _c)
	{
		assert(s[r1][_c]);
		const int v1=s[r1][_c],v2=s[r2][_c];
		for(int i=0;i<=c;i++)s[r2][i]=Mod(s[r2][i]*v1-s[r1][i]*v2);
		assert(s[r2][_c]==0);
	}
	bool Solvable()
	{
		int row,col;
		for(row=0,col=0;row<r&&col<c;row++)
		{
			if(!s[row][col])
			{
				bool found=false;
				for(int i=row+1;i<r;i++)if(s[i][col]){SwapRow(row,i);found=true;break;}
				if(!found){row--,col++;continue;}
			}
			for(int i=row+1;i<r;i++)Eliminate(row,i,col);
			col++;
		}
		for(int i=row;i<r;i++)if(s[i][c])return false;
		return true;
	}
};
void Dfs(const int dep,vector<int>&now,const int step)
{
	if(step>=ANS)return;
	if(dep==N)
	{
		assert(now.size()==N);
		for(int i=0;i<N;i++)if(now[i]!=PASSWORD[i])return;
		ANS=step;
		return;
	}
	for(int move=0;move<B;move++)
	{
		Matrix m=Matrix(N,N-dep-1);
		for(int i=dep+1;i<N;i++)for(int j=0;j<N;j++)m.s[j][i-dep-1]=PLATE[i][j];
		for(int i=0;i<N;i++)m.s[i][N-dep-1]=Mod(PASSWORD[i]-now[i]);
		if(m.Solvable())Dfs(dep+1,now,step+move);
		for(int i=0;i<N;i++)(now[i]+=PLATE[dep][i])%=B;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&B)==2&&!(N==0&&B==0))
	{
		PASSWORD.clear(),PLATE.clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			v--;assert(v>=0&&v<B);
			PASSWORD.push_back((B-v)%B);
		}
		for(int i=0,p;i<N;i++)
		{
			vector<int>plate;
			for(int j=0;j<N;j++)plate.push_back(0);
			scanf("%d",&p);
			for(int j=0,a,b;j<p;j++)
			{
				scanf("%d%d",&a,&b);
				a--;
				assert(a>=0&&a<N);
				(plate[a]+=b)%=B;
			}
			PLATE.push_back(plate);
		}
		ANS=INF;
		vector<int>now;
		for(int i=0;i<N;i++)now.push_back(0);
		Dfs(0,now,0);
		if(ANS==INF)puts("No solution");
		else printf("%d\n",ANS);
	}
	return 0;
}
/*
1 4
2
1 1 2
4 8
8 8 8 8
4 1 1 2 2 4 1 3 1
2 4 7 3 2
2 1 5 3 5
1 2 7
20 10
10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
20 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1
1 20 1
0 0
*/
