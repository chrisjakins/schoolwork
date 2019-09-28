// Jakins, Christopher
// cfj2309
// 2019-09-28

import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.regex.Pattern;

public class hmwk_02 {
  final static private Pattern effpea = Pattern.compile("[0-9a-fA-F]+\\(}[aeiouAEIOU]+");
  final static private Pattern stir = Pattern.compile("\\)[A-Mn-z]*\\{");
  final static private Pattern ent = Pattern.compile("#@+[\\dR-W]*\\.");

  public static void processToken( String token )
  {
      String result = "does not match.";
      if (Pattern.matches(effpea.toString(), token)) {
          result = "matches EffPea.";
      }
      else if (Pattern.matches(stir.toString(), token)) {
          result = "matches Stir.";
      }
      else if (Pattern.matches(ent.toString(), token)) {
          result = "matches Ent.";
      }
      System.out.println( ">" + token + "< " + result);
  }

  public static void main( String[] args )
  {
    System.out.println( "processing tokens from " + args[ 0 ] + " ..." );

    try {
      Files.lines( Paths.get( args[ 0 ] ) ).filter(line -> line.length() > 0).forEachOrdered(
        line -> Arrays.stream( line.split( "\\s+" )  )
            .forEachOrdered( token -> processToken( token ) ) );
    } catch ( java.io.IOException e ) {
      e.printStackTrace();
    }
  }
}
