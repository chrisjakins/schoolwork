// Dalio, Brian A.
// dalioba
// 2019-06-26

import java.util.function.Consumer;
import java.util.function.Supplier;
import java.util.function.UnaryOperator;
import java.util.function.BinaryOperator;

public class sampleLambda {
  static Supplier<Integer>
    forty_two = () -> 42;

  static Consumer<String>
    dump = ( String s ) -> { System.out.println( s ); };

  static UnaryOperator<Integer>
    negate = ( Integer i ) -> -i;

  static BinaryOperator<Integer>
    add = ( Integer i, Integer j ) -> i+j;

  public static void main( String[] args ) {
    // Observed output should be:
    //   forty_two() is 42
    //   Dumped String
    //   negate( 1 ) is -1
    //   add( 2, 3 ) is 5

    System.out.format( "forty_two() is %d\n", forty_two.get() );
    dump.accept( "Dumped String" );
    System.out.format( "negate( 1 ) is %d\n", negate.apply( 1 ) );
    System.out.format( "add( 2, 3 ) is %d\n", add.apply( 2, 3 ) );
  }
}
