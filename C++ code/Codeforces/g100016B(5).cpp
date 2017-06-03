#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double INF=1e100,EPS=1e-7,PI=acos(-1.0);
bool getmax(double &a,const double &b){if(b>a){a=b;return true;}return false;}
bool getmax(double &a,const double &b1,const double &b2)
{
	if(b1==-INF||b2==-INF)return false;
	if(b1+b2>a){a=b1+b2;return true;}
	return false;
}
int N,K;
struct Matrix
{
	double S[1000][1000];
	int MID[1000][1000];
	Matrix *ch[2];
	Matrix(Matrix *a,Matrix *b):ch{a,b}{}
};
//Matrix *Mul(Matrix *a,Matrix *b)
//{
//	Matrix *ans=new Matrix(a,b);
//	for(int i=0;i<N*2;i++)for(int j=0;j<N*2;j++)
//	{
//		double &v=ans->S[i][j]=-INF;
//		int &mid=ans->MID[i][j]=-1;
//		for(int k=0;k<N*2;k++)if(getmax(v,a->S[i][k],b->S[k][j]))mid=k;
//	}
//	return ans;
//}
void Solve(const int from,const int l,const int r,const int bl,const int br,Matrix *ans,Matrix *a,Matrix *b)
{
	if(l>r)return;
	const int mid=(l+r)/2;
	int &bm=ans->MID[from%N][mid%N]=bl;
	double &v=ans->S[from%N][mid%N]=-INF;
	for(int i=max(bl,from+1);i<=br&&i<mid;i++)
	{
		if(getmax(v,a->S[from%N][i%N],b->S[i%N][mid%N]))bm=i;
	}
	Solve(from,l,mid-1,bl,bm,ans,a,b),Solve(from,mid+1,r,bm,br,ans,a,b);
}
Matrix *Mul(Matrix *a,Matrix *b)
{
	Matrix *ans=new Matrix(a,b);
	for(int i=0;i<N;i++)
	{
		ans->S[i][(i+1)%N]=-INF;
		Solve(i,i+2,i+N,i+1,i+N-1,ans,a,b);
	}
	return ans;
}
void ExtractPath(Matrix *o,const int l,const int r,vector<int>&output)
{
	if(!o->ch[0])return;
	const int mid=o->MID[l%N][r%N];
	assert(mid!=-1);
	ExtractPath(o->ch[0],l,mid,output);
	output.push_back(mid);
	ExtractPath(o->ch[1],mid,r,output);
}
struct Opl
{
	double ANGLE;
	int ID;
	bool operator<(const Opl &o)const{return ANGLE<o.ANGLE;}
};
Opl OPL[2000];
double DP[2000][2000];
int main()
{
	freopen("post.in","r",stdin);
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lf",&OPL[i].ANGLE),OPL[i].ID=i+1;
		sort(OPL,OPL+N);
		for(int i=0;i<N;i++)OPL[N+i].ID=OPL[i].ID,OPL[N+i].ANGLE=OPL[i].ANGLE+2.0*PI;
		static Matrix *m[12];
		vector<Matrix*>trash;
		trash.push_back(m[0]=new Matrix(NULL,NULL));
		for(int i=0;i<N;i++)for(int j=i+1;j<i+N;j++)
		{
			double &v=m[0]->S[i%N][j%N]=-INF;
			if(OPL[j].ANGLE-OPL[i].ANGLE-EPS<=PI)v=0.5*sin(OPL[j].ANGLE-OPL[i].ANGLE);
		}
		int bound=0;
		for(int i=1;(1<<i)<=K;i++)trash.push_back(m[i]=Mul(m[i-1],m[i-1])),bound=i;
		Matrix *mans=NULL;
		for(int i=bound;i>=0;i--)if(K&(1<<i))
		{
			if(!mans)mans=m[i];
			else trash.push_back(mans=Mul(mans,m[i]));
		}
		double ans=0.0;
		int best_loc=-1;
		for(int i=0;i<N;i++)if(getmax(ans,mans->S[i][i]))best_loc=i;
//		printf("%.3lf\n",ans);
		if(best_loc==-1)puts("0");
		else
		{
			vector<int>path;
			path.push_back(best_loc);
			ExtractPath(mans,best_loc,best_loc+N,path);
			for(int &v:path)v%=N;
			sort(path.begin(),path.end());
			for(int i=0;i<(int)path.size();i++)
			{
				if(i)putchar(' ');
				printf("%d",OPL[path[i]].ID);
			}
			puts("");
			assert((int)path.size()==K);
		}
		for(Matrix *v:trash)delete v;
	}
	return 0;
}
