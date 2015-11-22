count = 0
curScore = 0
curMove = 0

stateString = ""

function tellme()
        --local file = io.open("example.txt", "w")
        --file:write("This is coming from lua.tellme.\n".. "count = " .. count .. "\n")
        count = count + 1;
end


function square(n)
        --squared = n*n
        --[[local file = io.open("example.txt", "a")
        file:write("the square of " .. n .. " is " .. squared .. "\n")
        file:write("count = " .. count .. "\n")
        return(squared)]]--
end


function setCurrentScore(score)
    curScore = score
    local file = io.open("score.txt", "w")
    file:write("curScore = " .. curScore .. "\n")
end

function setCurrentMove(move)
    curMove = move
    local file = io.open("move.txt", "w")
    file:write("curMove = " .. curMove .. "\n")
end

-- NOTE this will have all of the text including things we don't really want
-- like the score and curMove
-- and special characters
-- and the begining text of the game
-- will have to clean that out.
function appendState(word)
    stateString = stateString .. " " .. word;

    local file = io.open("stateString.txt", "w")
    file:write("stateString = " .. stateString .. "\n")
    file:flush();
    file:close();
end


function getAction() 
    me = "Open the mailbox.";
    --stateString = ""
    return me, tonumber(string.len(me));
end

function writeIt(val)
    local file = io.open("scratch.txt", "a")
    file:write("buf = " .. val .. "\n")
    file:flush();
    file:close();
end