#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int T,N,Q;
vector<int>S;
vector<int>ST;
vector<int>TAG;
vector<bool>INV;
void Build(const int id,const int l,const int r)
{
	while(ST.size()<=id)ST.push_back(0),TAG.push_back(-1),INV.push_back(false);
	TAG[id]=-1,INV[id]=false;
	if(l==r){ST[id]=S[l];return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	ST[id]=ST[id*2]+ST[id*2+1];
}
void PutDown(const int id,const int l,const int r,const int mid)
{
	if(TAG[id]!=-1)
	{
		ST[id*2]=(mid-l+1)*TAG[id];
		ST[id*2+1]=(r-mid)*TAG[id];
		TAG[id*2]=TAG[id*2+1]=TAG[id];
		INV[id*2]=INV[id*2+1]=false;
		TAG[id]=-1;
	}
	if(INV[id])
	{
		ST[id*2]=(mid-l+1)-ST[id*2];
		ST[id*2+1]=(r-mid)-ST[id*2+1];
		INV[id*2]=(INV[id*2]^true),INV[id*2+1]=(INV[id*2+1]^true);
		INV[id]=false;
	}
}
void Modify(const int id,const int l,const int r,const int lb,const int rb,const int v)
{
	if(r<lb||rb<l)return;
	if(lb<=l&&r<=rb)
	{
		if(v==-1)
		{
			ST[id]=(r-l+1)-ST[id];
			INV[id]=(INV[id]^true);
		}
		else
		{
			ST[id]=(r-l+1)*v;
			TAG[id]=v;
			INV[id]=false;
		}
		return;
	}
	const int mid=(l+r)/2;
	PutDown(id,l,r,mid);
	Modify(id*2,l,mid,lb,rb,v),Modify(id*2+1,mid+1,r,lb,rb,v);
	ST[id]=ST[id*2]+ST[id*2+1];
}
int Query(const int id,const int l,const int r,const int lb,const int rb)
{
	if(r<lb||rb<l)return 0;
	if(lb<=l&&r<=rb)return ST[id];
	const int mid=(l+r)/2;
	PutDown(id,l,r,mid);
	return Query(id*2,l,mid,lb,rb)+Query(id*2+1,mid+1,r,lb,rb);
}
//void Print()
//{
//	for(int i=0;i<N;i++)printf("%d",Query(1,0,N-1,i,i));puts("");
//}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		S.clear();
		while(N--)
		{
			static char tmp[1000000];
			static int repeat;
			scanf("%d%s",&repeat,tmp);
			for(int i=0;i<repeat;i++)
			{
				for(int j=0;tmp[j];j++)
				{
					if(tmp[j]=='0')S.push_back(0);
					else if(tmp[j]=='1')S.push_back(1);
					else assert(0);
				}
			}
		}
		Build(1,0,(N=S.size())-1);
		static int kase=1;
		printf("Case %d:\n",kase++);
		scanf("%d",&Q);
		int qkase=1;
//		Print();
		while(Q--)
		{
			static char tmp[2];scanf("%s",tmp);
			static int a,b;scanf("%d%d",&a,&b);
			switch(tmp[0])
			{
				case'F':Modify(1,0,N-1,a,b,1);break;
				case'E':Modify(1,0,N-1,a,b,0);break;
				case'I':Modify(1,0,N-1,a,b,-1);break;
				case'S':printf("Q%d: %d\n",qkase++,Query(1,0,N-1,a,b));break;
				default:assert(0);
			}
//			Print();
		}
//		Print();
	}
	return 0;
}
