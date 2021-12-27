/* Problem: framing
 * Problem Solver: Michael Do
 * Date: 5/7/10
 */
#include <stdio.h>
#include <math.h>

int main(){
 
   FILE *in;
   int numGroups, numPeople, numFrames;
   int curGroup, curPerson, curFrame;
   double delta, area, sin45;
   double l, w, d;
   
   // Calculate the sin of 45 degrees ( 1 / rt(2) is equivalent)
   sin45 = 1 / sqrt(2.0);
   
   in = stdin;
 
   fscanf(in, "%d", &numGroups);

   // For each group
   for(curGroup = 1;curGroup <= numGroups;curGroup++){
      fscanf(in, "%d", &numPeople);
      area = 0;
      
      // For each person
      for(curPerson = 0;curPerson < numPeople;curPerson++){
         
         fscanf(in, "%d", &numFrames);      
         
         // For each frame
         for(curFrame = 0;curFrame < numFrames;curFrame++){
       
            // Read in input
            fscanf(in, "%lf %lf %lf", &l, &w, &d);
            
            // Calculate delta, the amount of vertical and horizontal
            // increase made by the frame, which is the product of 
            // sin 45 degrees and the diagonal.
            delta = sin45*d;

            // Calculate the area of the rectangle with the frame, and subtract
            // out the area of the picture. Because the depth is 1, the value
            // for area and volume are equivalent. The dimensions of the frame
            // and picture are increased by 2*delta. Add that area.
            area += (l+2*delta)*(w+2*delta) - l*w;
         }
      }
      
      // Output
      printf("Group #%d: %.2lf cubic inches\n\n", curGroup, area);
   }
   return 0;
}
