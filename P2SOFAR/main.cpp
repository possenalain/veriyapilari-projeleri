#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

using namespace std;

int ANDgate(int a,int b);
int NANDgate(int a,int b);
int ORgate(int a,int b);
int NORgate(int a,int b);
int NOTgate(int a);
int XORgate(int a,int b);
int XNORgate(int a, int b);


int findspace(string dump);
string trim(string dump);
string yorumlaricikar(string dump);
int kackapi(string dump);
void writetolog(string dump);
string ucuzerinde(string dump);


string giriscikis="";
string girisler="";
string cikisler="";
string kapilar="";
string logsimulation=" ";

int kapisayisi;
int nsntoplam;
int active;

struct eleman
{
    char name;
    int deger;
};

struct kapi
{
    string isim;
    int girissayisi;
    char giris[3];
    char cikis;
    int flag;
    int nanosaniye;
};


void I(struct eleman *initialize,int elemansayisi);
void  Y(struct eleman *devreelemanlar,struct kapi *devrekapi);
void Gstar(struct eleman *devreelemanlar,int elemansayisi);
void G(struct eleman *devreelemanlar,int elemansayisi,string uc);
void L(struct eleman *devreelemanlar,int elemansayisi,string uc);
void H(struct eleman *devreelemanlar,int elemansayisi,string uc);
void S(struct kapi *devrekapilar,struct eleman *devreelemanlar);
void kapiuygula(struct kapi kapieleman,struct eleman *devreelemanlar);
void devrerun();
void hkmtcalis(struct eleman *devreelemanlari,struct kapi *devrekapilari,string uclar,string komut,string Kbasi,char *kmt);

void S(struct kapi *devrekapilar,struct eleman *devreelemanlar);
void devrekmt(struct eleman * devreelemanlari,struct kapi * devrekapilari);

int main()
{



    devrerun();


    return 0;

}//MAININ SONU




/*
GATES BLOCK
*/
int ANDgate(int a,int b)
{
    return(a&&b);
}
int NANDgate(int a,int b)
{
    return(!(a&&b));
}
int ORgate(int a,int b)
{
    return(a||b);
}
int NORgate(int a,int b)
{
    return(!(a||b));
}
int NOTgate(int a)
{
    return(!a);
}
int XORgate(int a,int b)
{
    return(a^b);
}
int XNORgate(int a, int b)
{
    return(!(a^b));
}
/*
GATES BLOCK
*/

/*
WRITE TO LOG.TXT FUNCTION
*/
void writetolog(string dump)
{

    FILE *loghandler;
    loghandler=fopen("log.txt","a+");
    if(loghandler==NULL)
    {
        cout<<"log.txt dosyasi Olusulmadi";
        getchar();
        exit(1);
    }
    dump+="\n";
    if(!fputs(&dump[0],loghandler));
    else
    {
        cout<<"log dosyayi ulasilmadi";
        getchar();
        exit(1);
    }
    fclose(loghandler);
}
/*
WRITE TO LOG.TXT FUNCTION
*/

