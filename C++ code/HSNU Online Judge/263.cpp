#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int X[150000],L,EXPECT;
struct Node
{
	Node *nl,*nr;
	vector<int>elephant,camera,rspan;
	Node():nr(NULL),nl(NULL){}
	int size()const{return elephant.size();}
	int Loc(const int rank){return X[elephant[rank]];}
	void Rebuild()
	{
		camera.resize(size()),rspan.resize(size());
		for(int i=(int)size()-1;i>=0;i--)
		{
			int l=i,r=size()-1;
			while(l<r)
			{
				const int mid=(l+r+1)/2;
				if(Loc(mid)<=Loc(i)+L)l=mid;
				else r=mid-1;
			}
			if(l==size()-1)camera[i]=1,rspan[i]=Loc(i)+L;
			else camera[i]=1+camera[l+1],rspan[i]=rspan[l+1];
		}
	}
	int LastLoc(){return Loc(size()-1);}
	int FirstLoc(){return Loc(0);}
	int Camera(int &loc)
	{
		int l=0,r=size();
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Loc(mid)<=loc)l=mid+1;
			else r=mid;
		}
		if(l==size())return 0;
		loc=rspan[l];
		return camera[l];
	}
	void CastElephants()
	{
		assert(nr);
		nr->elephant.clear();
		int mid=size()/2;
		for(int i=mid;i<size();i++)nr->elephant.push_back(elephant[i]);
		while(size()>mid)elephant.pop_back();
		Rebuild(),nr->Rebuild();
	}
	bool Insert(const int ei)
	{
		if(nl&&nl->LastLoc()>X[ei])return false;
		if(nr&&nr->FirstLoc()<X[ei])return false;
		elephant.push_back(-1);
		int idx;
		for(idx=size()-1;idx>=1&&Loc(idx-1)>X[ei];elephant[idx]=elephant[idx-1],idx--);
		elephant[idx]=ei;
		if(size()>=EXPECT*3)
		{
			Node *ch=new Node();
			if(nr)nr->nl=ch;
			ch->nl=this,ch->nr=nr;
			nr=ch;
			CastElephants();
		}
		else Rebuild();
		return true;
	}
	void MergeRight()
	{
		assert(nr);
		for(int i=0;i<nr->size();i++)elephant.push_back(nr->elephant[i]);
		if(size()<EXPECT*5/2)
		{
			Node *tmp=nr->nr;
			delete nr;
			nr=tmp;
			if(nr)nr->nl=this;
			Rebuild();
		}
		else CastElephants();
	}
	bool Erase(const int ei)
	{
		int l=0,r=size()-1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Loc(mid)<X[ei])l=mid+1;
			else r=mid;
		}
		if(elephant[l]!=ei)return false;
		for(int i=l+1;i<size();i++)elephant[i-1]=elephant[i];
		elephant.pop_back();
		if(size()<EXPECT)
		{
			if(nr)MergeRight();
			else if(nl)nl->MergeRight();
			else Rebuild();
		}
		else Rebuild();
		return true;
	}
//	void Print()
//	{
//		putchar('{');
//		for(int i=0;i<size();i++)printf("(%d,%d,c=%d,s=%d)",elephant[i],Loc(i),camera[i],rspan[i]);
//		putchar('}');
//	}
}*FIRST;
//void Print()
//{
//	for(Node *u=FIRST;u;u=u->nr)u->Print();puts("");
//}
int Solve()
{
	int ans=0,loc=-1;
	for(Node *u=FIRST;u;u=u->nr)ans+=u->Camera(loc);
	return ans;
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&L,&M);
	EXPECT=1;
	while(2*EXPECT*EXPECT<N)EXPECT++;
	for(int i=0,x;i<N;i++)scanf("%d",&X[i]);
	Node *tmp=FIRST=new Node();
	for(int i=0;i<N;i++)
	{
		if(tmp->size()>=EXPECT*2)
		{
			tmp->Rebuild();
			tmp->nr=new Node();
			tmp->nr->nl=tmp;
			tmp=tmp->nr;
		}
		tmp->elephant.push_back(i);
	}
	tmp->Rebuild();
//	Print();
	int pre=0;
	while(M--)
	{
		static int a,b;scanf("%d%d",&a,&b);
		a-=pre,b-=pre;
//		printf("Elephant %d move to %d\n",a,b);
		bool found=false;
		for(tmp=FIRST;tmp;tmp=tmp->nr)if(tmp->Erase(a)){found=true;break;}
		assert(found&&"Erase");
		X[a]=b;
		found=false;
		for(tmp=FIRST;tmp;tmp=tmp->nr)if(tmp->Insert(a)){found=true;break;}
		assert(found&&"Insert");
		pre=Solve();
//		Print();
		printf("%d\n",pre);
	}
	return 0;
}
