

#include <stdio.h>
#include <math.h>

struct vert{
   double angle;
   int index;
};

int absI(int i)
{
   if (i < 0) return -1 * i;
   return i;
}

double minD(double a, double b)
{
   if (a < b) return a;
   return b;
}

int main()
{
   // The graph should never have more than 42 nodes 
   double graph [42][42];
   struct vert verts[11][20];
   int nVert [11];
   int radii[11];

   // Lets use a nice infiniti value and PI value
   double oo = 987654321.0;
   double PI = 3.141592653589793;

   int t;

   FILE * in = stdin;

   // Go through each test case
   fscanf(in, "%d", &t);
   for (int c=1; c<=t; c++)
   {
      int circles, roads;
      fscanf(in, "%d", &circles);
      fscanf(in, "%d", &roads);

      // Go through the entire graph and fill infiniti
      for (int i=0; i<50; i++)
         for (int j=0; j<50; j++)
            graph[i][j] = oo;

      // Go through each vertex list resetting the size
      for (int i=0; i<11; i++)
         nVert[i] = 0;

      // Read in each of the radii values
      for (int i=1; i<=circles; i++)
      {
         int temp;
         fscanf(in, "%d", &temp);
         radii[i] = temp;
      }

      // Read in each vertex
      int numVerts=0;
      for (int r=0; r<roads; r++)
      {
         int level;
         int angle;
         fscanf(in, "%d", &level);
         fscanf(in, "%d", &angle);

         // When saving nodes note we keep an index
         // we assign to each end of a straight road
         // We use these verticies to form a graph
         // of the entire map of ucf

         // Save the first new node we have
         int loc = nVert[level];
         verts[level][loc].angle = angle;
         verts[level][loc].index = numVerts;
         nVert[level]++;
         numVerts++;

         // Save the second new node we have
         level++;
         loc = nVert[level];
         verts[level][loc].angle = angle;
         verts[level][loc].index = numVerts;
         nVert[level]++;
         numVerts++;
      
         // Get the distance we need to travel, the distance for side
         // roads is just the radius of the larger circle minus the
         // radius of the smaller circle
         double dist = radii[level] - radii[level-1];

         // Connect the two indecies remember side roads go both ways
         graph[numVerts-1][numVerts-2] = dist;
         graph[numVerts-2][numVerts-1] = dist;
      }

      // Add the nodes for start and finish
      int sc, sa, si, fc, fa, fi;
      fscanf(in, "%d %d %d %d", &sc, &sa, &fc, &fa);

      // Add the starting node
      int loc = nVert[sc];
      verts[sc][loc].angle = sa;
      si = verts[sc][loc].index = numVerts;
      nVert[sc]++;
      numVerts++;
      
      // Add the finishing node
      loc = nVert[fc];
      verts[fc][loc].angle = fa;
      fi = verts[fc][loc].index = numVerts;
      nVert[fc]++;
      numVerts++;

      // Add the level connections for each level
      // This code connects each node connections with
      // all other connects on each level!
      for (int i=1; i<=circles; i++)
      {
         for (int j=0; j<nVert[i]; j++)
         {
            for (int k=j+1; k<nVert[i]; k++)
            {
               // We calculate the angle first by taking the absolute value
               // of the angle between the two nodes we are given
               int finalAngle = absI(verts[i][j].angle - verts[i][k].angle);
               
               // Then we find which is quicker going left or going right
               // we can do this by getting the other angle with some trig
               // the other angle equals 360 - the first angle
               finalAngle = minD(finalAngle, 360 - finalAngle);
               
               // Now we use the arc length formula to find the distance
               // between the two nodes, to use arc length we first convert
               // the angles into radians, then we use the formula 
               // angle * radius to get the arc length of our path
               double ffAngle = PI*(finalAngle/180.0);
               double len = ffAngle * radii[i];
               
               // Now we set that length for our path, remember we can
               // go boths ways down the road so save both edges!
               int index1 = verts[i][j].index;
               int index2 = verts[i][k].index;
               graph[index1][index2] = len;
               graph[index2][index1] = len;
            }
         }
      }

      // Run Floyd's, its a shortest path algorithm thats easy to code,
      // look it up! it will find the shortest path between all points in 
      // the graph in O(n^3) time and is very handy in contest programming
      for (int k=0; k<numVerts; k++)
      {
         for (int i=0; i<numVerts; i++)
         {
            for (int j=0; j<numVerts; j++)
            {
               if (graph[i][j] > (graph[i][k] + graph[k][j]))
                  graph[i][j] = graph[i][k] + graph[k][j];
            }
         }
      }

      // Print our result which is the dist start to finish!
      // Round the output appropriately, so that we get correct results
      printf("%.2lf\n", graph[si][fi]);
   }

   return 0;
}
