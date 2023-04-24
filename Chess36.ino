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
//create board
Piece Board[36] = {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,\
              Empty,Empty,Empty,Knight,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty};
//Piece Board[6][6] = {{Empty,Empty,Empty,Empty,Empty,Empty},{Empty,Empty,Knight,Empty,Empty,Empty},{Empty,Empty,Empty,Empty,Empty,Empty},\
              {Empty,Empty,Empty,Empty,Empty,Empty},{Empty,Empty,Empty,Empty,Empty,Empty},{Empty,Empty,Empty,Empty,Empty,Empty}};
//light information
int clockPin = 6;
int latchPin = 5;
int LightPin = 4;
//switch information
int switchPin = 1;
int load = 10;
int clockPulse = 9;
int clockEnable = 7;
//define switch states
int switchValues[36];
//define last states of switches
int lastStates[36] = {1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0};
//define locations
int location;
int newLocation;
//define range of piece
int range[4];
//create openings
int openings[36];
//get temp piece
Piece current = {Empty};

//functions
void getCurrentPiece(void)
{
  //current = Board[location/6][location%6];
  current = Board[location];
}
void getRange(void)
{
  int xloc = location/6;
  int yloc = location%6;
  //pawn range
  if(current.value == 1)
  {
    range[0] = 0;
    range[1] = 0;
    range[3] = 0;
    if(yloc < 5)
    {
      range[2] = 1;
    }
    else
    {
      range[2] = 0;
    }
  }
  if(current.value == 10)
  {

    if(xloc == 0)
    {
      range[1] = 0;
    }
    else if(xloc == 5)
    {
      range[0] = 0;
    }
    else if(yloc == 0)
    {
      range[3] = 0;
    }
    else if(yloc == 5)
    {
      range[2] = 0;
    }
  }
  if(current.value == 5 || 9 || 4)
  {
    range[0] = 5 - xloc;
    range[1] = xloc;
    range[2] = 5 - yloc;
    range[3] = yloc;
  }
}
void KnightValidMoves(void)
{/*
  int xloc = location/6;
  int yloc = location%6;
  //set current space 1
  openings[yloc*6 + xloc] = 1;
  if(xloc+2 < 5)
  {
    //over 2 up 1
    if(yloc + 1 < 5 && Board[xloc+2][yloc+1].value == 0)
    {
      openings[6*(xloc+2) + (yloc+1)] = 1;
    }
    //over 2 down 1
    if(yloc -1  > 0 && Board[xloc+2][yloc-1].value == 0)
    {
      openings[6*(xloc+2) + (yloc-1)] = 1;
    }
  }
  if(xloc + 1 < 5)
  {
    if(yloc + 2 < 5 && Board[xloc+1][yloc+2].value == 0)
    {
        openings[6*(xloc+1) + yloc + 2] = 1;
    }
    else if(yloc - 2 > 0 && Board[xloc+1][yloc-2].value == 0)
    {
        openings[6*(xloc+1) + yloc - 2] = 1;
    }
  }
  else if(xloc - 1 >= 0)
  {
    if(yloc + 2 < 5 && Board[xloc-1][yloc+2].value == 0)
    {
        openings[6*(xloc-1) + yloc + 2] = 1;
    }
    else if(yloc - 2 > 0 && Board[xloc-1][yloc-2].value == 0)
    {
        openings[6*(xloc-1) + yloc - 2] = 1;
    }
  }
  else if(xloc-2 >= 0)
  {
    //over 2 up 1
    if(yloc + 1 < 5 && Board[xloc-2][yloc+1].value == 0)
    {
      openings[6*(xloc+2) + (yloc+1)] = 1;
    }
    //over 2 down 1
    else if(yloc -1  >= 0 && Board[xloc-2][yloc-1].value == 0)
    {
      openings[6*(xloc+2) + (yloc-1)] = 1;
    }
  }
  */
    //set current space 1
  openings[location] = 1;
  
  if(Board[location+8].value == 0)
  {
	  openings[location+8] = 1;
  }
  if(Board[location+4].value == 0)
  {
	  openings[location+4] = 1;
  }
  if(Board[location-8].value == 0)
  {
	  openings[location-8] = 1;
  }
  if(Board[location-11].value == 0)
  {
	  openings[location-11] = 1;
  }
   if(Board[location+11].value == 0)
  {
	  openings[location+11] = 1;
  }
  if(Board[location+13].value == 0)
  {
	  openings[location+13] = 1;
  }
  if(Board[location-13].value == 0)
  {
	  openings[location-13] = 1;
  }
  if(Board[location-4].value == 0)
  {
	  openings[location-4] = 1;
  }

}
/*
void RookValidMoves(void)
{
  int xloc = location/6;
  int yloc = location%6;
  //set current space 1
  openings[yloc*6 + xloc] = 1;
  //+ x direction
  for(int x = xloc+1;x <= xloc + range[0]; x++)
  {
    if(Board[x][yloc].value == 0)
    {
       openings[yloc*6 + x] = 1;
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
       openings[yloc*6 + (xloc-x)] = 1;
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
       openings[y*6 + xloc] = 1;
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
       openings[(yloc - y)*6 + xloc] = 1;
    }
    else
    {
      break;
    }
  }  
}
void BishopValidMoves(void)
{
  int xloc = location/6;
  int yloc = location%6;
  //set current space 1
  openings[yloc*6 + xloc] = 1;
  int count = 0;
  //+ x + y direction
  for(int x = xloc+1;x <= xloc + range[0]; x++)
  {
    // + y direction
    for(int y = yloc+1; y <= yloc + range[2]; y++)
    {
          if(Board[x][y].value == 0)
          {
            openings[y*6 + x] = 1;
          }
          else
          {
            count = 1;
            break;
          }
          x++;
     }
     if(count == 1)
     {
       break;
     }
  }

  //+x -y
  count = 0;
  for(int x = xloc+1;x <= xloc + range[0]; x++)
  {
    // - y direction
    for(int y = 1; y <= range[3]; y++)
    {
      if(Board[x][yloc - y].value == 0)
      {
        openings[(yloc - y)*6 + x] = 1;
      }
      else
      {
        count = 1;
        break;
      }
      x++;
    }
    if(count == 1)
    {
      break;
    }
  }  

  //-x + y
  count = 0;
  for(int y = yloc+1; y <= yloc + range[2]; y++)
  {
        // - x direction
      for(int x = 1;x <= range[1]; x++)
      {
        if(Board[xloc-x][y].value == 0)
        {
          openings[y*6 + (xloc-x)] = 1;
        }
        else
        {
          count = 1;
          break;
        }
        y++;
      }
      if(count == 1)
      {
        break;
      }
  }

  //-x -y
  count = 0;
  for(int y = 0; y <= range[3]; y++)
  {
        // - x direction
      for(int x = 0;x <= range[1]; x++)
      {
        if(Board[x][y].value == 0)
        {
          openings[y*6 + x] = 1;
        }
        else
        {
          count =1;
          break;
        }
        y++;
      }
      if(count ==1)
      {
        break;
      }
  }

}
void PawnValidMoves(void)
{
  int xloc = location/6;
  int yloc = location%6;
  //set current space 1
  openings[yloc*6 + xloc] = 1;
    if(range[2] == 1)
    {
      openings[yloc*6 + xloc+1] = 1;
    }
}
*/
void callType(void)
{
  if(current.value == 5)
   {
   // RookValidMoves();
  }
  if(current.value == 4)
  {
   // BishopValidMoves();
  }
  if(current.value == 9 || current.value == 10)
  {
   // RookValidMoves();
   // BishopValidMoves();
  }
  if(current.value == 1)
  {
   // PawnValidMoves();
  }
  if(current.value == 3)
  {
    KnightValidMoves();
  }
}

