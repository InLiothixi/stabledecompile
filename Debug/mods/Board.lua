math.randomseed(os.time())

function GetNumWaves(gamemode, level, waves, stage)
    return -1
end

function GetZombiePoints(gamemode, level, wave, points, stage)
    return -1
end

function PickZombieWaves(gamemode, level, wave, points, stage, isflag, isfinalflag, board, picker)
end

function GetLevelName(gamemode, level, name)
    return nil
end

function GetBackground(gamemode, level, background)
    return -1
end

function UpdateGame(board, gamemode, level, wave, stage)
end

-- Commands
-- TodStringTranslate(name)
-- PutZombieInWave(board, type, wave, picker) USE ONLY AT PickZombieWaves(...
-- ChangeBackground(board, id)
-- ChangeMusic(board, id)
