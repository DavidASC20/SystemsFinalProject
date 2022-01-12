# Risk Strategy Game (Systems Final Project)
By Flora Au, David Chong, and Kirsten Szeto -- PD 5
Risk is a complex board game produced by Hasbro that involves both luck and skill. The goal is simple: take over the world.  (Taken from Google)

We are creating a turn-based strategy game that involves raising troops and capturing territory.  


## Basic Rundown

Users will connect to a server, and once enough users have connected/all users vote to start the game, the game will commence.

Each player will start with a set amount of troops, and can place them on the map that we will create.  The end goal of the game is to own all the locations in the map(most likely in a grid format).

With
Currently, there are 3 different parts of the game.

<ul>
  <li>Placing New Armies</li>
  <li>Fighting</li>
  <li>Fortifying</li>
</ul>

Below will be a more in-depth look at each phase

## Placing New Armies

The amount added to your total count would be based off of a number of factors that are up for discussion

We can also points for different territories on the map(think continent based)

We might also implement cards?  Also up for discussion


## Fighting

Fighting will be based off the amount of troops at a square, and look at both attacking and defending amounts.

This is also up for discussion, as we want a well balanced game

## Fortifying

At the end of each turn, players can move any amt of troops from a single territopry they own into an adjacent territory that they also own.  

## How it will involve class concepts

- All players will connect to a common server
- Server will push out identical boards to each user through pipes
- Players will have to send requests back to the server for their turn (Ex: Attack request with location, troop usage, + other stats)
- Each user's data will be malloced so that after each turn the data is not lost
- Will use signals for turn termination.
- Card features will require storage + file work (an additional feature to be implemented)

## Who is responsible for which parts

We will be working together at Dojo to make a working board and a one player version first since this is pretty involved. Multplayer implementation work will be redistributed when we get to that stage. (Will update README accordingly)

## Data Structures and Algorithms

We will be using structs for different action requests (Ex: Attack struct will have troop distribution counter, location string etc...)

Different players will also have their respective stats stored in player structs

(Still working on researching helpful algorithms)

## Timeline

Display Board with general server connection capabilities by 1/16/22

Users are able to send turn based action requests(ie attack or fortify) to the server by 1/19/22

Additional features like having a GUI instead of typing in the commands might be implemented by 1/23/22, which we are assuming is the due date.





