# Risk Strategy Game (Systems Final Project)
By Flora Au, David Chong, and Kirsten Szeto -- PD 5

Risk is a complex board game produced by Hasbro that involves both luck and skill. The goal is simple: take over the world.  (Taken from Google)

We are creating a turn-based strategy game based off this idea that involves capturing territory.  


## Basic Rundown

Two users will connect to a server, and the game will commence.

Each player will start in a corner, and can capture territory adjacent to their owned squares.  The end goal of the game is to own all the locations in the map(or more likely just more than half of the board).

## How the game works

Each user starts in a corner, and can capture squares adjacent to their owned squares.  Once they decide on a target color, they will switch all of their owned squares to that color, and all of the unowned squares with that color adjacent to an owned block will be claimed.  

There are certain restrictions, as you cannot change to the color you are currently, and you cannot change to your opponents color.  There are 6 in total, which usually leaves 4 colors to change to. 

## How it will involve class concepts

- All players will connect to a common server
- Server will push out identical boards to each user through pipes
- Players will have to send requests back to the server for their turn
- Each user's data will be malloced so that after each turn the data is not lost
- Will use signals for turn termination.

## Who is responsible for which parts

Flora - Server and pipes

Kirsten - Graphical Interface

David - Game design

## Data Structures and Algorithms

We will be using structs for each individual portion

Different players will also have their respective stats stored in player structs

## Timeline

Display Board with general server connection capabilities by 1/16/22

Users are able to send turn based action requests(ie attack or fortify) to the server by 1/19/22

Additional features like having a GUI instead of typing in the commands might be implemented by 1/23/22, which we are assuming is the due date.





