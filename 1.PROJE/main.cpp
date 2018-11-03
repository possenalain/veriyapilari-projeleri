#include<graphics.h>
#include<stdio.h>
#include<time.h>

#define ARROW_SIZE 6
struct yol
{
    int x,y;
    int hareket;
};
struct yol yollar[9];
void yoluciz(int kacinci);
void yon_hareketi(int x,int y,int hangisi);
void swap_rows(int *row1,int *row2,int *right_b,int r1,int r2,int number);
void sifirla_rows(int *rowdegisen,int *rowdegismeyen,int *right_b,int r1,int r2,int number,int flag);
void scale(int *row,int *right_b,int r,int number,int hangi);
void yazdir(int *matris,int *b,int n);
int hangihareket(int index,int direction);
void harekete(int roads);


int main()
{
    /*
    INITIALIZE THE GRAPHICS AND SELECT THE MAP
    */
    int wind1=initwindow(1500,1000, "1. Proje-kavsaklar");
    setcolor(4);
    int x=getmaxx();
    int y=getmaxy();
    int current_x,current_y;
    int circle_x,circle_y,radius_o,radius_i;
    yoluciz(1);
    yoluciz(2);
    srand((unsigned) time(NULL));
    int selected=0;
    while(!kbhit()||!selected)
    {

        if(ismouseclick(513))
        {
            if(mousex()<(getmaxx()/2)-50)
            {
                selected=1;
            }
            else if(mousex()>((getmaxx()/2)+50))
            {
                selected=2;
            }
            else
            {
                selected=0;
            }
            clearmouseclick(513);
        }
        /*
        NE YOL SECILECEGINI MOUSE CLICK ILE SECILIR
        */
    }
    getch();
    closegraph(wind1);
    int wind2=initwindow(700,700,"SELECTED");
    cleardevice();
    setbkcolor(0);

    if(selected==1)//BIRINCI YOLU SECILMIS
    {
        yoluciz(3);
        setcolor(2);
    }
    else //IKINCI INCI YOL SECILMIS
    {
        yoluciz(4);
        setcolor(2);

    }
    int roads,dimy=5,dimx=4;
    char names[]= {'A','B','C','D','W','X','Y','Z','T'};
    roads=8;
// IF THE SECOND ROAD WAS SELECTED
    printf("\nselected:%d\n\n",selected);
    if(selected==2)
    {
        roads=9;
    }
    int relations[dimy][roads]=
    {
        {0,-1,-1,-1,4,-1,-1,7,-1},
        {-1,1,-1,-1,4,5,-1,-1,-1},
        {-1,-1,2,-1,-1,5,6,-1,-1},
        {-1,-1,-1,3,-1,-1,6,7,-1},
        {0,1,2,3,-1,-1,-1,-1,-1}
    };//relationship of every variable at a give roundabout
    int denklem[dimy][roads]=
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };//draft equations ready to be sorted out
    int deger[9]= {0,0,0,0,0,0,0,0,0};

    int i,j;
//initialize variables for the first road
    if(roads==9)
    {
        relations[0][8]=8;
        relations[2][8]=8;
    }
//present the main instructions about making choices
    printf("#secimler yaparken 1 ve -1 rakamlar kullaniliyor\n\n");
    printf("\t--ana yollar icin gobege giriyorsa 1 cikiyorsa -1\n");
    printf("\t--ana yollar 2 cikis 2 giris seklinde olmak zorunda\n");

    int choice=0,girisler=0,cikisler=0;
    char baslangic,gittigi;
    int yogunluk=-1;
