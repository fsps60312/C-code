#include<cstdio>
#include<cstdlib>
#include<vector>
#include<map>
//#include<set>
using namespace std;
struct twolonglong
{
    long long x;
    long long y;
    bool operator()(struct twolonglong a,struct twolonglong b)
    {
        if(a.x!=b.x) return a.x<b.x;
        return a.y<b.y;
    }
};
struct inputtype
{
    int x;
    int y;
    bool operator()(inputtype a,inputtype b)
    {
        if(a.x!=b.x) return a.x<b.x;
        return a.y<b.y;
    }
};
struct pairtype
{
    vector<int> to;
    vector<int> from;
    bool loop;
    twolonglong ups;
    bool vis;
    double ans;
    int index;
};
struct matrixtype
{
    double p[100][100];//x, y
    int x;
    int y;
    void exchange(int a,int b)
    {
    	double c;
    	for(int i=0;i<y;i++)
    	{
    		c=p[a][i];
    		p[a][i]=p[b][i];
    		p[b][i]=c;
		}
	}
    void addto(int a,int b,double c)
    {
    	for(int i=0;i<y;i++)
    	{
    		p[b][i]+=p[a][i]*c;
		}
	}
};
int n;
vector<int> vist[100];
pairtype S[100];
map<twolonglong,int,twolonglong> vism;
void termin()
{
    int a=2000000000;
    int b[a][a][a][a][a][a][a][a][a][a][a][a][a];
    b[a][a][a][a][a][a][a][a][a][a][a][a][a]++;
    //for(int k=0;;k--) i[k]++;
}
void dfsloopdown(int a,long long b,long long c)
{
    if(a<50) b|=(((long long)1)<<a);
    else c|=(((long long)1)<<(a-50));
    if(b==S[a].ups.x&&c==S[a].ups.y) return;
    b|=S[a].ups.x;
    c|=S[a].ups.y;
    S[a].ups.x=b;
    S[a].ups.y=c;
    for(int i=0;i<S[a].from.size();i++)
    {
        int j=S[a].from[i];
        dfsloopdown(j,b,c);
    }
}
void dfsvis(int a)
{
    if(S[a].vis) return;
    S[a].vis=true;
    for(int i=0;i<S[a].to.size();i++)
    {
        int j=S[a].to[i];
        dfsvis(j);
    }
}
double absf(double a)
{
    return a>=0?a:-a;
}
matrixtype inverse(matrixtype a)
{
	if(a.x!=a.y) termin();
	int c=a.x;
	matrixtype b;
	b.x=b.y=c;
	for(int i=0;i<c;i++)
	{
		for(int j=0;j<c;j++)
		{
			b.p[i][j]=i==j?1:0;
		}
	}
	for(int i=0;i<c;i++)
	{
	    int Max=i;
        for(int j=i+1;j<c;j++)
        {
            if(absf(a.p[j][i])>absf(a.p[Max][i])) Max=j;
        }
        a.exchange(i,Max);
        b.exchange(i,Max);
		if(a.p[i][i]==0) termin();
		double j;
		for(int k=i+1;k<c;k++)
		{
			j=-a.p[k][i]/a.p[i][i];
			a.addto(i,k,j);
			b.addto(i,k,j);
		}
	}
	//a become up-triangle matrix
	for(int i=c-1;i>=0;i--)
	{
		double k;
		if(a.p[i][i]==0) termin();
		for(int j=i-1;j>=0;j--)
		{
			k=-a.p[j][i]/a.p[i][i];
			a.addto(i,j,k);
			b.addto(i,j,k);
		}
	}
	for(int i=0;i<c;i++)
	{
	    if(a.p[i][i]==0) termin();
		for(int j=0;j<c;j++)
		{
			b.p[i][j]/=a.p[i][i];
		}
	}
	return b;
}
matrixtype mul(matrixtype a,matrixtype b)
{
	if(a.y!=b.x) termin();
	matrixtype c;
	c.x=a.x;
	c.y=b.y;
	for(int i=0;i<c.x;i++)
	{
		for(int j=0;j<c.y;j++)
		{
			c.p[i][j]=0;
			for(int k=0;k<a.y;k++)
			{
				c.p[i][j]+=a.p[i][k]*b.p[k][j];
			}
		}
	}
	return c;
}
int main()
{
	int T=1;
	freopen("in.txt","r",stdin);
	//termin();
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=0;i<n;i++)
        {
            S[i].to.clear();
            S[i].from.clear();
            S[i].loop=false;
            S[i].vis=false;
            S[i].ups.x=0;
            S[i].ups.y=0;
            vist[i].clear();
        }
        for(int i,j;scanf("%d%d",&i,&j)==2;)
        {
            if(i==0) break;
            S[--i].to.push_back(--j);
            S[j].from.push_back(i);
        }
		for(int i=0;i<n;i++)
		{
		    dfsloopdown(i,0,0);
		}
		vism.clear();
        for(int i=0;i<n;i++)
        {
            if(vism.find(S[i].ups)==vism.end())
            {
                vism[S[i].ups]=vism.size()-1;
            }
            vist[vism[S[i].ups]].push_back(i);
        }
        int vismsize=vism.size();
        for(int i=0;i<vismsize;i++)
        {
            if(S[vist[i][0]].to.size()==0) continue;
            twolonglong k=S[vist[i][0]].ups;
            for(int j=0;j<vist[i].size();j++)
            {
                int l=vist[i][j];
                if(l<50) k.x-=(((long long)1)<<l);
                else k.y-=(((long long)1)<<(l-50));
            }
            if(k.x==0&&k.y==0)
            {
                for(int j=0;j<vist[i].size();j++)
                {
                    int l=vist[i][j];
                    S[l].loop=true;
                }
            }
        }
        dfsvis(0);
        vector<pairtype> v;
        for(int i=0;i<n;i++)
        {
        	if(S[i].vis&&!S[i].loop)
        	{
        		S[i].index=i;
        		v.push_back(S[i]);
			}
		}
        matrixtype trans;
        trans.x=trans.y=v.size();
        for(int i=0;i<v.size();i++)
        {
            for(int j=0;j<v.size();j++)
            {
                trans.p[i][j]=0;
            }
        }
        for(int i=0;i<v.size();i++)//S to trans
        {
            //i to S[i].to[j]
            int l=v[i].to.size();
            for(int j=0;j<l;j++)
            {
                int k=v[i].to[j];
                trans.p[k][i]+=(double)1/(double)l;//from i to k
            }
        }
        if(v.size()>0)
        {
            matrixtype origin;
            origin.x=v.size();
            origin.y=1;
            for(int i=0;i<v.size();i++)
            {
                origin.p[i][0]=0;
            }
            origin.p[0][0]=1;
            //S=o+A*o+A^2*o+...
            //AS= A*o+A^2*o+...
            //(I-A)S=o
            //S=(I-A)^-1 * o
            for(int i=0;i<v.size();i++)
            {
                for(int j=0;j<v.size();j++)
                {
                    trans.p[i][j]*=-1;
                    if(i==j) trans.p[i][j]+=1;
                }
            }
            //printf("6pass\n");
            //trans now become I-A
            trans=inverse(trans);
            //printf("7pass\n");
            //trans is (I-A)^-1
            trans=mul(trans,origin);
            //printf("8pass\n");
            //trans is S
            for(int i=0;i<v.size();i++)
            {
                S[v[i].index].ans=trans.p[i][0];
            }
        }
		int q;
		scanf("%d",&q);
		printf("Case #%d:\n",T++);
		//for(int i=0;i<n;i++) printf(" %d",S[i].vis);printf("\n");
		while(q--)
		{
			int A;
			scanf("%d",&A);
			A--;
			if(!S[A].vis) printf("0.000\n");
			else if(S[A].loop) printf("infinity\n");
			else printf("%.3lf\n",S[A].ans);
		}
    }
    return 0;
}
