#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
#include<algorithm>
using namespace std;
bool getmax(int &a,const int b){if(b>a){a=b;return true;}return false;}
bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
const int INF=2147483647;
void BuildSa(const char *str,const int n,int *sa)
{
	assert(n<=100002);
	static int membase[3][100002];
	int *x=membase[0],*y=membase[1],*c=membase[2];
	int p=256;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=(int)str[i]+128]++,assert(x[i]>=0&&x[i]<p);
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<=n;move<<=1)
	{
		int idx=0;
		for(int i=n-move;i<n;i++)y[idx++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[idx++]=sa[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0;
		x[sa[0]]=p++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]])x[sa[i]]=p++;
			else if((sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=p++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?p-1:p++);
		}
		if(p==n)break;
	}
}
void BuildHeight(const char *str,const int n,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)ans--;
		if(rank[i]==0){height[0]=0;continue;}
		int j=sa[rank[i]-1];
		while(str[i+ans]==str[j+ans])ans++;
		height[rank[i]]=ans;
	}
}
struct Seg
{
	int s[200000];
	void Build(const int id,const int l,const int r)
	{
		assert(id<200000);
		s[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	bool Add(const int id,const int l,const int r,const int bl,const int br)
	{
		if(s[id]==r-l+1)return false;
		if(r<bl||br<l)return false;
		if(bl<=l&&r<=br){s[id]=r-l+1;return true;}
		const int mid=(l+r)/2;
		bool ans=(Add(id*2,l,mid,bl,br)|Add(id*2+1,mid+1,r,bl,br));
		s[id]=s[id*2]+s[id*2+1];
		return ans;
	}
	void Print(const int id,const int l,const int r)
	{
		if(s[id]==r-l+1)
		{
			for(int i=l;i<=r;i++)putchar('1');
			return;
		}
		if(l==r){putchar('0');return;}
		const int mid=(l+r)/2;
		Print(id*2,l,mid),Print(id*2+1,mid+1,r);
	}
}SEG;
bool Check(char *a,const char *b)
{
	int n=-1;
	bool ans=true;
	while(a[++n])
	{
		if(a[n]=='\n'){a[n]='\0';break;}
		assert(a[n]!=(char)1);
		ans&=(a[n]==b[n]);
	}
	ans&=(a[n]==b[n]);
	return ans;
}
void Insert(vector<char>&str,const char *tmp){for(int i=0;tmp[i];i++)str.push_back(tmp[i]);str.push_back('\n');}
int N,K,MID;
int SA[100002],RANK[100002],HEIGHT[100002],MATCH[100002],ID[100002];
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(;;)
	{
		static char tmp[50002];
		assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&K)==1);
		if(K==0)break;
		assert(fgets(tmp,INF,stdin)&&Check(tmp,"BEGIN TDP CODEBASE"));
		vector<char>str;
		for(;;)
		{
			assert(fgets(tmp,INF,stdin));
			if(Check(tmp,"END TDP CODEBASE"))break;
			Insert(str,tmp);
		}
		MID=str.size();
		str.push_back((char)1);
		assert(fgets(tmp,INF,stdin)&&Check(tmp,"BEGIN JCN CODEBASE"));
		for(;;)
		{
			assert(fgets(tmp,INF,stdin));
			if(Check(tmp,"END JCN CODEBASE"))break;
			Insert(str,tmp);
		}
		str.push_back('\0');
		N=str.size();
		assert(N<=100002);
		BuildSa(&str[0],N,SA);
		BuildHeight(&str[0],N,SA,RANK,HEIGHT);
		for(int i=0;i<N;i++)MATCH[i]=0;
		for(int i=1,now=0,id=-1;i<N;i++)
		{
			if(SA[i]>MID)
			{
				if(SA[i-1]<=MID)now=HEIGHT[i],id=SA[i-1];
				else getmin(now,HEIGHT[i]);
				if(getmax(MATCH[SA[i]],now))ID[SA[i]-MID-1]=id;
			}
		}
		for(int i=N-2,now=0,id=-1;i>=0;i--)
		{
			if(SA[i]>MID)
			{
				if(SA[i+1]<=MID)now=HEIGHT[i+1],id=SA[i+1];
				else getmin(now,HEIGHT[i+1]);
				if(getmax(MATCH[SA[i]],now))ID[SA[i]-MID-1]=id;
			}
		}
		map<int,vector<int>,greater<int> >ans;
		for(int i=MID+1;i<N;i++)if(MATCH[i])ans[MATCH[i]].push_back(i-MID-1);
		static int kase=0;
		if(kase++)puts("");
		printf("CASE %d\n",kase);
		SEG.Build(1,0,N-MID-2);
		int cnt=0;
		for(const auto &it:ans)
		{
			if(cnt==K)break;
			for(const auto i:it.second)
			{
				if(cnt==K)break;
				if(!SEG.Add(1,0,N-MID-2,i,i+it.first-1))continue;
				SEG.Print(1,0,N-MID-2);puts("");
				printf("INFRINGING SEGMENT %d LENGTH %d POSITION %d\n",++cnt,it.first,i);
				for(int j=0;j<it.first;j++)putchar(str[MID+1+i+j]),assert(ID[i]+j<MID&&str[ID[i]+j]==str[MID+1+i+j]);
				putchar('\n');
			}
		}
//		printf("(%d,%d)\n",30,10+MID+1);
//		for(int i=RANK[30]-10;i<=RANK[30]+10;i++)
//		{
//			printf("(rank=%d,idx=%3d,h=%d): ",i,SA[i],HEIGHT[i]);
//			for(int j=0;j<10&&SA[i]+j<N;j++)putchar(str[SA[i]+j]);puts("");
//		}
	}
	return 0;
}
