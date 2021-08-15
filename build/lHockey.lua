
lua_arena = { WallThickness = 10, WallBuffer = 50, GoalWidth = 250, GoalHeight = 500 }

-- P1StartingPos = { x1 = 450, y1 = 640, 
--                   x2 = 450, y2 = 480,
--                   x3 = 450, y3 = 320 }
--
-- P2StartingPos = { x1 = 1150, y1 = 640, 
--                   x2 = 1150, y2 = 480, 
--                   x3 = 1150, y3 = 320 }

-- Better Data Organization.

BallStartPos = { P1 = { b1 = {450, 640},  b2 = {450, 480},  b3 = {450, 320} },
                 P2 = { b1 = {1150, 640}, b2 = {1150, 480}, b3 = {1150, 320} } }

ScoreDisplayPos = { P1 = { 150, 50 },
                    P2 = { 800, 50 } }

GoalPositions = { P1 = { 1400, 450 },
                  P2 = { 200,  450 } }

GoalSize = { 250, 500 }

Border = { WallThickness = 10, WallBuffer = 50 }
