#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct observation
{
   int    x;
   int    y;
   int class;
} observation;

typedef struct centroid
{
   double x;
   double y;
} centroid;

#define MAX_SAMPLES    600
#define K                3

#define SQR( x )       ( double ) ( (x) * (x) )

#define getSRand()      ( ( double ) rand( ) / ( double ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

centroid Centroids[ K ];
observation Observations[ MAX_SAMPLES ];

int Read_Dataset( char *filename )
{
   FILE *fin = fopen( filename, "r" );
   int  Index=0;

   while ( !feof( fin ) )
   {
      fscanf( fin, "%d %d %d\n", 
                        &Observations[ Index ].x, 
                        &Observations[ Index ].y, 
                        &Observations[ Index ].class );
      Index++;
   }

   fclose( fin );

   return Index;
}

void Write_Dataset( int Samples )
{
   for ( int i = 0 ; i < Samples ; i++ )
   {
      printf("%d %d %d\n", 
         Observations[ i ].x, Observations[ i ].y, Observations[ i ].class );
   }

   return;
}

void Assignment( int Samples )
{
   void UpdateCentroids( int Samples );

   // Assign each observation to a random cluster.
   for ( int Target = 0 ; Target < Samples ; Target++ )
   {
      Observations[ Target ].class = getRand( K );
   }

   UpdateCentroids( Samples );

   return;
}

// Calculate the Euclidean distance between two points.
double distance( int x1, int y1, int x2, int y2 )
{
   return sqrt( SQR( ( x2 - x1 ) ) + SQR( ( y2 - y1 ) ) );
}


int FindNearestCluster( int Index )
{
   int    NearestCluster;
   double Closest;

   // Initialize with the first cluster
   NearestCluster = 0;
   Closest = distance( (double)Observations[ Index ].x, 
                       (double)Observations[ Index ].y, 
                        Centroids[ NearestCluster ].x,
                        Centroids[ NearestCluster ].y );

   // Now test against the other K-1
   for ( int Cluster = 1 ; Cluster < K ; Cluster++ )
   {
      double Distance;
      Distance = distance( (double)Observations[ Index ].x, 
                           (double)Observations[ Index ].y, 
                            Centroids[ Cluster ].x,
                            Centroids[ Cluster ].y );

      if ( Distance < Closest )
      {
         Closest = Distance;
         NearestCluster = Cluster;
      }
   }

   return NearestCluster;
}

void UpdateCentroids( int Samples )
{
   int MembershipCount[ K ];

   // Initialize the clusters
   for ( int Cluster = 0 ; Cluster < K ; Cluster++ )
   {
      Centroids[ Cluster ].x = 0.0;
      Centroids[ Cluster ].y = 0.0;
      MembershipCount[ Cluster ] = 0;
   }

   // Update the cluster centroids
   for ( int Index = 0 ; Index < Samples ; Index++ )
   {
      Centroids[ Observations[ Index ].class ].x += (double)Observations[ Index ].x;
      Centroids[ Observations[ Index ].class ].y += (double)Observations[ Index ].y;
      MembershipCount[ Observations[ Index ].class ]++;
   }

   // Update centroids to average based upon the number of members.
   for ( int Cluster = 0 ; Cluster < K ; Cluster++ )
   {
      if ( MembershipCount[ Cluster ] > 1 )
      {
         Centroids[ Cluster ].x /= (double)MembershipCount[ Cluster ];
         Centroids[ Cluster ].y /= (double)MembershipCount[ Cluster ];
      }
   }

   return;
}


int Update( int Samples )
{
   int Moved = 0;

   for ( int Index = 0 ; Index < Samples ; Index++ )
   {
      int NearestClass = FindNearestCluster( Index );

      if ( NearestClass != Observations[ Index ].class )
      {
         // Change the membership of this observation to the new cluster.
         Observations[ Index ].class = NearestClass;
         Moved++;
      }

   }

   UpdateCentroids( Samples );

   return Moved;
}

int main( int argc, char *argv[] )
{
   int Samples;

   if ( argc != 2 )
   {
      printf( "Usage is %s <observations_file>\n\n", argv[0] );
      return 0;
   }

   srand( time( NULL ) );

   // Read the input dataset from the file.
   Samples = Read_Dataset( argv[1] );

   // Assignment step, initialize observations to clusters.
   Assignment( Samples );

   // Update step, continue to perform until convergence.
   while ( Update( Samples ) );

   // Write the dataset back out.
   Write_Dataset( Samples );

   return 0;
}


