
## HockeyGame

Compiled on Linux(Kubuntu 20.10) with g++.  Built with [Cmake](https://cmake.org).

This is a simple physics Hockey game & built-from-scratch engine which uses (along with the STL)
 - [Box2D](https://box2d.org) for physics simulation. 
 - [SDL2](https://www.libsdl.org/) for graphics, keyboard input, and text.
 - [Lua](https://www.lua.org) for Scripting/Variable manipulation.
 - [Sol](https://www.github.com/ThePhD/sol2) for binding Lua to C++.


The engine itself utilizes a finite state-machine for game states, a command system for unique and varied abilities, and an Entity-Component system for creating unique, manageable game entities.


The Ice Hockey game is implemented within the 'GameMatchState'. 

###Design

The objective gameplay is a 1v1 hockey game/ 'slow' RTS, where the unpredictability and challenge of planning commands for units and working with 'friendly/team ai' 
are replaced by inertia, and potentially delayed and interacting responses from the physics engine. So instead of the non-selected player on the hockey team making decision
based on their AI while you don't control them, the resolution of ongoing physical events will determine their behavior.  The gameplay might also compared to a slow 'real-time pool',
especially when more 'impulse' (rather than 'force') -based abilities are implemented.  Allow for the eventual possibility of differentiating the abilities and attributes of
each ball, so player balls could be drafted to fill different roles (like Dota 2, Overwatch) from a diverse cast of characters (such as the variety found in boardgames like
Battlecon, Unmatched) with different approaches to winning.

###Controls 

By default are: (Should soon be configurable in the Lua script)

    Player 1
Up key       - Forward
Down key     - Backward
Left key     - Rotate Left
Right key    - Rotate Right
i key        - Swap to Ball 1
o key        - Swap to Ball 2
p key        - Swap to Ball 3

    Player 2
w key        - Forward
a key        - Backward
s key        - Rotate Left
d key        - Rotate Right
v key        - Swap to Ball 1
b key        - Swap to Ball 2
n key        - Swap to Ball 3



###TODO:
    Create additional states for: Main Menu(EntryPoint),
                                  MatchSetUp (Set many of the variables currently "statically" determined in the Initialization of the GameState),
                                  Pause

    Implement control customization through Lua script.
