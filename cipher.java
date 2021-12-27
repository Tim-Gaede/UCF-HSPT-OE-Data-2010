
import java.io.*;
import java.util.*;


public class cipher
{
   public static void main(String[] args) throws Exception
   {
      new cipher(new Scanner(System.in));
   }

   public cipher(Scanner in)
   {
      int n = in.nextInt();
      int r = in.nextInt();

      // Loop over all test cases
      while (n != 0)
      {
         // First we make an array of strings to represent the
         // rails in the cipher that way our job of reading them 
         // off becomes a lot simpler
         String[] rails = new String[n];
         
         // Fill the string array with empty strings
         for (int i=0; i<n; i++)
            rails[i] = "";

         // We need to read in the dummy line from the previous line
         // so that way we don't waste and endline
         String dummy = in.nextLine();
         
         // Now we read in the whole next line so we can parse it but
         // I will put in some regex to remove spaces from the input line
         char[] str = in.nextLine().replaceAll("[ ?()*^%$#@!*^&,.]", "").toCharArray();

         // Now we go back and forth across the rails adding the
         // strings to the appropriate lines on the rails
         int curRail = 0;
         int dir = 1;
         for (int i=0; i<str.length; i++)
         {
            rails[curRail] = rails[curRail] + str[i];

            // Now for the tricky part, if we run out of bounds
            // we just flip back in the opposite direction, 
            // after we finish this we change directions
            curRail += dir;
            if ((curRail == -1)||(curRail == n))
            {
               // Change direction
               dir *= -1;

               // Move back to the previous rail
               curRail += 2*dir;

               // We mod by the rail size for extra safeness
               curRail = curRail%n;
            }
         }

         // Very last step is building the composite string we start 
         // on the appropriate rail building the string character by
         // character, that way we can put spaces every 5 characters
         // we use the offset to read from the correct rail 
         String res = "";
         int curLoc = 0;
         for (int i=0; i<n; i++)
         {
            // We do this little trick to wrap the rails
            curRail = (i+r+n-1)%n;

            // Go through each character of this rail adding characters
            for (int j=0; j<rails[curRail].length(); j++)
            {
               // Special condition, every 5 characters add a space
               if ((curLoc%5) == 0)
                  res = res + " ";
               
               res = res + rails[curRail].charAt(j);
               curLoc++;
            }
         }

         // Print the result with a '.' and the initial space chopped off
         System.out.println(res.substring(1, res.length()) + ".");

         // Go to the next data set
         n = in.nextInt();
         r = in.nextInt();
      }
   }
}