//start by getting the main roads directions and values
    for(i=0; i<4; i++)
    {
        printf("\n%c - gobege giriyorsa 1 cikiyorsa -1: ",names[i]);
        scanf("%d",&choice);
        while((choice!=-1&&choice!=1))
        {
            printf("\n%c tekrar giriniz:",names[i]);
            scanf("%d",&choice);
        }
//count ins and outs
        for(j=0; j<4; j++)
        {
            if(denklem[4][j]>0)
            {
                girisler++;
            }

            if(denklem[4][j]<0)
            {
                cikisler++;
            }
        }
        while((girisler==2&&choice==1)||(cikisler==2&&choice==-1))
        {
            printf("\n --- 2 giris 2 cikis olamali");
            printf("\n\n%c - tekrar giriniz:",names[i]);
            scanf("%d",&choice);
        }//check if ins or outs are outnumbered

        printf("\n\t- %c - gecen arabalarin yogunlugu :",names[i]);
        scanf("%d",&yogunluk);
        while(yogunluk<-1)
        {
            printf("\n\t- %c - yanlis deger, tekrar giriniz :",names[i]);
            scanf("%d",&yogunluk);
        }
//get the density of cars passing a given route
        deger[i]=yogunluk;
//store them in their respective places
        if(choice==1)
        {
            if(yogunluk==-1)
            {
                denklem[i][i]=-yogunluk;
                denklem[4][i]=-yogunluk;
            }
            else
            {
                denklem[i][i]=yogunluk;
                denklem[4][i]=yogunluk;
            }
        }
        if(choice==-1)
        {
            if(yogunluk==-1)
            {
                denklem[i][i]=yogunluk;
                denklem[4][i]=yogunluk;
            }
            else
            {
                denklem[i][i]=-yogunluk;
                denklem[4][i]=-yogunluk;
            }
        }
        yollar[i].hareket=hangihareket(i,choice);
        yon_hareketi(yollar[i].x,yollar[i].y,yollar[i].hareket);
//reset the values, for the next instantiation
        girisler=0;
        cikisler=0;
        yogunluk=-1;
    }
//for the next petite route
    for(i=4; i<roads; i++)
    {
        int gecerli=0;
        while(gecerli==0)
        {
            printf("\n%c icin \n",names[i]);
            printf("baslangic:");
            scanf(" %c",&baslangic);
            printf("gittigi:");
            scanf(" %c",&gittigi);
            int a,b,ilk,son;
//CHECK IF BASLANGIC VE GITTIGI ARE AMONG THE MAIN ROADS
            for(a=0; a<4; a++)
                if(baslangic==names[a])
                    for(b=0; b<4; b++)
                        if(gittigi==names[b])
                        {
                            son=b;
                            ilk=a;
                            gecerli=1;
                        }
            if(ilk!=i-4&&ilk!=i-3)
                gecerli=0;
            if(son!=i-4&&son!=i-3)
                gecerli=0;
            if(i==7)
            {
                if(ilk==0||ilk==3)
                {
                    if(son==0||son==3)
                        gecerli=1;
                }
            }
            if(i==8)
            {
                if(ilk==0||ilk==2)
                {
                    if(son==0||son==2)
                        gecerli=1;
                }
            }
//is it A B C D
            if(gecerli)
            {
                if(ilk==son)//A---A
                    gecerli=0;

                if(((son-ilk!=1)&&(son-ilk!=-1)))//A---C or C----D
                    gecerli=0;

                if(roads==9)
                {
                    if((ilk==0&&son==2)||(ilk==2&&son==0)) // 9Rd, A -- C
                        gecerli=1;
                }
                if((ilk==0&&son==3)||(ilk==3&&son==0)) // A -- D
                    gecerli=1;
//OK? continue with getting their densities
                if(gecerli)
                {
                    printf("\t\tbaslangic: %d   gittigi :%d  gecerliligi:%d\n",ilk,son,gecerli);
                    printf("\n\t- %c - gecen arabalarin yogunlugu :",names[i]);
                    scanf("%d",&yogunluk);
                    while(yogunluk<-1)
                    {
                        printf("\n\t- %c - yanlis deger, tekrar giriniz :",names[i]);
                        scanf("%d",&yogunluk);
                    }
                    deger[i]=yogunluk;
                    /*
                    SHOW IT'S MOVEMENT ACCORDINGLY
                    */
                    yollar[i].hareket=hangihareket(i,son-ilk);
                    yon_hareketi(yollar[i].x,yollar[i].y,yollar[i].hareket);
                    int n;
//put the values in draft equation array with their directions effects
                    for(a=0; a<4; a++)
                    {
                        if(relations[a][i]==i)
                        {
                            if(yogunluk==-1)
                            {
                                denklem[ilk][i]=yogunluk;
                                denklem[son][i]=-yogunluk;
                            }
                            else
                            {
                                denklem[ilk][i]=-yogunluk;
                                denklem[son][i]=yogunluk;
                            }
                            break;
                        }
                    }
                }
                if(!gecerli) // direction is valid
                {
                    printf("\t--- yanlis yonu, tekrar giriniz\n");
                }
            }
            else
            {
                printf("\n\t---yon belirtmede hatta var tekrar giriniz ---");
                gecerli=0;
            }
        }
    }
    /*
    CREATE THE FINE EQUATION READY TO BE PROCESSED
    */
    int bilinmeyen_sayisi=0;
    for(i=0; i<roads; i++)
    {
        if(deger[i]==-1)
            bilinmeyen_sayisi++;
    }
    int bilinmeyen[bilinmeyen_sayisi],h=0;
    for(i=0; i<roads; i++)
        if(deger[i]==-1)
        {
            bilinmeyen[h]=i;
            h++;
        }
    int b[dimy]= {0,0,0,0,0};
    int gauss_m[5][bilinmeyen_sayisi],column=0;
    for(i=0; i<bilinmeyen_sayisi; i++)
    {
        column=bilinmeyen[i];
        for(j=0; j<5; j++)
        {
            gauss_m[j][i]=denklem[j][column];
        }
    }
    int unknown,t,k;
    for(i=0; i<roads; i++)
    {
        unknown=0;
        for(t=0; t<bilinmeyen_sayisi; t++)
            if(i==bilinmeyen[t]&&deger[i]==-1)
                unknown=1;
        if(unknown==1)
            continue;
        for(j=0; j<5; j++)
            b[j]-=denklem[j][i];
    }