/*
Y KOMUTUNUN FONKSIYONU
*/
void  Y(struct eleman *devreelemanlar,struct kapi *devrekapi)
{
    int position=0;;
    char row[255];

    FILE *devrehandler;
    FILE *degerhandler;
    FILE *baskahandler=NULL;
    devrehandler=fopen("devre.txt","r");
    if(devrehandler==NULL)
    {
        cout<<"\n Devre.txt okunamiyor";
        exit(1);
    }

    string line=fgets(row,255,devrehandler);
    string baskelime;

    int i=0;
    while(row) //GET THE BLANK SPACE
    {
        if(isspace(line[i])||line[i]=='\0')
            break;
        i++;
    }
    baskelime=line.substr(0,i);
    /*
    BASKA DOSYASI DAHIL EDILMISSE
    */
    if(strcasecmp(&baskelime[0],".include")==0)
    {
        baskahandler=fopen("baska_dosya.txt","r");
        if(baskahandler==NULL)
        {
            cout<<"baska_dosyayi acilmiyor";
            exit(1);
        }
    }
    else
    {
        rewind(devrehandler);
    }
    baskelime="";
    /*
    DEVRE DOSYAYI BASKA DOSYAYI OKUNACAK
    SONRA DEGISKENLERI TANIMLANMASI GEREKIR
    VE ILK DEGERLER ATANMASI GEREKIR
    */
    while(fgets(row,255,devrehandler))//DEVRE DOSYASINDAN OKUMA
    {
        line=row;
        line=trim(line);
        int i=0;
        while(1) //GET BLANK SPACE
        {
            if(isspace(line[i]))
                break;
            i++;
        }
        baskelime=line.substr(0,i);
        /*
        GIRIS
        */
        if(strcasecmp(&baskelime[0],".giris")==0)
        {
            girisler+=trim(line.substr(i,line.length()));
        }
        /*
        CIKIS
        */
        if(strcasecmp(&baskelime[0],".cikis")==0)
        {
            cikisler+=trim(line.substr(i,line.length()));
        }
        /*
        KAPI
        */
        if(strcasecmp(&baskelime[0],".kapi")==0)
        {
            kapilar+=trim(line.substr(i,line.length()));
            kapilar+="\n";
        }
        /*
        SONLANDIRMA
        */
        if(strcasecmp(&baskelime[0],".son")==0)
        {
            fclose(devrehandler);
        }
    }
    if(baskahandler!=NULL)
    {
        while(fgets(row,255,baskahandler))//BASKA DOSYASINDAN OKUMA
        {
            line=trim(row);
            baskelime="";
            int i=0;
            while(1) //GET BLANK SPACE
            {
                if(isspace(line[i])||line[i]=='\0')
                    break;
                i++;
            }
            baskelime=line.substr(0,i);
            string temp;
            if(strcasecmp(&baskelime[0],".giris")==0)//GIRIS
            {
                girisler+=trim(line.substr(i,line.length()));
            }
            if(strcasecmp(&baskelime[0],".cikis")==0)//CIKIS
            {
                cikisler+=trim(line.substr(i,line.length()));
            }
            if(strcasecmp(&baskelime[0],".kapi")==0)//KAPI
            {
                kapilar+=trim(line.substr(i,line.length()));
                kapilar+="\n";
            }
            if(strcasecmp(&baskelime[0],".son")==0)//SON
            {
                fclose(baskahandler);
            }
        }
    }

    char *token;
    const char delimiter[2]="\t";
    token = strtok(&girisler[0], delimiter);
    /* WALK THROUGH OTHER TOKENS*/
    while( token != NULL )
    {
        int i=0,vardi=0;
        char temp=token[0];
        while(giriscikis[i])
        {
            if(giriscikis[i]==temp)
            {
                vardi=1;
                break;
            }
            i++;
        }
        if(vardi==0)
        {
            giriscikis+=temp;
        }
        token = strtok(NULL, delimiter);
    }
    token = strtok(&cikisler[0], delimiter);
    /* WALK THROUGH OTHER TOKENS */
    while( token != NULL )
    {
        int i=0,vardi=0;
        char temp=token[0];
        while(giriscikis[i])
        {
            if(giriscikis[i]==temp)
            {
                vardi=1;
                break;
            }
            i++;
        }
        if(vardi==0)
        {
            giriscikis+=temp;
        }
        token = strtok(NULL, delimiter);
    }
    /*
    KAPILARI DA OKU VE PROGRAMA YUKLE SONRA
    ELEMANLARIN STRUCT EKLE
    */
    kapisayisi=kackapi(kapilar);
    token = strtok(&kapilar[0], "\n");
    i=0;
    /* WALK THROUGH THE OTHER TOKENS */
    string sprinted="";
    while( token != NULL )
    {
        string temp=token;
        int tokenlength=temp.length();
        char *where=&token[tokenlength+1];
        char *templine=strtok(&temp[0],"\t, ");

        while(templine!=NULL)
        {
            sprinted+=templine;
            sprinted+=" ";
            templine=strtok(NULL,"\t, ");
        }
        char spritemp[100];
        strcpy(spritemp,&sprinted[0]);
        char name[5];
        int gs,d;
        char ck,g0,g1,g2;
        char m=sprinted[findspace(spritemp)+1];
        int kacgiris=atoi(&m);

        //KNOW HOW MANY ENTRIES DOES A GATE HAVE;
        if(kacgiris==2)
        {
            sscanf(spritemp," %s %d  %c %c %c %d",name,&gs,&ck,&g0,&g1,&d);
            devrekapi[i].giris[2]=' ';
            devrekapi[i].giris[1]=g1;
        }
        else if(kacgiris==3)
        {
            sscanf(spritemp," %s %d  %c %c %c %c %d",name,&gs,&ck,&g0,&g1,&g2,&d);
            devrekapi[i].giris[2]=g2;
            devrekapi[i].giris[1]=g1;
        }
        else if(kacgiris==1)
        {
            sscanf(spritemp," %s %d  %c %c %d",name,&gs,&ck,&g0,&d);
            devrekapi[i].giris[1]=' ';
            devrekapi[i].giris[2]=' ';
        }
        else
        {   cout<<kacgiris;
            cout<<"\n\nverilimis girislerinde uyusmazlik var";
            exit(1);
        }
        devrekapi[i].isim=name;
        devrekapi[i].girissayisi=gs;
        devrekapi[i].cikis=ck;
        devrekapi[i].giris[0]=g0;
        devrekapi[i].nanosaniye=d;
        sprinted="";
        token = strtok(where,"\n");
        i++;
    }
//ADD ELEMENTS TO GIRISCIKIS DEGISKENI
    for(i=0; i<kapisayisi; i++)
    {
        int j=0;
        while(j<devrekapi[i].girissayisi)
        {
            int t=0,vardi=0;
            char temp=devrekapi[i].giris[j];
            while(giriscikis[t])
            {
                if(giriscikis[t]==temp)
                {
                    vardi=1;
                    break;
                }
                t++;
            }
            if(vardi==0)
            {
                giriscikis+=temp;
            }
            j++;
        }
    }
    for(i=0; i<giriscikis.length(); i++)
    {
        devreelemanlar[i].name=giriscikis[i];
    }
}

