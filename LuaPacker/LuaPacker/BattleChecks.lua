---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Olegase.
--- DateTime: 27.04.2019 19:03
---
--- There will be all my functions

-- Функции для проверок в миссии

function checkAutoBattle()
    if (delayedAutoBattleCheck) then
        if (offReg:exists(on, 0.5)) then
            highlight(1, _, offReg);
            click(offReg:getLastMatch());
        elseif (autoBattleOffReg:exists(autoBattleOff, 0.5)) then
            click(autoBattleOffReg);
            if (cancelReg:exists(cancel, 1)) then
                highlight(1, _, cancelReg);
                click(cancelReg:getLastMatch());
            end
        end
    elseif (autoBattleCheck and not checkAutoBattleDone) then
        debugStatus("Checking auto battle");
        if (offReg:exists(off, 1)) then
            highlight(1, _, offReg);
            click(offReg:getLastMatch());
            if (cancelReg:exists(cancel, 1)) then
                highlight(1, _, cancelReg);
                click(cancelReg:getLastMatch());
            end
            checkAutoBattleDone = true;
        end
    end
end

function checkAmbush()
    debugStatus("Checking ambush");
    if (ambushReg:exists(ambush, 1)) then
        highlight(1, _, ambushReg);
        click(evadeReg);
        return true;
    end
    return false
end

function checkOnlyBossIsLeft()
    if (unableToReachTargetLocationCheck) then
        attempts = attempts - 1;
        return false;
    end
    goToTheAngle();
    debugStatus("Checking only boss is left")
    resetAttempts();
    local enemies = findAllMax(allFoe[1], battleArea, _, forbiddenRegs, allFoe[2]);
    while ((isEmpty(enemies) or (#enemies < 2 and searchBoss(enemies[1]))) and attempts > 0) do
        swipeDiagonal();
        enemies = findAllMax(allFoe[1], battleArea, _, forbiddenRegs, allFoe[2]);
    end
    onlyBossIsLeft = (attempts == 0);
    resetAttempts();
    return onlyBossIsLeft;
end

function checkHaveStartedBattle()
    debugStatus("Checking having started battle");
    if (not updateCurrentShipLocation()) then
        return false;
    end
    retreatReg = Region(currentShipReg:getX() + 70, currentShipReg:getY() + 50, 110, 110);
    if (findAllMax(retreatAll, retreatReg, _, _, retreatColorAll)) then
        for _, elem in ipairs(getLastMatches()) do
            local r, g, b = getColor(Location(elem:getX() + 9, elem:getY()));
            if (r * 2 - g - b ~= 0) then
                highlight(1, elem);
                local target = Location(elem:getX() - 80, elem:getY());
                click(target);
                return true;
            end
        end
    end
    return false;
end

function checkMissionCompleted()
    return missionModeReg:exists(attack2, 1.5);
end

function checkCurrentInMission()
    debugStatus("Checking current in mission");
    return switchReg:exists(switch, 0.5);
end

function checkAccessiblePath()
    debugStatus("Checking accessible path");
    setScanIntervalPro(0.2);
    local result = messageBoxReg:exists(unableToReachTargetLocation, 1) or handleUnexpectedConfirm();
    setScanIntervalPro(standardTimeInterval);
    unableToReachTargetLocationCheck = result;
    if (result) then
        messageBoxReg:waitVanish(unableToReachTargetLocation);
    end
    return not result;
end

function resetAttempts()
    attempts = 4;
end

function checkUnexpectedExitButton()
    debugStatus("Checking unexpected exit button");
    if (exitButtonReg:exists(exitButton, 0.5)) then
        click(exitButtonReg);
    end
end

function resetMissionSettings()
    runCounter();
    allFoe = allLv;
    resetAttempts();
    onlyBossIsLeft = false;
    fleetChanged = false;
    unableToReachTargetLocationCheck = false;
    bossElem = nil;
    shipsMoraleChecked = false;
    countOfDefeatedFoes = 0;
end

function checkShipsMorale()
    if ((not isEmpty(alternativeMobsKillerIndex)) and (not shipsMoraleChecked) and exists(green, 0.5) and (not fleetChanged)) then
        debugStatus("Checking morale");
        highlight(1);
        local flag = mobsKillerIndex == bossKillerIndex;
        mobsKillerIndex = alternativeMobsKillerIndex[Number];
        if (flag) then
            bossKillerIndex = mobsKillerIndex;
        end
        if (#alternativeMobsKillerIndex > Number) then
            Number = Number + 1;
        end
        shipsMoraleChecked = true;
    end
end