//an equation ready to be solved by Gaussian elimination

    printf("\n\n\n\ eselon haline getirecegiz\n\n\n\n");
    /*
    YAZDIRMA
    */
    yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);
    for(i=0; i<5; i++)//eselon haline getir
    {
        int allzeros=0;//if the whole column under current is of zeros
        if(gauss_m[i][i]==0)
        {
            allzeros=1;
            for(j=i; j<5; j++)
            {
                if(gauss_m[j][i]!=0)
                {
                    swap_rows(gauss_m[i],gauss_m[j],b,i,j,bilinmeyen_sayisi);
                    allzeros=0;
                    /*
                    YAZDIRMA
                    */
                    yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);
                    break;
                }
            }
        }
        /*

        */
//if one is not on the diagonal
        if(allzeros==1)
        {
            int x,y;
            for(x=i; x<bilinmeyen_sayisi; x++)
            {
                int done=0;

                if(gauss_m[i][x]==0)
                {

                    for(j=i; j<5; j++)
                    {
                        if(gauss_m[j][x]!=0)
                        {

                            swap_rows(gauss_m[i],gauss_m[j],b,i,j,bilinmeyen_sayisi);
                            int t,k;
                            done=1;
                            /*
                            YAZDIRMA
                            */
                            yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);

                            break;
                        }
                    }

                }
                if(gauss_m[i][x]!=0)
                {
                    done=1;
                    for(y=0; y<5; y++)
                    {
                        if(y!=i)
                        {
                            if(gauss_m[y][x]!=0)
                            {
                                if(gauss_m[y][x]!=gauss_m[i][x])
                                {
                                    sifirla_rows(gauss_m[y],gauss_m[i],b,y,i,bilinmeyen_sayisi,1);
                                }
                                if(gauss_m[y][x]==gauss_m[i][x])
                                {

                                    sifirla_rows(gauss_m[y],gauss_m[i],b,y,i,bilinmeyen_sayisi,2);
                                }

                                /*
                                YAZDIRMA
                                */
                                yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);
                            }
                        }
                    }
                }
                if(done==1)
                    break;
            }
        }
//if a one is not on the diagonal
        /*
        */
        if(gauss_m[i][i]!=0)
        {
            for(j=0; j<5; j++)
            {
                if(i!=j)
                {
                    if(gauss_m[j][i]!=0)
                    {
                        if(gauss_m[j][i]!=gauss_m[i][i])
                        {
                            sifirla_rows(gauss_m[j],gauss_m[i],b,j,i,bilinmeyen_sayisi,1);
                        }
                        if(gauss_m[j][i]==gauss_m[i][i])
                        {
                            sifirla_rows(gauss_m[j],gauss_m[i],b,j,i,bilinmeyen_sayisi,2);
                        }

                        /*
                        YAZDIRMA
                        */
                        yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);
                    }
                }
            }
        }//if current differs from zeros

    }//end of