/*
Y KOMUTUNUN FONKSIYONUN SONU
*/

/*
I KOMUT
*/

void I(struct eleman *initialize,int elemansayisi)
{
    FILE *degerhandler;
    degerhandler=fopen("deger.txt","r");
    if(degerhandler==NULL)
    {
        cout<<"deger.txt dosyasi okunmadi";
        getchar();
        exit(1);
    }
    string line;
    char row[10];
    char bashalf;
    int i;
    while(fgets(row,5,degerhandler))//DEGER DOSYASINDAN OKUMA
    {
        line=row;
        line=yorumlaricikar(line);
        line=trim(line);
        char elmn;
        int deger;
        sscanf(row,"%c %d",&elmn,&deger);
        i=0;
        while(i<elemansayisi)
        {
            if(initialize[i].name==elmn)
            {
                initialize[i].deger=deger;
            }
            i++;
        }
    }
    fclose(degerhandler);
}
/*
I KOMUTUNUN FONKSIYONUN SONU
*/
/*
G KOMUTU
*/
void G(struct eleman *devreelemanlar,int elemansayisi,string uc)
{
    int i,j;

    for(i=0; i<elemansayisi; i++)
    {
        for(j=0; j<uc.length(); j++)
        {

            if(toupper(devreelemanlar[i].name)==toupper(uc[j]))
            {

                cout<<"\n"<<devreelemanlar[i].name<<"  :  "<<devreelemanlar[i].deger;
                break;
            }
        }
    }

}
/*
G
*/
/*
G* KOMUTUN FONKSYONU
*/
void Gstar(struct eleman *devreelemanlar,int elemansayisi)
{
    int i;
    cout<<"\n\n";
    for(i=0; i<elemansayisi; i++)
    {
        cout<<"\n"<<devreelemanlar[i].name<<"  :  "<<devreelemanlar[i].deger;
    }
    cout<<"\n\n";
}
/*
G* KOMUTUN FONKSYONU
*/
/*
L KOMUTU
*/
void L(struct eleman *devreelemanlar,int elemansayisi,string uc)
{

    int i,j;
    for(i=0; i<elemansayisi; i++)
    {
        for(j=0; j<uc.length(); j++)
        {

            if(toupper(devreelemanlar[i].name)==toupper(uc[j]))
            {

                char dm[25];
                sprintf(dm,"0 nsn: %c  %d -->  0",devreelemanlar[i].name,devreelemanlar[i].deger);
                logsimulation+=dm;
                logsimulation+="\n\n ";
                devreelemanlar[i].deger=0;

                break;
            }
        }
    }

}
/*
L KOMUTU
*/
/*
H KOMUTU
*/
void H(struct eleman *devreelemanlar,int elemansayisi,string uc)
{

    int i,j;
    for(i=0; i<elemansayisi; i++)
    {
        for(j=0; j<uc.length(); j++)
        {

            if(toupper(devreelemanlar[i].name)==toupper(uc[j]))
            {
                char dm[25];
                sprintf(dm,"0 nsn: %c  %d -->  1",devreelemanlar[i].name,devreelemanlar[i].deger);
                logsimulation+=dm;
                logsimulation+="\n\n ";
                devreelemanlar[i].deger=1;
                break;
            }
        }
    }

}
/*
H KOMUTU
*/
/*SIMILASIYON YAP*/
void S(struct kapi *devrekapilar,struct eleman *devreelemanlar)
{

    cout<< "\n\n";

    int i;
    nsntoplam=0;

    int onkapilari[kapisayisi];

    for(i=0; i<kapisayisi; i++)
    {
        int j;
        onkapilari[i]=-1;
        for(j=0; j<devrekapilar[i].girissayisi; j++)
        {
            int t=0;
            while(t<girisler.length())
            {
                if(toupper(devrekapilar[i].giris[j])==toupper(girisler[t]))
                {
                    onkapilari[i]=i;
                }
                t++;
            }
        }
        nsntoplam+=devrekapilar[i].nanosaniye;
    }
    cout<<logsimulation;
    for(i=1; i<nsntoplam; i++)
    {


        int j;

        for(j=0; j<kapisayisi; j++)
        {
            if(onkapilari[j]!=-1)
            {
                if(devrekapilar[j].nanosaniye==i)
                {
                    devrekapilar[j].flag=1;
                    cout<<i<<" nsn :";
                    kapiuygula(devrekapilar[j],devreelemanlar);

                }
            }
            else
            {
                int runable=0;
                int itstime=0;
                int k;
                for(k=0; k<kapisayisi; k++)
                {

                    int t=0;
                    while(t<devrekapilar[j].girissayisi)
                    {
                        if(toupper(devrekapilar[j].giris[t])==toupper(devrekapilar[k].cikis))
                        {
                            if(devrekapilar[k].flag==1)
                            {
                                runable=1;
                            }
                            if(devrekapilar[j].nanosaniye+devrekapilar[k].nanosaniye==i)
                            {
                                itstime=1;
                            }

                        }
                        t++;
                    }
                    if(itstime==1&&runable==1)
                    {
                        cout<<i<<" nsn :";
                        kapiuygula(devrekapilar[j],devreelemanlar);
                    }
                    itstime=0;
                    runable=0;
                }
            }


        }
    }
    logsimulation=" ";
}
/*
SIMILASYON*/
/*
HANGI UCLARA ISLEM YAPILACAK
*/
string ucuzerinde(string dump)
{
    string returntoken="";
    char *token;
    const char delimiter[4]="\t, ";
    token = strtok(&dump[0], delimiter);
    token = strtok(NULL, delimiter);
    /* WALK THROUGH OTHER TOKENS*/
    while( token != NULL )
    {
        int i=0,vardi=0;
        char temp=token[0];
        while(returntoken[i])
        {
            if(returntoken[i]==temp)
            {
                vardi=1;
                i++;
                continue;
            }
            i++;
        }
        if(vardi==0)
        {
            returntoken+=temp;
        }
        token = strtok(NULL, delimiter);
    }
    return returntoken;
}
/*
HANGI UCLARA ISLEM YAPILACAK
*/
int findspace(string dump)
{
    /*
    BOSLUK YERI OGRENME FONKSYONU
    */
    int position=0;
    while(1)
    {
        if(isspace(dump[position])||dump[position]=='\t')
            break;

        else
        {
            position++;
        }

        if(dump[position]=='\0')
            break;
    }
    return position;
}

