#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
struct Dp
{
	double S[3000][3000];
	vector<int>VIS;
	Dp(){for(int i=0;i<3000;i++)for(int j=0;j<3000;j++)S[i][j]=-1.0;}
	void Set(int i,int j,double a)
	{
		if(S[i][j]==-1.0)VIS.push_back(i*3000+j);
		S[i][j]=a;
	}
	double operator()(int i,int j)const{return S[i][j];}
	void Clear()
	{
		for(const auto &i:VIS)S[i/3000][i%3000]=-1.0;
		VIS.clear();
	}
}DP1,DP2;
int D,B;
int Get(int v,int i)
{
	while(i--)v/=B+1;
	return v%=B+1;
}
void Set(int &v,int i,int d)
{
	assert(Get(v,i)==B);
	d=d-B;
	while(i--)d*=B+1;
	v+=d;
}
double T(double v)
{
	if(v==-2.0)return -2.0;
	return 1.0-v;
}
double GetDP1(int a,int b,int step)
{
	if(DP1(a,b)!=-1.0)return DP1(a,b);
	if(step==D*2)
	{
		int av=0,bv=0;
		for(int i=0,v=1,ta=a,tb=b;i<D;i++,v*=B+1,ta/=B+1,tb/=B+1)
		{
			assert(ta%(B+1)!=B&&tb%(B+1)!=B);
			av+=v*(ta%(B+1));
			bv+=v*(tb%(B+1));
		}
		double ans=(a==b?-2.0:(a>b?1.0:0.0));
		DP1.Set(a,b,ans);
		return ans;
	}
	if(step%2==0)
	{
		double ans=0.0;
		for(int d=0;d<B;d++)
		{
			double ta=-3.0;
			for(int i=0;i<D;i++)if(Get(a,i)==B)
			{
				int nxta=a;
				Set(nxta,i,d);
				getmax(ta,T(GetDP1(nxta,b,step+1)));
			}
			assert(ta!=-3.0);
			ans+=(ta==-2.0?0.0:ta);
		}
		ans/=B;
		DP1.Set(a,b,ans);
		return ans;
	}
	else
	{
		double ans=0.0;
		for(int d=0;d<B;d++)
		{
			double ta=-3.0;
			for(int i=0;i<D;i++)if(Get(b,i)==B)
			{
				int nxtb=b;
				Set(nxtb,i,d);
				getmax(ta,T(GetDP1(a,nxtb,step+1)));
			}
			assert(ta!=-3.0);
			ans+=ta;
		}
		ans/=B;
		DP1.Set(a,b,ans);
		return ans;
	}
}
int F()
{
	int ans=1;
	for(int i=0;i<D;i++)ans*=B+1;
	return --ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&D,&B)==2)
	{
		if(D==0&&B==0)break;
		DP1.Clear();
		printf("%.10f\n",GetDP1(F(),F(),0));
	}
	return 0;
}
