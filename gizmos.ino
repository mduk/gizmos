#include <EEPROM.h>

int pins = 9;
int pin[] =   { 13, 9, 8, 7, 6, 5, 4, 3, 2 };

void setup()
{
  Serial.begin( 9600 );
  
  // Configure outputs and write initial state
  for ( int i = 0; i < pins; i++ )
  {
    int initialState = EEPROM.read( i );
    if ( initialState != 0 && initialState != 1 ) {
      EEPROM.write( i, 0 );
      initialState = 0;
    }
    pinMode( pin[i], OUTPUT );
    digitalWrite( pin[i], initialState );
    v( i );
  }
}

void loop()
{
  byte command, address;
  
  if ( Serial.available() == 2 )
  {
    command = Serial.read();
    address = Serial.read() - 48; // Maps the ASCII for 0..9 to literal 0..9
    
    if ( address < 0 || address > 9 ) {
      e( command, address );
      return;
    }
    
    switch ( command ) 
    {
      case 'r': // Read address
        v( address );
        break;
      
      case 'i': // Turn on address
        u( address, 1 );
        v( address );
        break;
      
      case 'o': // Turn off address
        u( address, 0 );
        v( address );
        break;
	
      case 't': // Toggle address
        if ( s( address ) == 0 ) {
          u( address, 1 );
        }
        else {
          u( address, 0 );
        }
        v( address );
        break;
      
      default:
        e( command, address );
        break;
    }
  }
}

int s( int address ) {
  return EEPROM.read( address );
}

void u( int address, int newState ) {
  EEPROM.write( address, newState );
  digitalWrite( pin[ address ], newState );
}

void v( int address )
{
  Serial.print( "v" );
  Serial.print( address );
  Serial.println( s( address ) );
}

void e( byte command, byte address ) {
  Serial.print( "e" );
  Serial.print( (char) command );
  Serial.println( address );
}