string trim(string dump)
{
    dump=yorumlaricikar(dump);
    dump+="\t";
    int i=0,j=dump.length()-1;
    while(1)
    {
        if(isspace(dump[i]))
        {
            i++;
        }
        else
            break;
    }
    while(1)
    {
        if(isspace(dump[j]))
        {
            j--;
        }
        else
            break;
    }
    return dump.substr(i,j+1);
}
string yorumlaricikar(string dump)
{
    int i=0;
    while(dump[i])
    {
        if(dump[i]=='\0')
            break;
        else if((dump[i]!='#'))
            i++;
        else if(dump[i]=='#')
        {
            int t=i+1;
            while(dump[t])
            {
                if(dump[t]==' '||dump[t]=='\t')
                    dump[t]='\0';
                dump[t]='\0';

                t++;
            }

            break;
        }

    }
    dump[i+1]='\0';
    dump=dump.substr(0,i);
    return dump;
}
int kackapi(string dump)
{
    int i=0;
    int kac=0;
    while(1)
    {
        if(dump[i]=='\n')
            kac++;
        if((dump[i]=='\n')&&(dump[i-1]=='\n'))
            kac--;
        if(dump[i]=='\0')
            break;
        i++;
    }
    return kac;
}
void kapiuygula(struct kapi kapieleman,struct eleman *devreelemanlar)
{
    int kelmn=kapieleman.girissayisi;
    int giris[kelmn];
    int cikis;
    string kapiismi=kapieleman.isim;

    int i,j;
    for(i=0; i<giriscikis.length(); i++)
    {
        for(j=0; j<kelmn; j++)
        {
            if(toupper(kapieleman.giris[j])==toupper(giriscikis[i]))
            {
                giris[j]=i;
            }
        }
        if(toupper(kapieleman.cikis)==toupper(giriscikis[i]))
        {
            cikis=i;
        }
    }
    int x,y,z;
    x=giris[0];
    y=giris[1];
    if(kelmn==3)
    {
        z=giris[2];
    }
    cout<<devreelemanlar[cikis].name<<"  "<<devreelemanlar[cikis].deger<<" -->  ";
    if(strcasecmp(&kapiismi[0],"AND")==0)
    {
        if(kelmn==2)
        {
            devreelemanlar[cikis].deger=ANDgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
        }
        else if(kelmn==3)
        {
            devreelemanlar[cikis].deger=ANDgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
            devreelemanlar[cikis].deger=ANDgate(devreelemanlar[cikis].deger,devreelemanlar[z].deger);
        }
    }
    else if(strcasecmp(&kapiismi[0],"NAND")==0)
    {
        if(kelmn==2)
        {
            devreelemanlar[cikis].deger=NANDgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
        }
        else if(kelmn==3)
        {
            devreelemanlar[cikis].deger=NANDgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
            devreelemanlar[cikis].deger=NANDgate(devreelemanlar[cikis].deger,devreelemanlar[z].deger);
        }
    }
    else if(strcasecmp(&kapiismi[0],"OR")==0)
    {
        if(kelmn==2)
        {
            devreelemanlar[cikis].deger=ORgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
        }
        else if(kelmn==3)
        {
            devreelemanlar[cikis].deger=ORgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
            devreelemanlar[cikis].deger=ORgate(devreelemanlar[cikis].deger,devreelemanlar[z].deger);
        }
    }
    else if(strcasecmp(&kapiismi[0],"NOR")==0)
    {
        if(kelmn==2)
        {
            devreelemanlar[cikis].deger=NORgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
        }
        else if(kelmn==3)
        {
            devreelemanlar[cikis].deger=NORgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
            devreelemanlar[cikis].deger=NORgate(devreelemanlar[cikis].deger,devreelemanlar[z].deger);
        }
    }
    else if(strcasecmp(&kapiismi[0],"XOR")==0)
    {
        if(kelmn==2)
        {
            devreelemanlar[cikis].deger=XORgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
        }
        else if(kelmn==3)
        {
            devreelemanlar[cikis].deger=XORgate(devreelemanlar[x].deger,devreelemanlar[y].deger);
            devreelemanlar[cikis].deger=XORgate(devreelemanlar[cikis].deger,devreelemanlar[z].deger);
        }
    }
    else if(strcasecmp(&kapiismi[0],"NOT")==0)
    {
        devreelemanlar[cikis].deger=NOTgate(devreelemanlar[x].deger);
    }
    else
    {
        cout<<"\n \n"<<kapiismi<<" \n\n kapi taninmadi \n ";
    }
    cout<<devreelemanlar[cikis].deger<<"\n\n ";
}
/*

HKMTCALIS
*/

