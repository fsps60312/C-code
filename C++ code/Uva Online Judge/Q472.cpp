#include<cstdio>
#include<cmath>
#include<cassert>
#include<algorithm>
using namespace std;
const double EPS=1e-9;
struct Complex
{
	double a,b;
	Complex(){}
	Complex(const double &_a,const double &_b):a(_a),b(_b){}
	bool IsZero()const{return Zero(a)&&Zero(b);}
	bool Zero(const double &a)const{return fabs(a)<EPS;}
	bool operator==(const Complex &c)const{return Zero(a-c.a)&&Zero(b-c.b);}
	Complex operator*(const Complex &c)const{return Complex(a*c.a-b*c.b,a*c.b+c.a*b);}
	//(a,b)*(x,y)=(c,d)
	//ax-by==c
	//bx+ay==d
	//aay+bby==ad-bc
	//y==(ad-bc)/(aa+bb)
	//aax+bbx==ac+bd
	//x==(ac+bd)/(aa+bb)
	Complex operator/(const Complex &c)const
	{
		Complex ans=Complex((c.a*a+c.b*b)/(c.a*c.a+c.b*c.b),(c.a*b-c.b*a)/(c.a*c.a+c.b*c.b));
		assert(ans*c==(*this));
		return ans;
	}
	void operator-=(const Complex &c){a-=c.a,b-=c.b;}
	bool Digit(const char c){return c>='0'&&c<='9';}
	void GetDouble(double &ans,char* &ptr)
	{
		ans=0.0;
		char c=*(ptr++);
		while(!Digit(c)&&c!='.')c=*(ptr++);
		if(Digit(c)){while(Digit(c))ans*=10.0,ans+=c-'0',c=*(ptr++);}
		if(c=='.')
		{
			double tmp=0.1;
			for(c=*(ptr++);Digit(c);c=*(ptr++),tmp*=0.1)ans+=tmp*(double)(c-'0');
		}
//		printf("%.5f\n",ans);
	}
	void Input(char* &ptr){GetDouble(a,ptr),GetDouble(b,ptr);}
};
int N,TN;
struct Matrix
{
	Complex s[99][100];
	void Swap(const int r1,const int r2){for(int i=0;i<=N;i++)swap(s[r1][i],s[r2][i]);}
	void Sub(const int r1,const int r2,const Complex &ratio){if(ratio.IsZero())return;for(int i=0;i<=N;i++)s[r1][i]-=s[r2][i]*ratio;}
}A;
bool Input()
{
	static char tmp[1000000];
	if(!fgets(tmp,1000000,stdin))return false;
	int cnt=0;
	for(int i=0;tmp[i];i++)if(tmp[i]=='(')cnt++;
	if(!cnt)return false;
	assert(TN==-1||TN==cnt);
	TN=cnt;
	char *ptr=tmp;
	for(int i=0;i<cnt;i++)A.s[N][i].Input(ptr);
}
bool Solve()
{
	for(int i=0;i<N;i++)
	{
		if(A.s[i][i].IsZero())
		{
			bool found=false;
			for(int j=i+1;j<N;j++)if(!A.s[j][i].IsZero()){A.Swap(i,j);found=true;break;}
			if(!found)return false;
		}
		for(int j=i+1;j<N;j++)A.Sub(j,i,A.s[j][i]/A.s[i][i]),assert(A.s[j][i].IsZero());
	}
	for(int i=N-1;i>=0;i--)for(int j=i-1;j>=0;j--)A.Sub(j,i,A.s[j][i]/A.s[i][i]),assert(A.s[j][i].IsZero());
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	for(;;)
	{
		static int kase=0;
		TN=-1;
		N=0;while(Input())N++;
		if(!N)break;
		if(kase++)puts("");
//		printf("TN=%d,N=%d\n",TN,N);
		assert(TN==N+1);
		if(!Solve())puts("No solution");
		else
		{
			for(int i=0;i<N;i++)
			{
				const Complex ans=A.s[i][N]/A.s[i][i];
				printf("(%.1f,%.1f)\n",ans.a,ans.b);
			}
		}
	}
	return 0;
}