//scaling  diagonals
    for(i=0; i<5; i++)
    {
        for(j=0; j<bilinmeyen_sayisi; j++)
        {
            if(gauss_m[i][j]!=0)
            {
                if(gauss_m[i][j]==-1)
                {
                    scale(gauss_m[i],b,i,bilinmeyen_sayisi,j);
                    /*
                    YAZDIRMA
                    */
                    yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);

                }
                break;
            }
        }
    }
    /*
    */
    printf(" \n\n eselon indirgenmis hali\n\n");
    /*
    YAZDIRMA
    */

    int sayac,point_to;
    for(sayac=0; sayac<bilinmeyen_sayisi; sayac++)
    {
        point_to=bilinmeyen[sayac];
        printf("     %c      ",names[point_to]);
    }
    printf("\n-----------------------------\n\n\n");



    yazdir(&gauss_m[0][0],b,bilinmeyen_sayisi);

    printf(" \n\n\n --presenting the results--\n\n\n");
    /*PRESENTING THE RESULTS*/
    for(t=0; t<5; t++)
    {
        int buldum=0,name;
        int first=1;
        for(k=0; k<=bilinmeyen_sayisi-1; k++)
        {
            char sign=' ';
            if(gauss_m[t][k]>0)
                sign='+';
            if(gauss_m[t][k]<0)
                sign=' ';

            if(gauss_m[t][k]!=0)
            {
                name=bilinmeyen[k];
                printf("  %c",sign);
                if(first){
                    printf("\b\b\b");
                    first=0;
                }
                printf(" %d%c",gauss_m[t][k],names[name]);
                sign=' ';
                buldum=1;
            }
        }
        if(buldum)
            printf("  =  %d\n\n",b[t]);
    }
    harekete(roads);
    getch();

    return 0;


}
/*


*/
/*
function for swapping rows when necessary

*/
void swap_rows(int *row1,int *row2,int *right_b,int r1,int r2,int number)
{
    int i,j,temp;

    for(int i=0; i<number; i++)
    {
        temp=row1[i];
        row1[i]=row2[i];
        row2[i]=temp;
    }
    temp=right_b[r1];
    right_b[r1]=right_b[r2];
    right_b[r2]=temp;
    printf("\n# R%d <-----> R%d",r1+1,r2+1);
}//end or function

/*


function for swapping rows when necessary


*/
void sifirla_rows(int *rowdegisen,int *rowdegismeyen,int *right_b,int r1,int r2,int number,int flag)
{
    int i,j,toplam;

    for(int i=0; i<number; i++)
    {
        if(flag==1)
        {
            toplam=rowdegisen[i]+rowdegismeyen[i];
            rowdegisen[i]=toplam;
        }
        if(flag==2)
        {
            toplam=rowdegisen[i]-rowdegismeyen[i];
            rowdegisen[i]=toplam;
        }
    }
    if(flag==1)
    {
        toplam=right_b[r1]+right_b[r2];
        right_b[r1]=toplam;
        printf("\n# R%d=R%d + R%d",r1+1,r1+1,r2+1);
    }
    if(flag==2)
    {
        toplam=right_b[r1]-right_b[r2];
        right_b[r1]=toplam;
        printf("\n# R%d=R%d - R%d",r1+1,r1+1,r2+1);
    }
}//end or function

/*function to scale a matrix row*/

void scale(int *row,int *right_b,int r,int number,int hangi)
{
    int i,changewith;
    changewith=row[hangi];
    if(changewith==-1)
    {
        for(int i=0; i<number; i++)
        {
            row[i]*=changewith;
        }
        right_b[r]*=changewith;
        printf("\n# R%d=R%d * %d",r+1,r+1,changewith);
    }
}//end or function
/*function to display a matrix on the screen*/
void yazdir(int *matris,int *b,int n)
{
    printf("\n\n\n\n");
    int t,k,nere=0,nereb=0;
    for(t=0; t<5; t++)
    {
        nere=t*n;
        for(k=0; k<n; k++)
        {
            printf("     %d     ",*(matris+nere+k));
        }
        printf("     =====%d\t\n\n\n\n",b[t]);
    }

}

