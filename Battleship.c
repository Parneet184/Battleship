#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct coord
{
    int x;
    int y;

}coords;

int randgen(int **ships_ptr,int n)
{
    int i,j,count=0;
    srand((unsigned)time(NULL));

     for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            ships_ptr[i][j]=rand()%2;
            if(ships_ptr[i][j]==1)
            {
                count++;
            }
        }
    }
    return count;
}

void draw_gui(char **pseudo_gui_ptr,int n)
{
    int i,j;

    pseudo_gui_ptr[0][0]=' ';
    for(i=1;i<(n+1);i++)
    {
        pseudo_gui_ptr[0][i]=i+48;
        pseudo_gui_ptr[i][0]=i+48;
         }

    for(i=1;i<(n+1);i++)
     {
        for(j=1;j<(n+1);j++)
        {
            pseudo_gui_ptr[i][j]='~';
        }
    }
}

void battle(int **ships_ptr, char **pseudo_gui_ptr,int n, struct coord z,int* count,int* miss)
{

    int i,j;

     for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(z.x-1 == i && z.y-1 == j)
                {
                      if(ships_ptr[i][j]==1)
                    {
                        if(pseudo_gui_ptr[i+1][j+1]=='H')

                        {
                            printf("\nYou've already uncovered this field!\n");
                            break;
                        }
                        printf("\nHit!\n");
                        pseudo_gui_ptr[i+1][j+1]='H';
                        (*count)--;
                    }
                    else
                    {
                        if(pseudo_gui_ptr[i+1][j+1]=='M')
                        {
                            printf("\nYou've already uncovered this field!\n\n");
                            break;
                        }
                        printf("\nMiss!\n");
                        pseudo_gui_ptr[i+1][j+1]='M';
                        (*miss)++;
                    }

                }
            }
        }
        
}

void buff_clr(void)
{
    char junk;
    do{
        junk=getchar();
    }while(junk!='\n');
}

void result(char **pseudo_gui_ptr,int n)
{
    int i,j;

    for(i=0;i<(n+1);i++)
    {
        for(j=0;j<(n+1);j++)
        {
            printf("%6c",pseudo_gui_ptr[i][j]);
        }
        printf("\n\n");
    }
    }


int main(){

   int **ships;
   char **pseudo_gui;
   int i,j;
   int n;
   char switch_size,switch_difficulty;
   int difficulty=0;
   int shipcount=0;
   int x_count=0;


   printf("\n\n\t***Welcome  To  My  Battleship***\n\tBy Parneet Kaur (BTech CSE 1st sem)\n\n");
   printf("\t Sink the ships>>\n");

   printf("\nChoose size(S,M,L):");
   scanf("%c",&switch_size);

    buff_clr();

      switch(switch_size)
   {
       case 's':
       case 'S':n=3;break;
       case 'm':
       case 'M':n=5;break;
       case 'l':
       case 'L':n=8;break;
       default:printf("\nYou've choosen poorly!");
       exit(EXIT_FAILURE);
   }

   printf("\nChoose difficulty(E,H):");
   scanf("%c",&switch_difficulty);
//    buff_clr();

   switch(switch_difficulty)
   {
       case 'e':
       case 'E':difficulty=(n*2)-2;break;
       case 'h':
       case 'H':difficulty=(n/2);break;
       default:printf("\nYou've choosen poorly!");
               exit(EXIT_FAILURE);
   }

   ships=(int**)malloc(n*sizeof(int*));

   for(i=0;i<n;i++)
   {
       ships[i]=(int*)malloc(n*sizeof(int));
   }

   pseudo_gui=(char**)malloc((n+1)*sizeof(char*));

   for(i=0;i<(n+1);i++)
   {
       pseudo_gui[i]=(char*)malloc((n+1)*sizeof(char));
   }

   shipcount=randgen(ships,n);

   printf("\n\nNumber of ships to be sunk:%d",shipcount);
   printf("\nNumber of misses allowed: %d\n\n",difficulty);

   draw_gui(pseudo_gui,n);
   result(pseudo_gui,n);

   while(shipcount!=0 && x_count!=difficulty)
   {
   printf("\nEnter the Target (x,y):");
   scanf("%d,%d",&coords.x,&coords.y);
//    buff_clr();
    system("cls");

   battle(ships,pseudo_gui,n,coords,&shipcount,&x_count);
   result(pseudo_gui,n);

   printf("Number of ships to be sunk:%d",shipcount);
   printf("\nNumber of misses(out of %d): %d\n\n",difficulty,x_count);
   }

   if(shipcount==0)
   {
       printf("\nWinner!\n\n");
   }
   else if(x_count==difficulty)
   {
       printf("\nYou Lose!\n");
   }

   return 0;
}