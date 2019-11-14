// Jakins, Christopher
// cfj2309
// 2019-11-13

import java.util.function.UnaryOperator;
import java.util.function.BinaryOperator;

public class hmwk_05_lambda {
  public static double EPSILON = 1e-8;

  //----------------------------------------------------------
  // Babylonian cube root lambda goes here.
  static BinaryOperator<Double>
      babylonian = (Double num, Double guess) ->
        Math.abs(num - Math.pow(guess, 3)) < EPSILON ? guess : hmwk_05_lambda.babylonian.apply(num, 2 * guess / 3 + num / (3 * Math.pow(guess, 2)));

  // pseudoPell lambda goes here.
  static UnaryOperator<Long>
      pseudoPell = (Long n) ->
        n <= 2 ? n : 3 * hmwk_05_lambda.pseudoPell.apply(n - 1) + 2 * hmwk_05_lambda.pseudoPell.apply(n - 2) + hmwk_05_lambda.pseudoPell.apply(n - 3);
  // GCF lambda goes here.
  static BinaryOperator<Long>
      GCF = (Long n, Long m) -> m == n ? m : (m > n ? hmwk_05_lambda.GCF.apply(m - n, n) : hmwk_05_lambda.GCF.apply(m, n - m));

  //----------------------------------------------------------
  public static void main( String[] args )
  {
    // Put for loop here that calls babylonian().
    for (double i = 0; i <= 340; i += 17) {
        double cubeRoot = babylonian.apply(i, EPSILON);
        System.out.format("babylonian(%3.0f) is %.6f = %10.6f\n", i, cubeRoot, Math.pow(cubeRoot, 3));
    }

    // Put for loop here that calls pseudoPell().
    for (Long i = 0l; i <= 20l; ++i) {
        Long result = pseudoPell.apply(i);
        System.out.format("pseudoPell(%d) is %d\n", i, result);
    }

    // Put nested for loops here that call GCF().
    for (Long i = 1l; i <= 10; ++i) {
        for (Long j = 1l; j <= 10; ++j) {
            Long result = GCF.apply(i, j);
            System.out.format("GCF(%d, %d) is %d\n", i, j, result);
        }
    }
  }
}
