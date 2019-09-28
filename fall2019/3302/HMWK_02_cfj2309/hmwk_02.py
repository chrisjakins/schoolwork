# Jakins, Christopher
# cfj2309
# 2019-09-28
#--------------------------------------------------
import re
import sys

effpea = r'[0-9a-fA-F]+\(}[aeiouAEIOU]+'
stir = r'\)[A-Mn-z]*\{'
ent = r'#@+[\dR-W]*\.'

#--------------------------------------------------
def processToken( token ) :
  result = "does not match."
  if (re.fullmatch(effpea, token)):
    result = "matches EffPea."
  elif (re.fullmatch(stir, token)):
    result = "matches Stir."
  elif (re.fullmatch(ent, token)):
    result = "matches Ent."

  print( '>%s< %s' % ( token, result ) )

#--------------------------------------------------
def main() :
  fName = sys.argv[ 1 ]
  print( 'processing tokens from ' + fName + ' ...' )

  with open( fName, 'r' ) as fp :
    lines = fp.read().replace( '\r', '' ).split( '\n' )

  for line in lines :
    for token in line.split() :
      processToken( token )

#--------------------------------------------------
if ( __name__ == '__main__' ) :
  main()

#--------------------------------------------------
