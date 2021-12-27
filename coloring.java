import java.util.*;
import java.io.*;

public class coloring {
	
	//An adjacency matrix for keeping track of the connections
	boolean adj[][];
	
	//This is for the DFS check on the graph later
	boolean visited[];
	
	//I prefer to initialize my java solutions this way
	// to avoid having to put the static keyword in front
	// of everything.
	public coloring(Scanner in)
	{
		//Dots and lines
		int d = in.nextInt();
		int l = in.nextInt();
		
		//This is an important trick. You'll notice that my
		// adjacency matrix cannot hold multiple connections
		// to one point, which the data allows (I could keep track
		// of that  by changing it to a two-dimensional int array)
		// So instead I keep track of the number of edges
		// connecting to a single dot.
		// By graph theory, if there are more than two edges connecting
		// to a single dot, it can't be 2-edge colored!
		int[] conns;
		
		//Just a counter for the page.
		int page = 1;
		
		//Keep reading in input until we see 0 0
		while(d != 0 || l != 0)
		{
			//Initialize the variables to this problem
			conns = new int[d];
			adj = new boolean[d][d];
			visited = new boolean[d];
			
			//Read in all the lines
			for(int i = 0; i < l; i++)
			{
				//The dots are 1-indexed, so subtract 1
				int a = in.nextInt()-1;
				int b = in.nextInt()-1;
				
				//Update the connection counters
				conns[a]++;
				conns[b]++;
				
				//Set that these two places are connected
				adj[a][b] = true;
				adj[b][a] = true;
			}
			
			//If the graph is 2-edge colorable, good is true.
			boolean good = true;
			
			//This is the connection check, if any edge has
			// more than two edges connecting to it, it's no good
			for(int i = 0; i < d; i++)
				if(conns[i] > 2)
				{
					good = false;
					break;
				}
			
			//Now we run a simple DFS to look for cycles of odd lengths
			// -if the cycle is even length, we can 2-edge color by
			// alternating colors.
			for(int i = 0; i < d && good; i++)
				if(!visited[i])
				{
					Stack<Integer> prevs = new Stack<Integer>();
					prevs.add(-1);	
					//I use -1 as the start symbol so
					// the stack won't be empty to start with
					good = check(i, prevs);
				}
			
			//Now we print out the results
			System.out.println("Page #" + page + ":");
			
			if(good)
				System.out.println("Yes, I can color it.");
			else
				System.out.println("No, I can't color it.");

			System.out.println();
			
			//Update for the next case
			page++;
			d = in.nextInt();
			l = in.nextInt();
		}
		
	}
	
	//This is where the DFS gets done. We're looking specifically
	// for odd-length cycles.
	boolean check(int node, Stack<Integer> prev)
	{
		//For all the nodes, look for ones that connect to this one
		for(int i = 0; i < adj.length; i++)
			//If the node is not the same one we are at, or the one
			// we just came from, and contains a connection to our
			// starting node, then check it. Finally, we don't want
			// to re-check nodes we've already considered.
			if(i != node && i != prev.peek() && adj[node][i] && !visited[i])
			{
				//If our previous list has i in it (i is a valid connection
				// so far) we have found a cycle! We need to check if there
				// are an odd number (plus the starting -1) of nodes we've 
				// already visited. If so, we've got a graph that's not
				// 2-edge colorable!
				if(prev.contains(i))
				{
					if((prev.size() & 1) == 1)
						return false;
					
				}
				else
				{
					//Else the node is just one we haven't visited yet,
					// so add it to our previous list, and continue DFSing
					prev.add(node);
					
					//If this one returns false, no need to check
					// anything else, just return false.
					if(!check(i, prev))
						return false;
					
					//Remove this node from the prev list for future
					// DFS paths.
					prev.pop();
				}
			}
		
		//Once we have fully considered all the connections this dot
		// has, we mark it as visited so that it doesn't
		// get re-considered later.
		visited[node] = true;
		
		//Return true - the graph is 2-edge colorable if it made it this far.
		return true;
	}
	
	//A generic main function, whose only job is to initialize the
	// solution.
	public static void main(String[] args) throws Exception
	{
		new coloring(new Scanner(System.in));
	}
}
