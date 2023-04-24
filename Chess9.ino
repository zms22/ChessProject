#include "SimplePiece.h"
//define pieces
Piece Knight(3);
Piece Pawn(1);
Piece King(10);
Piece Rook(5);
Piece Bishop(4);
Piece Queen(9);
Piece Empty(0);
//create board
Piece Board[3][3] = {{Empty,Queen,Empty},{Empty,Empty,Empty},{Empty,Empty,Empty}};
//create switches
//int switches[9] = {0,1,2,3,4,5,6,7,8};
int switchPin = 7;
//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int LightPin = 4;
//
int switchClock = 10;
int switchLatch = 9;
//define switch states
int switchStates[9] = {};
//define last states of switches
int lastStates[9] = {};
//define location
int location;
int newLocation;
//define range of piece
int range[4];
//create openings
int openings[9];
//define bit
int bitVal = 0;
Piece current = {Empty};
//get current piece
void getCurrentPiece(void)
{
  current = Board[location/3][location%3];
}
void getRange(void)
{
  int xloc = location/3;
  int yloc = location%3;
  //pawn range
  if(current.value == 1)
  {
    range[0] = 0;
    range[1] = 0;
    range[3] = 0;
    if(yloc < 2)
    {
      range[2] = 1;
    }
    else if(yloc == 1)
    {
      range[2] = 2;
    }
    else
    {
      range[2] = 0;
    }
  }
  if(current.value == 10)
  {

    if(xloc = 0)
    {
      range[1] = 0;
    }
    else if(xloc == 7)
    {
      range[0] = 0;
    }
    else if(yloc == 0)
    {
      range[3] = 0;
    }
    else if(yloc ==2)
    {
      range[2] = 0;
    }
  }
  if(current.value == 5 || 9 || 4)
  {
    range[0] = 2 - xloc;
    range[1] = xloc;
    range[2] = 2 - yloc;
    range[3] = yloc;
  }
}
void KnightValidMoves(void)
{
  int xloc = location/3;
  int yloc = location%3;
  //if(xloc+2 && )
}
void RookValidMoves(void)
{
  int xloc = location/3;
  int yloc = location%3;
  //set current space 1
  openings[yloc*3 + xloc] = 1;
  //+ x direction
  for(int x = xloc+1;x <= xloc + range[0]; x++)
  {
    if(Board[x][yloc].value == 0)
    {
       openings[yloc*3 + x] = 1;
    }
    else
    {
     break;
    }
  }
  // - x direction
  for(int x = 1;x <= range[1]; x++)
  {
    if(Board[xloc-x][yloc].value == 0)
    {
       openings[yloc*3 + (xloc-x)] = 1;
    }
    else
    {
      break;
    }
  }
  // + y direction
  for(int y = yloc+1; y <= yloc + range[2]; y++)
  {
    if(Board[xloc][y].value == 0)
    {
       openings[y*3 + xloc] = 1;
    }
    else
    {
      break;
    }
  }
  // - y direction
  for(int y = 1; y <= range[3]; y++)
  {
    if(Board[xloc][yloc - y].value == 0)
    {
       openings[(yloc - y)*3 + xloc] = 1;
    }
    else
    {
      break;
    }
  }  
}
void BishopValidMoves(void)
{
  int xloc = location/3;
  int yloc = location%3;
  //set current space 1
  openings[yloc*3 + xloc] = 1;
  
  //+ x + y direction
  for(int x = xloc+1;x <= xloc + range[0]; x++)
  {
    // + y direction
    for(int y = yloc+1; y <= yloc + range[2]; y++)
    {
          if(Board[x][y].value == 0)
          {
            openings[y*3 + x] = 1;
          }
          else
          {
            break;
          }
          x++;
     }
  }
  //+x -y
  for(int x = xloc+1;x <= xloc + range[0]; x++)
  {
    // - y direction
    for(int y = 1; y <= range[3]; y++)
    {
      if(Board[x][yloc - y].value == 0)
      {
        openings[(yloc - y)*3 + x] = 1;
      }
      else
      {
        break;
      }
      x++;
    }
  }  

  //-x + y
  for(int y = yloc+1; y <= yloc + range[2]; y++)
  {
        // - x direction
      for(int x = 1;x <= range[1]; x++)
      {
        if(Board[xloc-x][y].value == 0)
        {
          openings[y*3 + (xloc-x)] = 1;
        }
        else
        {
          break;
        }
        y++;
      }
  }

  //-x -y
  for(int y = 0; y <= range[3]; y++)
  {
        // - x direction
      for(int x = 0;x <= range[1]; x++)
      {
        if(Board[x][y].value == 0)
        {
          openings[y*3 + x] = 1;
        }
        else
        {
          break;
        }
        y++;
      }
  }

}
void PawnValidMoves(void)
{
  int xloc = location/3;
  int yloc = location%3;
  //set current space 1
  openings[yloc*3 + xloc] = 1;
  //if not first row
    if(range[0] = 1)
    {
      openings[xloc*3 + 3*(yloc+1)] = 1;
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
  if(current.value == 9 || current.value == 10)
  {
    RookValidMoves();
    BishopValidMoves();
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

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(LightPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() 
{
  location = 1;
  //set all variables 0
 // range[0] = 0;
 //range[1] = 0;
  //range[2] = 0;
 //range[3] = 0;
 /*
  digitalWrite(latch2, LOW);
  for(int i = 8; i >= 0; i--)
  {
    digitalWrite(clock2, LOW);
    if(digitalRead(switchPin) == LOW);
    {
      location = i;
    }   
    digitalWrite(clock2, HIGH);
  }
  digitalWrite(latch2, HIGH);
*/
  //get switch states and location
//  for(int i = 0; i < 9; i++)
 // {
    //switchStates[i] = digitalRead(switches[i]);
  //  if(switchStates[i] != lastStates[i])
   // {
    //  location = i;
    //}
 // }
  //get piece that corresponds to location
  /*
  digitalWrite(switchLatch, LOW);
  for(int i = 8; i >= 0;i--)
  {
    digitalWrite(switchClock, LOW);
    if(digitalRead(switchPin) == HIGH)
    {
      location = i;
    } 
    digitalWrite(switchClock, HIGH);
  }
  digitalWrite(switchLatch, HIGH);
  */
  getCurrentPiece();

  //get the range of current piece
  getRange();
  //call the piece type
  callType();
  //output lights
    //output lights
    digitalWrite(latchPin, LOW);
  for(int i = 35; i >= 0; i--)
  {
      digitalWrite(clockPin, LOW);
      digitalWrite(LightPin, LOW);   
      digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);

  digitalWrite(latchPin, LOW);
  for(int i = 31; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(LightPin, HIGH);   
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
  //wait for user input
  //while(Serial.available() == 0) {}  
  //check where the piece ended 
  //for(int i = 0; i < 9; i++)
  //{
    //switchStates[i] = digitalRead(switches[i]);
   // if(switchStates[i] != lastStates[i])
    //{
     // newLocation = i;
   // }
 // }
  //write new Board location
  //Board[newLocation/3][newLocation] = current;
  //erase old location
  //Board[location/3][location].name = "Empty";

}
