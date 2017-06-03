#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long LL;
//typedef double fraction;
LL T,n,m,vars;
//LL abs(LL a){return a>=0?a:-a;}
LL gcd(LL a,LL b)
{
	if(a<0) a=-a;
	if(b<0) b=-b;
	if(a<b) a^=b^=a^=b;
	return b==0?a:gcd(b,a%b);
}
/*struct fraction
{
	double up;
	double down;
	fraction(){up=0,down=1;}
	fraction(double a){up=a,down=1;}
	double value(){return up;}
	fraction operator+(fraction a){fraction ans=up+a.up;return ans;}
	fraction operator+=(fraction a){return (*this)=(*this)+a;}
	fraction operator-(fraction a){fraction ans=up-a.up;return ans;}
	fraction operator-(){fraction ans=-up;return ans;}
	fraction operator-=(fraction a){return (*this)=(*this)-a;}
	fraction operator*(fraction a){fraction ans=up*a.up;return ans;}
	fraction operator*=(fraction a){return (*this)=(*this)*a;}
	fraction operator/(fraction a){fraction ans=up/a.up;return ans;}
	fraction operator/=(fraction a){return (*this)=(*this)/a;}
	bool iszero(){return up>=-1e-5&&up<=1e-5;}
	bool operator>(fraction a){return up>a.up;}
	bool operator<(fraction a){return up<a.up;}
	bool operator==(fraction a){return up==a.up;}
	bool operator!=(fraction a){return up!=a.up;}
};*/
struct fraction
{
	LL up;
	LL down;
	fraction()
	{
		up=0;
		down=1;
	}
	fraction(LL a)
	{
		up=a;
		down=1;
	}
	double value()
	{
		return (double)up/down;
	}
	bool operator>(fraction a)
	{
		return value()>a.value();
	}
	fraction operator/(fraction a)
	{
		fraction ans;
		ans.up=up;
		ans.down=down;
		ans.up*=a.down;
		ans.down*=a.up;
		ans.carry();
		return ans;
	}
	fraction operator/=(fraction a)
	{
		return (*this)=(*this)/a;
	}
	fraction operator+(fraction a)
	{
		fraction ans;
		ans.down=down*a.down;
		ans.up=up*a.down+a.up*down;
		//printf("%.2lf+%.2lf=%.2lf\n",value(),a.value(),ans.value());
		ans.carry();
		return ans;
	}
	fraction operator+=(fraction a)
	{
		//printf("ha\n");
		return (*this)=(*this)+a;
	}
	fraction operator-()
	{
		fraction ans;
		ans.up=-up;
		ans.down=down;
		return ans;
	}
	fraction operator-(fraction a)
	{
		fraction ans;
		ans.down=down*a.down;
		ans.up=up*a.down-a.up*down;
		return ans;
	}
	fraction operator-=(fraction a)
	{
		return (*this)=(*this)-a;
	}
	fraction operator*(fraction a)
	{
		fraction ans;
		ans.up=up*a.up;
		ans.down=down*a.down;
		ans.carry();
		return ans;
	}
	bool operator==(fraction a)
	{
		return value()==a.value();
	}
	bool operator!=(fraction a)
	{
		return value()!=a.value(); 
	}
	bool iszero()
	{
		return value()>=-1e-5&&value()<=1e-5;
	}
	void carry()
	{
		LL a=gcd(up,down);
		up/=a;
		down/=a;
		if(down<0)
		{
			up*=-1;
			down*=-1;
		}
		while(up>2147483647||down>2147483647)
		{
			up>>=1,down>>=1;
		}
	}
};
fraction resis[200][200];
fraction allans[200][200];
LL equate[200];
LL input[200][3];
LL leader[200];
struct volttype
{
	bool vis;
	LL index,thisindex;
	fraction voltage;
	vector<int> to;
	fraction equation[200];
	void setequation()
	{
		for(LL i=0;i<vars;i++) equation[i]=0;
		for(LL i=0;i<to.size();i++)
		{
			LL j=to[i];
			//(Vj-Vi)/resis[i][j]
			//printf("%.2lf+%.2lf=",equation[j].value(),((fraction)1/resis[thisindex][j]).value());
			equation[j]+=(fraction)1/resis[thisindex][j];
			//printf("%.2lf\n",equation[j].value());
			equation[thisindex]-=(fraction)1/resis[thisindex][j];
		}
	}
};
volttype volt[200];
LL fin(LL a)
{
	if(leader[a]==a) return a;
	return leader[a]=fin(leader[a]);
}
struct Matrix
{
	LL nn,mm;
	fraction s[200][200];
	void exchange(LL a,LL b)
	{
		fraction c;
		for(LL i=0;i<m;i++)
		{
			c=s[a][i];
			s[a][i]=s[b][i];
			s[b][i]=c;
		}
	}
	void addto(LL a,LL b,fraction c)
	{
		//printf("addto%.2lf %.2lf %.2lf",s[a][6].value(),s[b][6].value(),c.value());
		for(LL i=0;i<m;i++)
		{
			//printf(" %lld",i);//find:after 6 fail
			/*if(s[b][i].down==0||s[a][i].down==0||c.down==0)
			{
				printf("fail\n");
			}
		if(i==6)
		{
			printf(" %lld/%lld+",s[b][i].up,s[b][i].down);
			printf("%lld/%lld*%lld/%lld=",(s[a][i]).up,(s[a][i]).down,c.up,c.down);
		}*/
			s[b][i]+=s[a][i]*c;
		//if(i==6)printf("%lld/%lld",s[b][i].up,s[b][i].down);
		}
	}
	void makeI()
	{
		for(LL i=0;i<nn;i++)
		{
			LL Max=i;
			if(s[i][i].iszero())
			{
				for(LL j=i+1;j<nn;j++)
				{
					if(s[j][i]>s[Max][i]) Max=j;
				}
				if(s[Max][i].iszero()) continue;
				exchange(i,Max);
			}
			for(LL j=i+1;j<nn;j++)
			{
				fraction k=-s[j][i]/s[i][i];
				//printf("k=%.2lf,j=%lld,",k.value(),j);
				addto(i,j,k);
				//printf("pass\n");
			}
		}
		//show();
		for(LL i=nn-1;i>=0;i--)
		{
			if(s[i][i].iszero()) continue;
			for(LL j=i-1;j>=0;j--)
			{
				fraction k=-s[j][i]/s[i][i];
		//printf("%.2lfpass\n",k.value());
				addto(i,j,k);
			}
		}
		for(LL i=0;i<nn;i++)
		{
			if(s[i][i].iszero()) continue;
			s[i][mm-1]/=s[i][i];
			s[i][i]/=s[i][i];
		}
	}
	void show()
	{
		for(LL i=0;i<nn;i++)
		{
			for(LL j=0;j<mm;j++)
			{
				printf(" %.2lf",s[i][j].value());
			}
			printf("\n");
		}
	}
};
Matrix MakeMatrix(LL a,LL b)
{
	Matrix ans;
	ans.nn=a,ans.mm=b;
	for(LL i=0;i<a;i++)
	{
		for(LL j=0;j<b;j++)
		{
			ans.s[i][j]=0;
		}
	}
	return ans;
}
fraction solve(LL a,LL b)
{
	vector<int> g;
	for(LL i=0;i<vars;i++) volt[i].vis=false;
	for(LL i=0;i<n;i++)
	{
		if(leader[i]==leader[a]&&equate[i]!=equate[a]&&equate[i]!=equate[b]&&!volt[equate[i]].vis)
		{
			volt[equate[i]].index=g.size();
			g.push_back(equate[i]);
			volt[equate[i]].vis=true;
		}
	}
	//printf("g:");for(LL i=0;i<g.size();i++) printf(" %lld",g[i]);printf("\n");
	Matrix a1=MakeMatrix(g.size(),g.size()+1);
	//printf("a1:\n");a1.show();
	for(LL i=0;i<g.size();i++)
	{
		for(LL j=0;j<vars;j++)
		{
			//if(!volt[j].vis) continue;
			if(j==equate[a])
			{
				a1.s[i][g.size()]-=volt[g[i]].equation[j];
			}
			else if(volt[j].vis)
			{
			//printf("%lld %lld %.2lf %.2lfpass\n",i,volt[j].index,a1.s[i][volt[j].index].value(),volt[g[i]].equation[j].value());
				a1.s[i][volt[j].index]+=volt[g[i]].equation[j];
			}
		}
	}
	//printf("a1:\n");a1.show();
	a1.makeI();
	//printf("solve()\n");
	//printf("a1:\n");a1.show();
	for(LL i=0;i<g.size();i++)
	{
		volt[g[i]].voltage=a1.s[i][g.size()];
	}
	fraction ans=0;//current
	volt[a].voltage=1;
	volt[b].voltage=0;
	for(LL i=0;i<volt[equate[b]].to.size();i++)
	{
		LL j=volt[equate[b]].to[i];
		//if(!volt[j].vis) continue;
		//printf("%.2lf+%.2lf(%.2lf)=",ans.value(),(volt[j].voltage/resis[b][j]).value(),volt[j].voltage.value());
		ans+=volt[j].voltage/resis[b][j];
		//printf("%.2lf\n",ans.value());
	}
	return (fraction)1/ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	for(LL kase=1;kase<=T;kase++)
	{
		scanf("%lld%lld",&n,&m);
		for(LL i=0;i<n;i++)
		{
			equate[i]=i;
			leader[i]=i;
			for(LL j=0;j<n;j++)
			{
				resis[i][j]=(i==j?0:-1);
				allans[i][j]=-1;
			}
		}
		for(LL i=0,a,b,c;i<m;i++)
		{
			scanf("%lld%lld%lld",&a,&b,&c);
			leader[fin(a)]=fin(b);
			input[i][0]=a,input[i][1]=b,input[i][2]=c;
			if(resis[a][b]>0)
			{
				fraction d=resis[a][b];
				resis[a][b]=resis[b][a]=(fraction)1/((fraction)1/d+(fraction)1/c);
			}
			else if(resis[a][b]==-1) resis[a][b]=resis[b][a]=c;
		}
		for(LL i=0;i<n;i++)
		{
			leader[i]=fin(i);
			for(LL j=i+1;j<n;j++)
			{
				if(resis[i][j]==0)
				{
					equate[j]=i;
				}
			}
		}
		vars=0;
		for(LL i=0;i<n;i++)
		{
			if(equate[i]!=i)
			{
				equate[i]=equate[equate[i]];
			}
			else equate[i]=vars++;
		}
		for(LL i=0;i<vars;i++)
		{
			volt[i].to.clear();
			volt[i].thisindex=i;
			for(LL j=0;j<vars;j++)
			{
				resis[i][j]=(i==j?0:-1);
			}
		}
		for(LL i=0,a,b;i<m;i++)
		{
			double c;
			a=equate[input[i][0]],b=equate[input[i][1]],c=input[i][2];
			if(resis[a][b]==-1) resis[a][b]=resis[b][a]=c;
			else if(a!=b)
			{
				fraction d=resis[a][b];
				resis[a][b]=resis[b][a]=(fraction)1/((fraction)1/d+(fraction)1/c);
			}
		}
		/*printf("resis:\n");
		for(LL i=0;i<vars;i++)
		{	for(LL j=0;j<vars;j++)
				printf(" %.2lf",resis[i][j].value());
			printf("\n");}*/
		//no problem above
		for(LL i=0;i<vars;i++)
		{
			for(LL j=i+1;j<vars;j++)
			{
				if(resis[i][j]!=-1)
				{
					volt[i].to.push_back(j);
					volt[j].to.push_back(i);
				}
			}
		}
		for(LL i=0;i<vars;i++)
		{
			volt[i].setequation();
			//printf("volt %lld:",volt[i].thisindex);for(LL j=0;j<vars;j++) printf(" %.2lf",volt[i].equation[j].value());printf("\n");
			//printf("  ->to:");for(LL j=0;j<volt[i].to.size();j++) printf(" %lld",volt[i].to[j]);printf("\n");
		}
		printf("Case #%lld:\n",kase);
		LL Q;
		scanf("%lld",&Q);
		while(Q--)
		{
			LL a,b;
			scanf("%lld%lld",&a,&b);
			if(leader[a]!=leader[b])
			{
				//printf("infinity  ");
				printf("Resistance between %lld and %lld is 1/0\n",a,b);
			}
			else
			{
		//printf("%lld %lldelse\n",a,b);
				if(allans[a][b]==-1) allans[a][b]=allans[b][a]=solve(a,b);
				printf("Resistance between %lld and %lld is %lld/%lld\n",a,b,allans[a][b].up,allans[a][b].down);
			}
		}
	}
	return 0;
}
