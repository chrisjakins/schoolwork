// Jakins, Christopher
// cfj2309
// 2019-10-21

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getToken( FILE *fp );

// (Hint: Put your regex_t declarations here.)
regex_t GeePea;
regex_t Shake;
regex_t Orc;

void processToken( char *token )
{
  regcomp(&GeePea, "^(([!\?][!\?])*PP*PEA)|(([!\?][!\?])*gg*gee)|(([!\?][!\?])*(g|P)+)$", REG_EXTENDED|REG_NOSUB);
  regcomp(&Shake, "(\\([M-W]([M-W][M-W])*[\\|-])|(\\|[M-W]([M-W][M-W])*[\\(-])|(-[M-W]([M-W][M-W])*[\\(\\|])", REG_EXTENDED|REG_NOSUB);
  regcomp(&Orc, "(&[a-m]*\\+)|(&[N-Z]*\\?)|(&\\*)", REG_EXTENDED|REG_NOSUB);

  if (regexec(&GeePea, token, 0, NULL, 0) == 0) {
    printf(">%s< matches GeePea.\n", token);
  }
  else if (regexec(&Shake, token, 0, NULL, 0) == 0) {
    printf(">%s< matches Shake.\n", token);
  }
  else if (regexec(&Orc, token, 0, NULL, 0) == 0) {
    printf(">%s< matches Orc.\n", token);
  }
  else {
    printf( ">%s< does not match.\n", token);
  }

  regfree(&GeePea);
  regfree(&Shake);
  regfree(&Orc);
}

int main( int argc, char *argv[] )
{
  // (Hint: Put the initialization of your regular expressions here.
  //        This would be the calls to regcomp.)

  // DO NOT CHANGE anything below this line!
  if ( argc > 1 ) {
    printf( "processing tokens from %s ...\n", argv[1] );

    FILE *fp = fopen( argv[1], "r" );
    char *token = NULL;

    if ( fp != NULL ) {
      while ( token = getToken( fp ) ) {
        processToken( token );
        free( token );
      }

      fclose( fp );
    } else {
      printf( "unable to open %s?\n", argv[1] );
    }
  } else {
    printf( "No input file specified.\n" );
  }
}

#define MAX_TOKEN_SIZE (1024)

char *getToken( FILE *fp )
{
  char token[ MAX_TOKEN_SIZE+1 ];
  int  i  = 0;

  while ( i < MAX_TOKEN_SIZE ) {
    int ch = fgetc( fp );

    if ( ch == EOF ) { break; }

    if ( isspace( ch ) ) {
      if ( i == 0 ) { continue; }
      break;
    }

    token[ i++ ] = ch;
  }

  if ( i == 0 ) { return NULL; }

  token[ i ] = '\0';

  return strdup( token );
}
