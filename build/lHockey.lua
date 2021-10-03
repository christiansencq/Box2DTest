--Potentially change to:640, 360
--Currently W = 400, H = 225
--         W/2 = 200 ; W/4 = 50
PuckRadius = 5
BallRadius = 10
Border = { WallThickness = 2, WallBuffer = 10 }
GoalSize = { 30, 60 }


p1BallStartX = (SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)
p2BallStartX = (SCREEN_WIDTH/2) + (SCREEN_WIDTH/8)

BallStartPos = { P1 = { b1 = {p1BallStartX,  3*SCREEN_HEIGHT/4},  b2 = {p1BallStartX,  2*SCREEN_HEIGHT/4},  b3 = {p1BallStartX,  1*SCREEN_HEIGHT/4} }, 
                 P2 = { b1 = {p2BallStartX, 3*SCREEN_HEIGHT/4},  b2 = {p2BallStartX, 2*SCREEN_HEIGHT/4},  b3 = {p2BallStartX, 1*SCREEN_HEIGHT/4} } }

PuckPos = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 }

ScoreDisplayPos = { P1 = { SCREEN_WIDTH/3, 10 },
                    P2 = { (2*SCREEN_WIDTH/3), 10 } }
GoalDisplayPos = { P1 = { 4*SCREEN_WIDTH/5, 90 },
                   P2 = { (SCREEN_WIDTH/5),  90 } }

TopWallPos =    { SCREEN_WIDTH/2, 6 }
BottomWallPos = { SCREEN_WIDTH/2, SCREEN_HEIGHT - 6}
LeftWallPos =   { 6, SCREEN_HEIGHT/2 }
RightWallPos =  { SCREEN_WIDTH-6, SCREEN_HEIGHT/2}
