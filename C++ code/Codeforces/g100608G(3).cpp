#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<cstdlib>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
struct Dp
{
	pair<double,double>S[3000][3000];
	bool VIS[3000][3000];
	vector<int>HIS;
	Dp(){for(int i=0;i<3000;i++)for(int j=0;j<3000;j++)VIS[i][j]=false;}
	inline void Set(int i,int j,pair<double,double>a)
	{
		if(!VIS[i][j])VIS[i][j]=true,HIS.push_back(i*3000+j);
		S[i][j]=a;
	}
	inline pair<double,double>operator()(int i,int j)const{return S[i][j];}
	inline void Clear()
	{
		for(const auto &i:HIS)VIS[i/3000][i%3000]=false;
		HIS.clear();
	}
};
int D,B;
int _Get[3000][10];
inline int Get(int v,int i)
{
	return _Get[v][i];
}
inline int RawGet(int v,int i)
{
	while(i--)v/=B+1;
	return v%=B+1;
}
int _Set[10][10];
inline void Set(int &v,int i,int d)
{
	assert(Get(v,i)==B&&0<=d&&d<B);
	v+=_Set[i][d];
}
inline int RawSet(int i,int d)
{
	d=d-B;
	while(i--)d*=B+1;
	return d;
}
inline pair<double,double>T(pair<double,double> v)
{
	return make_pair(1.0-v.first-v.second,v.second);
}
Dp DP2;
pair<double,double>GetDP2(int a,int b,int step)
{
	if(DP2.VIS[a][b])return DP2(a,b);
	if(step==D*2)
	{
		pair<double,double>ans=make_pair(0.0,1.0);
		for(int i=D-1;i>=0;i--)if(Get(a,i)!=Get(b,i))
		{
			ans=make_pair(Get(a,i)>Get(b,i)?1.0:0.0,0.0);
			break;
		}
		DP2.Set(a,b,ans);
		return ans;
	}
	if(step<D)
	{
		pair<double,double>ans=make_pair(0.0,0.0);
		for(int d=0;d<B;d++)
		{
			pair<double,double>ta=make_pair(-1.0,-1.0);
			for(int i=0;i<D;i++)if(Get(a,i)==B)
			{
				int nxta=a;
				Set(nxta,i,d);
				getmax(ta,step%D==D-1?T(GetDP2(nxta,b,step+1)):GetDP2(nxta,b,step+1));
			}
			assert(ta.first!=-1.0);
			ans.first+=ta.first,ans.second+=ta.second;
		}
		ans.first/=B,ans.second/=B;
		DP2.Set(a,b,ans);
		return ans;
	}
	else
	{
		pair<double,double>ans=make_pair(0.0,0.0);
		for(int d=0;d<B;d++)
		{
			pair<double,double>ta=make_pair(-1.0,-1.0);
			for(int i=0;i<D;i++)if(Get(b,i)==B)
			{
				int nxtb=b;
				Set(nxtb,i,d);
				getmax(ta,step%D==D-1?T(GetDP2(a,nxtb,step+1)):GetDP2(a,nxtb,step+1));
			}
			assert(ta.first!=-1.0);
			ans.first+=ta.first,ans.second+=ta.second;
		}
		ans.first/=B,ans.second/=B;
		DP2.Set(a,b,ans);
		return ans;
	}
}
Dp DP1;
pair<double,double>GetDP1(int a,int b,int step)
{
	if(DP1.VIS[a][b])return DP1(a,b);
	if(step==D*2)
	{
		pair<double,double>ans=make_pair(0.0,1.0);
		for(int i=D-1;i>=0;i--)if(Get(a,i)!=Get(b,i))
		{
			ans=make_pair(Get(a,i)>Get(b,i)?1.0:0.0,0.0);
			break;
		}
		DP1.Set(a,b,ans);
		return ans;
	}
	if(step%2==0)
	{
		pair<double,double>ans=make_pair(0.0,0.0);
		for(int d=0;d<B;d++)
		{
			pair<double,double>ta=make_pair(-1.0,-1.0);
			for(int i=0;i<D;i++)if(Get(a,i)==B)
			{
				int nxta=a;
				Set(nxta,i,d);
				getmax(ta,T(GetDP1(nxta,b,step+1)));
			}
			assert(ta.first!=-1.0);
			ans.first+=ta.first,ans.second+=ta.second;
		}
		ans.first/=B,ans.second/=B;
		DP1.Set(a,b,ans);
		return ans;
	}
	else
	{
		pair<double,double>ans=make_pair(0.0,0.0);
		for(int d=0;d<B;d++)
		{
			pair<double,double>ta=make_pair(-1.0,-1.0);
			for(int i=0;i<D;i++)if(Get(b,i)==B)
			{
				int nxtb=b;
				Set(nxtb,i,d);
				getmax(ta,T(GetDP1(a,nxtb,step+1)));
			}
			assert(ta.first!=-1.0);
			ans.first+=ta.first,ans.second+=ta.second;
		}
		ans.first/=B,ans.second/=B;
		DP1.Set(a,b,ans);
		return ans;
	}
}
inline int F()
{
	int ans=1;
	for(int i=0;i<D;i++)ans*=B+1;
	return --ans;
}
inline long long Pow(long long a,int b)
{
	long long ans=1;
	for(int i=0;i<b;i++)ans*=a;
	return ans;
}
void gen()
{
	freopen("in.txt","w",stdout);
	for(int d=1;d<=10;d++)for(int b=2;b<=10;b++)if(Pow(b+1,d)<3000.1)
	{
		printf("%d %d\n",d,b);
	}
	exit(0);
}
inline pair<double,double>Solve()
{
	DP1.Clear(),DP2.Clear();
	int mx=(int)Pow(B+1,D);
	for(int i=0;i<mx;i++)for(int j=0;j<D;j++)_Get[i][j]=RawGet(i,j);
	for(int j=0;j<D;j++)for(int k=0;k<B;k++)_Set[j][k]=RawSet(j,k);
//	return make_pair(0.0,0.0);
	const auto &p=GetDP1(F(),F(),0);
	return make_pair(p.first,1.0-p.first-p.second);
}
#include<map>
map<pair<int,int>,pair<double,double> >ANS;
inline pair<double,double>GetANS()
{
	{
		const auto &it=ANS.find(make_pair(D,B));
		if(it!=ANS.end())return it->second;
	}
	return ANS[make_pair(D,B)]=Solve();
}
int main()
{
//	gen();
	freopen("in.txt","r",stdin);
//	freopen("greater.in","r",stdin);
//	freopen("greater.out","w",stdout);
	while(scanf("%d%d",&D,&B)==2)
	{
		if(D==0&&B==0)break;
		const auto &ans=GetANS();
		printf("%.10f %.10f\n",ans.first,ans.second);
		assert(ans.first<=ans.second+1e-9);
	}
	return 0;
}
