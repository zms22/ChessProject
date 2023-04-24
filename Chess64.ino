#include "SimplePiece.h"

//define website
Piece Knight("Knight");
Piece Pawn("Pawn");
Piece King("King");
Piece Rook("Rook");
Piece Bishop("Bishop");
Piece Queen("Queen");
Piece Empty("Empty");
//create board
Piece Row1[8] = {Rook, Knight, Bishop, King, Queen, Bishop, King, Rook};
Piece Row2[8] = {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn};
Piece Row3[8] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};
Piece Row4[8] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};
Piece Row5[8] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};
Piece Row6[8] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};
Piece Row7[8] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};
Piece Row8[8] = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty};
Piece Board[8][8] = {Row1, Row2, Row3, Row4, Row5, Row6, Row7, Row8};
//create lights
int lights[64] = {0,1,2,3,4,5,6,7, 8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23, 24,25,26,27,28,29,30,31, 32,33,34,35,36,37,38,39,\
 40,41,42,43,44,45,46,47, 48,49,50,51,52,53,54,55, 56,57,58,59,60,61,62,63};
//create switches
int switches[64] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23, 24,25,26,27,28,29,30,31, 32,33,34,35,36,37,38,39,\
 40,41,42,43,44,45,46,47, 48,49,50,51,52,53,54,55, 56,57,58,59,60,61,62,63};
 //define switch states
int switchStates[64] = {};
//define last states of switches
int lastStates[64] = {};
//define location
int location;
int newLocation;
//define range of piece
int range[4];
//create openings
int openings[64] = {};

//get current piece
Piece getCurrentPiece(int loc)
{
  return Board[loc/8][loc%8];
}
void getRange(Piece c, int loc)
{
  int xloc = loc/8;
  int yloc = loc%8;
  int range[4] = {1,1,1,1};
  //pawn range
  if(c.name == "Pawn")
  {
    range[0] = 0;
    range[1] = 0;
    range[3] = 0;
    if(yloc < 7)
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
  if(c.name == "King")
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
    else if(yloc ==7)
    {
      range[2] = 0;
    }
  }
  if(c.name == "Rook" || "Queen" || "Bishop")
  {
    range[0] = 7 - xloc;
    range[1] = xloc;
    range[2] = 7 - yloc;
    range[3] = yloc;
  }
}
void KnightValidMoves(int loc)
{
  int xloc = loc/8;
  int yloc = loc%8;
}
void RookValidMoves(int loc)
{
  int xloc = loc/8;
  int yloc = loc%8;
  //+ x direction
  for(int x = range[0]; x++; x < 7)
  {
    if(Board[x][yloc].name == "Empty")
    {
       openings[x*8 + yloc] = 1;
    }
    else
    {
      break;
    }
  }
  // - x direction
  for(int x = 0; x++; x < range[1])
  {
    if(Board[x][yloc].name == "Empty")
    {
       openings[x*8 + yloc] = 1;
    }
    else
    {
      break;
    }
  }
  // + y direction
  for(int y = range[2]; y++; y < 7)
  {
    if(Board[xloc][y].name == "Empty")
    {
       openings[xloc*8 + y] = 1;
    }
    else
    {
      break;
    }
  }
  // - y direction
  for(int y = 0; y++; y < range[3])
  {
    if(Board[xloc][y].name == "Empty")
    {
       openings[xloc*8 + y] = 1;
    }
    else
    {
      break;
    }
  }  
}
void BishopValidMoves(int loc)
{
  int xloc = loc/8;
  int yloc = loc%8;
  // + x + y
  for(int x = range[0]; x++; x < 7)
  {
    for(int y = range[2]; y++; y < 7)
    {
        if(Board[x][y].name == "Empty")
        {
          openings[x*8 + y] = 1;
        }
        else
        {
          break;
        }
    }
  }
  // - x + y
  for(int x = 0; x++; x < range[1])
  {
    for(int y = range[2]; y++; y < 7)
    {
        if(Board[x][y].name == "Empty")
        {
          openings[x*8 + y] = 1;
        }
        else
        {
          break;
        }
    }
  }
  // - x - y
  for(int x = 0; x++; x < range[1])
  {
    for(int y = 0; y++; y < range[3])
    {
        if(Board[x][y].name == "Empty")
        {
          openings[x*8 + y] = 1;
        }
        else
        {
          break;
        }
    }
  }
  // + x - y
  for(int x = range[0]; x++; x < 7)
  {
    for(int y = 0; y++; y < range[3])
    {
        if(Board[x][y].name == "Empty")
        {
          openings[x*8 + y] = 1;
        }
        else
        {
          break;
        }
    }
  }
}

void setup() 
{
  //assign each switch and light
  for(int i = 0; i < 64; i++)
  {
    pinMode(lights[i], OUTPUT);
    pinMode(switches[i], INPUT);
    digitalWrite(lights[i], LOW);
  }
  Serial.begin(9600);
}

void loop() 
{
  //set all variables 0
  location = 0;
  range[0] = 0;
  range[1] = 0;
  range[2] = 0;
  range[3] = 0;
  for(int i = 0; i < 64; i++)
  {
    switchStates[i] = 0;
    lastStates[i] = 0;
    openings[i] = 0;
  }
  //get switch states and location
  for(int i = 0; i < 64; i++)
  {
    switchStates[i] = digitalRead(switches[i]);
    if(switchStates[i] != lastStates[i])
    {
      location = i;
    }
  }
  //get piece that corresponds to location
  Piece current = getCurrentPiece(location);
  //get the range of current piece
  getRange(current, location);
  //get name
  char name = current.name;
  //call specific options
  if(name == "Rook")
  {
    RookValidMoves(location);
  }
  if(name == "Bishop")
  {
    BishopValidMoves(location);
  }
  if(name == "Queen"|| name == "King")
  {
    RookValidMoves(location);
    BishopValidMoves(location);
  }
  if(name == "Pawn")
  {
    RookValidMoves(location);
  }
  if(name == "Knight")
  {
    KnightValidMoves(location);
  }
  //output lights
  for(int i = 0; i < 64; i++)
  {
    if(openings[i] == 1)
    {
      digitalWrite(lights[i], HIGH);
    }
  }
  //wait for user input
  while(Serial.available() == 0) {}  
  //check where the piece ended 
  for(int i = 0; i < 64; i++)
  {
    switchStates[i] = digitalRead(switches[i]);
    if(switchStates[i] != lastStates[i])
    {
      newLocation = i;
    }
  }
  //write new Board location
  Board[newLocation/8][newLocation] = current;
  //erase old location
  Board[location/8][location].name = "Empty";
}
