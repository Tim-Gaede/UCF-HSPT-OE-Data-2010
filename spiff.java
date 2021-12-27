// Stephen Fulwider
//	Spaceman Spiff - 2010 High School Online Programming Contest

import java.io.File;
import java.util.Arrays;
import java.util.Scanner;


public class spiff
{

	public static void main(String[] args) throws Exception
	{
		// I like to instantiate my classes this way so that I don't have to use static variables or methods
		new spiff();
	}
	
	// dictionary
	int Dn;
	String[] D = new String[50];
	
	// message
	int Mn;
	String[] M = new String[50];
	
	// scramble solution
	int[][] S = new int[8][];
	
	spiff() throws Exception
	{
		// open the input file for reading
		Scanner in = new Scanner(System.in);
		
		// continue processing test cases until 0 read for dictionary size
		for (int T=1; (Dn=in.nextInt())>0; ++T)
		{
			// read in the dictionary
			for (int i=0; i<Dn; ++i)
				D[i]=in.next();
			
			// read in the scrambled message
			Mn=in.nextInt();
			for (int i=0; i<Mn; ++i)
				M[i]=in.next();
			
			// get the scramble template for each possible length
			for (int i=1; i<=7; ++i)
				unscramble(i);
			
			// once all templates have been found, just print the message, unscrambling each word with the correct template
			System.out.printf("Message #%d:",T);
			for (int i=0; i<Mn; ++i)
			{
				int[] sol=S[M[i].length()];
				System.out.print(' ');
				for (int j=0; j<M[i].length(); ++j)
					System.out.print(M[i].charAt(sol[j]));
			}
			System.out.println();
			System.out.println();
		}
	}
	
	// get the unscramble template for words of given length
	//	if there are no words in the message of this length then this does nothing
	void unscramble(int len)
	{
		int cnt=0;
		m: for (int i=0; i<Mn; ++i)
			if (M[i].length()==len) // this word is the right length and could have an unambiguous scramble
			{
				++cnt;
				if (!hasRepeatChar(M[i]))
				{
					int res=-1;
					
					// check all the words in the dictionary to see if a potential scramble is found
					for (int j=0; j<Dn; ++j)
						if (D[j].length()==len && isScramble(M[i],D[j]))
						{
							if (res<0) res=j; // this is the first potential match found, set it
							else continue m; // this word unscrambles to multiple words, so it's not helpful
						}
					if (res>=0) // found an unambiguous result, it will be our template for this length
					{
						// create the mapping to make it easy to unscramble words of this length when decoding the message
						//	S[len][j] gives the index of the character in M[i] that should be at index j in the unscrambled word 
						S[len]=new int[len];
						for (int j=0; j<len; ++j)
							S[len][j]=M[i].indexOf(D[res].charAt(j));
						return;
					}
				}
			}
		
		if (cnt>0) // this is just for judge data debugging
		{
			System.err.printf("Error in judge data for length %d - no unambiguous jumbles%n",len);
		}
	}
	
	// does x have a character which occurs more than once?
	boolean hasRepeatChar(String x)
	{
		char[] X=x.toCharArray();
		Arrays.sort(X);
		
		for (int i=0; i+1<X.length; ++i)
			if (X[i]==X[i+1])
				return true;
		return false;
	}
	
	// is x a permutation of the characters of y?
	boolean isScramble(String x, String y)
	{
		if (x.length()!=y.length()) return false;
		
		char[] X=x.toCharArray();
		char[] Y=y.toCharArray();
		Arrays.sort(X);
		Arrays.sort(Y);
		
		for (int i=0; i<X.length; ++i)
			if (X[i]!=Y[i])
				return false;
		return true;
	}

}
