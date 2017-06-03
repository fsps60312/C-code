#include<cstdio>
#include<vector>
#include<algorithm>
typedef long long LL;
using namespace std;
void termin(){int a[9];for(int i=0;;i++)printf("E");}
LL T,N,M;
int VIS[16];
vector<LL> TO[16];
struct Big
{
	vector<char> d;
	bool nega;
	Big(){d.clear();nega=false;}
	Big(LL a){nega=a<0LL;if(a<0LL)a=-a;d.clear();while(a)d.push_back(a%10),a/=10;}
	Big(const Big &a){nega=a.nega;d.clear();for(int i=0;i<a.d.size();i++)d.push_back(a.d[i]);}
	void showd(){for(int i=0;i<d.size();i++)printf("%ddigit: %d\n",d[i]);}
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
	void rintf()
	{
		if(nega)printf("-");
		if(!d.size()){printf("0");return;}
		for(int i=d.size()-1;i>=0;i--)printf("%d",d[i]);
	}
	char* c_str()
	{
		char *ans=new char[d.size()+2];
		int i=0;
		if(nega)ans[i++]='-';
		if(!d.size())ans[i++]='0';
		else for(int j=d.size()-1;j>=0;i++,j--)ans[i]='0'+d[j];
		ans[i]=0;
		return ans;
	}
	void AddDigits(const Big &a)
	{
		while(d.size()<a.d.size())d.push_back(0);
		for(int i=0;i<a.d.size();i++)d[i]+=a.d[i];
		carry();
	}
	void MinusDigits(const Big &a)
	{
		while(d.size()<a.d.size())d.push_back(0);
		for(int i=0;i<a.d.size();i++)d[i]-=a.d[i];
		carry();
	}
	Big DigitsMoveLeft(int m=1)
	{
		Big ans=Big();
		while(m--)ans.d.push_back(0);
		for(int i=0;i<d.size();i++)ans.d.push_back(d[i]);
		return ans;
	}
	Big DigitsMoveRight(int m=1)
	{
		Big ans=Big();
		for(int i=0;i<d.size();i++)
		{
			if(i<m)if(d[i]){printf("should be zero on the right\n");termin();}
			ans.d.push_back(d[i]);
		}
		return ans;
	}
	Big Abs(){Big ans=Big(*this);ans.nega=0;return ans;}
	bool operator!()const{return !d.size();}
	bool operator==(const Big &a)const{if(d.size()!=a.d.size())return false;for(int i=0;i<d.size();i++)if(d[i]!=a.d[i])return false;return true;}
	bool operator!=(const Big &a)const{return !((*this)==a);}
	bool operator<(const Big &a)const
	{
		if(nega!=a.nega)return nega;
		if(d.size()!=a.d.size())return (d.size()<a.d.size())^nega;
		if(!d.size())return false;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]<a.d[i])^nega;
		return false;
	}
	bool operator>(const Big &a)const
	{
		if(nega!=a.nega)return a.nega;
		if(d.size()!=a.d.size())return (d.size()>a.d.size())^nega;
		if(!d.size())return false;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]>a.d[i])^nega;
		return false;
	}
	bool operator<=(const Big &a)const
	{
		if(nega!=a.nega)return nega;
		if(d.size()!=a.d.size())return (d.size()<a.d.size())^nega;
		if(!d.size())return true;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]<a.d[i])^nega;
		return true;
	}
	bool operator>=(const Big &a)const
	{
		if(nega!=a.nega)return a.nega;
		if(d.size()!=a.d.size())return (d.size()>a.d.size())^nega;
		if(!d.size())return true;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]>a.d[i])^nega;
		return true;
	}
	Big operator+(Big &a)
	{
		Big ans=Big();
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
	Big operator-()
	{
		Big ans=Big(*this);
		ans.nega^=true;
		ans.carry();
		return ans;
	}
	Big operator-(Big &a)
	{
		a.nega^=true;
		Big ans=(*this)+a;
		a.nega^=true;
		return ans;
	}
	Big operator*(const Big &a)const
	{
		if(!(*this)||!a)return Big();
		Big ans=Big();
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
	Big operator/(Big &a)
	{
		if(!(*this)||Abs()<a.Abs())return Big();
		Big tmp=Big(*this),ans=Big();
		tmp.nega=false;
		for(int i=0,limit=d.size()-a.d.size();i<=limit;i++)ans.d.push_back(0);
		for(int i=d.size()-a.d.size();i>=0;i--)
		{
			char &_=ans.d[i];
			Big b=a.DigitsMoveLeft(i).Abs();
			while(tmp>=b)tmp-=b,_++;
			if(_>=10){printf("digit exceed range when div: %d\n",_);termin();}
		}
		if(tmp>=a.Abs()){printf("can't full divided: ");tmp.rintf();puts("");termin();}
		ans.nega=nega^a.nega;
		ans.carry();
		return ans;
	}
	Big operator%(Big &a){Big div=((*this)/a)*a;return (*this)-div;}
	Big operator+=(Big &a){return (*this)=(*this)+a;}
	Big operator-=(Big &a){return (*this)=(*this)-a;}
	Big operator*=(Big &a){return (*this)=(*this)*a;}
	Big operator/=(Big &a){return (*this)=(*this)/a;}
	Big operator%=(Big &a){return (*this)=(*this)%a;}
};
Big gcd(Big a,Big b){return !b?a:gcd(b,a%b);}
struct Fra
{
	Big up,down;
	Fra():up(0LL),down(0LL){}
	Fra(Big v):up(v),down(1LL){}
	Fra(Big u,Big d):up(u),down(d){carry();}
	void carry()
	{
//		if(!down&&!up){printf("both zero in fraction\n");termin();}
		if(!down){up=1LL;return;}
		if(!up){down=1LL;return;}
		Big g=gcd(up.Abs(),down.Abs());
		up/=g;
		down/=g;
		if(down<0LL)
		{
			down=-down;
			up=-up;
		}
	}
	char* c_str(){char *ans=new char[up.d.size()+down.d.size()+2];sprintf(ans,"%s/%s",up.c_str(),down.c_str());return ans;}
	bool ContainZero(){return !up||!down;}
	bool operator==(Fra f)const{return up==f.up&&down==f.down;}
	bool operator!=(Fra f)const{return !((*this)==f);}
	Fra operator*(Fra f)const{Fra ans=Fra(up*f.up,down*f.down);ans.carry();return ans;}
	Fra operator/(Fra f)const{return (*this)*Fra(f.down,f.up);}
	Fra operator+(Fra f)const{Big t1=down*f.up;Fra ans=Fra(up*f.down+t1,down*f.down);ans.carry();return ans;}
	Fra operator-(Fra f)const{Big t1=down*f.up;Fra ans=Fra(up*f.down-t1,down*f.down);ans.carry();return ans;}
	Fra operator+=(Fra f){return (*this)=(*this)+f;}
	Fra operator-=(Fra f){return (*this)=(*this)-f;}
	Fra operator/=(Fra f){return (*this)=(*this)/f;}
}RES[16][16],MAT[16][17];
Fra AddRes(Fra a,Fra b){return Fra(1LL)/((Fra(1LL)/a)+(Fra(1LL)/b));}
void initMAT()
{
	for(LL i=0LL;i<N;i++)
	{
		for(LL j=0;j<=N;j++)MAT[i][j]=Fra(0LL);
		for(LL _=0LL;_<TO[i].size();_++)
		{
			LL &j=TO[i][_];
			MAT[i][i]+=Fra(1LL)/RES[i][j];
			MAT[i][j]-=Fra(1LL)/RES[i][j];
		}
	}
}
void Exchange(LL r1,LL r2)
{
	Fra tmp;
	for(LL i=0LL;i<=N;i++)tmp=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=tmp;
}
void Kill(LL r1,LL r2)
{
	if(MAT[r2][r1]==Fra(0LL))return;
//	else if(MAT[r2][r1].ContainZero()){printf("encounter infinite when killing: %lld %lld\n",r1,r2);termin();}
	Fra ratio=MAT[r2][r1]/MAT[r1][r1];
	for(LL i=r1;i<=N;i++)MAT[r2][i]-=MAT[r1][i]*ratio;
}
void dfsVIS(LL u,int v)
{
	if(VIS[u]&v)return;
	VIS[u]|=v;
	for(LL _=0;_<TO[u].size();_++)
	{
		LL &j=TO[u][_];
		dfsVIS(j,v);
	}
}
void showGus(char *headline)
{
	puts(headline);
	for(LL i=0LL;i<N;i++)
	{
		for(LL j=0LL;j<=N;j++)printf("%8s",MAT[i][j].c_str());
		puts("");
	}
}
void solve()
{
	for(LL i=0LL;i<N;i++)
	{
		if(!VIS[i])continue;
		LL c;
		for(c=i;c<N;c++)if(!MAT[i][c].ContainZero())break;
		if(c==N){showGus("error");printf("can't find >0 row at column %lld\n",i);termin();}
		if(c!=i)Exchange(i,c);
		for(LL j=i+1LL;j<=N;j++)MAT[i][j]/=MAT[i][i];
		MAT[i][i]=Fra(1LL);
		for(LL j=0LL;j<N;j++)
		{
			if(!VIS[j]||j==i)continue;
			Kill(i,j);
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	LL kase=1LL;
	while(T--)
	{
		scanf("%lld%lld",&N,&M);
		for(LL i=0LL;i<N;i++)TO[i].clear();
		for(LL i=0LL;i<N;i++)for(LL j=0LL;j<N;j++)RES[i][j]=(i==j?Fra(0LL,1LL):Fra(1LL,0LL));
		for(LL i=0LL,a,b,r;i<M;i++)
		{
			scanf("%lld%lld%lld",&a,&b,&r);
			if(r<=0LL||r>=10)termin();
			if(a==b)continue;
			if(RES[a][b]==Fra(1LL,0LL))
			{
				TO[a].push_back(b);
				TO[b].push_back(a);
			}
			RES[a][b]=AddRes(RES[a][b],Fra(r));
			RES[b][a]=AddRes(RES[b][a],Fra(r));
		}
		for(LL i=0;i<N;i++)
		{
			sort(TO[i].begin(),TO[i].end());
			for(LL j=1;j<TO[i].size();j++)if(TO[i-1]==TO[i]){printf("repeated wire\n");termin();}
		}
		LL Q,A,B;scanf("%lld",&Q);
		printf("Case #%lld:\n",kase++);
		while(Q--)
		{
			scanf("%lld%lld",&A,&B);
			initMAT();
			for(LL i=0LL;i<N;i++)
			{
				VIS[i]=false;
				MAT[i][A]=Fra(0LL);
				MAT[i][N]-=MAT[i][B];
				MAT[i][B]=Fra(0LL);
			}
			dfsVIS(A,1);
			dfsVIS(B,2);
			VIS[A]=VIS[B]=0;
			for(int i=0;i<N;i++)
			{
				if(VIS[i]==3)VIS[i]=1;
				else VIS[i]=0;
			}
			solve();
			MAT[A][N]=Fra(0LL);
			MAT[B][N]=Fra(1LL);
			Fra ans_a=Fra(0LL);
			for(LL _=0LL;_<TO[A].size();_++)
			{
				LL &i=TO[A][_];
				if(!VIS[i])continue;
				Fra current=MAT[i][N]/RES[A][i];
				ans_a+=current;
			}
			Fra ans_b=Fra(0LL);
			for(LL _=0LL;_<TO[B].size();_++)
			{
				LL &i=TO[B][_];
				if(!VIS[i])continue;
				Fra current=(Fra(1LL)-MAT[i][N])/RES[B][i];
				ans_b+=current;
			}
			if(ans_a!=ans_b){printf("%s != %s\n",ans_a.c_str(),ans_b.c_str());termin();}
			ans_a=Fra(1LL)/ans_a;
			if(ans_a.up<0LL){printf("impossible <0\n");termin();}
			printf("Resistance between %lld and %lld is %s\n",A,B,ans_a.c_str());
		}
		puts("");
	}
}
