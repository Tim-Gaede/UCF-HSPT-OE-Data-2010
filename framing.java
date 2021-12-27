import java.io.*;
import java.util.*;

public class framing
{
	public static void main (String [] args) throws IOException
	{	
		Scanner scan = new Scanner(System.in);
		
		int numGroups = scan.nextInt();
		for (int z = 1; z <= numGroups; z++)
		{
			double total = 0;
			int numInGroup = scan.nextInt();
			
			for (int i = 0; i < numInGroup; i++)
			{
				int numFrames = scan.nextInt();
				for (int j = 0; j < numFrames; j++)
				{
					double l = scan.nextInt();
					double w = scan.nextInt();
					double d = scan.nextInt();
					
					double pictureArea = l * w;
					
					double tw = w + 2 * d / Math.sqrt(2);
					double tl = l + 2 * d / Math.sqrt(2);
					
					double totalArea = tw * tl;
					
					double frameArea = totalArea - pictureArea;
					total += frameArea;
				}
			}
			System.out.printf("Group #%d: %.02f cubic inches\n\n", z, total+1e-9);
		}
	}	
}
