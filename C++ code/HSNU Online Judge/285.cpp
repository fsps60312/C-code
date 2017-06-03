#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
const LL MOD=1000000000LL;
void Plus(LL &a,const LL &b){(a+=b)%=MOD;}
int N,M;
vector<LL>F,FSUM;
LL GetF(const int i)
{
	if(i<(int)F.size())return F[i];
	F.push_back((GetF(i-2)+GetF(i-1))%MOD);
	FSUM.push_back(FSUM[i-1]+F[i]);
	return F[i];
}
LL GetFSum(const int l,const int r){GetF(r);return FSUM[r]-FSUM[l-1];}
struct SegTree
{
	const int gap;
	vector<LL>sum,tag;
	SegTree(const int _gap):gap(_gap){}
	void Maintain(const int id){sum[id]=(sum[id*2]+sum[id*2+1])%MOD;}
	void PutDown(const int id,const int l,const int mid,const int r)
	{
		if(tag[id]==0LL)return;
		const LL v=tag[id];tag[id]=0LL;
		Plus(tag[id*2],v);
		Plus(tag[id*2+1],v);
		Plus(sum[id*2],v*GetFSum(gap+l,gap+mid));
		Plus(sum[id*2+1],v*GetFSum(gap+mid+1,gap+r));
	}
	void Build(const int id,const int l,const int r,const vector<LL>&s)
	{
		while((int)sum.size()<=id)sum.push_back(0LL),tag.push_back(0LL);
		tag[id]=0LL;
		if(l==r){sum[id]=(s[r]*GetF(gap+r))%MOD;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,s),Build(id*2+1,mid+1,r,s);
		Maintain(id);
	}
	void Add(const int id,const int l,const int r,const int bl,const int br,const LL &v)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){Plus(tag[id],v),Plus(sum[id],v*GetFSum(gap+l,gap+r));return;}
		const int mid=(l+r)/2;
		PutDown(id,l,mid,r);
		Add(id*2,l,mid,bl,br,v),Add(id*2+1,mid+1,r,bl,br,v);
		Maintain(id);
	}
	void Modify(const int id,const int l,const int r,const int loc,const LL &v)
	{
		if(l==r){assert(r==loc);sum[id]=(v*GetF(gap+r))%MOD;return;}
		const int mid=(l+r)/2;
		PutDown(id,l,mid,r);
		if(loc<=mid)Modify(id*2,l,mid,loc,v);
		else Modify(id*2+1,mid+1,r,loc,v);
		Maintain(id);
	}
	LL Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return 0LL;
		if(bl<=l&&r<=br)return sum[id];
		const int mid=(l+r)/2;
		PutDown(id,l,mid,r);
		return (Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br))%MOD;
	}
}SEG1=SegTree(1),SEG2=SegTree(2);
vector<pair<LL,LL> >COE;
pair<LL,LL>GetCOE(const int i)
{
	if(i<(int)COE.size())return COE[i];
	const pair<LL,LL>p1=GetCOE(i-2),p2=GetCOE(i-1);
	COE.push_back(make_pair((p1.first-p2.first+MOD)%MOD,(p1.second-p2.second+MOD)%MOD));
	return COE[i];
}
int main()
{
//	freopen("in.txt","r",stdin);
	F.push_back(1),F.push_back(1);
	FSUM.push_back(1),FSUM.push_back(2);
	COE.push_back(make_pair(1LL,0LL)),COE.push_back(make_pair(-1LL,1LL));
	while(scanf("%d%d",&N,&M)==2)
	{
		if(true)
		{
			vector<LL>s;
			for(int i=0;i<N;i++)
			{
				static LL v;scanf("%lld",&v);
				s.push_back(v);
			}
			SEG1.Build(1,0,N-1,s),SEG2.Build(1,0,N-1,s);
			s.clear(),vector<LL>().swap(s);
		}
		for(int type;M--;)
		{
			scanf("%d",&type);
			switch(type)
			{
				case 1:
				{
					static int x,v;
					scanf("%d%d",&x,&v),x--;
					SEG1.Modify(1,0,N-1,x,v),SEG2.Modify(1,0,N-1,x,v);
				}break;
				case 2:
				{
					static int l,r;
					scanf("%d%d",&l,&r),l--,r--;
					const LL v1=SEG1.Query(1,0,N-1,l,r),v2=SEG2.Query(1,0,N-1,l,r);
					const pair<LL,LL>p=GetCOE(SEG1.gap+l);
					const LL ans=((p.first*v1+p.second*v2)%MOD+MOD)%MOD;
					printf("%lld\n",ans);
				}break;
				case 3:
				{
					static int l,r,d;
					scanf("%d%d%d",&l,&r,&d),l--,r--;
					SEG1.Add(1,0,N-1,l,r,d),SEG2.Add(1,0,N-1,l,r,d);
				}break;
				default:assert(0);break;
			}
		}
		break;
	}
	return 0;
}
