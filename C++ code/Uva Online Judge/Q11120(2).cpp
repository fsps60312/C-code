#include<cstdio>
#include<vector>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1){}}
using namespace std;
int N;
struct Deq
{
	vector<char> db;
	int l,r;
	Deq():l(0),r(-1){db.clear(),db.resize(2);}
	void clear(){db.clear();db.resize(2);l=0,r=-1;}
	int size(){return ((r-l+1)%db.size()+db.size())%db.size();}
	void pop_back(){if(!size())termin("pop_back size==%d\n",size());r--;if(r<0)r+=db.size();}
	void pop_front(){if(!size())termin("pop_front size==%d\n",size());l++;if(l>=db.size())l-=db.size();}
	void expandsize()
	{
		vector<char> tdb;
		tdb.resize(db.size()*2);
		for(int i=0;i<size();i++)tdb[i]=(*this)[i];
		int sz=size();
		l=0,r=sz-1;
		db=tdb;
	}
	void push_back(char v)
	{
		if(size()+1==db.size())expandsize();
		r++;r%=db.size();
		db[r]=v;
	}
	void push_front(char v)
	{
		if(size()+1==db.size())expandsize();
		l--;if(l<0)l+=db.size();
		db[l]=v;
	}
	char front(){if(!size())termin("front size==%d\n",size());return db[l];}
	char back(){if(!size())termin("back size==%d\n",size());return db[r];}
	char &operator[](int idx){if(idx<0||idx>=size())termin("idx==%d size()==%d\n",idx,size());return db[(l+idx)%db.size()];}
};
void show(Deq a){for(int i=0;i<a.size();i++)printf("%d",a[i]);}
void castdigit(Deq &to,Deq &from)
{
	if(!from.size())to.push_front(0);
	else to.push_front(from.back()),from.pop_back();
}
void Add(Deq &d,char carry)
{
	for(int i=0;i<d.size();i++)
	{
		d[i]+=carry;carry=0;
		if(!d[i]/10)break;
		carry=d[i]/10;
		d[i]%=10;
	}
	if(carry)d.push_back(carry);
}
void Mul(Deq &d,char v)
{
	char carry=0;
	for(int i=0;i<d.size();i++)
	{
		d[i]*=v;
		d[i]+=carry;
		carry=d[i]/10;
		d[i]%=10;
	}
	if(carry)d.push_back(carry);
	while(d.size()&&!d.back())d.pop_back();
}
void Sub(Deq &d,Deq &m)
{
	char carry=0;
	for(int i=0;carry||i<m.size();i++)
	{
		if(i<m.size())d[i]-=m[i];
		d[i]+=carry;carry=0;
		while(d[i]<0)d[i]+=10,carry--;
	}
	if(carry)termin("carry=%d\n",carry);
	while(d.size()&&!d.back())d.pop_back();
}
Deq Addmul(Deq d,char v)
{
	Add(d,v);
	Mul(d,v);
	return d;
}
bool Nolarger(Deq &d1,Deq &d2)//<=
{
	if(d1.size()!=d2.size())return d1.size()<d2.size();
	for(int i=d1.size()-1;i>=0;i--)if(d1[i]!=d2[i])return d1[i]<d2[i];
	return true;
}
void solve()
{
	printf("%d ",N);
	Deq n,add,sub,tmp;
	while(N)
	{
		n.push_back(N%10);
		N/=10;
	}
	if(!n.size())termin("!n.size()\n");
	castdigit(sub,n);
	if(n.size()%2)castdigit(sub,n);
	char v,now=-1,cnt=0,r,m;
	int pos=0;
	while(1)
	{
		add.push_front(0);
		v=0,r=9;
		while(r>v)
		{
			m=(v+r+1)>>1;
			if(Nolarger(tmp=Addmul(add,m),sub))v=m;
			else r=m-1;
		}
		Sub(sub,tmp=Addmul(add,v));
		Add(add,v),Add(add,v);
		if(v==now)cnt++;
		else now=v,cnt=1;
		pos++;
		if(cnt==3)
		{
			printf("%d %d\n",pos-3,now);
			return;
		}
		castdigit(sub,n);
		castdigit(sub,n);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		solve();
	}
	return 0;
}
/*
79
723407
581149
0
Sample Output
79 0 8
723407 4 3
581149 1387 6
*/
