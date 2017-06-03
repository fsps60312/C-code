#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct Matrix
{
	int S[1<<5][1<<5];
};
void SubtractBy1(vector<int>&s)
{
	--s[0];
	for(int i=0;i<(int)s.size()&&s[i]<0;i++)s[i]+=10,--s[i+1];
	while(!s.empty()&&s.back()==0)s.pop_back();
}
void DivideBy2(vector<int>&s)
{
	for(int i=(int)s.size()-1,v=0;i>=0;i--)
	{
		v=v*10+s[i];
		s[i]=v/2;
		v%=2;
	}
	if(s.back()==0)s.pop_back();
}
int M,P;
Matrix operator*(const Matrix &a,const Matrix &b)
{
	Matrix ans;
	for(int i=0;i<(1<<M);i++)for(int j=0;j<(1<<M);j++)
	{
		int &v=ans.S[i][j]=0;
		for(int k=0;k<(1<<M);k++)(v+=a.S[i][k]*b.S[k][j])%=P;
	}
	return ans;
}
Matrix Pow(Matrix a,vector<int>p)
{
	Matrix ans;
	for(int i=0;i<(1<<M);i++)for(int j=0;j<(1<<M);j++)ans.S[i][j]=(i==j?1:0);
	for(;!p.empty();a=a*a,DivideBy2(p))
	{
//		putchar(':');for(int i=(int)p.size()-1;i>=0;i--)putchar('0'+p[i]);puts("");
		if(p[0]&1)ans=ans*a;
	}
	return ans;
}
vector<int>N;
void ReadInput()
{
	static char str[102];
	scanf("%s%d%d",str,&M,&P);
	int i=-1;while(str[++i]);
	N.clear();
	for(--i;i>=0;i--)N.push_back(str[i]-'0');
}
bool Same(const int a,const int b,const int v1,const int v2){return (a==v1&&b==v1)||(a==v2&&b==v2);}
int GetElement(const int a,const int b)
{
	for(int i=0;i<M-1;i++)if(Same((a>>i)&3,(b>>i)&3,0,3))return 0;
	return 1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int testcount;scanf("%d",&testcount)==1;)while(testcount--)
	{
		ReadInput();
		SubtractBy1(N);
		Matrix a;
		for(int i=0;i<(1<<M);i++)for(int j=0;j<(1<<M);j++)a.S[i][j]=GetElement(i,j);
		a=Pow(a,N);
		int ans=0;
		for(int i=0;i<(1<<M);i++)for(int j=0;j<(1<<M);j++)(ans+=a.S[i][j])%=P;
		printf("%d\n",ans);
	}
	return 0;
}
