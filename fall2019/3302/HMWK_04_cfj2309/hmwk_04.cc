// Jakins, Christopher
// cfj2309
// 2019-10-2

#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

void processToken( string token )
{
  std::regex GeePea("([!\?][!\?])*((PP*PEA)|(gg*gee)|((g|P)+))");
  std::regex Shake("(\\([M-W]([M-W][M-W])*[\\|-])|(\\|[M-W]([M-W][M-W])*[\\(-])|(-[M-W]([M-W][M-W])*[\\(\\|])");
  std::regex Orc("(&[a-m]*\\+)|(&[N-Z]*\\?)|(&\\*)");

  if (std::regex_match(token, GeePea)) {
    std::cout << ">" << token << "< matches GeePea." << std::endl;
  }
  else if (std::regex_match(token, Shake)) {
    std::cout << ">" << token << "< matches Shake." << std::endl;
  }
  else if (std::regex_match(token, Orc)) {
    std::cout << ">" << token << "< matches Orc." << std::endl;
  }
  else {
    std::cout << ">" << token << "< does not match." << std::endl;
  }
}

int main( int argc, char *argv[] )
{
  if ( argc > 1 ) {
    cout << "processing tokens from " << argv[ 1 ] << " ...\n";

    ifstream inputFile;
    string   token;

    inputFile.open( argv[ 1 ] );

    if ( inputFile.is_open() ) {
      while ( inputFile >> token ) {
        processToken( token );
      }
      inputFile.close();
    } else {
      cout << "unable to open " << argv[ 1 ] << "?\n";
    }
  } else {
    cout << "No input file specified.\n";
  }
}
