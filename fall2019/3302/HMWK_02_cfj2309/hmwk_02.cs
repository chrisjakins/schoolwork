// Jakins, Christopher
// cfj2309
// 2019-09-28

using System;
using System.IO;
using System.Text.RegularExpressions;

public class hmwk_02
{
  private static Regex effpea = new Regex(@"^[0-9a-fA-F]+\(}[aeiouAEIOU]+$");
  private static Regex stir = new Regex(@"^\)[A-Mn-z]*\{$");
  private static Regex ent = new Regex(@"^#@+[\dR-W]*\.$");

  static public void processToken( string token ) {
      string result = "does not match.";

      if (Regex.Match(token, effpea.ToString()).Success) {
          result = "matches EffPea.";
      }
      else if (Regex.Match(token, stir.ToString()).Success) {
          result = "matches Stir.";
      }
      else if (Regex.Match(token, ent.ToString()).Success) {
          result = "matches Ent.";
      }

      Console.WriteLine( ">" + token + "< " + result);
  }

  static public void Main( string[] args )
  {
    Console.WriteLine( "processing tokens from " + args[ 0 ] + " ..." );

    foreach ( string line in File.ReadAllLines( args[ 0 ] ) ) {
      foreach ( string token in line.Split( (char []) null, StringSplitOptions.RemoveEmptyEntries ) ) {
        processToken( token );
      }
    }
  }
}
