#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct dat_edge
{
	int aim,last,cost,site,dire;	
}edge[100001];

int f[50001],ans[50001],coun_ans,coun0[50001],coun1[50001],pl[50001],len_edge,n,m;
bool bi[50001];

void insert_edge(int x,int y,int s,int w,int p)
{
	len_edge++;
	edge[len_edge].aim=y;
	edge[len_edge].cost=s;
	edge[len_edge].site=w;
	edge[len_edge].dire=p;
	edge[len_edge].last=pl[x];
	pl[x]=len_edge;
}

void solve()
{
	static int o,w,que[50001],p,s,poi;
	o=1;w=0;que[1]=1;
	memset(f,0,sizeof(f));
	memset(bi,false,sizeof(bi));
	while(w<o)
	{
		w++;
		p=pl[que[w]];
		while(p!=-1)
		{
			if(edge[p].dire!=1)
			{
				p=edge[p].last;
				continue;
			}
			poi=edge[p].aim;
			if(f[que[w]]+edge[p].cost>f[poi])
				f[poi]=f[que[w]]+edge[p].cost;
			coun1[poi]--;
			if(coun1[poi]==0)
				que[++o]=poi;
			p=edge[p].last;
		}
		p=pl[que[w]];
		while(p!=-1)
		{
			if(edge[p].dire!=0)
			{
				p=edge[p].last;
				continue;
			}
			if(bi[edge[p].aim]==true)
			{
				bi[que[w]]=true;
				break;
			}
			s=f[edge[p].aim]+edge[p].cost;
			if(s==f[que[w]])
			{
				p=edge[p].last;
				continue;
			}
			bi[que[w]]=true;
			break;
		}
	}
}

bool re_solve()
{
	static int o,w,que[50001],p,s,poi,i,toll[50001];
	for(i=1;i<=n;i++)
		toll[i]=-1;
	o=1;w=0;que[1]=n;
	while(w<o)
	{
		w++;
		if(toll[que[w]]<0)
			toll[que[w]]=0;
		p=pl[que[w]];
		while(p!=-1)
		{
			if(edge[p].dire==1)
			{
				p=edge[p].last;
				continue;
			}
			poi=edge[p].aim;
			coun0[poi]--;
			if(coun0[poi]==0)
				que[++o]=poi;
			s=f[que[w]]-f[poi]-edge[p].cost+toll[que[w]];
			if(bi[poi]==false)
			{
				ans[edge[p].site]+=s;
			}
			else
			{
				if(toll[poi]!=-1&&toll[poi]!=s)
					return false;
				toll[poi]=s;
			}
			p=edge[p].last;
		}
	}
	return true;
}

int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("new.txt","w",stdout);
	int t=0,i,a,b,c;
	bool ok;
	while(scanf("%d%d",&n,&m)&&n+m!=0)
	{
		t++;
		memset(coun1,0,sizeof(coun1));
		memset(coun0,0,sizeof(coun0));
		len_edge=-1;
		for(i=1;i<=n;i++)
			pl[i]=-1;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			coun1[b]++;
			coun0[a]++;
			insert_edge(a,b,c,i,1);
			insert_edge(b,a,c,i,0);
		}
		coun_ans=0;
		memset(ans,0,sizeof(ans));
		memset(bi,false,sizeof(bi));
		solve();
		ok=re_solve();
		if(!ok)
			printf("Case %d: No solution\n",t);
		else
		{
			for(i=1;i<=m;i++)
				if(ans[i]!=0)
					coun_ans++;
			printf("Case %d: %d %d\n",t,coun_ans,f[n]);
			for(i=1;i<=m;i++)
				if(ans[i]!=0)
					printf("%d %d\n",i,ans[i]);
		}
	}
	return 0;
}
