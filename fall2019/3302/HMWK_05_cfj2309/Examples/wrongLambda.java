// Dalio, Brian A.
// dalioba
// 2019-06-26

import java.util.function.UnaryOperator;

public class wrongLambda {
 static UnaryOperator<Integer>
   wrong = ( Integer i ) -> i == 0 ? 0 : i + wrong.apply( i-1 );

 public static void main( String[] args ) {
   System.out.format( "wrong( 10 ) is %d\n", wrong.apply( 10 ) );
 }
}
