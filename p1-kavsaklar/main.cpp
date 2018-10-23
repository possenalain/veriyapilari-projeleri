#include<stdio.h>

void swap_rows(int *row1,int *row2,int *right_b,int r1,int r2,int number);
void sifirla_rows(int *rowdegisen,int *rowdegismeyen,int *right_b,int r1,int r2,int number,int flag);
void scale(int *row,int *right_b,int r,int number,int hangi);

int main()
{
    int graph_window=0;//choose among the too
    int roads,dimy=5,dimx=4;
    char names[]= {'A','B','C','D','W','X','Y','Z','T'};
    roads=8;
    while(graph_window!=1&&graph_window!=2)
    {
        printf("\n\n Harita yi secin 1 ya da 2 :");
        scanf("%d",&graph_window);
    }
// when the last road is active too
    if(graph_window==2)
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
            if(denklem[4][j]>0&&deger[j]!=-1)
                girisler++;
            if(denklem[4][j]<0&&deger[i]==-1)
                cikisler++;
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

                if(((son-ilk!=1)&&(son-ilk!=-1)))//A---C C----D
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
                if(!gecerli) //the direction is valid
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
    CREATE THE FINE EQUATION READY FOR PROCESSING
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
    int x,y;
    printf("\n\n\n\ eselon haline getirecegiz\n\n\n\n");
//yazdirma
    for(x=0; x<5; x++)
    {
        for(y=0; y<bilinmeyen_sayisi; y++)
            printf("     %d     ",gauss_m[x][y]);

        printf("     =====%d\t\n\n\n\n",b[x]);
    }
// yadirma

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
//yazdirma
                    printf("\n\n\n\n");
                    for(x=0; x<5; x++)
                    {
                        for(y=0; y<bilinmeyen_sayisi; y++)
                            printf("     %d     ",gauss_m[x][y]);

                        printf("     =====%d\t\n\n\n\n",b[x]);
                    }
// yazdirma
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
//yazdirma
                            printf(" \n\n\n\n");
                            for(t=0; t<5; t++)
                            {
                                for(k=0; k<bilinmeyen_sayisi; k++)
                                    printf("     %d     ",gauss_m[t][k]);
                                printf("     =====%d\t\n\n\n\n",b[t]);
                            }
//yazdirma

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

//yazdirma
                                printf("\n\n\n\n");
                                int t,k;
                                for(t=0; t<5; t++)
                                {
                                    for(k=0; k<bilinmeyen_sayisi; k++)
                                        printf("     %d     ",gauss_m[t][k]);
                                    printf("     =====%d\t\n\n\n\n",b[t]);
                                }
//yazdirma
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

//yazdirma
                        printf("\n\n\n\n");
                        int t,k;
                        for(t=0; t<5; t++)
                        {
                            for(k=0; k<bilinmeyen_sayisi; k++)
                                printf("     %d     ",gauss_m[t][k]);

                            printf("     =====%d\t\n\n\n\n",b[t]);
                        }
//yazdirma
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
//yazdirma
                    printf("\n\n\n\n");
                    int t,k;
                    for(t=0; t<5; t++)
                    {
                        for(k=0; k<bilinmeyen_sayisi; k++)
                            printf("     %d     ",gauss_m[t][k]);

                        printf("     =====%d\t\n\n\n\n",b[t]);
                    }
//yazdirma

                }
                break;
            }
        }
    }
//yazdirma
    printf(" \n\n eselon indirgenmis hali\n\n");
    for(t=0; t<5; t++)
    {
        for(k=0; k<bilinmeyen_sayisi; k++)
            printf("     %d     ",gauss_m[t][k]);

        printf("     =====%d\t\n\n\n\n",b[t]);
    }
//yazdirma

    return 0;
}
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


