#include<fstream>
#include<cstring>
#include<cmath>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
char matriceNumere[][20]={"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen",
"sixteen","seventeen","eighteen","nineteen","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};



void Operatie(char propozitie[],int &optiune)
{
    if(strstr(propozitie,"sum")!=0 || strstr(propozitie,"addition")!=0)
        optiune=1;
    else
        if(strstr(propozitie,"difference")!=0 || strstr(propozitie,"subtraction")!=0)
        optiune=2;
    else
        if(strstr(propozitie,"product")!=0 || strstr(propozitie,"multiplication")!=0)
        optiune=3;
    else
        if(strstr(propozitie,"division")!=0 || strstr(propozitie,"partitioning")!=0)
        optiune=4;
}




void transformLitereMici(char propozitie[])
{
    int i;
    for(i=0;i<strlen(propozitie);i++)
        if(propozitie[i]=='A' && propozitie[i+1]=='N' && propozitie[i+2]=='D')
        i=i+2;
    else
        if(propozitie[i]>='A' && propozitie[i]<='Z')
        propozitie[i]=propozitie[i]+'a'-'A';
}




void eliminaCuvinteInutile(char propozitie[])
{
    char *p;
    p=strstr(propozitie,"of");
    strcpy(p,p+3);
    strcpy(propozitie,p);
}




void eliminaAdouaParteDinSirCaSaScotPrimulNumar(char propozitie[])
{
    int i=0;
    while(propozitie[i]!='A')
        i++;
    propozitie[i-1]=0;
}




int ScotNumarInCifre(char propozitie[])
{
    char *p,aux[201];
    int nr,i,nrFinal=0,ok=0;
    if(strstr(propozitie,"hundred thousand")!=0)
        ok=1;
    fout<<endl;
    fout<<propozitie<<" ";
    p=strtok(propozitie," ?");
    while(p!=0)
    {
        if((strcmp(p,"million")!=0 && strcmp(p,"thousand")!=0 && strcmp(p,"hundred")!=0) && (strcmp(p,"million,")!=0 && strcmp(p,"thousand,")!=0 && strcmp(p,"hundred,")!=0))
        {
            if(strchr(p,'-')==0)
            {
                i=0;
                nr=20;
                while(strcmp(matriceNumere[i],p)!=0)
                    i++;
                if(i>20)
                while(i>20)
                {
                    nr=nr+10;
                    i--;
                }
                else
                    nr=i;
            }
            else
            {
                i=27;
                nr=20;
                while(strstr(p,matriceNumere[i])==0)
                    i--;
                while(i>20)
                {
                    nr=nr+10;
                    i--;
                }
                strcpy(aux,strchr(p,'-'));
                i=0;
                while(strstr(aux,matriceNumere[i])==0)
                    i++;
                nr=nr+i;
            }
            nrFinal=nrFinal+nr;
        }
        else
            if(strcmp(p,"million")==0 || strcmp(p,"million,")==0)
            nrFinal=nrFinal*1000000;
        else
            if(strcmp(p,"thousand")==0 || strcmp(p,"thousand,")==0)
            nrFinal=nrFinal*1000;
        else
            nrFinal=nrFinal*100;
        p=strtok(0," ?");
    }
    if(ok==1)
        nrFinal=nrFinal/10;
    return nrFinal;
}





int SpargePropozitiile(char propozitie[])
{
    int nrFinal=0,i=0,r;
    char aux[201];
    while(i<strlen(propozitie))
    if(propozitie[i]==',' || propozitie[i]=='?')
    {
        strcpy(aux,propozitie);
        aux[i]=0;
        r=ScotNumarInCifre(aux);
        nrFinal=nrFinal+r;
        fout<<r<<" ";
        strcpy(propozitie,propozitie+i+1);
        i=0;
    }
    else
        i++;
    return nrFinal;
}




void DigitToWord(short a)//transformarea nr din intervalul 0-99 in cuvinte
{
    if(a<21)
        {fout<< matriceNumere[a];
        return;}  //exceptiile pana la 20
    int z=a/10, u=a%10;
    if(z)
    fout<<matriceNumere[18+z];
    if(u)
    fout<<"-"<<matriceNumere[u];

}




void Hundreds(int n)//afisarea unei secvente de unitati
{
    if(n/100)
        {DigitToWord(n/100);
        fout<<" hundred,";
        }
    if(n%100)
        DigitToWord((n%100));
}




void Decimals(long double d)//afisarea directa a zecimalelor numarului
{   if(d)
    fout<<" point ";
    int x[10],l=9,aprox=0;
    d=d*10000000000;
    long long a=d;
    for(int i=9;i>=0;i--)
    {
        x[i]=a%10;
        a/=10;
    }
    while(x[l]==0)
        l--;
    int i=l;
    while(x[i]==9)
    {
        i--;
        aprox++;
    }
    if(aprox>2&&x[l]<9)
        x[l]++;
    for(int i=0;i<=l;i++)
    {DigitToWord(x[i]);fout<<" ";}
}





void NumberOut(long double n)
{   if(n==0)
    {
        fout<<"zero";
        return;
    }
    long long int a;
    a=n;
    if(n<0)
        a=-n;
    if(n<0)
        fout<<"negative ";
    if(a/1000000000)
    {
        Hundreds(a/1000000000);
        fout<<" billion,";
    }
    if(a/1000000%1000)
    {
        Hundreds(a/1000000%1000);
        fout<<" million,";
    }
    if(a/1000%1000)
    {
        Hundreds(a/1000%1000);
        fout<<" thousand,";
    }
    if(a%1000)
        Hundreds(a%1000);
    if(a!=n||a!=-n)
    Decimals(n-a);

}




void EcGrad2(double a, double b, double c)
{
    double var1,var2;
    double D = sqrt( (b*b) - (4*a*c) );
    if((b*b)-(4*a*c)<0)
        fout<<"Nu exista radacini reale"<<endl<<endl;
    else
    {
    if (!a)
        fout<<"Numitorul este zero, deci nu este ecuatie de gradul 2";
    else
    {
    var1 = ( -b + D)/(2*a);
    var2 = ( -b - D)/(2*a);
    var1=var1;
    var2=var2;
    fout<<"Cele doua radacini sunt: "<<var1<<" "<<var2;
    if(var1<0)
        var1=-var1;
    if(var2<0)
        var2=-var2;
    fout<<" iar forma desfasurata: "<<a<<"*(x-"<<var1<<")*(x-"<<var2<<')'<<endl;
    fout<<"Radacinile in litere sunt: ";
    NumberOut(var1);
    fout<<"si ";
    NumberOut(var2);
    fout<<endl<<endl;
    }
    }
}





int main ()
{
    char s[201],s2[201];
    int semn;
    long long int nr1,nr2,nr3;
    while(fin.getline(s,201))
    {
    if(strstr(s,"AND")==0)
    {
        double a,b,c;
        fin>>a>>b>>c;
        fin.get();
        EcGrad2(a,b,c);
    }
    else
    {
    long double nr4;
    int okk=0;
    transformLitereMici(s);
    Operatie(s,semn);
    eliminaCuvinteInutile(s);
    strcpy(s2,strstr(s,"AND"));
    strcpy(s2,s2+4);
    eliminaAdouaParteDinSirCaSaScotPrimulNumar(s);
    fout<<"Numarul se sparge in numere mai mici iar apoi se aduna toate pentru a obtine rezultatul:";
    nr1=SpargePropozitiile(s);
    fout<<endl;
    fout<<"Cel de-al doilea numar suporta aceleasi operatii:";
    nr2=SpargePropozitiile(s2);
    fout<<endl;
    fout<<"Cele doua numere extrase sunt: "<<nr1<<" si "<<nr2<<endl;
    if(nr2==0 && semn==4)
        fout<<"Impartirea nu este posibila"<<endl<<endl;
    else
    {
    switch(semn)
    {
case 1:
    nr3=nr1+nr2;
    break;
case 2:
    nr3=nr1-nr2;
    break;
case 3:
    nr3=nr1*nr2;
    break;
case 4:
    nr4=nr1/(long double)nr2;
    okk=1;
    break;
default:
    break;
    }
    if(okk==0)
    {
    fout<<"Dupa ce se efectueaza operatia obtinem numarul: "<<nr3<<endl;
    fout<<"In litere acesta este: ";
    NumberOut(nr3);
    }
    else
    {
    fout<<"Dupa ce se efectueaza operatia obtinem numarul: "<<nr4<<endl;
    fout<<"In litere acesta este: ";
    NumberOut(nr4);
    }
    fout<<endl<<endl;
    }
    }
    }
    return 0;
}
