import java.io.File;
import java.util.Scanner;

// Stephen Fulwider
//	Epic Win Dixie - 2010 High School Online Programming Contest

public class epic
{

	public static void main(String[] args) throws Exception
	{
		// I like to instantiate my classes this way so that I don't have to use static variables or methods
		new epic();
	}
	
	epic() throws Exception
	{
		// open input file
		Scanner in = new Scanner(System.in);
		
		// read in the number of test cases and process each
		for (int T=new Integer(in.nextLine().trim()); T-->0; )
		{
			// read in the line
			String line=in.nextLine();
			
			// if the line begins with "Win" or "Fail" print "Epic " first
			//	be careful not to use substring here, since the input string may be shorter than 3 chars
			if (line.startsWith("Win") || line.startsWith("Fail"))
				System.out.print("Epic ");
			
			// finally just print the original line
			System.out.println(line);
		}
	}

}

