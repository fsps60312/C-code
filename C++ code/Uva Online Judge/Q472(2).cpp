#include<cstdio>
#include<cmath>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-8;
bool Zero(const double &a){return fabs(a)<EPS;}
struct Complex
{
	double a,b;
	Complex(){}
	Complex(const double &_a,const double &_b):a(_a),b(_b){}
	bool IsZero()const{return Zero(a)&&Zero(b);}
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
	void operator+=(const Complex &c){a+=c.a,b+=c.b;}
	Complex operator+(const Complex &c)const{return Complex(a+c.a,b+c.b);}
	bool Digit(const char c){return c>='0'&&c<='9';}
	void GetDouble(double &ans,char* &ptr)
	{
		double sign=1.0;
		ans=0.0;
		char c=*(ptr++);
		while(!Digit(c)&&c!='.'&&c!='-')c=*(ptr++);
		if(c=='-')sign=-1.0,c=*(ptr++);
		if(Digit(c)){while(Digit(c))ans*=10.0,ans+=c-'0',c=*(ptr++);}
		if(c=='.')
		{
			double tmp=0.1;
			for(c=*(ptr++);Digit(c);c=*(ptr++),tmp*=0.1)ans+=tmp*(double)(c-'0');
		}
		ans*=sign;
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
}A,TMP;
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
void Print(const Complex &c){printf("(%.5f,%.5f)\n",c.a,c.b);}
double Round(const double &v)
{
	double ans=round(v*10.0)/10.0;
	return Zero(ans)?0.0:ans;
}
int main()
{
//	Print(Complex(-9.0,5.2)*Complex(1.0,-0.4)+Complex(-10.0,2.8)*Complex(-0.6,0.2));
//	Print(Complex(1.4,-3.9)*Complex(1.0,-0.4)+Complex(-6.6,-9.0)*Complex(-0.6,0.2));
//	Print(Complex(-9.0,5.2)*Complex(0.3,1.2)+Complex(-10.0,2.8)*Complex(0.4,-0.8));
//	Print(Complex(1.4,-3.9)*Complex(0.3,1.2)+Complex(-6.6,-9.0)*Complex(0.4,-0.8));
//	return 0;
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(;;)
	{
		static int kase=0;
		TN=-1;
		N=0;while(Input())N++;
		if(!N)break;
		if(kase++)puts("");
		assert(TN==N+1);
		TMP=A;
		if(!Solve())puts("No solution");
		else
		{
			vector<Complex>all;
			for(int i=0;i<N;i++)
			{
				const Complex ans=A.s[i][N]/A.s[i][i];
				all.push_back(ans);
				printf("(%.1f,%.1f)\n",Round(ans.a),Round(ans.b));
			}
			for(int i=0;i<N;i++)
			{
				Complex tmp=Complex(0.0,0.0);
				for(int j=0;j<N;j++)tmp+=TMP.s[i][j]*all[j];
//				if(!(tmp==TMP.s[i][N]))
//				printf("(%.5f,%.5f)==(%.5f,%.5f)\n",tmp.a,tmp.b,TMP.s[i][N].a,TMP.s[i][N].b);
				assert(tmp==TMP.s[i][N]);
			}
		}
//		break;
	}
	return 0;
}
