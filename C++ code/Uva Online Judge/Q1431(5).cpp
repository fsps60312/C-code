#include<cstdio>
#include<vector>
#include<cassert>
#include<stack>
using namespace std;
struct Big
{
	vector<int>s;
	Big(){}
	bool Scanf()
	{
		stack<int>digits;
		char c=getchar();
		while(c<'0'||c>'9')c=getchar();
		while(c>='0'&&c<='9')digits.push(c-'0'),c=getchar();
		s.clear();
		while(!digits.empty())s.push_back(digits.top()),digits.pop();
		return s[s.size()-1]!=0;
	}
	void Print(){for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
	void RemoveZero(){for(int i=s.size()-1;i>0&&s[i]==0;i--)s.pop_back();}
	void Carry()
	{
		for(int i=0;i<s.size();i++)if(s[i]>=10)
		{
			if(i+1==s.size())s.push_back(0);
			s[i+1]+=s[i]/10,s[i]%=10;
		}
	}
	void Minus()
	{
		s[0]--;
		for(int i=0;s[i]<0;i++)s[i]+=10,s[i+1]--;
		RemoveZero();
	}
	bool DivideBy(const int v,Big &ans)const
	{
		ans.s.resize(s.size());
		int tmp=0;
		for(int i=s.size()-1;i>=0;i--)
		{
			tmp=tmp*10+s[i];
			ans.s[i]=tmp/v;
			tmp%=v;
		}
		if(tmp!=0)return false;
		ans.RemoveZero();
		return true;
	}
	Big operator*(const int v)const{Big ans=(*this);ans*=v;return ans;}
	void operator*=(const int v)
	{
		for(int i=0;i<s.size();i++)s[i]*=v;
		Carry();
	}
	Big operator+(const int v){Big ans=(*this);ans+=v;return ans;}
	void operator+=(const int v){s[0]+=v;Carry();}
	void operator+=(const Big &a)
	{
		while(s.size()<a.s.size())s.push_back(0);
		for(int i=0;i<a.s.size();i++)s[i]+=a.s[i];
		Carry();
	}
	void operator-=(const Big &a)
	{
		while(s.size()<a.s.size())s.push_back(0);
		for(int i=0;i<a.s.size();i++)s[i]-=a.s[i];
		for(int i=0;i<s.size();i++)if(s[i]<0)assert((s[i]+=10)>=0),s[i+1]--;
		RemoveZero();
	}
	Big operator*(const Big &a)const
	{
		Big ans;
		for(int i=0;i<s.size()+a.s.size()-1;i++)ans.s.push_back(0);
		for(int i=0;i<s.size();i++)for(int j=0;j<a.s.size();j++)ans.s[i+j]+=s[i]*a.s[j];
		ans.Carry();
		return ans;
	}
	bool operator<=(const Big &a)const
	{
		if(s.size()!=a.s.size())return s.size()<a.s.size();
		for(int i=s.size()-1;i>=0;i--)if(s[i]!=a.s[i])return s[i]<a.s[i];
		return true;
	}
	Big Sqrt()
	{
		int d=0;while(d+2<s.size())d+=2;
		Big right;right.s.push_back(0);
		int idx=s.size()-1;
		Big left;left.s.push_back(0);
		stack<int>result;
		for(;d>=0;d-=2)
		{
			while(idx>=d)right*=10,right+=s[idx],idx--;
			int digit=0;
			for(;((left+(digit+1))*(digit+1))<=right;digit++);
			assert(digit>=0&&digit<=9);
			result.push(digit);
			right-=(left+digit)*digit;
			left+=digit,left*=digit;
		}
		printf("right: ");right.Print();puts("");
		Big ans;
		while(!result.empty())ans.s.push_back(result.top()),result.pop();
		return ans;
	}
};
Big N,D;
int E;
Big GetSub(const Big &a,Big n)
{
	Big tmp=a*a;
	n*=4;
	tmp.Print();putchar('-');n.Print();
	tmp-=n;
	putchar('=');tmp.Print();puts("");
	return tmp.Sqrt();
}
int main()
{
	freopen("in.txt","r",stdin);
	while(N.Scanf()|D.Scanf()|(scanf("%d",&E)&&E))
	{
		Big ALL=D;
		ALL*=E;
		ALL.Minus();
		static Big pq;
		//n(p-1)(q-1)==D*E-1, 1<=n<=E-1
		printf("D*E-1: ");ALL.Print();puts("");
		for(int n=E-1;;n--)if(ALL.DivideBy(n,pq))break;//summary (p-1)(q-1)
		printf("(p-1)(q-1): ");pq.Print();puts("");
		Big add=N;
		add-=pq;
		add+=1;
		printf("add: ");add.Print();puts("");
		Big sub=GetSub(add,N);
		static Big p,q;
		Big tmp=add;tmp-=sub;
		assert(tmp.DivideBy(2,p));
		tmp=add;tmp+=sub;
		assert(tmp.DivideBy(2,q));
		static int kase=1;
		printf("Case #%d: ",kase++);
		p.Print();putchar(' ');q.Print();puts("");
	}
}
