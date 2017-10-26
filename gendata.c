#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define getSRand()      ( ( double ) rand( ) / ( double ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

#define SQR( x ) ( (x) * (x) )

// Calculate the Euclidean distance between two points.
int distance( int x1, int y1, int x2, int y2 )
{
   return ( int )sqrt( (double)SQR( ( x2 - x1 ) ) + (double)SQR( ( y2 - y1 ) ) );
}

#define MAX_POINTS  600

void genDataPoint( int basex, int basey, int range, int color )
{
   int  x,  y;
   int cx, cy;

   cx = basex + 250;
   cy = basey + 250;

   x = basex + 50 + getRand( 400 );
   y = basey + 50 + getRand( 400 );

   if ( distance(x,y,cx,cy) < range )
   {
      printf( "%d %d 0\n", x, y );
   }

   return;
}

int main( void )
{
   int cluster1Range = getRand( 100 );
   int cluster2Range = getRand( 300 );
   int cluster3Range = getRand( 400 );

   srand( time( NULL ) );

   for ( int i = 0 ; i < MAX_POINTS ; i+=3 )
   {
      genDataPoint(   0,   0, 150 + cluster1Range, 0 );
      genDataPoint(   0, 500, 100 + cluster2Range, 1 );
      genDataPoint( 500, 250, 200 + cluster3Range, 2 );
   }

   return 0;
}