void hkmtcalis(struct eleman *devreelemanlari,struct kapi *devrekapilari,string uclar,string komut,string Kbasi,char *kmt)
{
    time_t kmttime;
    char tmlog[50];
    string logkomutlari="";
    int len=0;
    uclar=ucuzerinde(komut);
    if(strcasecmp(&Kbasi[0],"H")==0)
    {

        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);
        H(devreelemanlari,giriscikis.length(),uclar);

    }
    else if(strcasecmp(&Kbasi[0],"L")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);
        L(devreelemanlari,giriscikis.length(),uclar);
    }

    else if(strcasecmp(&Kbasi[0],"S")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);
        S(devrekapilari,devreelemanlari);

    }
    else if(strcasecmp(&Kbasi[0],"G")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);
        G(devreelemanlari,giriscikis.length(),uclar);

    }
    else if(strcasecmp(&Kbasi[0],"G*")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);
        Gstar(devreelemanlari,giriscikis.length());

    }
    else if(strcasecmp(&Kbasi[0],"K")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);

    }
    else if(strcasecmp(&Kbasi[0],"I")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        I(devreelemanlari,giriscikis.length());
        writetolog(&logkomutlari[0]);

    }
    else if(strcasecmp(&Kbasi[0],"C")==0)
    {
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+=kmt;
        writetolog(logkomutlari);
        exit(1);
    }
    else
    {
        cout<<"\nTANIMSIZ KOMUTU\n";
    }
    logkomutlari="";

}
/*
DEVRE RUN
*/
void devrerun()
{
    int i,len;
    string komut="";
    string Kbasi="";
    string logkomutlari="";
    string uclar="";

    time_t kmttime;
    char tmlog[50];
    struct eleman devreelemanlari[15];
    struct kapi devrekapilari[5];
    if(active!=1)
    {
        Y(devreelemanlari,devrekapilari);
        active=1;
    }

        while(strcasecmp(&komut[0],"Y")!=0)
        {

            if(strcasecmp(&komut[0],"")!=0)
            {
                cout<<"\nDEVRE YUKLENMEMIS\n";
            }
            if(strcasecmp(&komut[0],"K")==0)
            {
                devrekmt(devreelemanlari,devrekapilari);
            }
            cout<<"\n>";
            cin>>komut;
            if(strcasecmp(&komut[0],"C")==0)
            {
                exit(1);
            }
        }

        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+="\tY devre.txt";
        writetolog(&logkomutlari[0]);


        komut="";
        logkomutlari="";
        while(strcasecmp(&komut[0],"I")!=0)
        {
            if(strcasecmp(&komut[0],"")!=0)
            {
                cout<<"\nILKLENDIRME YAPILMAMIS\n";
            }
            if(strcasecmp(&komut[0],"K")==0)
            {
                devrekmt(devreelemanlari,devrekapilari);
            }
            cout<<"\n>";
            cin>>komut;
            if(strcasecmp(&komut[0],"C")==0)
            {
                exit(1);
            }
        }

        I(devreelemanlari,giriscikis.length());
        kmttime=time(NULL);
        sprintf(tmlog,"%s",ctime(&kmttime));
        logkomutlari+=tmlog;
        len=logkomutlari.length();
        logkomutlari[len-1]='\t';
        logkomutlari+="\tI devre.txt";
        writetolog(&logkomutlari[0]);
        /*
        KOMUTULARI ALALIM
        */
        logkomutlari="\n";
        do
        {
            char kmt[255];
            int len;
            cout<<"\n  >";
            fgets(kmt,255,stdin);
            komut=yorumlaricikar(kmt);
            komut=trim(kmt);
            if(strcasecmp(&komut[0],"")!=0)
            {
                Kbasi=komut.substr(0,findspace(komut));
            }
            else
            {
                continue;
            }
            if(strcasecmp(&komut[0],"K")==0)
            {
                devrekmt(devreelemanlari,devrekapilari);
            }
            else
            {
                hkmtcalis(devreelemanlari,devrekapilari,uclar,komut,Kbasi,kmt);
            }

        }
        while(strcasecmp(&Kbasi[0],"C")!=0);

}


