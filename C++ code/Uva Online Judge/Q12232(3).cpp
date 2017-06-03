#include<cstdio>
#include<cstdlib>
#define debug(...) ;//__VA_ARGS__
int n,Q;
struct pairtype{int head,v;};
pairtype S[20001];
bool conflicting;
bool isnum(char a){return a>='0'&&a<='9';}
bool inthree(char *d,int &a,int &b,int &c)
{
	a=b=c=0;
	while(!isnum(*d))d++;
	while(isnum(*d)){a*=10;a+=(*d)-'0';d++;}
	//debug(printf("a=%d\n",a););
	while(!isnum(*d))d++;
	while(isnum(*d)){b*=10;b+=(*d)-'0';d++;}
	//debug(printf("b=%d\n",b););
	while(!isnum(*d)&&(*d))d++;
	if(!(*d))return false;
	while(isnum(*d)){c*=10;c+=(*d)-'0';d++;}
	//debug(printf("c=%d\n",c););
	return true;
}
pairtype findset(int a)
{
	if(S[a].head==a)return S[a];
	if(S[a].head==0)return (pairtype){-a,0};
	pairtype b=findset(S[a].head);
	if(b.head>0)
	{
		S[a].head=a;
		S[a].v^=b.v;
		return S[a];
	}
	else
	{
		S[a].head=-b.head;
		b.v^=S[a].v;
		S[a].v=b.v;
		return b;
	}
}
void give(int v)
{
	if(conflicting)return;
	if(v==-1)printf("I don't know.\n");
	else printf("%d\n",v);
}
void setvalue(int a,int v)
{
	if(S[a].head==a||S[a].head==0)
	{
		S[a].head=a;
		S[a].v=v;
		return;
	}
	setvalue(S[a].head,v^S[a].v);
	S[a].head=a;
	S[a].v=v;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d%d",&n,&Q)==2&&(n||Q))
	{
		printf("Case %d:\n",kase++);
		conflicting=false;
		for(int i=1;i<=n;i++)S[i].head=S[i].v=0;
		char tstr[1000];do{scanf("%c",&tstr[0]);}while(tstr[0]!='\n');
		int qn=0;
		while(Q--)
		{
			int sl=-1;
			while(scanf("%c",&tstr[++sl])==1&&tstr[sl]!='\n');tstr[sl]=0;
			if(conflicting)continue;
			int ni=0;while(tstr[ni]==' ')ni++;
			if(tstr[ni++]=='I')
			{
				qn++;
				int p,q,v;
				if(inthree(&tstr[ni],p,q,v))
				{
					p++,q++;
					pairtype j=findset(p),j2=findset(q);
					if(j.head==j2.head||(j.head==p&&j2.head==q))
					{
						if((j2.v^j.v)!=v)
						{
							printf("The first %d facts are conflicting.\n",qn);
							conflicting=true;
						}
					}
					else if(j.head>0)
					{
						setvalue(q,v^j.v);
					}
					else if(j2.head>0)
					{
						setvalue(p,v^j2.v);
					}
					else
					{
						S[-j.head].head=-j2.head;
						S[-j.head].v=v^j.v^j2.v;
					}
				}
				else
				{
					p++;
					pairtype j=findset(p);
					if(j.head>0)
					{
						if(j.v!=q)
						{
							printf("The first %d facts are conflicting.\n",qn);
							conflicting=true;
						}
					}
					else
					{
						j.head*=-1;
						S[j.head].head=j.head;
						S[j.head].v=q^j.v;
					}
				}
			}
			else
			{
				while(!isnum(tstr[ni]))ni++;
				int k;sscanf(&tstr[ni],"%d",&k);
				while(isnum(tstr[ni]))ni++;
				if(k==1)
				{
					sscanf(&tstr[ni],"%d",&k);k++;
					pairtype p=findset(k);
					if(p.head>0)give(p.v);
					else give(-1);
				}
				else
				{
					int hn=0,ans=0,cnt=0;
					bool ok=true;
					for(int i=0,j;i<k;i++)
					{
						sscanf(&tstr[ni],"%d",&j);
						while(!isnum(tstr[ni]))ni++;
						while(isnum(tstr[ni]))ni++;
						j++;
						pairtype p=findset(j);
						if(hn&&p.head<0&&hn!=p.head)ok=false;
						if(p.head<0)hn=p.head,cnt++;
						ans^=p.v;
					}
					give(ok&&cnt%2==0?ans:-1);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
