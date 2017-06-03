#include<cstdio>
#include<string>
#include<vector>
#include<map>
void getmin(int &a,int b){if(b<a)a=b;}
using namespace std;
int N;
map<string,int> IDX;
int getIDX(char* name)
{
	if(IDX.find(name)==IDX.end())
	{
		int sz=IDX.size();
		IDX[name]=sz;
	}
	return IDX[name];
}
char CNAME[25];
void canf(int &a)
{
	scanf("%s",CNAME);
	a=getIDX(CNAME);
}
class Cube
{
	public:
	int front,right,up,down,left,back;
	Cube(int f,int r,int u,int d,int l,int b):front(f),right(r),up(u),down(d),left(l),back(b){}
	Cube(){}
	void input()
	{
		canf(front);
		canf(right);
		canf(up);
		canf(down);
		canf(left);
		canf(back);
	}
	void TurnRight()
	{
		int f=left;
		left=back;
		back=right;
		right=front;
		front=f;
	}
	void TurnUp()
	{
		int f=down;
		down=back;
		back=up;
		up=front;
		front=f;
	}
	int directdiffer(Cube c)
	{
		int ans=0;
		if(front!=c.front)ans++;
		if(right!=c.right)ans++;
		if(up!=c.up)ans++;
		if(down!=c.down)ans++;
		if(left!=c.left)ans++;
		if(back!=c.back)ans++;
		return ans;
	}
	int turnrightdiffer(Cube c)
	{
		int ans=6;
		getmin(ans,directdiffer(c));c.TurnRight();
		getmin(ans,directdiffer(c));c.TurnRight();
		getmin(ans,directdiffer(c));c.TurnRight();
		getmin(ans,directdiffer(c));c.TurnRight();
		return ans;
	}
	int differ(Cube c)
	{
		int ans=6;
		getmin(ans,turnrightdiffer(c));c.TurnUp();
		getmin(ans,turnrightdiffer(c));c.TurnUp();
		getmin(ans,turnrightdiffer(c));c.TurnUp();
		getmin(ans,turnrightdiffer(c));c.TurnUp();
		c.TurnRight();c.TurnUp();
		getmin(ans,turnrightdiffer(c));
		c.TurnUp();c.TurnUp();
		getmin(ans,turnrightdiffer(c));
		return ans;
	}
};
vector<Cube> CUBE;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		CUBE.clear();
		IDX.clear();
		for(int i=0;i<N;i++)
		{
			Cube c;
			c.input();
			CUBE.push_back(c);
		}
		//printf("complete\n");
		int n=IDX.size();
		int ans=2147483647;
		for(int i0=0;i0<n;i0++)
		for(int i1=0;i1<n;i1++)
		{
			int v=i0>i1?i0:i1;
			for(int i2=v;i2<n;i2++)
			for(int i3=v;i3<n;i3++)
			for(int i4=v;i4<n;i4++)
			for(int i5=v;i5<n;i5++)
			{
				Cube c=Cube(i0,i1,i2,i3,i4,i5);
				int j=0;
				for(int i=0;i<N;i++)j+=c.differ(CUBE[i]);
				if(j<ans)ans=j;
				c=Cube(i2,i3,i0,i1,i4,i5);
				j=0;
				for(int i=0;i<N;i++)j+=c.differ(CUBE[i]);
				if(j<ans)ans=j;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
