int pins = 9;
int pin[] =   { 13, 9, 8, 7, 6, 5, 4, 3, 2 };
int state[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setup()
{
  Serial.begin( 9600 );
  
  // Configure outputs and write initial state
  for ( int i = 0; i < pins; i++ )
  {
    pinMode( pin[i], OUTPUT );
    digitalWrite( pin[i], state[i] );
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
      
      default:
        e( command, address );
        break;
    }
  }
}

void u( int address, int newState ) {
  state[ address ] = newState;
  digitalWrite( pin[ address ], state[ address ] );
}

void v( int address )
{
  Serial.print( "v" );
  Serial.print( address );
  Serial.println( state[ address ] );
}

void e( byte command, byte address ) {
  Serial.print( "e" );
  Serial.print( (char) command );
  Serial.println( address );
}
