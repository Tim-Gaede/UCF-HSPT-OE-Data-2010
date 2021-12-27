import java.io.*;
import java.util.*;

public class magic 
{
	public static void main (String [] args) throws IOException
	{
		Scanner scan = new Scanner(System.in);
		
		int mult = scan.nextInt();
		int add = scan.nextInt();
		
		
		int z = 1;
		while (mult != 0 || add != 0)
		{
			boolean possible = true;
			for (int o = 1; o <= 10; o++)
			{
				if (mult == 0)
				{
					possible = false;
					break;
				}
					
				if (add % mult != 0) 
					possible = false;
					
				int cur = mult * o;
				
				if (cur > 144 || cur < 0)
					possible = false;
				
				cur += add;
				
				if (cur > 144 || cur < 0)
					possible = false;
					
				cur /= mult;
				
				if (cur > 144 || cur < 0)
					possible = false;
					
				cur -= o;
				
				if (cur > 144 || cur < 0)
					possible = false;
				
				
			}
			if (possible)
				System.out.printf("The number left over is %d.\n", add / mult);
			else
				System.out.println("The trick is too difficult to do.");
			
			mult = scan.nextInt();
			add = scan.nextInt();
		}
	}
}

