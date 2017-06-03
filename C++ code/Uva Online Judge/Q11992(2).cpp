#include<cstdio>
#include<cstdlib>
#include<vector>
#define LL long long
using namespace std;
LL r,n,m;
struct pairtype
{
	LL max,min,sum;
};
pairtype newpair(LL a,LL b,LL c){pairtype d;d.max=a,d.min=b,d.sum=c;return d;}
struct linetreetype
{
	struct sttype
	{
		bool seted;
		LL addv,setv;
		LL max,min,sum;
	};
	vector<sttype> st;
	//sttype st[800001];
	void buildtree(LL id,LL l,LL r)
	{
		if(id>=st.size())st.resize(id+1);
		st[id].sum=st[id].max=st[id].min=st[id].addv=0;
		st[id].seted=false;
		if(l==r)return;
		LL mid=(l+r)/2;
		buildtree(id*2,l,mid);
		buildtree(id*2+1,mid+1,r);
	}
	void putdown(LL id,LL l,LL r)
	{
		LL mid=(l+r)/2;
		if(st[id].seted)
		{
			st[id*2].sum=st[id].setv*(mid-l+1);
			st[id*2+1].sum=st[id].setv*(r-mid);
			st[id*2].max=st[id*2+1].max=st[id].setv;
			st[id*2].min=st[id*2+1].min=st[id].setv;
			st[id*2].setv=st[id*2+1].setv=st[id].setv;
			st[id*2].seted=st[id*2+1].seted=true;
			st[id*2].addv=st[id*2+1].addv=0;
			st[id].seted=false;
		}
		st[id*2].sum+=st[id].addv*(mid-l+1);
		st[id*2+1].sum+=st[id].addv*(r-mid);
		st[id*2].max+=st[id].addv;
		st[id*2+1].max+=st[id].addv;
		st[id*2].min+=st[id].addv;
		st[id*2+1].min+=st[id].addv;
		
		st[id*2].addv+=st[id].addv;
		st[id*2+1].addv+=st[id].addv;
		st[id].addv=0;
	}
	void setvalue(LL id,LL l,LL r,LL L,LL R,LL v,bool toadd)
	{
		if(l>=L&&r<=R)
		{
			if(toadd)
			{
				st[id].addv+=v;
				st[id].sum+=v*(r-l+1);
				st[id].max+=v;
				st[id].min+=v;
			}
			else
			{
				st[id].addv=0;
				st[id].seted=true;
				st[id].setv=v;
				st[id].sum=v*(r-l+1);
				st[id].max=st[id].min=v;
			}
			return;
		}
		if(l>R||r<L)return;
		putdown(id,l,r);
		LL mid=(l+r)/2;
		setvalue(id*2,l,mid,L,R,v,toadd);
		setvalue(id*2+1,mid+1,r,L,R,v,toadd);
		st[id].sum=st[id*2].sum+st[id*2+1].sum;
		st[id].max=st[id*2].max>st[id*2+1].max?st[id*2].max:st[id*2+1].max;
		st[id].min=st[id*2].min<st[id*2+1].min?st[id*2].min:st[id*2+1].min;
	}
	pairtype query(LL id,LL l,LL r,LL L,LL R)
	{
		if(l>=L&&r<=R)
		{
			return newpair(st[id].max,st[id].min,st[id].sum);
		}
		if(l>R||r<L) return newpair(-9223372036854775807LL,9223372036854775807LL,0);
		putdown(id,l,r);
		LL mid=(l+r)/2;
		pairtype a=query(id*2,l,mid,L,R),b=query(id*2+1,mid+1,r,L,R);
		a.sum+=b.sum;
		a.max=a.max>b.max?a.max:b.max;
		a.min=a.min<b.min?a.min:b.min;
		return a;
	}
};
vector<linetreetype> S;
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//printf("%lld\n",-9223372036854775808LL);
	while(scanf("%lld%lld%lld",&r,&n,&m)==3)
	{
		S.resize(r);
		for(LL i=0;i<r;i++)
		{
			S[i].st.clear();
			S[i].buildtree(1,1,n);
			//S[i].setvalue(1,1,n,1,n,0,false);
		}
		LL f,x1,y1,x2,y2,v;
		while(m--)
		{
			scanf("%lld%lld%lld%lld%lld",&f,&x1,&y1,&x2,&y2);
			//if(x1>x2)x1^=x2^=x1^=x2;
			//if(y1>y2)y1^=y2^=y1^=y2;
			if(f<=2)
			{
				scanf("%lld",&v);
				for(LL i=x1-1;i<x2;i++)
				{
					S[i].setvalue(1,1,n,y1,y2,v,f==1?true:false);
				}
			}
			else
			{
				pairtype ans=newpair(-9223372036854775807LL,9223372036854775807LL,0),a;
				for(LL i=x1-1;i<x2;i++)
				{
					a=S[i].query(1,1,n,y1,y2);
					ans.sum+=a.sum;
					ans.max=ans.max>a.max?ans.max:a.max;
					ans.min=ans.min<a.min?ans.min:a.min;
					//printf(" %lld %lld %lld\n",ans.sum,ans.min,ans.max);
				}
				printf("%lld %lld %lld\n",ans.sum,ans.min,ans.max);
			}
		}
	}
	return 0;
}