/*
YOLLAR CIZME FONKSIYONU
*/
void yoluciz(int kacinci)
{
    /*
    1 A YOLLARI SECIM OLMADAN
    2 B YOLLARI SECIM OLMADAN
    3 A YOLLARI SECIM OLDUKTAN SONRA
    4 B YOLLARI SECIM OLDUKTAN SONRA

    */

    int x=getmaxx();
    int y=getmaxy();
    int current_x,current_y;

    int circle_x,circle_y,radius_o,radius_i;

    if(kacinci==2)//IKINCI YOLU SECILMIS
    {
        settextstyle(9,HORIZ_DIR,2);
        outtextxy(getmaxx()/2+50,50, "IKINCI YOL");
        circle_x=3*(getmaxx()/4);
        circle_y=getmaxy()/2+50;
        radius_o=200;
        radius_i=100;
        current_x=circle_x;
        current_y=circle_y;
    }
    if(kacinci==1)//BIRINCI YOL ICIN
    {
        settextstyle(9,HORIZ_DIR,2);
        outtextxy(50,50, "BIRINCI YOL");
        circle_x=getmaxx()/4;
        circle_y=getmaxy()/2+50;
        radius_o=200;
        radius_i=100;


        current_x=circle_x;
        current_y=circle_y;

    }

    if(kacinci==3||kacinci==4)
    {
        setfillstyle(SOLID_FILL,7);
        settextstyle(9,HORIZ_DIR,2);
        circle_x=getmaxx()/2;
        circle_y=getmaxy()/2+50;
        radius_o=200;
        radius_i=100;
        circle(circle_x,circle_y,radius_o);
        circle(circle_x,circle_y,radius_i);
        floodfill(circle_x+radius_i,(circle_y+radius_i),15);
        current_x=circle_x;
        current_y=circle_y;
    }
    if(kacinci==4)//IKINCI YOLU SECILMIS
    {
        outtextxy(50+getmaxx()/3,50, "IKINCI YOL SECILDI");
        bar((current_x-300),(current_y-50),(current_x+300),(current_y+50));//LEFT-CENTRE-RIGTH
        yollar[0].x=current_x-250;
        yollar[0].y=current_y;

        yollar[2].x=current_x+250;//RIGHT
        yollar[2].y=current_y;

        yollar[8].x=current_x;//T
        yollar[8].y=current_y;
        outtextxy(yollar[8].x,yollar[8].y,"T");
    }
    if(kacinci==3)//BIRINCI YOL SECILMIS
    {
        outtextxy(50+getmaxx()/3,50, "BIRINCI YOL SECILDI");
        bar((current_x-300),(current_y-50),(current_x-100),(current_y+50));//LEFT
        yollar[0].x=current_x-250;
        yollar[0].y=current_y;

        bar((current_x+100),(current_y-50),(current_x+300),(current_y+50));//RIGHT
        yollar[2].x=current_x+250;
        yollar[2].y=current_y;
    }

    radius_o=200;
    radius_i=100;
    circle(circle_x,circle_y,radius_o);
    circle(circle_x,circle_y,radius_i);
    if(kacinci==1||kacinci==2)
    {
        floodfill(circle_x+radius_i,(circle_y+radius_i),4);
    }
    bar((current_x-50),(current_y-300),(current_x+50),(current_y-100));//TOP
    yollar[1].x=current_x;
    yollar[1].y=current_y-250;

    bar((current_x-50),(current_y+100),(current_x+50),(current_y+300));//BOTTOM
    yollar[3].x=current_x;
    yollar[3].y=current_y+250;

    yollar[4].x=current_x-115;//W
    yollar[4].y=current_y-115;

    yollar[5].x=current_x+115;//X
    yollar[5].y=current_y-115;

    yollar[6].x=current_x+115;//Y
    yollar[6].y=current_y+115;

    yollar[7].x=current_x-115;//Z
    yollar[7].y=current_y+115;

    if(kacinci==1)
    {
        bar((current_x-300),(current_y-50),(current_x-100),(current_y+50));//LEFT
        yollar[0].x=current_x-250;
        yollar[0].y=current_y;
        bar((current_x+100),(current_y-50),(current_x+300),(current_y+50));//RIGHT
        yollar[2].x=current_x+250;
        yollar[2].y=current_y;
        current_x=getmaxx()/2;
        bar(current_x-2,0,current_x+2,getmaxy());
    }
    if(kacinci==2)//IKINCI
    {
        bar((current_x-300),(current_y-50),(current_x+300),(current_y+50));//LEFT-CENTRE-RIGTH
        yollar[0].x=current_x-250;
        yollar[0].y=current_y;
        yollar[2].x=current_x+250;//RIGHT
        yollar[2].y=current_y;

        yollar[8].x=current_x;//T
        yollar[8].y=current_y;
        outtextxy(yollar[8].x,yollar[8].y,"T");
    }
    current_x=getmaxx()/2;

    settextstyle(9,HORIZ_DIR,2);
    outtextxy(yollar[0].x,yollar[0].y,"A");
    outtextxy(yollar[1].x,yollar[1].y,"B");
    outtextxy(yollar[2].x,yollar[2].y,"C");
    outtextxy(yollar[3].x,yollar[3].y,"D");
    outtextxy(yollar[4].x,yollar[4].y,"W");
    outtextxy(yollar[5].x,yollar[5].y,"X");
    outtextxy(yollar[6].x,yollar[6].y,"Y");
    outtextxy(yollar[7].x,yollar[7].y,"Z");
    outtextxy(yollar[7].x,yollar[7].y,"Z");
}
/*
END OF  DRAW ROADS FUNCTIONS
*/
/*
YON HAREKETLENDIRME FONKSIYONU
*/
void yon_hareketi(int x,int y,int hangisi)
{
    int ax,ay;
    ax=x;
    ay=y-20;

    /*
    0 LEFT-RIGHT
    1 RIGHT -LEFT
    2 TOP-BOTTOM
    3 BOTTOM-TOP
    4 -RIGHTTOP
    5 -LEFTBOTTOM
    6 -RIGHTBOTTOM
    7 -LEFTTOP

    */
    moveto(ax,ay);
    int cro,pro;
    cro=ax;
    pro=ay;
    /*
    LEFT-RIGHT
    */
    setlinestyle(1,2,6);
    int howlong=0;
    if(hangisi==0)
    {
        while(howlong<=20)
        {
            linerel(ARROW_SIZE*(howlong%2),0);
            //outtextxy(cro,pro,">");
            delay(50);
            //cro+=ARROW_SIZE*(howlong%2);
            howlong++;
        }
        linerel(-ARROW_SIZE,-ARROW_SIZE);
        linerel(0,2*ARROW_SIZE);
        linerel(ARROW_SIZE,-ARROW_SIZE);
    }
    /*
    RIGHT-LEFT
    */
    else if(hangisi==1)
    {
        while(howlong<=20)
        {
            linerel(-ARROW_SIZE*(howlong%2),0);
            delay(50);
            howlong++;
        }
        //linerel(-ARROW_SIZE*4,0);
        linerel(2*ARROW_SIZE,-1*ARROW_SIZE);
        linerel(0,2*ARROW_SIZE);
        linerel(-2*ARROW_SIZE,-ARROW_SIZE);
    }
    /*
    TOP-BOTTOM
    */
    else if(hangisi==2)
    {
        while(howlong<=20)
        {
            linerel(0,ARROW_SIZE*(howlong%2));
            delay(50);
            howlong++;
        }
        //linerel(0,ARROW_SIZE*4);
        linerel(-1*ARROW_SIZE,-2*ARROW_SIZE);
        linerel(2*ARROW_SIZE,0);
        linerel(-ARROW_SIZE,2*ARROW_SIZE);
    }
    /*
    BOTTOM-TOP
    */
    else if(hangisi==3)
    {
        while(howlong<=20)
        {
            linerel(0,-ARROW_SIZE*(howlong%2));
            delay(50);
            howlong++;
        }
        //linerel(0,-ARROW_SIZE*4);
        linerel(-1*ARROW_SIZE,2*ARROW_SIZE);
        linerel(2*ARROW_SIZE,0);
        linerel(-ARROW_SIZE,-2*ARROW_SIZE);
    }
    /*
    -RIGHTTOP
    */
    else if(hangisi==4)
    {

        ax=x-20;
        ay=y+25;
        moveto(ax,ay);
        while(howlong<=20)
        {
            linerel(ARROW_SIZE*(howlong%2),-ARROW_SIZE*(howlong%2));
            delay(50);
            howlong++;
        }
        //linerel(ARROW_SIZE*4,-ARROW_SIZE*4);
        linerel(-1*ARROW_SIZE,0);
        linerel(1*ARROW_SIZE,1*ARROW_SIZE);
        linerel(0,-ARROW_SIZE);
    }
    /*
    -LEFTBOTOM
    */
    else if(hangisi==5)
    {
        ax=x+20;
        ay=y-25;
        moveto(ax,ay);
        while(howlong<=20)
        {
            linerel(-ARROW_SIZE*(howlong%2),ARROW_SIZE*(howlong%2));
            delay(50);
            howlong++;
        }
        //linerel(-ARROW_SIZE*4,ARROW_SIZE*4);
        linerel(0,-1*ARROW_SIZE);
        linerel(1*ARROW_SIZE,1*ARROW_SIZE);
        linerel(-ARROW_SIZE,0);
    }
    /*
    -RIGHTBOTTOM
    */
    else if(hangisi==6)
    {
        ax=x-10;
        ay=y-35;
        moveto(ax,ay);
        while(howlong<=20)
        {
            linerel(ARROW_SIZE*(howlong%2),ARROW_SIZE*(howlong%2));
            delay(50);
            howlong++;
        }
        //linerel(ARROW_SIZE*4,ARROW_SIZE*4);
        linerel(0,-1*ARROW_SIZE);
        linerel(-1*ARROW_SIZE,1*ARROW_SIZE);
        linerel(ARROW_SIZE,0);
    }
    /*
    -LEFTTOP
    */
    else if(hangisi==7)
    {
        ax=x;
        ay=y;
        moveto(ax,ay);
        while(howlong<=20)
        {
            linerel(-ARROW_SIZE*(howlong%2),-ARROW_SIZE*(howlong%2));
            delay(50);
            howlong++;
        }
        //linerel(-ARROW_SIZE*4,-ARROW_SIZE*4);
        linerel(0,ARROW_SIZE);
        linerel(ARROW_SIZE,-ARROW_SIZE);
        linerel(-ARROW_SIZE,0);
    }
}
/*
END OF YON_HAREKETI
*/
/*
DETERMINE WHAT KING OF MOVE THE ARROW WILL MAKE
*/
int hangihareket(int index,int direction)
{
    int hareketturu;
    if(index==0)//ROAD A
    {
        if(direction==1)
            hareketturu=0;//LEFT-TO-RIGHT
        else
            hareketturu=1;
    }
    if(index==1)//ROAD B
    {
        if(direction==1)
            hareketturu=2;//TOP TO BOTTOM
        else
            hareketturu=3;
    }
    if(index==2)//ROAD C
    {
        if(direction==1)
            hareketturu=1;//RIGHT TO LEFT
        else
            hareketturu=0;
    }
    if(index==3)//ROAD D
    {
        if(direction==1)
            hareketturu=3;//BOTTOM TO TOP
        else
            hareketturu=2;
    }
    if(index==4)//ROAD W
    {
        if(direction==1)
            hareketturu=4;//RIGHTTOP
        else
            hareketturu=5;
    }
    if(index==5)//ROAD X
    {
        if(direction==1)
            hareketturu=6;//RIGHTBOTTOM
        else
            hareketturu=7;
    }
    if(index==6)//ROAD Y
    {
        if(direction==1)
            hareketturu=5;//LEFTBOTTOM
        else
            hareketturu=4;
    }
    if(index==7)//ROAD Z
    {
        if(direction==3)
            hareketturu=6;//RIGHTBOTTOM
        else
            hareketturu=7;
    }
    if(index==8)//ROAD T
    {
        if(direction==2)
            hareketturu=0;//LEFT-TO-RIGHT
        else
            hareketturu=1;
    }
    return hareketturu;
}
/*
END OF HAREKETTURU
*/

/*
SET ALL ON MOVE
*/
void harekete(int roads)
{
    int i,current_color=7;
    while(current_color==7)
        current_color=(rand()%14)+1;
    setcolor(current_color);
    for(i=0; i<roads; i++)
    {
        yon_hareketi(yollar[i].x,yollar[i].y,yollar[i].hareket);
    }
    while(!kbhit())
    {
        harekete(roads);
    }
}
/*
HAREKETLE
*/
