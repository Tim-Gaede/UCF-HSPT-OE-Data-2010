
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define PI  3.14159265359


struct Street
{
   int   level;
   int   angle;
};


int  windowWidth, windowHeight;

FILE *   inputFile;
int      numMaps;
int      mapNumber;
int      circles[16];
int      numCircles;
Street   streets[32];
int      numStreets;
int      startCircle, startAngle;
int      finishCircle, finishAngle;


void drawCircle(int width, int height, int radius)
{
   int      dimension;
   int      max;
   double   factor;
   int      numVerts;
   float    verts[1024];
   int      i;

   // Maximum radius circle
   max = circles[numCircles - 1];

   // Convert the radius to a fraction of the largest circle's radius
   factor = (double) radius / (double) max;

   // Figure out the longer window dimension
   if (width > height)
      dimension = height - 20;
   else
      dimension = width - 20;

   // 256 verts in the largest circle, proportionally fewer on the smaller
   // ones
   numVerts = factor * 256;
   if (numVerts < 16)
      numVerts = 16;
   if (numVerts > 256)
      numVerts = 256;

   for (i = 0; i < numVerts*2; i++)
   {
      verts[i*2] = factor * (dimension/2) *
                       cos( (2.0 * PI) * ((double) i / numVerts) );
      verts[i*2+1] = factor * (dimension/2) *
                       sin( (2.0 * PI) * ((double) i / numVerts) );
   }

   glColor3f(0.0, 0.7, 0.7);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, 0, verts);
   glDrawArrays(GL_LINE_LOOP, 0, numVerts);
   glDisableClientState(GL_VERTEX_ARRAY);
}


void reshape(int width, int height)
{
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glDisable(GL_DEPTH_TEST);

   windowWidth = width;
   windowHeight = height;
}


void display()
{
   int     max;
   int     dimension;
   int     i;
   int     level;
   double  factor;
   float   streetVerts[128];
   float   startX, startY;
   float   finishX, finishY;

   // Clear the screen
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);

   glPointSize(10.0);
   glEnable(GL_POINT_SMOOTH);
   glLineWidth(3.0);
   glEnable(GL_LINE_SMOOTH);

   // Bail if no circles
   if (numCircles <= 0)
      return;

   for (i = 0; i < numCircles; i++)
   {
      drawCircle(windowWidth, windowHeight, circles[i]);
   }

   // Maximum radius circle
   max = circles[numCircles - 1];

   // Figure out the longer window dimension
   if (windowWidth > windowHeight)
      dimension = windowHeight - 20;
   else
      dimension = windowWidth - 20;

   if (numStreets > 0)
   {
      for (i = 0; i < numStreets; i++)
      {
         // Figure out at which circle the street begins
         level = abs(streets[i].level) - 1;

         // Convert the circle's radius to a fraction of the largest circle
         factor = (double) circles[level] / max;

         // Calculate the starting coordinates
         streetVerts[i*4+0] = factor * (dimension/2) *
                                cos( (double) streets[i].angle * PI / 180.0);
         streetVerts[i*4+1] = factor * (dimension/2) *
                                sin( (double) streets[i].angle * PI / 180.0);

         // Figure out to which circle the street connects
         if (streets[i].level > 0)
            level++;
         else
            level--;

         // Convert the circle's radius to a fraction of the largest circle
         factor = (double) circles[level] / max;

         // Calculate the ending coordinates
         streetVerts[i*4+2] = factor * (dimension/2) *
                                cos( (double) streets[i].angle * PI / 180.0);
         streetVerts[i*4+3] = factor * (dimension/2) *
                                sin( (double) streets[i].angle * PI / 180.0);
      }

      // Draw the streets
      glColor3f(1.0, 1.0, 0.0);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(2, GL_FLOAT, 0, streetVerts);
      glDrawArrays(GL_LINES, 0, numStreets * 2);
      glDisableClientState(GL_VERTEX_ARRAY);
   }

   // Draw the start and end points
   factor = (double) circles[startCircle-1] / max;
   startX = factor * (dimension/2) * cos( (double) startAngle * PI / 180.0);
   startY = factor * (dimension/2) * sin( (double) startAngle * PI / 180.0);
   factor = (double) circles[finishCircle-1] / max;
   finishX = factor * (dimension/2) * cos( (double) finishAngle * PI / 180.0);
   finishY = factor * (dimension/2) * sin( (double) finishAngle * PI / 180.0);
   glBegin(GL_POINTS);
      glColor3f(0.0, 1.0, 0.0);
      glVertex2f(startX, startY);
      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(finishX, finishY);
   glEnd();
   
   // Flush and swap
   glFlush();
   glutSwapBuffers();
}

void readNextMap()
{
   int i;

   mapNumber++;
   if (mapNumber >= numMaps)
   {
      fclose(inputFile);
      exit(0);
   }

   // Read in the number of circular roads and connecting streets
   fscanf(inputFile, "%d %d\n", &numCircles, &numStreets);

   // Read the circles
   for (i = 0; i < numCircles; i++)
   {
      // Read the next road radius
      fscanf(inputFile, "%d", &circles[i]);
   }

   // Eat the newline
   fscanf(inputFile, "\n");

   // Read the streets
   for (i = 0; i < numStreets; i++)
   {
      fscanf(inputFile, "%d %d\n", &streets[i].level, &streets[i].angle);
   }

   // Read the starting and ending locations
   fscanf(inputFile, "%d %d %d %d\n", &startCircle, &startAngle,
          &finishCircle, &finishAngle);
}


void keyboard(unsigned char key, int x, int y)
{
   if (key == 'q')
   {
      fclose(inputFile);
      exit(0);
   }
   else
   {
      readNextMap();
      glutPostRedisplay();
   }
}


int main(int argc, char *argv[])
{
   // inputFile = fopen("circles.in", "r");
   inputFile = stdin;

   fscanf(inputFile, "%d\n", &numMaps);
   mapNumber = -1;
   readNextMap();

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(800, 800);
   glutCreateWindow("CIRCLES Data Visualizer");

   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);

   glutMainLoop();

   fclose(inputFile);
}
