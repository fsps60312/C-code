#include<cstdio>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
const double EPS=1e-9;
char LINE[1000000];
int contain(int l,int r,char c1,char c2)
{
    int cnt=0;
    while(l<=r)
    {
        if(LINE[l]=='(')cnt++;
        else if(LINE[l]==')')cnt--;
        if(cnt)continue;
        if(LINE[l]==c1||LINE[l]==c2)return l;
        l++;
    }
    return -1;
}
struct Node
{
    char ope;
    double v;
    Node *lch,*rch;
    Node():ope(1){}
    void readv(int l,int r)
    {
        ope=0;
        v=0.0;
        while(l<=r)
        {
            if(LINE[l]=='.')
            {
                double now=1.0;
                l++;
                while(l<=r)
                {
                    now*=0.1;
                    v+=now*(LINE[l]-'0');
                    l++;
                }
                break;
            }
            v=v*10.0+(LINE[l]-'0');
            l++;
        }
    }
    Node(int l,int r):lch(NULL),rch(NULL)
    {
        while(LINE[l]=='('&&LINE[r]==')')l++,r--;
        int result;
        if((result=contain(l,r,'+','-'))!=-1||(result=contain(l,r,'*','/'))!=-1)
        {
            ope=LINE[result];
            int tl=l,tr=result-1;
            lch=new Node(tl,tr);
            tl=result+1,tr=r;
            rch=new Node(tl,tr);
        }
        else if(l==r&&LINE[l]=='x')ope='x';
        else readv(l,r);
    }
    double GetValue(double x)
    {
        if(ope=='x')return x;
        else if(!ope)return v;
        double v1=lch->GetValue(x);
        double v2=rch->GetValue(x);
        switch(ope)
        {
            case'+':return v1+v2;
            case'-':return v1-v2;
            case'*':return v1*v2;
            case'/':return v1/v2;
            default:termin("invalid ope: ",ope);
        }
    }
}E1,E2;
double H,B,W,WP;
double abs(double a){return a>=0.0?a:-a;}
double FB(double x){double v=E1.GetValue(x)+E2.GetValue(x);return v*v;}
double getB(double l,double r){return (r-l)/6.0*(FB(l)+FB(r)+4.0*FB(0.5*(l+r)));}
double inteB(double l,double r)
{
    double s0=getB(l,r);
    double mid=0.5*(l+r),s1=getB(l,mid)+getB(mid,r);
    if(abs(s0-s1)<EPS)return s1;
    return inteB(l,mid)+inteB(mid,r);
}
double FH(double x){double v1=E1.GetValue(x),v2=E2.GetValue(x);v2+=v1;return v2*v2-v1*v1;}
double getH(double l,double r){return (r-l)/6.0*(FH(l)+FH(r)+4.0*FH(0.5*(l+r)));}
double inteH(double l,double r)
{
    double s0=getH(l,r);
    double mid=0.5*(l+r),s1=getH(l,mid)+getH(mid,r);
    if(abs(s0-s1)<EPS)return s1;
    return inteH(l,mid)+inteH(mid,r);
}
double getW(double h)
{
    if(h<=B)return inteB(0.0,h);
    return inteB(0.0,B)+inteH(B,h);
}
void getWP()
{
    double l=0.0,r=H,mid;
    while(r-l>EPS)
    {
        mid=0.5*(l+r);
        if(getW(mid)>0.5*W)r=mid;
        else l=mid;
    }
    WP=l;
}
double F1(double x){double v=E1.GetValue(x);return v*v;}
double get1(double l,double r){return (r-l)/6.0*(F1(l)+F1(r)+F1(0.5*(l+r)));}
double init1(double l,double r)
{
    double s0=get1(l,r);
    double mid=0.5*(l+r),s1=get1(l,mid)+get1(mid,r);
    if(abs(s0-s1)<EPS)return s1;
    return init1(l,mid)+init1(mid,r);
}
int main()
{
    freopen("in.txt","r",stdin);
    while(scanf("%lf%lf",&H,&B)==2&&!(H==0.0&&B==0.0))
    {
        scanf("%s",LINE);
        int l=0,r=-1;while(LINE[++r]);
        E1=Node(l,r);
        scanf("%s",LINE);
        l=0,r=-1;while(LINE[++r]);
        E2=Node(l,r);
        W=getW(H);
        getWP();
        printf("%.3lf %.3lf\n",W,WP);
        //double v;while(scanf("%lf",&v)==1)printf("value1=%.3f,value2=%.3f\n",E1.GetValue(v),E2.GetValue(v));

    }
    return 0;
}
