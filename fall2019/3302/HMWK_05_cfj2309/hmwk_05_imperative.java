// Jakins, Christopher
// cfj2309
// 2019-11-13

public class hmwk_05_imperative {
  public static double EPSILON = 1e-8;

  //----------------------------------------------------------
  // Babylonian cube root
  public static double babylonian( double number, double guess ) {
    // Put something here
    if (Math.abs(number - Math.pow(guess, 3)) < EPSILON) {
        return guess;
    }
    
    return babylonian(number, 2 * guess / 3 + number / (3 * Math.pow(guess, 2)));
  }

  // Pseudo-Pell numbers
  public static Long pseudoPell( Long n ) {
    // Put something here
    if (n <= 2) {
        return n;
    }
    return 3 * pseudoPell(n - 1) + 2 * pseudoPell(n - 2) + pseudoPell(n - 3);
  }

  // GCF
  public static Long GCF( Long m, Long n ) {
    // Put something here
    if (m == n) {
        return m;
    }
    if (m > n) {
        return GCF(m - n, n);
    }
    return GCF(m, n - m);
  }

  //----------------------------------------------------------
  public static void main( String[] args )
  {
    // Put for loop here that calls babylonian().
    for (double i = 0; i <= 340; i += 17) {
        double cubeRoot = babylonian(i, EPSILON);
        System.out.format("babylonian(%3.0f) is %.6f = %10.6f\n", i, cubeRoot, Math.pow(cubeRoot, 3));
    }

    // Put for loop here that calls pseudoPell().
    for (Long i = 0l; i <= 20l; ++i) {
        Long result = pseudoPell(i);
        System.out.format("pseudoPell(%d) is %d\n", i, result);
    }

    // Put nested for loops here that call GCF().
    for (Long i = 1l; i <= 10; ++i) {
        for (Long j = 1l; j <= 10; ++j) {
            Long result = GCF(i, j);
            System.out.format("GCF(%d, %d) is %d\n", i, j, result);
        }
    }
  }
}
