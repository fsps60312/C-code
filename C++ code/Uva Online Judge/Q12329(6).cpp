#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
LL N;
struct NodeInfo
{
	LL value,row,column;
	NodeInfo *ch[2];
	NodeInfo(const LL &_v,const LL &_h):value(_v),row(_h),column(-1LL),ch{NULL,NULL}{}
};
map<LL,NodeInfo*>NODE;
bool AtRange(const LL &v,const LL &l,const LL &r){return l<=v&&v<=r;}
bool AtRange(const LL &r,const LL &c,const LL &r1,const LL &r2,const LL &c1,const LL &c2){return AtRange(r,r1,r2)&&AtRange(c,c1,c2);}
struct OutputAns
{
	char grid[200][200];
	LL row1,row2,column1,column2;
	void Clear(const LL &_r1,const LL &_c1,const LL &_r2,const LL &_c2)
	{
		row1=_r1,row2=_r2,column1=_c1,column2=_c2;
		for(LL r=row1;r<=row2;r++)for(LL c=column1;c<=column2;c++)grid[r-row1][c-column1]=' ';
	}
	void Set(char &o,const char v){assert(o==' ');o=v;}
	void Set(const LL &_r,const LL &_c,const char v)
	{
		if(!AtRange(_r,_c,row1,row2,column1,column2))return;
		Set(grid[_r-row1][_c-column1],v);
	}
	void Set(const LL &_r,const LL &_c1,const LL &_c2,const char v)
	{
		if(!AtRange(_r,row1,row2))return;
		for(LL c=max(column1,_c1);c<=min(column2,_c2);c++)Set(_r,c,v);
	}
	void Print()
	{
		for(LL r=row1;r<=row2;r++)
		{
			bool found=false;
			for(LL c=column1;c<=column2;c++)if(grid[r-row1][c-column1]!=' '){found=true;break;}
			if(!found)continue;
			for(LL c=column1;c<=column2;c++)putchar(grid[r-row1][c-column1]);
			putchar('\n');
		}
		putchar('\n');
	}
}ANS;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casenumber;
	assert(scanf("%d",&casenumber)==1);
	while(casenumber--)
	{
		assert(scanf("%lld",&N)==1);
		NODE.clear();
		for(;;)
		{
			static LL val;assert(scanf("%lld",&val)==1);
			NODE[val]=new NodeInfo(val,1LL);
			break;
		}
		for(LL i=1LL,val;i<N;i++)
		{
			assert(scanf("%lld",&val)==1);
			auto it=NODE.upper_bound(val);
			NodeInfo *nr=(it==NODE.end()?NULL:it->second);
			NodeInfo *nl;
			if(it==NODE.begin())nl=NULL;
			else assert((--it)->first<val),nl=it->second;
			const bool left_connectable=(nl?(nl->ch[1]?false:true):false);
			const bool right_connectable=(nr?(nr->ch[0]?false:true):false);
			assert(!left_connectable||!right_connectable);
			if(left_connectable)nl->ch[1]=NODE[val]=new NodeInfo(val,(nl->row)+2LL);
			else if(right_connectable)nr->ch[0]=NODE[val]=new NodeInfo(val,(nr->row)+2LL);
			else assert(0&&"Can't connect to any node");
		}
		LL cnt=1LL;
		for(auto &it:NODE)it.second->column=cnt++;
		static int querynumber;assert(scanf("%d",&querynumber)==1);
		static int kase=1;
		printf("Case #%d:\n",kase++);
		while(querynumber--)
		{
			static LL row1,column1,row2,column2;
			assert(scanf("%lld%lld%lld%lld",&row1,&column1,&row2,&column2)==4);
			row2=row1+row2-1LL,column2=column1+column2-1LL;
			ANS.Clear(row1,column1,row2,column2);
			for(const auto &it:NODE)
			{
				const NodeInfo *o=it.second;
				ANS.Set(o->row,o->column,'o');
				if(o->ch[0])
				{
					const NodeInfo *lch=o->ch[0];
					assert((o->row)+2LL==(lch->row));
					ANS.Set(o->row,(lch->column)+1LL,(o->column)-1LL,'-');
					ANS.Set(o->row,lch->column,'+');
					ANS.Set(o->row+1LL,lch->column,'|');
				}
				if(o->ch[1])
				{
					const NodeInfo *rch=o->ch[1];
					assert((o->row)+2LL==(rch->row));
					ANS.Set(o->row,(o->column)+1LL,(rch->column)-1LL,'-');
					ANS.Set(o->row,rch->column,'+');
					ANS.Set(o->row+1LL,rch->column,'|');
				}
			}
			ANS.Print();
		}
	}
	assert(scanf("%d",&casenumber)!=1);
	return 0;
}
