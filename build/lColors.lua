
-- while(lua_istable(L, -1)
--                          r    g    b    a
-- Colors = {   WHITE     = { 255, 255, 255, 255 },
--              BLACK     = {   0,   0,   0, 255 },
--              RED       = { 250,   5,   5, 255 },
--              GREEN     = {   5, 240,   5, 255 },
--              LT_GREEN  = { 110, 250, 110, 255 },
--              BLUE      = {   5,   5, 250, 255 },
--              PURPLE    = { 200,   5, 200, 255 },
--              ORANGE    = { 200, 120,  15, 255 },
--              LT_ORANGE = { 250, 180,  95, 255 } }

local WHITE     = { 255, 255, 255, 255 }
local BLACK     = {   0,   0,   0, 255 }
local RED       = { 250,   5,   5, 255 }
local GREEN     = {   5, 240,   5, 255 }
local LT_GREEN  = { 110, 250, 110, 255 }
local BLUE      = {   5,   5, 250, 255 }
local PURPLE    = { 200,   5, 200, 255 }
local ORANGE    = { 200, 120,  15, 255 }
    
local Player_Selector_Colors = { GREEN, ORANGE }

local Default_Text_Color = PURPLE;

local index = ...
function ColorLoad(index)
    r = Player_Selector_Colors[index][1]
    g = Player_Selector_Colors[index][2]
    b = Player_Selector_Colors[index][3]
    a = Player_Selector_Colors[index][4]

    print("[Lua] Color "..index.." loaded. Values : r = "..r.." g = "..g.." b = "..b.." a = "..a)
    return r, g, b, a
end

-- P1SelColor = Colors[GREEN]
-- P2SelColor = Colors[ORANGE]

-- Player_Selector_Colors = { Colors[GREEN], Colors[ORANGE] }
-- Player_Score_Display_Colors = { Colors[GREEN], Colors[ORANGE] }
-- Player_Goal_Zone_Colors = { Colors[LT_GREEN], Colors[LT_ORANGE] }

