#include<bits/stdc++.h>
using namespace std;
int N,X[10],Y[10];
int VIS[1001],KASE=0;
vector<int>VX[10],VY[10];
bool Valid(const int &x,const int &y,const int &v)
{
	if(VX[x].size()==2||VY[y].size()==2)return false;
	if(VX[x].size()==1){if(X[x]!=v)return false;}
	else if(X[x]%v!=0)return false;
	if(VY[y].size()==1){if(Y[y]!=v)return false;}
	else if(Y[y]%v!=0)return false;
	if(VIS[v]==KASE)return false;
	return true;
}
void Add(const int &x,const int &y,const int &v)
{
	VIS[v]=KASE;
	VX[x].push_back(v),VY[y].push_back(v);
	X[x]/=v,Y[y]/=v;
}
void Remove(const int &x,const int &y,const int &v)
{
	VIS[v]=0;
	VX[x].pop_back(),VY[y].pop_back();
	X[x]*=v,Y[y]*=v;
} 
bool Set(const int &x,const int &y,const int &a)
{
	if(!Valid(x,y,a))return false;
	Add(x,y,a);
	if(VY[y].size()==1)
	{
		int aa=Y[y]/a;
		for(int xx=0;xx<N;xx++)
		{
			assert(VX[xx].size()==0||VX[xx].size()==2);
			if(!Valid(xx,y,aa))continue;
			Add(xx,y,aa);
			int bb=X[xx];
			for(int yy=0;yy<N;yy++)
			{
				if(yy==y||!Valid(xx,yy,bb))continue;
				if(Set(xx,yy,bb))return true;
			}
			Remove(xx,y,aa);
		}
		return false;
	}
	else
	{
		for(int i=0;i<N;i++)
		{
			assert(VX[i].size()==0||VX[i].size()==2);
			if(VX[i].size()==0)
			{
				for(int aa=1;aa*aa<=X[i];aa++)
				{
					if(X[i]%aa!=0)continue;
					int bb=X[i]/aa;
					for(int j=0;j<N;j++)
					{
						if(!Valid(i,j,aa))continue;
						Add(i,j,aa);
						for(int k=0;k<N;k++)
						{
							if(k==j||!Valid(i,k,bb))continue;
							if(Set(i,k,bb))return true;
						}
						Remove(i,j,aa);
					}
				}
				return false;
			}
		}
		return true;
	}
	Remove(x,y,a);
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=1;i<=1000;i++)VIS[i]=0;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&X[i]);
		for(int i=0;i<N;i++)scanf("%d",&Y[i]);
		for(int i=0;i<N;i++)VX[i].clear(),VY[i].clear();
		KASE++;
		for(int a=1;a*a<=X[0];a++)
		{
			if(X[0]%a!=0)continue;
			int b=X[0]/a;
			for(int y1=0;y1<N;y1++)
			{
				if(!Valid(0,y1,a))continue;
				Add(0,y1,a);
				for(int y2=0;y2<N;y2++)
				{
					if(y2==y1||!Valid(0,y2,b))continue;
					if(Set(0,y2,b))goto printans;
				}
				Remove(0,y1,a);
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
