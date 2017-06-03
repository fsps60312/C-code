#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1000000000;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
class SegTree
{
	private:
		int mn[4000000],mx[4000000];
		void Build(const int id,const int l,const int r)
		{
			mn[id]=INF,mx[id]=-INF;
			if(l==r)return;
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
		void Maintain(const int id){mn[id]=min(mn[id*2],mn[id*2+1]),mx[id]=max(mx[id*2],mx[id*2+1]);}
		void Modify(const int id,const int l,const int r,const int loc,const int mn_val,const int mx_val)
		{
			if(l==r){assert(loc==r);getmin(mn[id],mn_val),getmax(mx[id],mx_val);return;}
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc,mn_val,mx_val);
			else Modify(id*2+1,mid+1,r,loc,mn_val,mx_val);
			Maintain(id);
		}
		void Reset(const int id,const int l,const int r)
		{
			if(mn[id]==INF&&mx[id]==-INF)return;
			if(l==r){mn[id]=INF,mx[id]=-INF;return;}
			const int mid=(l+r)/2;
			Reset(id*2,l,mid),Reset(id*2+1,mid+1,r);
			Maintain(id);
			assert(mn[id]==INF&&mx[id]==-INF);
		}
		int Query(const int id,const int l,const int r,const int bl,const int br,const bool is_mn)const
		{
			if(r<bl||br<l)return is_mn?INF:-INF;
			if(bl<=l&&r<=br)return is_mn?mn[id]:mx[id];
			const int mid=(l+r)/2;
			const int lv=Query(id*2,l,mid,bl,br,is_mn),rv=Query(id*2+1,mid+1,r,bl,br,is_mn);
			return is_mn?min(lv,rv):max(lv,rv);
		}
	public:
		SegTree(){Build(1,1,1000000);}
		void Modify(const int loc,const int mn_val,const int mx_val){Modify(1,1,1000000,loc,mn_val,mx_val);}
		int QueryMin(const int bl,const int br)const{return Query(1,1,1000000,bl,br,true);}
		int QueryMax(const int bl,const int br)const{return Query(1,1,1000000,bl,br,false);}
		void Reset(){Reset(1,1,1000000);}
};
struct Operation
{
	int time,x,y;
	Operation(){}
	Operation(const int _time,const int _x,const int _y):time(_time),x(_x),y(_y){}
};
bool CmpT(const Operation &a,const Operation &b){return a.time<b.time;}
bool CmpY(const Operation &a,const Operation &b){return a.y<b.y;}
int N,ANS[200000];
void Query(const vector<Operation>&ope_add,const vector<Operation>&ope_que,const int l,const int r,SegTree &seg_tree)
{
	if(ope_add.empty()||ope_que.empty())return;
	const int mid=(l+r)/2;
	vector<Operation>ch_ope_add[2],ch_ope_que[2];
	for(const Operation &o:ope_add)ch_ope_add[o.time>mid].push_back(o);
	for(const Operation &o:ope_que)ch_ope_que[o.time>mid].push_back(o);
	if(true)
	{
		auto &ope=ch_ope_add[0],&que=ch_ope_que[1];
		sort(ope.begin(),ope.end(),CmpY);
		sort(que.begin(),que.end(),CmpY);
		if(true)
		{
			int i=-1;
			for(const Operation &q:que)
			{
				while(i+1<(int)ope.size()&&ope[i+1].y<=q.y)
				{
					i++,seg_tree.Modify(ope[i].x,ope[i].x-ope[i].y,ope[i].x+ope[i].y);
				}
				getmin(ANS[q.time],seg_tree.QueryMin(q.x,1000000)-(q.x-q.y));
				getmin(ANS[q.time],(q.x+q.y)-seg_tree.QueryMax(1,q.x));
			}
			seg_tree.Reset();
		}
		for(int l=0,r=(int)ope.size()-1;l<r;l++,r--)swap(ope[l],ope[r]);
		for(int l=0,r=(int)que.size()-1;l<r;l++,r--)swap(que[l],que[r]);
		if(true)
		{
			int i=-1;
			for(const Operation &q:que)
			{
				while(i+1<(int)ope.size()&&ope[i+1].y>=q.y)
				{
					i++,seg_tree.Modify(ope[i].x,ope[i].x+ope[i].y,ope[i].x-ope[i].y);
				}
				getmin(ANS[q.time],seg_tree.QueryMin(q.x,1000000)-(q.x+q.y));
				getmin(ANS[q.time],(q.x-q.y)-seg_tree.QueryMax(1,q.x));
			}
			seg_tree.Reset();
		}
		sort(ope.begin(),ope.end(),CmpT);
		sort(que.begin(),que.end(),CmpT);
	}
	Query(ch_ope_add[0],ch_ope_que[0],l,mid,seg_tree);
	Query(ch_ope_add[1],ch_ope_que[1],mid+1,r,seg_tree);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		vector<Operation>ope_add,ope_que;
		for(int i=0,type,x,y;i<N;i++)
		{
			scanf("%d%d%d",&type,&x,&y);
			(type==0?ope_add:ope_que).push_back(Operation(i,x,y));
			if(type==1)ANS[i]=INF;
		}
		static SegTree seg_tree=SegTree();
		Query(ope_add,ope_que,0,N-1,seg_tree);
		for(const Operation &o:ope_que)printf("%d\n",ANS[o.time]);
	}
	return 0;
}
