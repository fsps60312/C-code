#include<bits/stdc++.h>
using namespace std;
typedef map<int,vector<int> > Avail;
int N,X[10],Y[10],VIS[1001],KASE=0;
vector<int>VX[10],VY[10];
void Add(const int &x,const int &y,const int &v)
{
	VIS[v]=KASE;
	VX[x].push_back(v);
	VY[y].push_back(v);
}
void Remove(const int &x,const int &y,const int &v)
{
	VIS[v]=0;
	VX[x].pop_back();
	VY[y].pop_back();
}
bool Valid(const int &x,const int &y,const int &v)
{
	if(VIS[v]==KASE)return false;
	if(VX[x].size()==2||VY[y].size()==2)return false;
	if(VX[x].size()==1&&v*VX[x][0]!=X[x])return false;
	if(VY[y].size()==1&&v*VY[y][0]!=Y[y])return false;
	if(VX[x].size()==0&&X[x]%v)return false;
	if(VY[y].size()==0&&Y[y]%v)return false;
	return true;
}
void GetAvail(const int &y,const int &a,Avail &avail)
{
	avail.clear();
	int b=Y[y]/a;
	for(int x1=0;x1<N;x1++)
	{
		if(!Valid(x1,y,a))continue;
		vector<int>&ava=avail[x1];
		for(int x2=0;x2<N;x2++)if(x2!=x1&&Valid(x2,y,b))ava.push_back(x2);
		if(!ava.size())avail.erase(x1);
	}
}
void GetAvail(const int &x,const int &y,const int a,vector<int>&ava)
{
	
}
bool Set(const int &ox,const int &oy,const int &ob)
{
	Add(ox,oy,ob);
	if(VX[ox].size()==2)
	{
		for(int y=0;y<N;y++)
		{
			if(VX[ox].size()==2)continue;
			Avail avail;
			for(int a=1;a*a<=Y[y];a++)
			{
				if(Y[y]%a!=0)continue;
				Avail avail;
				GetAvail(y,a,avail);
				int b=Y[y]/a;
				for(Avail::iterator it=avail.begin();it!=avail.end();it++)
				{
					const int &x1=it->first;
					const vector<int>&ava=it->second;
					Add(x1,y,a);
					for(int i=0;i<ava.size();i++)
					{
						int &x2=ava[i];
						if(Set(x2,y,b))return true;
					}
					Remove(x1,y,a);
				}
			}
			return false;
		}
		return true;
	}
	int a=X[ox]/ob;
	for(int y=0;y<N;y++)
	{
		if(y==oy||!Valid(ox,y,a))continue;
		Add(ox,y,a);
		vector<int>ava;
		GetAvail(ox,y,a,ava);
		int b=Y[y]/a;
		for(int i=0;i<ava.size();i++)
		{
			int &x=ava[i];
			if(Set(x,y,b))return true;
		}
		Remove(ox,y,a);
	}
	Remove(ox,oy,ob);
	return false;
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		KASE++;
		for(int i=0;i<N;i++)scanf("%d",&X[i]);
		for(int i=0;i<N;i++)scanf("%d",&Y[i]);
		for(int i=0;i<N;i++)
		{
			VX[i].clear(),VY[i].clear();
		}
		for(int a=1;a*a<=Y[0];a++)
		{
			if(Y[0]%a!=0)continue;
			static Avail avail;
			GetAvail(0,a,avail);
			int b=Y[0]/a;
			for(Avail::iterator it=avail.begin();it!=avail.end();it++)
			{
				const int &x1=it->first;
				const vector<int>&ava=it->second;
				Add(x1,0,a);
				for(int i=0;i<ava.size();i++)
				{
					int &x2=ava[i];
					if(Set(x2,0,b))goto printans;
				}
				Remove(x1,0,a);
			}
		}
		assert(0);
		printans:;
		static int xans[1001],ans[10][10];
		for(int i=0;i<N;i++)
		{
			xans[VX[i][0]]=xans[VX[i][1]]=i;
			for(int j=0;j<N;j++)ans[i][j]=0;
		}
		for(int i=0;i<N;i++)
		{
			ans[i][xans[VY[i][0]]]=VY[i][0];
			ans[i][xans[VY[i][1]]]=VY[i][1];
			printf("%d",ans[i][0]);
			for(int j=1;j<N;j++)printf(" %d",ans[i][j]);puts("");
		}
		puts("");
	} 
	return 0;
}