/*
KOMUTLAR FROM DOSYA RUN
*/
void devrekmt(struct eleman * devreelemanlari,struct kapi * devrekapilari)
{
    int len;
    string komut="";
    string Kbasi="";
    string logkomutlari="";
    string uclar="";

    time_t kmttime;
    char tmlog[50];

    if(active!=1)
    {
        Y(devreelemanlari,devrekapilari);
        active=1;
    }


    FILE *komhandler;
    komhandler=fopen("komut.txt","r");
    if(komhandler==NULL)
    {
        cout<<"\n komut.txt okunamiyor";
        exit(1);
    }
    string line;
    int i=0;
    char row[100];

    while(fgets(row,100,komhandler))//KOMUT DOSYASINDAN OKUMA
    {
        komut="";
        line=row;
        line=yorumlaricikar(line);
        line=trim(line);
        komut=line;
        Kbasi=line.substr(0,findspace(line));

        if(i==0)
        {

            if((strcasecmp(&Kbasi[0],"C")==0)||strcasecmp(&Kbasi[0],"Y")!=0)
            {
                cout<<"\nDEVRE YUKLENMEMIS\n";
                exit(1);
            }



            kmttime=time(NULL);
            sprintf(tmlog,"%s",ctime(&kmttime));
            logkomutlari+=tmlog;
            len=logkomutlari.length();
            logkomutlari[len-1]='\t';
            logkomutlari+="\tY devre.txt";
            writetolog(&logkomutlari[0]);
            komut="";
            logkomutlari="";

        }
        else if(i==1)
        {
            if((strcasecmp(&Kbasi[0],"C")==0)||strcasecmp(&Kbasi[0],"I")!=0)
            {
                cout<<"\nDEVRE ILKLENDIRIMEMIS\n";
                exit(1);
            }
            I(devreelemanlari,giriscikis.length());
            kmttime=time(NULL);
            sprintf(tmlog,"%s",ctime(&kmttime));
            logkomutlari+=tmlog;
            len=logkomutlari.length();
            logkomutlari[len-1]='\t';
            logkomutlari+="\tI deger.txt";
            writetolog(&logkomutlari[0]);
            komut="";
            logkomutlari="";
        }
        else
        {
            hkmtcalis(devreelemanlari,devrekapilari,uclar,komut,Kbasi,row);

        }
        Kbasi="";
        i++;

    }





}




