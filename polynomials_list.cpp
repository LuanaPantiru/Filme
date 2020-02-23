#include <iostream>
using namespace std;
class Pereche
{
    double coef;
    int expo;
    Pereche *urm;
public:
    double getc();
    int gete();
    Pereche *getu();
    void setc(double c);
    void sete(int e);
    void setu(Pereche *u);
    Pereche();
    Pereche(double coef,int expo,Pereche *urm);
   friend istream  &operator >> (istream &i,Pereche &p);
   friend ostream &operator << (ostream &o,Pereche &p);
   friend class Polinom;
};
double Pereche::getc()
{
    return coef;
}
int Pereche::gete()
{
    return expo;
}
Pereche* Pereche::getu()
{
    return urm;
}
void Pereche::setc(double c)
{
    coef=c;
}
void Pereche::sete(int e)
{
    expo=e;
}
void Pereche::setu(Pereche *u)
{
    urm=u;
}
Pereche::Pereche()
{
    this->urm=0;
}
Pereche::Pereche(double coef,int expo,Pereche *urm)
{
    this->coef=coef;
    this->expo=expo;
    this->urm=urm;

}
istream &operator>>(istream &i,Pereche &p)
 {
     i>>p.expo>>p.coef;
     return i;
 }
ostream &operator << (ostream &o,Pereche &p)
 {
     if(p.expo==0) o<<p.coef;
     else o<<p.coef<<"*x^"<<p.expo;
     return o;
 }
