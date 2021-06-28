
Compiled on Linux(Kubuntu 20.10) with g++.  Built with Cmake/makefiles.

This is a simple ECS game engine integrating the Box2D physics library with SDL for input/output.

The Ice Hockey game implemented is within the 'GameMatchState'.  
The objective gameplay is a 1v1 hockey game/ 'slow' RTS, where the unpredictability and challenge of planning commands for units and working with 'friendly/team ai' 
are replaced by inertia, and potentially delayed and interacting responses from the physics engine. So instead of the non-selected player on the hockey team making decision
based on their AI while you don't control them, the resolution of ongoing physical events will determine their behavior.  The gameplay might also compared to 'real-time pool',
especially when more 'impulse' (rather than 'force') -based abilities are implemented.  Allow for the eventual possibility of differentiating the abilities and attributes of
each ball, so player balls could be drafted to fill different roles (like Dota 2, Overwatch) from a diverse cast of characters (such as the variety found in boardgames like
Battlecon, Unmatched, or the Funkoverse game) with different approaches to winning.

Controls by default are:

    Player 1

Up key       - Forward
Down key     - Backward
Left key     - Rotate Left
Right key    - Rotate Right
i key        - Swap to Ball 1
o key        - Swap to Ball 2
p key        - Swap to Ball 3

    Player 2

w key       - Forward
a key     - Backward
s key     - Rotate Left
d key    - Rotate Right
v key        - Swap to Ball 1
b key        - Swap to Ball 2
n key        - Swap to Ball 3

TODO:
    Create additional states for: Main Menu(EntryPoint),
                                  MatchSetUp (Set many of the variables currently "statically" determined in the Initialization of the GameState),
                                  Pause
    Finish Score tracking.
