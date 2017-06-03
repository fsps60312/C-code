#include<cstdio>
#include<vector>
#include<map>
#include<string>
#define LL long long
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define termin(x,...) {while(1){std::printf(x,##__VA_ARGS__);}}
using namespace std;
char LINE[1000000];
struct BigInt
{
	vector<char> d;
	bool nega;
	int scanf()
	{
		std::scanf("%s",LINE);
		return sscanf(LINE);
	}
	bool Digit(char &c){return c>='0'&&c<='9';}
	int sscanf(char *c)
	{
		int i=0;
		while(c[i]!='-'&&c[i]!='.'&&!Digit(c[i]))i++;
		if(c[i]=='-'){nega=true;i++;}
		else nega=false;
		d.clear();
		vector<char> tmp;
		bool dot=false;
		int dcmplc=0;
		for(;c[i]=='.'||Digit(c[i]);i++)
		{
			if(c[i]=='.'){dot=true;continue;}
			if(dot)dcmplc++;
			tmp.push_back(c[i]-'0');
		}
		for(int i=0;i<tmp.size();i++)d.push_back(tmp[tmp.size()-1-i]);
		return dcmplc;
	}
	BigInt(){d.clear();nega=false;}
	BigInt(LL a){nega=a<0LL;if(a<0LL)a=-a;d.clear();while(a)d.push_back(a%10),a/=10;}
	BigInt(const BigInt &a){nega=a.nega;d.clear();for(int i=0;i<a.d.size();i++)d.push_back(a.d[i]);}
	void showd(){for(int i=0;i<d.size();i++)std::printf("%ddigit: %d\n",d[i]);}
	void carry()
	{
		if(!d.size()){nega=false;return;}
		index1:;
		for(int i=0;;i++)
		{
			int a=(d[i]%10+10)%10;
			if(i+1==d.size())
			{
				if(d[i]>a)d.push_back(0);
				else if(d[i]<a)
				{
					nega^=true;
					for(int j=0;j<d.size();j++)d[j]*=-1;
					goto index1;
				}
				else break;
			}
			d[i+1]+=(d[i]-a)/10;
			d[i]=a;
		}
		if(!d.size()){nega=false;return;}
		for(int i=d.size()-1;i>=0&&d[i]==0;i--)d.pop_back();
		if(!d.size()){nega=false;return;}
	}
	void printf()
	{
		if(nega)std::printf("-");
		if(!d.size()){std::printf("0");return;}
		for(int i=d.size()-1;i>=0;i--)std::printf("%d",d[i]);
	}
	void sprintf(char *c)
	{
		int i=0;
		if(nega)c[i++]='-';
		if(!d.size())c[i++]='0';
		else for(int j=d.size()-1;j>=0;i++,j--)c[i]='0'+d[j];
		c[i]=0;
	}
	void AddDigits(const BigInt &a)
	{
		while(d.size()<a.d.size())d.push_back(0);
		for(int i=0;i<a.d.size();i++)d[i]+=a.d[i];
		carry();
	}
	void MinusDigits(const BigInt &a)
	{
		while(d.size()<a.d.size())d.push_back(0);
		for(int i=0;i<a.d.size();i++)d[i]-=a.d[i];
		carry();
	}
	BigInt DigitsMoveLeft(int m=1)
	{
		if(m<0)return DigitsMoveRight(-m);
		BigInt ans=BigInt();
		while(m--)ans.d.push_back(0);
		for(int i=0;i<d.size();i++)ans.d.push_back(d[i]);
		return ans;
	}
	BigInt DigitsMoveRight(int m=1)
	{
		if(m<0)return DigitsMoveLeft(-m);
		if(m>d.size())termin("out of bound of array %d %d\n",m,d.size());
		BigInt ans=BigInt();
		for(int i=0;i<d.size();i++)
		{
			if(i<m)
			{
				if(d[i])termin("should be zero on the right sz=%d %d %d %d\n",d.size(),m,i,d[i]);
			}
			else ans.d.push_back(d[i]);
		}
		return ans;
	}
	BigInt Abs(){BigInt ans=BigInt(*this);ans.nega=0;return ans;}
	bool operator!()const{return !d.size();}
	bool operator==(const BigInt &a)const{if(d.size()!=a.d.size())return false;for(int i=0;i<d.size();i++)if(d[i]!=a.d[i])return false;return true;}
	bool operator!=(const BigInt &a)const{return !((*this)==a);}
	bool operator<(const BigInt &a)const
	{
		if(nega!=a.nega)return nega;
		if(d.size()!=a.d.size())return (d.size()<a.d.size())^nega;
		if(!d.size())return false;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]<a.d[i])^nega;
		return false;
	}
	bool operator>(const BigInt &a)const
	{
		if(nega!=a.nega)return a.nega;
		if(d.size()!=a.d.size())return (d.size()>a.d.size())^nega;
		if(!d.size())return false;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]>a.d[i])^nega;
		return false;
	}
	bool operator<=(const BigInt &a)const
	{
		if(nega!=a.nega)return nega;
		if(d.size()!=a.d.size())return (d.size()<a.d.size())^nega;
		if(!d.size())return true;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]<a.d[i])^nega;
		return true;
	}
	bool operator>=(const BigInt &a)const
	{
		if(nega!=a.nega)return a.nega;
		if(d.size()!=a.d.size())return (d.size()>a.d.size())^nega;
		if(!d.size())return true;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]>a.d[i])^nega;
		return true;
	}
	BigInt operator+(BigInt &a)
	{
		BigInt ans=BigInt();
		if(nega==a.nega)
		{
			ans.AddDigits(*this);
			ans.AddDigits(a);
			ans.nega=nega;
		}
		else
		{
			bool thisnega=nega;
			nega=a.nega=false;
			if((*this)>a)
			{
				ans.AddDigits(*this);
				ans.MinusDigits(a);
				ans.nega=thisnega;
			}
			else
			{
				ans.AddDigits(a);
				ans.MinusDigits(*this);
				ans.nega=thisnega^true;
			}
			nega=thisnega,a.nega=thisnega^true;
		}
		ans.carry();
		return ans;
	}
	BigInt operator-()
	{
		BigInt ans=BigInt(*this);
		ans.nega^=true;
		ans.carry();
		return ans;
	}
	BigInt operator-(BigInt &a)
	{
		a.nega^=true;
		BigInt ans=(*this)+a;
		a.nega^=true;
		return ans;
	}
	BigInt operator*(const BigInt &a)const
	{
		if(!(*this)||!a)return BigInt();
		BigInt ans=BigInt();
		ans.nega=nega^a.nega;
		for(int i=0,limit=d.size()+a.d.size();i<limit;i++)ans.d.push_back(0);
		for(int i=0;i<d.size();i++)
		{
			for(int j=0;j<a.d.size();j++)
			{
				ans.d[i+j]+=d[i]*a.d[j];
				ans.d[i+j+1]+=ans.d[i+j]/10;
				ans.d[i+j]%=10;
			}
		}
		ans.carry();
		return ans;
	}
	BigInt operator/(BigInt &a)
	{
		if(!(*this)||Abs()<a.Abs())return BigInt();
		BigInt tmp=BigInt(*this),ans=BigInt();
		tmp.nega=false;
		for(int i=0,limit=d.size()-a.d.size();i<=limit;i++)ans.d.push_back(0);
		for(int i=d.size()-a.d.size();i>=0;i--)
		{
			char &_=ans.d[i];
			BigInt b=a.DigitsMoveLeft(i).Abs();
			while(tmp>=b)tmp-=b,_++;
			if(_>=10){termin("digit exceed range when div: %d\n",_);}
		}
		if(tmp>=a.Abs()){std::printf("can't full divided: ");tmp.printf();puts("");termin("");}
		ans.nega=nega^a.nega;
		ans.carry();
		return ans;
	}
	BigInt operator%(BigInt &a){BigInt div=((*this)/a)*a;return (*this)-div;}
	BigInt operator+=(BigInt &a){return (*this)=(*this)+a;}
	BigInt operator-=(BigInt &a){return (*this)=(*this)-a;}
	BigInt operator*=(BigInt &a){return (*this)=(*this)*a;}
	BigInt operator/=(BigInt &a){return (*this)=(*this)/a;}
	BigInt operator%=(BigInt &a){return (*this)=(*this)%a;}
};
const int RESERVED=10;
int ACCURACY;
struct Big
{
	BigInt v;
	int dcmplc,accuracy;
	Big():dcmplc(0),v(),accuracy(ACCURACY){}
	Big(LL a):dcmplc(0),v(a),accuracy(ACCURACY){}
	Big(const Big &a):dcmplc(a.dcmplc),v(a.v),accuracy(a.accuracy){}
	void carry()
	{
		int i=0;
		while(i<v.d.size()&&!v.d[i])i++;
		if(dcmplc-i>accuracy+RESERVED)
		{
			int j=dcmplc-(accuracy+RESERVED);
			if(v.d[j-1]>=5)v.d[j]++;
			for(;i<j;i++)v.d[i]=0;
		}
		if(i>v.d.size())termin("out of bound of array\n");
		v=v.DigitsMoveRight(i);
		dcmplc-=i;
	}
	void scanf(){dcmplc=v.scanf();}
	void printf()
	{
		v.sprintf(LINE);
//		if(dcmplc)
//		{
//			int n=-1;while(LINE[++n]);
//			LINE[n+1]=0;
//			for(int i=0;i<dcmplc&&n>=0;i++,n--)LINE[n]=LINE[n-1];
//			LINE[n]='.';
//		}
		std::printf("%s",LINE);
		std::printf(" dcmplc = %d",dcmplc);
	}
	bool operator<(Big &a){int b=dcmplc,c=a.dcmplc;if(b<0)c-=b,b=0;if(c<0)b-=c,c=0;return v.DigitsMoveLeft(c)<a.v.DigitsMoveLeft(b);}
	bool operator>(Big &a){int b=dcmplc,c=a.dcmplc;if(b<0)c-=b,b=0;if(c<0)b-=c,c=0;return v.DigitsMoveLeft(c)>a.v.DigitsMoveLeft(b);}
	bool operator==(Big &a){int b=dcmplc,c=a.dcmplc;if(b<0)c-=b,b=0;if(c<0)b-=c,c=0;return v.DigitsMoveLeft(c)==a.v.DigitsMoveLeft(b);}
	bool operator!=(Big &a){int b=dcmplc,c=a.dcmplc;if(b<0)c-=b,b=0;if(c<0)b-=c,c=0;return v.DigitsMoveLeft(c)!=a.v.DigitsMoveLeft(b);}
	bool operator<=(Big &a){int b=dcmplc,c=a.dcmplc;if(b<0)c-=b,b=0;if(c<0)b-=c,c=0;return v.DigitsMoveLeft(c)<=a.v.DigitsMoveLeft(b);}
	bool operator>=(Big &a){int b=dcmplc,c=a.dcmplc;if(b<0)c-=b,b=0;if(c<0)b-=c,c=0;return v.DigitsMoveLeft(c)>=a.v.DigitsMoveLeft(b);}
	Big operator+(Big &a)
	{
		Big ans=Big();
		BigInt a1=v,a2=a.v;
		if(dcmplc>a.dcmplc)a2=a2.DigitsMoveLeft(dcmplc-a.dcmplc),ans.dcmplc=dcmplc;
		else a1=a1.DigitsMoveLeft(a.dcmplc-dcmplc),ans.dcmplc=a.dcmplc;
		ans.v=a1+a2;
		ans.carry();
		return ans;
	}
	Big operator-(Big &a)
	{
		Big ans=Big();
		BigInt a1=v,a2=a.v;
		if(dcmplc>a.dcmplc)a2=a2.DigitsMoveLeft(dcmplc-a.dcmplc),ans.dcmplc=dcmplc;
		else a1=a1.DigitsMoveLeft(a.dcmplc-dcmplc),ans.dcmplc=a.dcmplc;
		ans.v=a1-a2;
		ans.carry();
		return ans;
	}
	Big operator*(Big &a)
	{
		Big ans=Big();
		ans.v=v*a.v;
		ans.dcmplc=dcmplc+a.dcmplc;
		ans.carry();
		return ans;
	}
	Big operator/(Big &a)
	{
		Big ans=Big();
		BigInt a1=v,a2=a.v;
		int d1=dcmplc,d2=a.dcmplc;
		d1-=d2,d2=0;
		if(accuracy+RESERVED+d2+1>d1)a1=a1.DigitsMoveLeft(accuracy+RESERVED+d2+1-d1),ans.dcmplc=accuracy+RESERVED+d2+1;
		else ans.dcmplc=d1;
		ans.v=a1/a2;
		ans.carry();
		return ans;
	}
void show(Big a)
{
	a.printf();
	puts("");
}
};
void show(Big a)
{
	a.printf();
	puts("");
}
Big sqrt(Big &a)
{
	Big one=Big(1LL),two=Big(2LL);
	Big l=Big(0LL),r=max(Big(a),one),mid;
	Big eps=Big(1LL);eps.dcmplc=eps.accuracy+RESERVED;
	while(l<r)
	{
		mid=(l+r)/two;
//		printf("l=");show(l);
//		printf("r=");show(r);
//		printf("two=");show(two);
//		printf("mid=");show(mid);
//		printf("mid*mid=");show(mid*mid);
//		printf("mid*mid?a=%d\n",(mid*mid)<a);
//		printf("eps=");show(eps);
		if(mid*mid<a)l=mid+eps;
		else r=mid-eps;
	}
	return l;
}
Big BIG1,BIG2;
map<string,int> IDX;
void initIDX()
{
	int idx=0;
	IDX["add"]=idx++;
	IDX["sub"]=idx++;
	IDX["mul"]=idx++;
	IDX["div"]=idx++;
	IDX["pow"]=idx++;
	IDX["atan2"]=idx++;
	IDX["exp"]=idx++;
	IDX["ln"]=idx++;
	IDX["sqrt"]=idx++;
	IDX["asin"]=idx++;
	IDX["acos"]=idx++;
	IDX["atan"]=idx++;
	IDX["sin"]=idx++;
	IDX["cos"]=idx++;
	IDX["tan"]=idx++;
}
int main()
{
	//add, sub, mul, div, pow, atan2
	//exp, ln, sqrt, asin, acos, atan, sin, cos, tan
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	initIDX();
	while(scanf("%s",LINE)==1)
	{
		if(IDX.find(LINE)==IDX.end()){puts("Illegal Operator\n");continue;}
		int type=IDX[LINE],d1,d2;
		BIG1.scanf();
		if(type<=5)BIG2.scanf();
		scanf("%d",&ACCURACY);BIG1.accuracy=BIG2.accuracy=ACCURACY;
		switch(type)
		{
			case 0:show(BIG1+BIG2);break;
			case 1:show(BIG1-BIG2);break;
			case 2:show(BIG1*BIG2);break;
			case 3:show(BIG1/BIG2);break;
			case 8:show(sqrt(BIG1));break;
			default:printf("not supported\n");break;
		}
	}
	return 0;
}
