#include<cstdio>
using namespace std;
void termin(){int a[1];for(int i=0;;i--)a[i]=9;}
int N,PILE[4][41];
struct vector
{
	int v,sz;
	vector():v(0),sz(0){}
	int operator[](int i){i=sz-1-i;return (v>>(5*i))&31;}
	void operator<<=(int i)
	{
		int mid=((*this)[i]);
		i=sz-1-i;
		int left=(v>>(5*(i+1)))<<(5*(i+1));
		int right=v-left-(mid<<(5*i));
		v=left+(right<<5);
	}
	int size(){return sz;}
	void push_back(int i)
	{
		v<<=5;
		v+=i;
		sz++;
	}
	void pop_back()
	{
		v>>=5;
		sz--;
	}
	void clear(){v=sz=0;}
};
vector DP[41][41][41][41];
void removeback(vector &v)
{
	int cmp=v[v.size()-1];
	for(int i=0;i<v.size()-1;i++)
	{
		if(v[i]==cmp)
		{
			v<<=i;
			v.pop_back();
			v.pop_back();
			return;
		}
	}
}
vector get_DP(int _I[4])
{
	int I[4]={_I[0],_I[1],_I[2],_I[3]};
	vector &ans=DP[I[0]][I[1]][I[2]][I[3]];
	if(ans.size())return ans;
	if(I[0]==N&&I[1]==N&&I[2]==N&&I[3]==N)
	{
		ans.push_back(0);
		return ans;
	}
	for(int d=0;d<4;d++)
	{
		if(I[d]+1>N)continue;
		I[d]++;
		vector _v=get_DP(new int[4]{I[0],I[1],I[2],I[3]});
		vector v;
		for(int i=0;i<_v.size();i++)v.push_back(_v[i]);
		I[d]--;
		if(v[0]==1)continue;
		v.push_back(PILE[d][I[d]+1]);
		if(v.size()-1>5)continue;
		removeback(v);
		if(!ans.size()||v.size()<ans.size())ans=v;
	}
	if(!ans.size())ans.push_back(1);
	//printf("%d %d %d %d is %d\n",I[0],I[1],I[2],I[3],ans.size());
	return ans;
}
void getmax(int &a,int b){if(b>a)a=b;}
int main()
{
	//freopen("in.txt","r",stdin);
	/*for(int i1=0;i1<=41;i1++)
		for(int i2=0;i2<=41;i2++)
			for(int i3=0;i3<=41;i3++)
				for(int i4=0;i4<=41;i4++)
				{
					DP[i1][i2][i3][i4].reserve(5);
				}*/
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=1;i<=N;i++)
		{
			for(int j=0;j<4;j++)
			{
				scanf("%d",&PILE[j][i]);
			}
		}
		for(int i1=0;i1<=N;i1++)
			for(int i2=0;i2<=N;i2++)
				for(int i3=0;i3<=N;i3++)
					for(int i4=0;i4<=N;i4++)
					{
						DP[i1][i2][i3][i4].clear();
					}
		int ans=0;
		for(int i1=0;i1<=N;i1++)
			for(int i2=0;i2<=N;i2++)
				for(int i3=0;i3<=N;i3++)
					for(int i4=0;i4<=N;i4++)
					{
						vector v=get_DP(new int[4]{i1,i2,i3,i4});
						if(v[0]==1)continue;
						int tmp=4*N-i1-i2-i3-i4-(v.size()-1);
						if(tmp%2==1)termin();
						getmax(ans,tmp/2);
					}
		printf("%d\n",ans);//break;
	}
	return 0;
}
