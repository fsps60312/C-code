#include<cstdio>
typedef long long LL;
const double INF=1e100;
LL N,A,B,C,S[1000001],SUM[1000001],DP[1000001];
LL Sum(const LL &l,const LL &r){return SUM[r]-SUM[l-1LL];}
LL Adjust(const LL &v){return A*v*v+C;}
void GetAB(const int &i,double &a,double &b){a=-2.0*A*SUM[i],b=double(A)*SUM[i]*SUM[i]+DP[i]+C;}
double Intersect(const int &l,const int &r)
{
	static double a1,b1,a2,b2;
	GetAB(l,a1,b1),GetAB(r,a2,b2);
	//a1x+b1==a2x+b2
	return (b2-b1)/(a1-a2);
}
struct Deq
{
	int s[1000001];
	int l,r;
	void clear(){l=0,r=-1;}
	int size(){return r-l+1;}
	double front(){return Intersect(s[l],s[l+1]);}
	double back(){return Intersect(s[r-1],s[r]);}
	double back(const int &i){return Intersect(s[r-1],i);}
	void push_back(const int &i){s[++r]=i;}
	void pop_front(){l++;}
	void pop_back(){r--;}
	int frontidx(){return s[l];}
}DEQ;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld%lld%lld%lld",&N,&A,&B,&C);
	for(LL i=1LL;i<=N;i++)scanf("%lld",&S[i]);
	DP[0]=SUM[0]=0LL;
	for(LL i=1LL;i<=N;i++)SUM[i]=SUM[i-1LL]+S[i];
	DEQ.clear();
	DEQ.push_back(0);
	for(LL i=1LL;i<=N;i++)
	{
		//DP[j]+A(SUM[i]*SUM[i]+SUM[j]*SUM[j]-2*SUM[i]*SUM[j])+C=DP[i]
		//DP[i]=A(SUM[i]*SUM[i]+SUM[j]*SUM[j]-2*SUM[i]*SUM[j])+DP[j]+C
		//DP[i]=A*SUM[i]*SUM[i]+A*SUM[j]*SUM[j]-2A*SUM[i]*SUM[j]+DP[j]+C
		//DP[i]=(A*SUM[i]*SUM[i]+C)+(A*SUM[j]*SUM[j]+DP[j])-2A*SUM[i]*SUM[j]
		//DP[r]=(A*SUM[r]*SUM[r])+(A*SUM[l]*SUM[l]+DP[l])-2A*SUM[r]*SUM[l]+C
		//x=SUM[r]
		//F=(A*SUM[l]*SUM[l]+DP[l])-2A*x*SUM[l]+C
		//=(-2A*SUM[l])x+(A*SUM[l]*SUM[l]+DP[l]+C)
		while(DEQ.size()>=2&&DEQ.front()<=double(SUM[i]))DEQ.pop_front();
		DP[i]=DP[DEQ.frontidx()]+Adjust(SUM[i]-SUM[DEQ.frontidx()]);
		while(DEQ.size()>=2&&DEQ.back()>=DEQ.back(i))DEQ.pop_back();
		DEQ.push_back(i);
//		printf("DP[%lld]=%lld\n",i,DP[i]);
	}
	printf("%lld\n",DP[N]+B*SUM[N]);
	return 0;
}
