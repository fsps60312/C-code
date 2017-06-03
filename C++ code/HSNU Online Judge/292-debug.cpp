#include<stdio.h>
#include<algorithm>
using namespace std ;
 
typedef long long int LL ;
LL gcd(LL a ,LL b){
    if (b==0)return a ;
    return gcd(b,a%b) ;
}
 
const int maxN=1000000000 ;
int inR ,inC ;
//1D struct -----------------
struct segD{
    int l ,r ; LL G ;
    segD *lc ,*rc ;
    segD (int l=0 ,int r=0 ):l(l),r(r),lc(NULL),rc(NULL) {}
};
void updateD(segD* &o ,int x ,LL val ,int L=1 ,int R=inC ){
    if (o==NULL){
        o=new segD(x,x) ;
        o->G=val ;
        return ;
    }
    if (x<o->l || o->r<x){
        int low=min(x,o->l) ,high=max(x,o->r) ;
        while (1){
            int mid=(L+R)>>1 ;
            if (mid<low)L=mid+1 ;
            else if (high<=mid)R=mid ;
            else break ;
        }
        segD* I=new segD(L,R) ;
        if (o->r<=(L+R)>>1)I->lc=o ;
        else I->rc=o ;
        o=I ;
    }
    int mid=(o->l+o->r)>>1 ;
    if (x<=mid){
        updateD(o->lc,x,val,o->l,mid) ;
        o->G=o->lc->G ;
        if (o->rc)o->G=gcd(o->G,o->rc->G) ;
    }
    else {
        updateD(o->rc,x,val,mid+1,o->r) ;
        o->G=o->rc->G ;
        if (o->lc)o->G=gcd(o->G,o->lc->G) ;
    }
}
LL queryD(segD* &o ,int l ,int r ){
    if (o==NULL || o->r<l || r<o->l)return 0 ;
    if (l<=o->l && o->r <=r )return o->G ;
    else {
        int mid=(o->l+o->r)>>1 ;
        LL qL=queryD(o->lc,l,r) ,qR=queryD(o->rc,l,r) ;
        if (qL&&qR)return gcd(qL,qR) ;
        else if (qL)return qL ;
        else if (qR)return qR ;
        else return 0 ;
    }
}
struct segDD{
    segD *S ;
    segDD *lc ,*rc ;
    segDD():S(NULL),lc(NULL),rc(NULL) {}
};
LL updateDD(segDD* &o ,int qR ,int qC ,LL val ,int L=1 ,int R=inR ){
    if (o==NULL)o=new segDD() ;
    if (L==R){
        updateD(o->S,qC ,val) ;
        return val ;
    }
    else {
        int mid=(L+R)>>1 ;
        if (qR<=mid){
            LL uL=updateDD(o->lc,qR,qC,val,L,mid) ;
            LL uR=0 ; if (o->rc)uR=queryD(o->rc->S,qC,qC) ;
            LL uP=uL ; if (uR!=0)uP=gcd(uL,uR) ;
            updateD(o->S,qC,uP) ;
            return uP ;
        }
        else {
            LL uL=0 ; if (o->lc)uL=queryD(o->lc->S,qC,qC) ;
            LL uR=updateDD(o->rc,qR,qC,val,mid+1,R) ;
            LL uP=uR ; if (uL!=0)uP=gcd(uL,uR) ;
            updateD(o->S,qC,uP) ;
            return uP ;
        }
    }
}
LL queryDD(segDD* &o ,int P ,int Q ,int U ,int V ,int L=1 ,int R=inR ){
    if (o==NULL)return 0 ;
    if (P<=L && R<=U )return queryD(o->S,Q,V) ;
    else {
        int mid=(L+R)>>1 ;
        if (mid<P){
            if (o->rc==NULL)return 0 ;
            return queryDD(o->rc,P,Q,U,V,mid+1,R) ;
        }
        else if (mid>=U){
            if (o->lc==NULL)return 0 ;
            return queryDD(o->lc,P,Q,U,V,L,mid) ;
        }
        else {
            if (o->lc && o->rc ){
                return gcd(queryDD(o->lc,P,Q,U,V,L,mid),queryDD(o->rc,P,Q,U,V,mid+1,R)) ;
            }
            else if (o->lc){
                return queryDD(o->lc,P,Q,U,V,L,mid) ;
            }
            else if (o->rc){
                return queryDD(o->rc,P,Q,U,V,mid+1,R) ;
            }
            else {
                return 0 ;
            }
        }
    }
}
 
segDD *SEG=NULL ;
 
int main(){
	freopen("IN.txt","r",stdin);
	freopen("NEW.txt","w",stdout);
    int N ;
    while(scanf("%d%d%d",&inR ,&inC ,&N )==3)
    {
    	SEG=NULL;
	    for (int i=0 ,order ;i<N ;i++ ){
	        scanf("%d",&order) ;
	        if (order==1){
	            int P ,Q ; LL K ;
	            scanf("%d%d%lld",&P ,&Q ,&K ) ; ++P ,++Q ;
	            updateDD(SEG,P,Q,K) ;
	        }
	        else {
	            int P ,Q ,U ,V ;
	            scanf("%d%d%d%d",&P ,&Q ,&U ,&V ) ; ++P ,++Q ,++U ,++V ;
	            printf("%lld\n",queryDD(SEG,min(P,U),min(Q,V),max(P,U),max(Q,V))) ;
	        }
	    }
	}
}
