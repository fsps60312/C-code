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
void show(Deq a){for(int i=a.size()-1;i>=0;i--)printf("%d",a[i]);}
bool Nolarger(Deq &d1,Deq &d2)//<=
{
	if(d1.size()!=d2.size())return d1.size()<d2.size();
	for(int i=d1.size()-1;i>=0;i--)if(d1[i]!=d2[i])return d1[i]<d2[i];
	return true;
}
void castdigit(Deq &to,Deq &from)
{
	if(!from.size())to.push_front(0);
	else to.push_front(from.back()),from.pop_back();
	while(to.size()&&!to.back())to.pop_back();
}
void Add(Deq &d,char carry)
{
	if(carry<0||carry>9)termin("Add: carry=%d\n",carry);
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
	if(v<0||v>9)termin("Mul: v=%d\n",v);
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
	if(!Nolarger(m,d))
	{
		show(d);puts("");
		show(m);puts("");
		termin("Sub: m>d\n");
	}
	char carry=0;
	Deq td=d,tm=m;
	for(int i=0;carry||i<m.size();i++)
	{
		if(i==d.size())
		{
			puts("");
			show(d);puts("");show(m);puts("");
			show(td);puts("");show(tm);puts("");
			termin("carry=%d d.size()=%d m.size()=%d\n",carry,d.size(),m.size());
		}
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
//FILE *F=fopen("out.txt","w");
#define cout(x,...) printf(x,##__VA_ARGS__)
//#define cout(x,...) fprintf(F,x,##__VA_ARGS__)

//#define DEBUG
void solve()
{
	cout("%d ",N);
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
		#ifdef DEBUG
		cout("%d",v);
		#endif
		Sub(sub,tmp=Addmul(add,v));
		Add(add,v),Add(add,v);
		if(v==now)cnt++;
		else now=v,cnt=1;
		pos++;
		if(cnt==3)
		{
			cout("%d %d\n",pos-3,now);
			return;
		}
//		printf("*");show(sub);puts("");
//		printf("*");show(add);puts("");
		castdigit(sub,n);
		castdigit(sub,n);
//		printf("#");show(sub);puts("");
//		printf("#");show(add);puts("");
	}
}
int main()
{
//	Deq d;
//	d.push_front(1);show(d);puts("");
//	d.push_front(2);show(d);puts("");
//	d.push_front(3);show(d);puts("");
//	d.push_front(4);show(d);puts("");
//	d.push_front(5);show(d);puts("");
//	d.push_front(6);show(d);puts("");
//	d.push_front(0);show(d);puts("");
//	d.push_front(0);show(d);puts("");
//	d.push_front(0);show(d);puts("");
//	d.push_front(0);show(d);puts("");
//	d.push_front(0);show(d);puts("");
//	freopen("in.txt","r",stdin);
//	vector<int> p;
//	p.push_back(2),p.push_back(3);
//	for(int i=2,j;;i++)
//	{
//		p.push_back(p[i-1]);
//		do
//		{
//			p[i]+=2;
//			for(j=0;p[j]*p[j]<=p[i]&&p[i]%p[j];j++);
//		}while(p[i]%p[j]==0);
//		if(p[i]>1000000)break;
//		N=p[i];
//		printf("%d\n",N);
//		solve();
//	}return 0;
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
