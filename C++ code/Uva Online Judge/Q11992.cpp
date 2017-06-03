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
		bool add;
		LL tag;
		LL max,min,sum;
	};
	vector<sttype> st;
	//sttype st[800001];
	void buildtree(LL id,LL l,LL r)
	{
		if(id*2+1>=st.size())st.resize(id*2+2);
		st[id].sum=st[id].max=st[id].min=st[id].tag=0;
		st[id].add=false;
		if(l==r)return;
		LL mid=(l+r)/2;
		buildtree(id*2,l,mid);
		buildtree(id*2+1,mid+1,r);
	}
	void putdown(LL id,LL l,LL r)
	{
		LL mid=(l+r)/2;
		if(st[id].add)
		{
			st[id*2].sum+=st[id].tag*(mid-l+1);
			st[id*2+1].sum+=st[id].tag*(r-mid);
			st[id*2].max+=st[id].tag;
			st[id*2+1].max+=st[id].tag;
			st[id*2].min+=st[id].tag;
			st[id*2+1].min+=st[id].tag;
		}
		else
		{
			st[id*2].sum=st[id].tag*(mid-l+1);
			st[id*2+1].sum=st[id].tag*(r-mid);
			st[id*2].max=st[id].tag;
			st[id*2+1].max=st[id].tag;
			st[id*2].min=st[id].tag;
			st[id*2+1].min=st[id].tag;
		}
		st[id*2].tag=st[id*2+1].tag=st[id].tag;
		st[id*2].add=st[id*2+1].add=st[id].add;
		st[id].tag=0;
		st[id].add=true;
	}
	void setvalue(LL id,LL l,LL r,LL L,LL R,LL v,bool toadd)
	{
		putdown(id,l,r);
		if(l>=L&&r<=R)
		{
			st[id].add=toadd;
			st[id].tag=v;
			if(toadd)
			{
				st[id].sum+=v*(r-l+1);
				st[id].max+=v;
				st[id].min+=v;
			}
			else
			{
				st[id].sum=v*(r-l+1);
				st[id].max=st[id].min=v;
			}
			return;
		}
		if(l>R||r<L)return;
		LL mid=(l+r)/2;
		setvalue(id*2,l,mid,L,R,v,toadd);
		setvalue(id*2+1,mid+1,r,L,R,v,toadd);
		st[id].sum=st[id*2].sum+st[id*2+1].sum;
		st[id].max=st[id*2].max>st[id*2+1].max?st[id*2].max:st[id*2+1].max;
		st[id].min=st[id*2].min<st[id*2+1].min?st[id*2].min:st[id*2+1].min;
	}
	pairtype query(LL id,LL l,LL r,LL L,LL R)
	{
		putdown(id,l,r);
		if(l>=L&&r<=R)
		{
			return newpair(st[id].max,st[id].min,st[id].sum);
		}
		if(l>R||r<L) return newpair(-9223372036854775808LL,9223372036854775807LL,0);
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
	freopen("in.txt","r",stdin);
	//printf("%lld\n",-9223372036854775808LL);
	while(scanf("%lld%lld%lld",&r,&n,&m)==3)
	{
		S.resize(r);
		for(LL i=0;i<r;i++)
		{
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
				pairtype ans=newpair(-9223372036854775808LL,9223372036854775807LL,0),a;
				for(LL i=x1-1;i<x2;i++)
				{
				//printf("%lld:\t%lld %lld %lld\n",i,ans.sum,ans.min,ans.max);
					a=S[i].query(1,1,n,y1,y2);
					ans.sum+=a.sum;
					ans.max=ans.max>a.max?ans.max:a.max;
					ans.min=ans.min<a.min?ans.min:a.min;
				}
				printf("%lld %lld %lld\n",ans.sum,ans.min,ans.max);
			}
		}
	}
	return 0;
}
