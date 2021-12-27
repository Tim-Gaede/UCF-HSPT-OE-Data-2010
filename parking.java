/* Problem: parking
 * Problem Solver: Michael Do
 * Date: 5/7/10
 */

import java.io.*;
import java.util.*;

public class parking {

	public static int l, w, f, k;
	public static int[][] corners;
	
	public static void main(String[] args) throws Exception{
		
		Scanner In = new Scanner(System.in);
		
		// Taking in the number of days
		int numDays = In.nextInt();
		
		for(int curDay = 1;curDay <= numDays;curDay++){
			
			// Read in the parking lot parameters
			l = In.nextInt();
			w = In.nextInt();
			f = In.nextInt();
			k = In.nextInt();
			
			// Setup the 4 corners of the parking long (0, 0), (l, 0), (0, w) & (l, w)
			corners = new int[][]{{0, 0, l, l}, {0, w, 0, w}};
			
			// Used to record best spot
			int bestTime = Integer.MAX_VALUE;
			int[] best = new int[3];
			
			// For each spot
			for(int i = 0;i < k;i++){
				
				// Read in the coordinates
				int[] cur = new int[3];
				for(int j = 0;j < 3;j++) cur[j] = In.nextInt();
				
				// Get the time it takes to exit out the parking lot
				int curTime = getTime(cur);
				
				// Compare to current best time. If better, the current spot becomes the best spot
				if(curTime < bestTime){
					bestTime = curTime;
					for(int j = 0;j < 3;j++) best[j] = cur[j];
				}
				
			}
			
			// Output the answer
			System.out.printf("Day #%d: %d %d %d %d%n", curDay, best[0], best[1], best[2], bestTime);
			
			
		}
		
	}
	
	public static int getTime(int[] spot){
		
		int time = Integer.MAX_VALUE;
		
		// Find the Manhattan distance from the spot to each corner and take the smallest
		for(int i = 0;i < corners[0].length;i++)
			time = Math.min(time, Math.abs(corners[0][i] - spot[0]) + Math.abs(corners[1][i] - spot[1]));
		
		// Add the time it takes to get from current floor to bottom floor
		time += (spot[2]-1)*2;
		
		return time;
	}
	
	
	
}