class Polinom
{
protected:
    Pereche *first;
    Pereche *last;
public:
    Pereche *getf();
    Pereche *getl();
    Polinom();
    void add_first(Pereche x);
    void add_last(Pereche x);
    void add(Pereche x);
    double val(double x);
    Polinom operator +(Polinom P1);
    Polinom operator -(Polinom P1);
    Polinom produs(Polinom P1,Polinom P2);
    Polinom operator *(Polinom P1);
    friend istream  &operator >> (istream &i,Polinom &P);
   friend ostream &operator << (ostream &o,Polinom &P);
    //void afisare();
};
Pereche* Polinom::getf()
{
    return first;
}
Pereche* Polinom::getl()
{
    return last;
}
Polinom::Polinom()
{
    first=last=0;
}
void Polinom::add_first(Pereche x)
{
    Pereche *p;
    p=new Pereche(x.getc(),x.gete(),0);
    p->urm=first;
    first=p;
}
void Polinom::add_last(Pereche x)
{
    Pereche *p;
    p=new Pereche(x.getc(),x.gete(),0);
    last->urm=p;
    last=p;
}
void Polinom::add(Pereche x)
{
    Pereche *p;
    p=new Pereche(x.getc(),x.gete(),0);
    if(first==NULL) first=last=p;
    else
    {
        Pereche *aux=first;
        while(x.gete()>aux->expo && aux->urm!=0)
            aux=aux->urm;
         if(aux==first && x.gete()<aux->expo)
                add_first(x);
            else if (aux==first && x.gete()>aux->expo)
                add_last(x);
             else if(aux==last && x.gete()>aux->expo)
                add_last(x);
            else
            {
                p->urm=aux->urm;
                aux->urm=p;
            }
    }
}
double Polinom::val(double x)
{
    double s=0,p=1;
    Pereche *aux=first;
    while(aux!=0)
    {
        for(int i=1;i<=aux->expo;i++)
        p=p*x;
        s=s+aux->coef*p;
        aux=aux->urm;
    }
    return s;
}
Polinom Polinom::operator +(Polinom P1)
{
    Polinom F;
    Pereche *aux=this->first;
    Pereche x;
    while(P1.first!=0 && aux!=0)
    {
       if(P1.first->expo==aux->expo)
       {
           x.setc(P1.first->coef+aux->coef);
           x.sete(P1.first->expo);
           F.add(x);
           P1.first=P1.first->urm;
           aux=aux->urm;
       }
       else if(P1.first->expo<aux->expo)
       {
           x.setc(P1.first->coef);
           x.sete(P1.first->expo);
           F.add(x);
           P1.first=P1.first->urm;
       }
       else
       {
           x.setc(aux->coef);
           x.sete(aux->expo);
           F.add(x);
           aux=aux->urm;
       }
    }
    while(P1.first!=0)
    {
        x.setc(P1.first->coef);
           x.sete(P1.first->expo);
           F.add(x);
           P1.first=P1.first->urm;
    }
    while(aux!=0)
    {
        x.setc(aux->coef);
           x.sete(aux->expo);
           F.add(x);
           aux=aux->urm;
    }
    return F;
}
Polinom Polinom::operator -(Polinom P1)
{
    Polinom F;
    Pereche *aux=this->first;
    Pereche x;
    while(P1.first!=0 && aux!=0)
    {
       if(P1.first->expo==aux->expo)
       {
           x.setc(aux->coef-P1.first->coef);
           x.sete(P1.first->expo);
           F.add(x);
           P1.first=P1.first->urm;
           aux=aux->urm;
       }
       else if(P1.first->expo<aux->expo)
       {
           x.setc(0-P1.first->coef);
           x.sete(P1.first->expo);
           F.add(x);
           P1.first=P1.first->urm;
       }
       else
       {
           x.setc(aux->coef);
           x.sete(aux->expo);
           F.add(x);
           aux=aux->urm;
       }
    }
    while(P1.first!=0)
    {
        x.setc(0-P1.first->coef);
           x.sete(P1.first->expo);
           F.add(x);
           P1.first=P1.first->urm;
    }
    while(aux!=0)
    {
        x.setc(aux->coef);
           x.sete(aux->expo);
           F.add(x);
           aux=aux->urm;
    }
    return F;
}
Polinom Polinom::produs(Polinom P1,Polinom P2)
{
    Polinom F;
    Pereche x;
    while(P1.first!=0)
    {
        x.setc(P1.first->coef*P2.first->coef);
        x.sete(P1.first->expo+P2.first->expo);
        F.add(x);
        P1.first=P1.first->urm;
    }
    return F;
}
Polinom Polinom::operator *(Polinom P1)
{
    Polinom A,B;
    A=A.produs((*this),P1);
    P1.first=P1.first->urm;
    while(P1.first!=0)
    {
        B=B.produs((*this),P1);
        A=A+B;
        P1.first=P1.first->urm;
    }
     return A;
}
istream  &operator >> (istream &i,Polinom &P)
{
    int n;
    Pereche x;
    cout<<"Numarul de monoame: ";
    cin>>n;
    cout<<"Citim EXPONENT COEFICIENT";
    for(int j=0;j<n;j++)
        {
            i>>x;
            P.add(x);
        }

 return i;
}
ostream &operator << (ostream &o,Polinom &P)
{
    Pereche *z=P.getf();
    while(z!=0)
    {
        o<<*z;
        z=z->getu();
        if(z!=0 && z->getc()>0) cout<<"+";
    }
    return o;
}
int main()
{
    Polinom P,F1,Q,F2,F3;
    int x;
    cin>>P;
    cout<<"P(x)=";
    cout<<P;
    cout<<endl;
    cout<<"Punctul dat este: ";
    cin>>x;
    cout<<"P("<<x<<")=";
    cout<<P.val(x);
    cout<<endl;
    cin>>Q;
    cout<<"Q(x)=";
    cout<<Q;
    cout<<endl;
    F1=P+Q;
    cout<<"P(x)+Q(x)=";
    cout<<F1;
    cout<<endl;
    F2=P-Q;
    cout<<"P(x)-Q(x)=";
    cout<<F2;
    cout<<endl;
    F3=P*Q;
    cout<<"P(x)*Q(x)=";
    cout<<F3;
    return 0;
}
