"""
    Chris Jakins
    1000802309
    CSE 3313 HW3
    2/14  
"""

import numpy as np
import csv

def readFromCSV( filename ) :
    data = []
    with open( filename ) as csvfile :
        # csv.QUOTE_NONNUMERIC converts input to float data type
        reader = csv.reader( csvfile, quoting = csv.QUOTE_NONNUMERIC )
        for element in next( reader ) :
            data.append( element )
    return data

def convertToBits( values ) :
    pulse0 = np.ones( 10 )
    norm0 = np.linalg.norm( pulse0 )
    pulse0 = pulse0 / norm0

    pulse1 = np.append( np.ones(5), -1 * np.ones(5) )
    norm1 = np.linalg.norm( pulse1 )
    pulse1 = pulse1 / norm1

    bits = []
    for x in range(0, int( len(data) / 10 )) :
        pulseIn = data[10 * x : 10 * x + 10]
        normIn = np.linalg.norm( pulseIn )
        if ( np.absolute(pulse0.dot(pulseIn)) > np.absolute(pulse1.dot(pulseIn)) ) :
            bits.append( 0 )
        else :
            bits.append( 1 )
    return bits

def binaryListToString( list ) :
    output = ""
    for x in range(0, int( len(list) / 8 )) :
        bitPattern = list[8 * x : 8 * x + 8]
        strBits = ''.join(str(a) for a in bitPattern)
        output += chr( int( strBits, base = 2 ) )
    return output

#
#   Effective "main"
#

data = readFromCSV( 'data-communications.csv' )
bits = convertToBits( data )
print( binaryListToString( bits ) )
