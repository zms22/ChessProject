//include libraries
#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//set up keypad
char Data[2]; 
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte data_count = 0;
byte rowPins[ROWS] = {0, 1, 2, 3}; 
byte colPins[COLS] = {7,8,9,10}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//class Piece
class Piece
{
  public:
  int value;
  Piece(int v)
  {
    value = v;
  }
};
//define pieces
Piece Knight(3);
Piece Pawn(1);
Piece King(10);
Piece Rook(5);
Piece Bishop(4);
Piece Queen(9);
Piece Empty(0);
//create board
Piece Board[36] = {Rook,Pawn,Empty,Empty,Empty,Empty,Knight,Pawn,Empty,Empty,Empty,Empty,King,Pawn,Empty,Empty,Empty,Empty,\
              Queen,Pawn,Empty,Empty,Empty,Empty,Bishop,Pawn,Empty,Empty,Empty,Empty,Rook,Pawn,Empty,Empty,Empty,Empty};
//light information
int clockPin = 6;
int latchPin = 5;
int LightPin = 4;
//define locations
int location;
int newLocation;
//create openings
int openings[36];
int temp;
int switches[36];
int count = 0;
//get temp piece
Piece current = {Empty};
//functions
void getCurrentPiece(void)
{
  current = Board[location];
}
void KnightValidMoves(void)
{
   //set current space 1
  openings[location] = 1;

  if(Board[location+8].value == 0 && location/6 +1 == (location+8)/6)
  {
	  openings[location+8] = 1;
  }
  if(Board[location+4].value == 0 && location/6 +1 == (location+4)/6)
  {
	  openings[location+4] = 1;
  }
  if(Board[location-8].value == 0 && location/6 -1 == (location-8)/6)
  {
	  openings[location-8] = 1;
  }
  if(Board[location-11].value == 0 && location/6 -2 == (location-11)/6)
  {
	  openings[location-11] = 1;
  }
   if(Board[location+11].value == 0 && location/6 +2 == (location+11)/6)
  {
	  openings[location+11] = 1;
  }
  if(Board[location+13].value == 0 && location/6 +2 == (location+13)/6)
  {
	  openings[location+13] = 1;
  }
  if(Board[location-13].value == 0 && location/6 -2 == (location-13)/6)
  {
	  openings[location-13] = 1;
  }
  if(Board[location-4].value == 0 && location/6 -1 == (location-4)/6)
  {
	  openings[location-4] = 1;
  }
}
void RookValidMoves(void)
{
  //set current space 1
  openings[location] = 1;
  //+y
  for(int y = location+1; y/6 <= location/6; y++)
  {
    if(Board[y].value == 0)
    {
      openings[y] = 1;
    }
    else
    {
      break;
    } 
  }
  //-y
  for(int y = location-1; y/6 >= location/6; y--)
  {
    if(Board[y].value == 0)
    {
      openings[y] = 1;
    }
    else
    {
      break;
    }  
  } 
  //+x
  for(int x = location+6; x/6 < 6; x+=6)
  {
    if(Board[x].value == 0)
    {
      openings[x] = 1;
    }
    else
    {
      break;
    }  
  } 
  //-x
  for(int x = location-6; x/6 >= 0; x-=6)
  {
    if(Board[x].value == 0)
    {
      openings[x] = 1;
    }
    else
    {
      break;
    }  
  }
}
void BishopValidMoves(void)
{
  //set current space 1
  openings[location] = 1;
  //+y+x
  for(int l = location; l <= 35; l+=7)
  {
    if((Board[l].value == 0 && l%6 > location%6)|| l== location)
    {
      openings[l] = 1;
    }
    else
    {
      break;
    } 
  }
  //-y+x
  for(int l = location; l <= 35; l+=5)
  {
    if((Board[l].value == 0 && l%6 < location%6)|| l == location)
    {
      openings[l] = 1;
    }
    else
    {
      break;
    } 
  }

  //-y-x
  for(int l = location; l >= 0; l-=5)
  {
    if((Board[l].value == 0 && l%6 > location%6)|| l == location)
    {
      openings[l] = 1;
    }
    else
    {
      break;
    } 
  }
  //+y-x
  for(int l = location; l >= 0; l-=7)
  {
    if((Board[l].value == 0 && l%6 < location%6)|| l == location)
    {
      openings[l] = 1;
    }
    else
    {
      break;
    } 
  }
}
void PawnValidMoves(void)
{
  //set current space 1
  openings[location] = 1;
    if(location%6 < 5)
    {
      openings[location+1] = 1;
    }
}
void KingValidMoves(void)
{
     //set current space 1
  openings[location] = 1;
  //+y+x
    if(Board[location+7].value == 0 && (location+7)%6 > location%6)
    {
      openings[location+7] = 1;
    }
    //+x-y
    if(Board[location+5].value == 0 && (location+5)%6 < location%6)
    {
      openings[location+5] = 1;
    }
    //+y-x
    if(Board[location-7].value == 0 && (location-7)%6 < location%6)
    {
      openings[location-7] = 1;
    }
    //-x-y
    if(Board[location-5].value == 0 && (location-5)%6 > location%6)
    {
      openings[location-5] = 1;
    }
    //+y
    if(Board[location+1].value == 0 && (location+1)/6 == location/6)
    {
      openings[location+1] = 1;
    }
    //-y
    if(Board[location-1].value == 0 && (location-1)/6 == location/6)
    {
      openings[location-1] = 1;
    }
    //+x
    if(Board[location+6].value == 0 && (location+6)%6 == location%6)
    {
      openings[location+1] = 1;
    }
    //-x
    if(Board[location-6].value == 0 && (location-6)%6 == location%6)
    {
      openings[location-6] = 1;
    }
}
void callType(void)
{
  if(current.value == 5)
   {
    RookValidMoves();
  }
  if(current.value == 4)
  {
    BishopValidMoves();
  }
  if(current.value == 9) 
  {
    RookValidMoves();
    BishopValidMoves();
  }
  if(current.value == 10)
  {
    KingValidMoves();
  }
  if(current.value == 1)
  {
    PawnValidMoves();
  }
  if(current.value == 3)
  {
    KnightValidMoves();
  }
}
void getName()
{
  getCurrentPiece();
  //display piece value
  display.clearDisplay();
  display.setCursor(17, 24);
  display.setTextSize(1); //Setup text size

  if(current.value == 5)
  {
      display.print("The selected piece is: Rook");
      display.display();
  }
  if(current.value == 4)
  {
      display.print("The selected piece is: Bishop");
      display.display();
  }
  if(current.value == 9) 
  {
      display.print("The selected piece is: Queen");
      display.display();
  }
  if(current.value == 10)
  {
      display.print("The selected piece is: King");
      display.display();
  }
  if(current.value == 1)
  {
      display.print("The selected piece is: Pawn");
      display.display();
  }
  if(current.value == 3)
  {
      display.print("The selected piece is: Knight");
      display.display();
  }
  delay(100);
}
//main setup
void setup() 
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); // Don't proceed, loop forever
  }
 
  display.setTextSize(2); //Setup text size
  display.setTextColor(WHITE); //Setup font color
  //lights
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(LightPin, OUTPUT);

  //write all the lights low
  digitalWrite(latchPin, LOW);
  for(int i = 35; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(LightPin, LOW);   
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);

  //start game
  //prompt input row
  display.clearDisplay();
  display.setCursor(17, 24);
  display.setTextSize(1); //Setup text size
  display.println(F("Press any key to\n start the game."));
  display.display();
  //wait for start
  char start = customKeypad.waitForKey();
}
//main loop
void loop() 
{

  //reset openings
  for(int i = 0; i < 36; i++)
  {
    current.value = 0;
     openings[i] = 0;
  } 
  //prompt input row
  display.clearDisplay();
  display.setCursor(17, 24);
  display.setTextSize(1); //Setup text size
  display.println(F("Enter the current\n column:"));
  display.display();
  
  //wait for input
  char row = customKeypad.waitForKey();

  //prompt input row
  display.clearDisplay();
  display.setCursor(17, 24);
  display.setTextSize(1); //Setup text size
  display.println(F("Enter the current row:"));
  display.display();

  //wait for input
  char col = customKeypad.waitForKey();
  //convert to int
  int r = row - '0';
  int c = col - '0';

  //get location
  location = r*6 + c;

  //display selection
  getName();

  //get potential moves
  getCurrentPiece();
  callType();
  
  //write all the outputs
  digitalWrite(latchPin, LOW);
  for(int i = 35; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(LightPin, openings[i]);   
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);

  //prompt new input row
  display.clearDisplay();
  display.setCursor(17, 24);
  display.setTextSize(1); //Setup text size
  display.println(F("Enter the new\n column:"));
  display.display();
  
  //wait for input
  char new_row = customKeypad.waitForKey();

  //prompt input row
  display.clearDisplay();
  display.setCursor(17, 24);
  display.setTextSize(1); //Setup text size
  display.println(F("Enter the new row:"));
  display.display();

  //wait for input
  char new_col = customKeypad.waitForKey();
  //convert to int
  int new_r = new_row - '0';
  int new_c = new_col - '0';

  //get location
  newLocation = new_r*6 + new_c;

  //erase old location
  Board[location].value = 0;

  //write new locatoin
  Board[newLocation].value = current.value;

  //write all the lights low
  digitalWrite(latchPin, LOW);
  for(int i = 35; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(LightPin, LOW);   
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
}

