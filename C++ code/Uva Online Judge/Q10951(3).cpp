#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<map>
using namespace std;
int P;
int mod(int a){return (a%P+P)%P;}
int max(int a,int b){return a>b?a:b;}
int log(int a,int b)//a*?===b
{
	int q=sqrt(P)+1;
	map<int,int> m;
	for(int i=0;i<q;i++)
	{
		int md=mod(a*i);
		if(md==b)return i;
		if(m.find(md)==m.end())m[md]=i;
	}
	for(int i=1;i<=q;i++)
	{
		b=mod(b-a*q);
		if(m.find(b)!=m.end())return m[b]+i*q;
	}
	return -1;
}
struct Polynomial
{
	int DEGREE,COE[101];
	void scanfp()
	{
		scanf("%d",&DEGREE);
		for(int i=DEGREE;i>=0;i--)
		{
			scanf("%d",&COE[i]);
		}
		carry();
	}
	void carry()
	{
		for(int i=0;i<=DEGREE;i++)
		{
			COE[i]=mod(COE[i]);
		}
		while(!COE[DEGREE]&&DEGREE>=0)DEGREE--;
	}
	Polynomial operator<<(int a)
	{
		Polynomial ans;
		ans.DEGREE=DEGREE+a;
		for(int i=DEGREE;i>=0;i--)
		{
			ans.COE[i+a]=COE[i];
		}
		for(int i=a-1;i>=0;i--)
		{
			ans.COE[i]=0;
		}
		return ans;
	}
	Polynomial operator*(int a)
	{
		Polynomial ans;
		ans.DEGREE=DEGREE;
		for(int i=0;i<=DEGREE;i++)
		{
			ans.COE[i]=COE[i]*a;
		}
		ans.carry();
		return ans;
	}
	Polynomial operator-(Polynomial a)
	{
		Polynomial ans;
		ans.DEGREE=max(DEGREE,a.DEGREE);
		for(int i=0;i<=ans.DEGREE;i++)
		{
			int &coe=ans.COE[i];
			coe=0;
			if(i<=DEGREE)coe+=COE[i];
			if(i<=a.DEGREE)coe-=a.COE[i];
		}
		ans.carry();
		return ans;
	}
	Polynomial operator-=(Polynomial a){return (*this)=((*this)-a);}
	Polynomial operator%(Polynomial a)
	{
		Polynomial up;
		up.DEGREE=DEGREE;
		for(int i=0;i<=DEGREE;i++)up.COE[i]=COE[i];
		//printf("up=");up.show();printf("\na=");a.show();printf("\n");
		for(int i=DEGREE-a.DEGREE;i>=0;i--)
		{
			if(!up.COE[i+a.DEGREE])continue;
			Polynomial p=(a<<i);
			up-=(p*log(p.COE[i+a.DEGREE],up.COE[i+a.DEGREE]));
			/*for(int j=1;j<P;j++)
			{
				if((p*j).COE[i+a.DEGREE]==up.COE[i+a.DEGREE])
				{
					up-=(p*j);
					break;
				}
			}*/
			//printf("%%");up.show();printf("\n");
		}
		up.carry();
		return up;
	}
	Polynomial operator/=(int a)
	{
		int p=log(a,1);
		/*for(p=1;p<P;p++)
		{
			if(mod(p*a)==1)break;
		}*/
		for(int i=0;i<=DEGREE;i++)
		{
			COE[i]*=p;
		}
		carry();
		return (*this);
	}
	void show()
	{
		printf(" %d",DEGREE);
		for(int i=DEGREE;i>=0;i--)printf(" %d",COE[i]);
	}
}P1,P2;
Polynomial gcd(Polynomial a,Polynomial b)
{
	if(b.DEGREE>a.DEGREE)return gcd(b,a);
	if(b.DEGREE<0)return a;
	return gcd(b,a%b);
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&P)==1&&P)
	{
		P1.scanfp();
		P2.scanfp();
		//P1.show();printf("\n");
		//P2.show();printf("\n");
		//(P1*2).show();printf("\n");
		//(P2%P1).show();printf("\n");
		//return 0;
		Polynomial ans=gcd(P1,P2);
		ans/=ans.COE[ans.DEGREE];
		printf("Case %d:",kase++);
		ans.show();
		printf("\n");
	}
	return 0;
}
