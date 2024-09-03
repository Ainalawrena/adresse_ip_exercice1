#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "address_ip.h"

void enter_msr(char *chaine1)
{
    printf("entrer le masque de sous reseau : ");
    scanf("%s",chaine1);
}

void valide()
{   
    int a=0,b=0,c=0,d=0,i;
    char chaine[100]="",chaine1[100]="";
    printf("entrer l'adresse ip (ex : 192.168.10.50) ");
    scanf("%s",chaine);
    char *token=strtok(chaine,".");
    if(token != NULL)
        a=atoi(token);
    token=strtok(NULL,".");
    if(token != NULL){
        b=atoi(token);
    }
     
    token=strtok(NULL,".");
    if(token != NULL){
        c=atoi(token);
    }
     
    token=strtok(NULL,".");
    if(token != NULL){
        d=atoi(token);
    }
    if(a<0 || a>255 || b<0 || b>255 || c<0 || c>255 || d<0 || d>255)
    {
        printf("==> invalide \n");
        exit(1);
    }
   
    else
    {
        enter_msr(chaine1);
        execution_msr(chaine1,chaine,a,b,c,d);
    }
}

void separe(char *chaine,int *a,int *b,int *c,int *d)
{   
    char *token=strtok(chaine,".");
    if(token != NULL){
        *a=atoi(token);
    }
     
    token=strtok(NULL,".");
    if(token != NULL){
        *b=atoi(token);
    }
     
    token=strtok(NULL,".");
    if(token != NULL){
        *c=atoi(token);
    }
     
    token=strtok(NULL,".");
    if(token != NULL){
        *d=atoi(token);
    }
}

int tableau(int *tab)
{
    int i,a=0,s=0,j=0;
    for(i=7 ; i>=0 ; i--)
    {
        a = pow(2,i);
        s = s+(tab[j]*a);
        j++;
    }
    return s;
}

void execution_msr(char *chaine,char *ip,int a1,int b1,int c1,int d1)
{   
    int a=0,b=0,c=0,d=0,i,e=0,f=0,g=0,h=0;
    //reto pour msr
    char chaine1[8]="",chaine2[8]="",chaine3[8]="",chaine4[8]="";
    //reto pour ip
    char chaine11[8]="",chaine22[8]="",chaine33[8]="",chaine44[8]="";
    //reverse anle msr
    char reverse_msr1[8]="",reverse_msr2[8]="",reverse_msr3[8]="",reverse_msr4[8]="";
    //reto pour reseau
    int reseau1[8],reseau2[8],reseau3[8],reseau4[8];
    //reto pour broadcast
    int board1[8],board2[8],board3[8],board4[8];
    int total[32], boardcast[32];                             //apifampitohizana anle msr bedebe
    //separe(ip,)
    separe(chaine,&a,&b,&c,&d);                                //misepare an msr
    printf("separer : %d.%d.%d.%d\n",a,b,c,d);
    decimal(a,chaine1);
    decimal(b,chaine2);
    decimal(c,chaine3);
    decimal(d,chaine4);
    for(i=0 ; i<8 ; i++)                                        //eto le mapitohy teo
    {
        total[i] = chaine1[i] - '0';
        total[i+8] = chaine2[i] - '0';
        total[i+16] = chaine3[i]- '0';
        total[i+24] = chaine4[i]-'0';
    }
    condition(total,a1,b1,c1,d1,chaine11,chaine22,chaine33,chaine44);
    for(i=0 ; i<8 ; i++)
    {
        reseau1[i] = (chaine1[i] -'0' ) * (chaine11[i] - '0');
        reseau2[i] = (chaine2[i] -'0' ) * (chaine22[i] - '0');
        reseau3[i] = (chaine3[i] -'0' ) * (chaine33[i] - '0');
        reseau4[i] = (chaine4[i] -'0' ) * (chaine44[i] - '0');
    }
    e=tableau(reseau1);
    f=tableau(reseau2);
    g=tableau(reseau3);
    f=tableau(reseau4);
    printf("\n\tadresse reseau : %d.%d.%d.%d\n",e,f,g,h);
    board(total,boardcast);
    for(i = 0; i < 8; i++)
    {
        reverse_msr1[i] = '0' + boardcast[i];
        reverse_msr2[i] = '0' + boardcast[i + 8];
        reverse_msr3[i] = '0' + boardcast[i + 16];
        reverse_msr4[i] = '0' + boardcast[i + 24];
    }
    for(i = 0 ; i < 8 ; i++)
    {
        board1[i] = (reverse_msr1[i] - '0') | (chaine11[i] - '0');
        board2[i] = (reverse_msr2[i] - '0') | (chaine22[i] - '0');
        board3[i] = (reverse_msr3[i] - '0') | (chaine33[i] - '0');
        board4[i] = (reverse_msr4[i] - '0') | (chaine44[i] - '0');
    } 
    printf("\t--------------------------------------\n");    
    printf("\tadresse broadcast : %d.%d.%d.%d\n",tableau(board1),tableau(board2),tableau(board3),tableau(board4));
}

void decimal(int x,char *chaine)
{
    int i,a=0,b=0;
    for(i=7 ; i>=0 ; i--)
    {
        a=pow(2,i);
        if(x>=a)
        {   
            b=x-a;
            x=b;
            strcat(chaine,"1");
        }
        else 
        {
            strcat(chaine,"0");
        }
    }
}

void condition(int *total,int a,int b,int c,int d,char *chaine1,char *chaine2,char *chaine3,char *chaine4)
{
    int i,val,compteur=0;
    if(total[0]==0)
    {
        printf("\n==> msr invalide\n");
        exit(1);
    }
    else
    {
        for(i=0 ; i<32 ; i++)
        {
            if(total[i]==1){
                compteur++;
            }
            else
                break;
        }
        for(i=compteur+1 ; i<32 ; i++)
        {
            if(total[i]==1)
            {
                val=0;
            }
            else 
                val=1;
        }
        if(val==0)
        {
            printf("\n==> msr invalide\n");
            exit(1);
        }
        else
            printf("\n==> msr valide\n");
            decimal(a,chaine1);
            decimal(b,chaine2);
            decimal(c,chaine3);
            decimal(d,chaine4);
    }
}
void board(int *total,int *boardcast)
{
    int i;
    for(i=0 ; i<32 ; i++)
    {
        if(total[i] == 0)
            boardcast[i] = 1;
        else if(total[i] == 1)
            boardcast[i] = 0;  
    }
}
