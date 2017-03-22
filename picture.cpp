/*
 Svaki od trobitnih mikro-automata sa ulazom b = [b0 b1 b2] moze kao ulaz dobiti 2^3(8) razlicitih kombinacija ulaza,
 odnosno za svaki od ovih ulaza automat genrise izlaz (ukupno 8 izlaza),svaki automat ima jednu        kombinaciju za 8 izlaza,sto predsavlja jedno mikro-pravilo koje predstavlja jedan automat,od tih 8 izlaza moze se iskobinovati 2^8(256) razlicitih izlaza iz automata odnosno 256 razlicitih mikro-pravila

Najvise me fascinirala smimetrija slike koja se dobije sa mikroautomatom 130 koji daje fantasticanu strukturu trouglova simetricno poredjanih jedan u drugom      

*/
#include <iostream>
#include <stdlib.h>
using namespace std;

 typedef enum {BLACK = 0, WHITE} COLOR;
 //Stuktura jednog piksela
 typedef struct {

   COLOR color;
   int xPos;
   int yPos;

 } PIXEL;
 
 //Klasa koja predstavlja sliku
 class Picture 
 {
   private:

     int     dimX;
     int     dimY;
     char    n;
     PIXEL** picture;

   public:
     //Inicijalno svi pikseli crne boje sem u inicijalnom redu i srednjoj koloni gde je boja bela 
     Picture(int dim1,int dim2,char num):dimX(dim1),dimY(dim2),n((int)--num)
     {
        picture = new PIXEL* [dimY];
        for (int i = 0; i < dimX; i++)
        {
           *(picture + i) = new PIXEL [dimY];
           for (int j = 0; j < dimY; j++)
           {
             (*(picture + i) + j)->color = BLACK;
             (*(picture + i) + j)->xPos = i; 
             (*(picture + i) + j)->yPos = j;
           }
        }
        
        (*picture + (dimY/2 - 1))->color = WHITE;
     }
     //Generisanje mikro pravila
     COLOR microAutomat(PIXEL b2,PIXEL b1,PIXEL b0)
     {
       int shwn; // Broj bita koji predstavljaju broj puta za koji ce se maska shiftovati odnosno maskira  ulaznu kombinaciju  
       unsigned char mask = 0x80; //Maska

       if ( (b2.color == BLACK) && (b1.color == BLACK) && (b0.color == BLACK) )
       {
          shwn = 0;
       }
       
       if ( (b2.color == BLACK) && (b1.color == BLACK) && (b0.color == WHITE) )
       {
          shwn = 1;
       }

       if ( (b2.color == BLACK) && (b1.color == WHITE) && (b0.color == BLACK) )
       {
          shwn = 2;
       }

       if ( (b2.color == BLACK) && (b1.color == WHITE) && (b0.color == WHITE) )
       {
          shwn = 3;
       }

       if ( (b2.color == WHITE) && (b1.color == BLACK) && (b0.color == BLACK) )
       {
          shwn = 4;
       }

       if ( (b2.color == WHITE) && (b1.color == BLACK) && (b0.color == WHITE) )
       {
          shwn = 5;
       }

       if ( (b2.color == WHITE) && (b1.color == WHITE) && (b0.color == BLACK) )
       {
          shwn = 6;
       }

       if ( (b2.color == WHITE) && (b1.color == WHITE) && (b0.color == WHITE) )
       {
          shwn = 7;
       }
       
       mask >>= shwn;
       //Generisanje izlaza mikroautomata n je broj koji u svojim binarnim ciframa "krije" izlaz jednog mirko-pravila kojeg maskiramo u zavisnosti od ulaza
       if (mask & n)
       {
          return WHITE;
       } 
       else 
       {
          return BLACK;
       }

     }
     //Generisanje slike zadate dimenzije ivice sam "peglao" tako da piksel na pocetku kolone uzima piksele iznad i desno od njega a na kraju kolone da uzima piksele iznad njega i levo od njega
     void generateBinaryPicture()
     {
       int i,j;

       for (i = 1; i < dimX; i++)
       {
           for (j = 0;j < dimY; j++)
           {
             if (j == 0)
             {
               (picture[i][j]).color = microAutomat(picture[i-1][j],picture[i-1][j+1],picture[i-1][j+2]);  
             }
             else if (j == dimY-1)
             {
                (picture[i][j]).color = microAutomat(picture[i-1][j-2],picture[i-1][j-1],picture[i-1][j]); 
             }
             else 
             {
                (picture[i][j]).color = microAutomat(picture[i-1][j-1],picture[i-1][j],picture[i-1][j+1]);
             }
           }
       }
     }

     void printPicture()
     {
        int i,j;

        cout << endl << endl << endl;
        cout << "        				Picture " << endl << endl << endl << endl;


        for (i = 0; i < dimX; i++)
        {
           for (j = 0; j < dimY; j++)
           {
              if ( (picture[i][j]).color == WHITE)
              {
                 cout << "1";
              }
              else 
              {
                 cout << "0";
              }
           }
           cout << endl;
        }
     }
     
     ~Picture()
     {
        int i = 0;

        for (i = 0; i < dimX; i++)
        {
          delete [] *(picture + i);
        }

        delete [] picture;
     }

 };

int main(int argc , char *argv[]) 
{
   //Broj binarnog automata se zadaje kao argument komandne linije
   int N = atoi(argv[1]);

   Picture pic(51,100,N);

   pic.generateBinaryPicture();
   pic.printPicture();

   return 0;
} 
