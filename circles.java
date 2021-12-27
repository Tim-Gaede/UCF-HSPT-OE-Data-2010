// Stephen Fulwider
//	Driving in Circles - 2010 High School Online Programming Contest

import java.io.File;
import java.util.Arrays;
import java.util.Scanner;


public class circles
{

	public static void main(String[] args) throws Exception
	{
		// I like to instantiate my classes this way so that I don't have to use static variables or methods
		new circles();
	}
	
	final double RAD=Math.PI/180; // for angle->radian conversion
	final double oo=1e50; // a big value for infinity
	
	// circle radii
	int Cn;
	int[] C=new int[10];
	
	// number of roads
	int Rn;
	
	// points on the map - at most 42 since 20*2+2=42
	int Pn;
	point[] P=new point[42];
	
	// distance matrix
	double[][] D=new double[42][42];
	
	circles() throws Exception
	{
		Scanner in = new Scanner(System.in);
		for (int T=in.nextInt(); T-->0; )
		{
			// read input
			Cn=in.nextInt();
			Rn=in.nextInt();
			Pn=0;
			
			for (int i=0; i<Cn; ++i)
				C[i]=in.nextInt();
			
			// clear out distance matrix
			for (double[] d : D) Arrays.fill(d, oo);
			
			// read in each road
			for (int i=0; i<Rn; ++i)
			{
				// get circle and angle
				int d=in.nextInt();
				int a=in.nextInt();
				
				// get from and to circle
				int f=d;
				int t=d+1;
				--f; --t; // make 0 based
				
				// put point on from and to circles
				P[Pn++]=new point(a,f);
				P[Pn++]=new point(a,t);
				
				// put this road in the distance matrix
				D[Pn-1][Pn-2]=D[Pn-2][Pn-1]=Math.abs(C[f]-C[t]);
			}
			
			// get start circle and angle
			int sc=in.nextInt()-1;
			int sa=in.nextInt();
			
			P[Pn++]=new point(sa,sc);
			
			// get finish circle and angle
			int fc=in.nextInt()-1;
			int fa=in.nextInt();

			P[Pn++]=new point(fa,fc);
			
			// get distances between all points on same circle
			for (int i=0; i<Pn; ++i)
				for (int j=i+1; j<Pn; ++j)
					if (P[i].c==P[j].c)
						D[i][j]=D[j][i]=cirDist(i,j);
			
			// run floyds algorithm to get shortest point between all points
			//	note: there are more efficient algorithms than this since
			//	we are only interested in shortest distance from a single
			//	point, but since the graph is so small I just use the
			//	simplest graph algorithm to code
			for (int k=0; k<Pn; ++k)
				for (int i=0; i<Pn; ++i)
					for (int j=0; j<Pn; ++j)
						D[i][j]=Math.min(D[i][j], D[i][k]+D[k][j]);
			
			// print the distance between the start and finish point, making sure to add a small amount for tolerance
			System.out.printf("%.2f%n", D[Pn-2][Pn-1]+1e-11);
		}
	}
	
	// arc length = R*theta, theta = angle between points i and j
	double cirDist(int i, int j)
	{		
		// theta is just the minimum angle between the two points, converted to radians
		double theta=Math.min(Math.abs(P[i].a-P[j].a), 360-Math.abs(P[i].a-P[j].a))*RAD;
		return C[P[i].c]*theta;
	}
	
	// helper class to hold an angle and which circle it's on
	class point
	{
		int a;
		int c;
		
		point(int a, int c)
		{
			this.a=a;
			this.c=c;
		}
	}

}
