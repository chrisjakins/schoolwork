// Dalio, Brian A.
// dalioba
// 2019-06-26

import java.util.function.UnaryOperator;

public class okLambda {
 static UnaryOperator<Integer>
   ok = ( Integer i ) -> i == 0 ? 0 : i + okLambda.ok.apply( i-1 );

 public static void main( String[] args ) {
   System.out.format( "ok( 10 ) is %d\n", ok.apply( 10 ) );
 }
}
