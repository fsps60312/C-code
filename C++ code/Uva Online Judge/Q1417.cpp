#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
using namespace std;
int C;
bool ROAD[99999][2];
struct Node
{
	bool conect[2][2];
	bool *operator[](const int i){return conect[i];}
	Node(){}
	Node(const bool uu,const bool ud,const bool du,const bool dd):conect{{uu,ud},{du,dd}}{}
}ST[400000];
Node Merge(Node a,Node b,const int loc)
{
	assert(loc>=0&&loc+1<C);
	Node ans;
	ans[0][0]=(a[0][0]&&ROAD[loc][0]&&b[0][0])||(a[0][1]&&ROAD[loc][1]&&b[1][0]);
	ans[0][1]=(a[0][0]&&ROAD[loc][0]&&b[0][1])||(a[0][1]&&ROAD[loc][1]&&b[1][1]);
	ans[1][0]=(a[1][0]&&ROAD[loc][0]&&b[0][0])||(a[1][1]&&ROAD[loc][1]&&b[1][0]);
	ans[1][1]=(a[1][0]&&ROAD[loc][0]&&b[0][1])||(a[1][1]&&ROAD[loc][1]&&b[1][1]);
	return ans;
}
void Build(const int id,const int l,const int r)
{
	if(l==r){ST[id]=Node(true,false,false,true);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	ST[id]=Merge(ST[id*2],ST[id*2+1],mid);
}
void ModifyV(const int id,const int l,const int r,const int loc,const bool value)
{
	assert(l<=loc&&loc<=r);
	if(l==r){ST[id]=Node(true,value,value,true);return;}
	const int mid=(l+r)/2;
	if(loc<=mid)ModifyV(id*2,l,mid,loc,value);
	else ModifyV(id*2+1,mid+1,r,loc,value);
	ST[id]=Merge(ST[id*2],ST[id*2+1],mid);
}
void ModifyH(const int id,const int l,const int r,const int loc)
{
	if(r<=loc||l>=loc+1)return;
	const int mid=(l+r)/2;
	ModifyH(id*2,l,mid,loc);
	ModifyH(id*2+1,mid+1,r,loc);
	ST[id]=Merge(ST[id*2],ST[id*2+1],mid);
}
Node Query(const int id,const int l,const int r,const int bl,const int br)
{
	assert(bl<=br);
	if(bl<=l&&r<=br)return ST[id];
	const int mid=(l+r)/2;
	if(mid<bl)return Query(id*2+1,mid+1,r,bl,br);
	else if(mid+1>br)return Query(id*2,l,mid,bl,br);
	Node a,b;
	return Merge(a=Query(id*2,l,mid,bl,br),b=Query(id*2+1,mid+1,r,bl,br),mid);
}
Node Query(const int bl,const int br){return Query(1,0,C-1,bl,br);}
set<int>VR;
bool Solve(const int r1,const int c1,const int r2,const int c2)
{
	assert(c1<=c2);
	if(Query(c1,c2)[r1][r2])return true;
	if(r1!=r2)
	{
		auto it=VR.lower_bound(c1);
		if(it!=VR.begin())
		{
			const int l=*(--it);
//			printf("l=%d\n",l);
			if(Query(l,c1)[r1][r1]&&Query(l,c2)[r2][r2])return true;
		}
		it=VR.upper_bound(c2);
		if(it!=VR.end())
		{
			const int r=*it;
//			printf("r=%d\n",r);
			if(Query(c1,r)[r1][r1]&&Query(c2,r)[r2][r2])return true;
		}
		return false;
	}
	else return (Solve(r1,c1,r1^1,c1)&&Solve(r1^1,c1,r2,c2))||(Solve(r1,c1,r2^1,c2)&&Solve(r2^1,c2,r2,c2));
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		scanf("%d",&C);
		for(int i=0;i+1<C;i++)ROAD[i][0]=ROAD[i][1]=false;
		VR.clear();
		Build(1,0,C-1);
		static char tmp[5];
		while(scanf("%s",tmp)==1)
		{
			static int r1,c1,r2,c2;
			switch(tmp[0])
			{
				case'E':goto end_of_case;
				case'C':
				case'O':
				{
					assert(scanf("%d%d%d%d",&r1,&c1,&r2,&c2)==4);
					r1--,c1--,r2--,c2--;
					if(r1>r2)swap(r1,r2);
					if(c1>c2)swap(c1,c2);
					assert((r1==r2)!=(c1==c2));
					if(r1==r2)
					{
						assert(c1+1==c2);
						ROAD[c1][r1]=(tmp[0]=='O');
						ModifyH(1,0,C-1,c1);
					}
					else
					{
						assert(r1+1==r2);
						ModifyV(1,0,C-1,c1,tmp[0]=='O');
						if(tmp[0]=='O')VR.insert(c1);
						else VR.erase(c1);
					}
				}break;
				case'A':
				{
					assert(scanf("%d%d%d%d",&r1,&c1,&r2,&c2)==4);
					r1--,c1--,r2--,c2--;
					if(c1>c2)swap(r1,r2),swap(c1,c2);
					puts(Solve(r1,c1,r2,c2)?"Y":"N");
				}break;
				default:assert(0);break;
			}
		}
		end_of_case:;
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
