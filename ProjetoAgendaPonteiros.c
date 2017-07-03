#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agenda
{
    int reg; 
    char nome[80]; 
    float nota; 
}agenda;

void aloca(agenda **p, int tam);
int verifica();
void grava(agenda *p);
void cadastro(agenda *p,int num);
void mostra(agenda *p);
void excluir(agenda *p);
void alterar(agenda *p,int num);

main()
{
      agenda *ag=NULL;
      int cont=0,op,qtde;
      aloca(&ag,1);
      
      
      
      do{
          system("CLS");
          printf("[1] - Cadastrar\n[2] - Excluir\n[3] - Alterar\n[4] - Mostra\n[5] - SAIR\n");
          scanf("%i",&op);
          fflush(stdin);
          
          switch(op)
          {
                    case 1:
                         qtde = verifica();
                         cadastro(ag,qtde);
                         break;
                    case 2:
                         excluir(ag);
                         break;
                    case 3:
                         qtde = verifica();
                         alterar(ag,qtde);
                         break;
                    case 4:
                         mostra(ag);
                         break;
          }
      }while(op!=5);
      
}

void excluir(agenda *p)
{
     int reg;
     FILE *fp=NULL;
 
     printf("Qual o registro a ser excluido?: ");
     scanf("%i",&reg);
     fflush(stdin);
     
     if((fp = fopen("agenda.bin","rb+")) == NULL)
     {
        printf("Erro");
     }
     else
     {
        fseek(fp,reg*sizeof(agenda),0);
        p->reg = -1;
        strcpy(p->nome,"@");  
        p->nota = -1;
        fwrite(p,sizeof(agenda),1,fp);
        fclose(fp);
 
     }
}
void alterar(agenda *p,int num)
{
     int reg;
     FILE *fp=NULL;
   
     printf("Qual o registro a ser alterado?: ");
     scanf("%i",&reg);
     fflush(stdin);
     reg-1;
     if((fp = fopen("agenda.bin","rb+")) == NULL)
     {
        printf("Erro");
     }
     else
     {
        fseek(fp,reg*sizeof(agenda),0);
        
        p->reg=num+1;
        printf("\nRegistro %i",p->reg);
        printf("\nNome: ");
        fflush(stdin);
        gets(p->nome);
        printf("Nota: ");
        scanf("%f",&p->nota);
        
        fwrite(p,sizeof(agenda),1,fp);
        fclose(fp);
 
     }
}




void mostra(agenda *p)
{
    int i;
    long int qtde;
    FILE *fp=NULL;
    qtde=verifica();
    system("cls");
    if((fp = fopen("agenda.bin","rb")) == NULL)
      {
      printf("Erro");
      }
    else
      {
          for(i=0;i<qtde;i++)
            {               
                fseek(fp,i*sizeof(agenda),0);                
                fread(p, sizeof(agenda),1, fp);
                printf("\nRegistro: %i", p->reg);  
                printf("\nNome: %s", p->nome); 
                printf("\nNota: %.2f\n",p->nota);
            }
            fclose(fp);
      }
      system("PAUSE");
}


void cadastro(agenda *p,int num)
{
    p->reg=num+1;
    printf("\nRegistro %i",p->reg);
    printf("\nNome: ");
    fflush(stdin);
    gets(p->nome);
    printf("Nota: ");
    scanf("%f",&p->nota);
    grava(p);
}

void aloca(agenda **p, int tam)
{
     if((*p=(agenda*)realloc(*p,tam*sizeof(agenda)))==NULL)
      exit(1);
 }
 
 void grava(agenda *p)
{
    FILE *fp=NULL;
    
    if((fp=fopen("agenda.bin","ab"))==NULL)
        {
            printf("erro na gravação");
        }
        else
        {
            fwrite(p,sizeof(agenda),1,fp);
            printf("Salvo com sucesso!");
        }
        fclose(fp);
        system("PAUSE");
}

int verifica()
{
    FILE *fp=NULL;
    long int pos=0;
    
    if((fp=fopen("agenda.bin","rb"))==NULL)
          printf("erro na gravação");
    else
      {
          fseek(fp,0,2);             
          pos=ftell(fp)/sizeof(agenda);
          fclose(fp);
      }
    return pos;
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