//main setup
void setup() 
{
  //lights
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(LightPin, OUTPUT);
  //switches
  pinMode(switchPin, INPUT);
  pinMode(load, OUTPUT);
  pinMode(clockPulse, OUTPUT);
  pinMode(clockEnable, OUTPUT);
}
//main loop
void loop() 
{
  //set all variables 0
  range[0] = 0;
  range[1] = 0;
  range[2] = 0;
  range[3] = 0;

  //write all the lights low
  digitalWrite(latchPin, LOW);
  for(int i = 35; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(LightPin, LOW);   
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
  /*
  //wait for inital removal
  int count = 0;
  while(count == 0)
  {
    //read in state change
    digitalWrite(ioSelect, 0);
    digitalWrite(clockPulse, 0);
    digitalWrite(clockPulse,1);
    digitalWrite(ioSelect, 1);

    for(int i = 35; i >= 0; i--)
    {
      switchValues[i] = digitalRead(switchPin);
      if(switchValues[i] != lastStates[i])
      {
        count++;
      }
      digitalWrite(clockPulse, LOW);
      digitalWrite(clockPulse, HIGH);
    }
  } 

  //read in all switch information
  digitalWrite(ioSelect, 0);
  digitalWrite(clockPulse, 0);
  digitalWrite(clockPulse,1);
  digitalWrite(ioSelect, 1);

  for(int i = 35; i >= 0; i--)
  {
    switchValues[i] = digitalRead(switchPin);
    if(switchValues[i] == 0 && lastStates[i] == 1)
    {
      location = 1;
      lastStates[i] = 0;
    }
    digitalWrite(clockPulse, LOW);
    digitalWrite(clockPulse, HIGH);
  }
  */
  location = 21;
  //get current piece
  getCurrentPiece();
  //get the range of current piece
  getRange();
  //call the piece type and fill openings
  callType();
  
  //read in all switch information
  /*
  byte overall;
  for(int i = 0; i < 5; i++)
  {
    digitalWrite(load, LOW);
    digitalWrite(load, HIGH);
    digitalWrite(clockPulse, HIGH);
    digitalWrite(clockEnable,LOW);
    byte incoming = shiftIn(switchPin, clockPulse, LSBFIRST);
    overall = overall + incoming;
    digitalWrite(clockEnable, HIGH);
  }
  */
  //location = log(overall)/log(2);
  /*
  for(int i = 0; i < 5; i++)
  {
    //output lights
    digitalWrite(latchPin, LOW);
    shiftOut(LightPin, clockPin,MSBFIRST, openings);
    digitalWrite(latchPin, HIGH);
  }
  */
    digitalWrite(latchPin, LOW);
  for(int i = 35; i >= 0; i--)
  {
      digitalWrite(clockPin, LOW);
      digitalWrite(LightPin, openings[i]);   
      digitalWrite(clockPin, HIGH);
  }
      digitalWrite(latchPin, HIGH);
  /*
  //wait for piece to be placedd down
  count = 0;
  while(count == 0)
  {
    //read in state change
    digitalWrite(ioSelect,0);
    digitalWrite(clockPulse,0);
    digitalWrite(clockPulse,1);
    digitalWrite(ioSelect,1);

    for(int i = 35; i >= 0; i--)
    {
      switchValues[i] = digitalRead(switchPin);
      if(switchValues[i] != lastStates[i])
      {
        count++;
      }
      digitalWrite(clockPulse, LOW);
      digitalWrite(clockPulse, HIGH);
    }
  } 

  //get new location
  digitalWrite(ioSelect, 0);
  digitalWrite(clockPulse, 0);
  digitalWrite(clockPulse,1);
  digitalWrite(ioSelect, 1);

  for(int i = 35; i >= 0; i--)
  {
    switchValues[i] = digitalRead(switchPin);
    if(switchValues[i] == 1 && lastStates[i] == 0)
    {
      newLocation = i;
      lastStates[i] = 1;
    }
    digitalWrite(clockPulse, LOW);
    digitalWrite(clockPulse, HIGH);
  }

  //write new Board location
  Board[newLocation/6][newLocation%6] = current;
  //erase old location
  Board[location/6][location%6].value = 0;
  */
}
