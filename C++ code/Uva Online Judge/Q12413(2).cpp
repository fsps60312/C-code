#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const int MaxDigit=100;
char S[6];
bool isnum(char a)
{
	return a>='0'&&a<='9';
}
struct Big
{
	vector<int> up;
	vector<int> down;
	bool isnega;
	Big pow(int b)
	{
		Big ans=1,a=(*this);
		//print();printf("^%d -> ",b);
		while(b)
		{
			if(b&1)
			{
				ans*=a;
			}
			a*=a;
			b>>=1;
		}//ans.print();printf("\n");
		return ans;
	}
	Big abs(){Big ans=(*this);ans.isnega=false;return ans;}
	Big exp(Big a){return exp(a,-MaxDigit);}
	Big exp(Big a,int b)
	{
		//a.print();printf(" %d\n",b);
		Big ans=0,errorrate=0;
		errorrate.adddigit(b,1);
		errorrate.print();printf(" errorrate\n");
		Big a1=1;
		int now=1;
		while(a1>errorrate)
		{
			ans+=a1;
			a1*=a;
			a1/=now;
			now++;
		}
		return ans;
	}
	Big pow(Big b){return pow(b,-MaxDigit);}
	Big pow(Big b,int c)
	{
		return b;
		//printf("%d\n",c);
		Big errorrate=0;errorrate.adddigit(c,1);
		Big a1=(*this).pow(b.toint()),a2=(a1*(*this));
		//errorrate.print();printf(" errorrate\n");
		Big ans=(a1*a2).sqrt(c);
		Big b1=b.toint(),b2=(b1+1),mid;
		while((a1-a2).abs()>errorrate)
		{
			//b1.print();printf("+");b2.print();printf("=");((b1+b2)/2).print();printf("\n");
			mid=((b1+b2)/2);
			ans=(a1*a2).sqrt(c);//ans is pow(mid)
			//printf("ans=");ans.print();printf("\n");
			if(mid<b) b1=mid,a1=ans;
			else b2=mid,a2=ans;
		}
		return ans;
	}
	int toint()
	{
		int ans=0;
		if(up.size())for(int i=up.size()-1;i>=0;i--)ans*=10,ans+=up[i];
		//print();printf("->%d\n",ans);
		return ans;
	}
	Big sqrt(){return sqrt(-MaxDigit);}
	Big sqrt(int b)
	{
		if((*this)<0){printf("sqrt(");print();printf(") is not valid!\n");return (*this);}
		Big ans=0,a=(*this),a1=0;
		int now=0;
		while(a>=100)a/=100,now++;
		//printf("pass\n");}
		while(now>=b&&a!=0)
		{
			for(int i=1;i<=10;i++)
			{
				if(((a1+i)*i)>a)
				{
					i--;
					ans.adddigit(now,i);
					//printf("%d",i);
					a-=((a1+i)*i);
					a1+=(i*2);
					a1*=10;
					break;
				}
			}
			a*=100;
			now--;
		}
		ans.carry();
		return ans;
	}
	bool operator<=(Big a){return !((*this)>a);}
	bool operator>=(Big a){return !((*this)<a);}
	Big operator/(Big b)
	{
		Big ans=0,a=(*this);
		//print();printf(" -> ");
		ans.isnega=(a.isnega^b.isnega);
		a.isnega=b.isnega=false;
		int now=(int)up.size()-1;
		Big pointzero=0;
		pointzero.adddigit(-1,1);
		while(a>=10)a*=pointzero;
		while(now>=-MaxDigit&&a!=0)
		{
			for(int i=1;i<=10;i++)
			{
				if(b*i>a)
				{
					i--;
					ans.adddigit(now,i);
					a-=(b*i);
					break;
				}
			}
			a*=10;
			now--;
		}
		ans.carry();
		//print();printf("\n");
		return ans;
	}
	Big operator/=(Big a){return (*this)=(*this)/a;}
	bool operator!=(Big a){return !((*this)==a);}
	bool operator<(Big a)
	{
		if(isnega!=a.isnega) return isnega;
		if(up.size()!=a.up.size()) return up.size()<a.up.size()^isnega;
		if(up.size())for(int i=up.size()-1;i>=0;i--)if(up[i]!=a.up[i]) return up[i]<a.up[i]^isnega;
		for(int i=0;i<down.size()&&i<a.down.size();i++)if(down[i]!=a.down[i]) return down[i]<a.down[i]^isnega;
		if(down.size()!=a.down.size()) return down.size()<a.down.size()^isnega;
		return false;
	}
	bool operator>(Big a)
	{
		if(isnega!=a.isnega) return a.isnega;
		if(up.size()!=a.up.size()) return up.size()>a.up.size()^isnega;
		if(up.size())for(int i=up.size()-1;i>=0;i--)if(up[i]!=a.up[i]) return up[i]>a.up[i]^isnega;
		for(int i=0;i<down.size()&&i<a.down.size();i++)if(down[i]!=a.down[i]) return down[i]>a.down[i]^isnega;
		if(down.size()!=a.down.size()) return down.size()>a.down.size()^isnega;
		return false;
	}
	bool operator==(Big a)
	{
		if(up.size()!=a.up.size()) return false;
		if(up.size())for(int i=up.size()-1;i>=0;i--)if(up[i]!=a.up[i]) return false;
		for(int i=0;i<down.size()&&i<a.down.size();i++)if(down[i]!=a.down[i]) return false;
		if(down.size()!=a.down.size()) return false;
		return true;
	}
	Big operator*(Big a)
	{
		Big ans=0;
		ans.isnega=isnega^a.isnega;
		for(int i=0;i<up.size();i++)for(int j=0;j<a.up.size();j++)ans.adddigit(i+j,up[i]*a.up[j]);
		for(int i=0;i<up.size();i++)for(int j=0;j<a.down.size();j++) ans.adddigit(i-j-1,up[i]*a.down[j]);
		for(int i=0;i<down.size();i++)for(int j=0;j<a.up.size();j++) ans.adddigit(j-i-1,down[i]*a.up[j]);
		for(int i=0;i<down.size();i++)for(int j=0;j<a.down.size();j++) ans.adddigit(-i-j-2,down[i]*a.down[j]);
		ans.carry();
		//print();printf("*");a.print();printf("=");ans.print();printf("\n");
		return ans;
	}
	Big operator*=(Big a){return (*this)=(*this)*a;}
	Big operator-(Big a)
	{
		Big ans=0;
		for(int i=0;i<up.size();i++) ans.adddigit(i,isnega?-up[i]:up[i]);
		for(int i=0;i<down.size();i++) ans.adddigit(-1-i,isnega?-down[i]:down[i]);
		for(int i=0;i<a.up.size();i++) ans.adddigit(i,a.isnega?a.up[i]:-a.up[i]);
		for(int i=0;i<a.down.size();i++) ans.adddigit(-1-i,a.isnega?a.down[i]:-a.down[i]);
		ans.carry();
		return ans;
	}
	Big operator-=(Big a){return (*this)=(*this)-a;}
	Big operator+(Big a)
	{
		Big ans=0;
		for(int i=0;i<up.size();i++) ans.adddigit(i,isnega?-up[i]:up[i]);
		for(int i=0;i<down.size();i++) ans.adddigit(-1-i,isnega?-down[i]:down[i]);
		for(int i=0;i<a.up.size();i++) ans.adddigit(i,a.isnega?-a.up[i]:a.up[i]);
		for(int i=0;i<a.down.size();i++) ans.adddigit(-1-i,a.isnega?-a.down[i]:a.down[i]);
		ans.carry();
		return ans;
	}
	Big operator+=(Big a){return (*this)=(*this)+a;}
	void adddigit(int b,int a)//add a to digit b
	{
		if(b>=0)
		{
			while(up.size()<=b) up.push_back(0);
			up[b]+=a;
		}
		else
		{
			b=-1-b;
			while(down.size()<=b) down.push_back(0);
			down[b]+=a;
		}
	}
	Big(){up.clear(),down.clear(),isnega=false;}
	Big(int a)
	{
		up.clear();
		down.clear();
		if(a<0)
		{
			isnega=true;
			a*=-1;
		}
		else isnega=false;
		while(a)
		{
			up.push_back(a%10);
			a/=10;
		}
	}
	Big(double a)
	{
		up.clear();
		down.clear();
		if(a<0)
		{
			isnega=true;
			a*=-1;
		}
		else isnega=false;
		int b=(int)a;
		while(b)
		{
			up.push_back(b%10);
			b/=10;
		}
		a-=b;
		while(a>0&&down.size()<MaxDigit)
		{
			a*=10;
			if((int)a<0) break;
			down.push_back((int)a);
		}
	}
	Big operator=(Big a)
	{
		isnega=a.isnega;
		up.clear();
		down.clear();
		for(int i=0;i<a.up.size();i++) up.push_back(a.up[i]);
		for(int i=0;i<a.down.size();i++) down.push_back(a.down[i]);
		return (*this);
	}
	void carry()
	{
		if(down.size())
		{
			for(int i=down.size()-1;i>=0;i--)
			{
				if(down[i]>=10||down[i]<=-10)
				{
					adddigit(-i,down[i]/10);
					down[i]%=10;
				}
				if(down[i]<0)
				{
					adddigit(-i,-1);
					down[i]+=10;
				}
			}
		}
		if(up.size())
		{
			for(int i=0;i<up.size();i++)
			{
				if(i==up.size()-1&&up[i]<0)
				{
					isnega^=1;
					for(int j=0;j<up.size();j++) up[j]*=-1;
					for(int j=0;j<down.size();j++) down[j]*=-1;
					carry();
					return;
				}
				if(up[i]>=10||up[i]<=-10)
				{
					adddigit(i+1,up[i]/10);
					up[i]%=10;
				}
				if(up[i]<0)
				{
					adddigit(i+1,-1);
					up[i]+=10;
				}
			}
		}
		if(up.size())while(up[up.size()-1]==0)up.pop_back();
		if(down.size())while(down[down.size()-1]==0)down.pop_back();
	}
	void print()
	{
		if(isnega) printf("-");
		if(up.size()) for(int i=up.size()-1;i>=0;i--) printf("%d",up[i]);
		else printf("0");
		if(down.size())
		{
			printf(".");
			for(int i=0;i<down.size();i++) printf("%d",down[i]);
		}
	}
	void print(int a)
	{
		if(isnega) printf("-");
		if(up.size()) for(int i=up.size()-1;i>=0;i--) printf("%d",up[i]);
		else printf("0");
		printf(".");
		for(int i=0;i<a-1;i++) printf("%d",i<down.size()?down[i]:0);
		if(down.size()>a) printf("%d",down[a]>=5?down[a-1]+1:down[a-1]);
		else if(down.size()==a) printf("%d",down[a-1]);
		else printf("0");
	}
	void scan()
	{
		up.clear();
		down.clear();
		isnega=false;
		char c;
		vector<int> a;
		while(scanf("%c",&c)==1&&!isnum(c))
		{
			if(c=='-') isnega=true;
			else isnega=false;
		}
		a.push_back(c-'0');
		while(scanf("%c",&c)==1&&isnum(c)) a.push_back(c-'0');
		for(int i=a.size()-1;i>=0;i--) up.push_back(a[i]);
		if(c=='.') while(scanf("%c",&c)==1&&isnum(c)) down.push_back(c-'0');
	}
};
int main()
{// add, sub, mul, div, pow, atan2,
 // exp, ln, sqrt, asin, acos, atan, sin, cos, tan,
	//Big a=0.000000001;
	//a.scan();
	//printf("pass\n");
	//a.print();
	Big a=0,b=0;
	int p;
	freopen("in.txt","r",stdin);
	//printf("%d %d\n",a.up.size(),a.down.size());
	//a.print();
	while(scanf("%s",S)==1)
	{
		switch(S[0])
		{
			case 'a':// add, atan2, asin, acos, atan,
			{//
				switch(S[1])
				{
					case 'd':// add,
					{
						a.scan();
						b.scan();
						//a.print();printf("\n");
						//b.print();printf("\n");
						scanf("%d",&p);
						(a+b).print(p);printf("\n");
					}break;
					case 't':// atan2, atan,
					{
					}break;
					case 's':// asin,
					{
					}break;
					default:// acos,
					{
					}break;
				}
			}break;
			case 's':// sub, sqrt, sin,
			{//
				switch(S[1])
				{
					case 'u':// sub,
					{
						a.scan();
						b.scan();
						scanf("%d",&p);
						(a-b).print(p);printf("\n");
					}break;
					case 'q':// sqrt,
					{
						a.scan();
						scanf("%d",&p);
						a.sqrt(-p-1).print(p);printf("\n");
					}break;
					default:// sin,
					{
					}break;
				}
			}break;
			case 'm':// mul,
			{
				a.scan();
				b.scan();
				scanf("%d",&p);
				(a*b).print(p);printf("\n");
			}break;
			case 'd':// div,
			{
				a.scan();
				b.scan();
				scanf("%d",&p);
				(a/b).print(p);printf("\n");
			}break;
			case 'p':// pow,
			{
				a.scan();
				b.scan();
				scanf("%d",&p);
				a.pow(b,-p-1).print(p);printf("\n");
			}break;
			case 'e':// exp,
			{
				a.scan();
				scanf("%d",&p);
				a.exp(a,-p-1).print(p);printf("\n");
			}break;
			case 'l':// ln,
			{
			}break;
			case 'c':// cos,
			{
			}break;
			default:// tan,
			{
			}break;
		}
	}
	return 0;
}
