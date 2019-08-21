---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Olegase.
--- DateTime: 01.05.2019 23:21
---

-- Основные функции для боя

function battleMission(key)
    if (key == nil and not battleMissionCheck) then
        return;
    end
    time = Timer();
    snapshot();
    local goHomePage = (not missionModeReg:exists(attack2, 0.5)) and (not checkCurrentInMission());
    usePreviousSnap(false);
    if (goHomePage) then
        goHome();
        wait(1);
        goMission();
        wait(1);
    end
    debugStatus("Battle mission")
    if (count == 0) then
        count = 9999;
    end
    while (count > 0) do
        resetMissionSettings();
        if (not checkCurrentInMission()) then
            selectingMap();
            logInBattle();
            handleUnexpectedConfirm();
            wait(1);
        else
            countOfDefeatedFoes = 99;
        end
        if (checkHaveStartedBattle()) then
            wait(1);
            fight();
        end
        while (not checkMissionCompleted()) do
            searchBattle();
        end
        count = count - 1;
        wait(1);
    end
    print("Battle: Minutes: "..string.format("%.2f", time:check() / 60));
end

function searchBattle()
    debugStatus("Search battle");
    if (((not ignoreBossCheck) or onlyBossIsLeft) and searchBoss()) then --All screen
        highlight(1, getLastMatches()[1]);
        if (bossKillerIndex ~= mobsKillerIndex and not fleetChanged) then
            changeFleet();
            setBossVisible();
        end
        bossElem = getLastMatches()[1];
        if (preparingForFight(bossElem)) then
            return;
        else
            attemptsToFightBoss = 0;
        end
    elseif (countOfDefeatedFoes >= limitOfDefeatedFoes) then
        findAllMax({item}, battleArea, list, forbiddenRegs, {_})
        for _, elem in ipairs(getLastMatches()) do
            highlight(1, elem);
            click(Location(elem:getX() + 30, elem:getY() + 110));
            if (checkAccessiblePath()) then
                handleFindPathToItem(Location(elem:getX() + 30, elem:getY() + 110));
                wait(1.5);
                click(safeClickLoc);
                click(safeClickLoc);
                if (searchBoss()) then
                    return;
                end
            end
        end
    end
    if (searchOrdinaryFoe()) then
        local foes = getLastMatches();
        for _, foe in ipairs(foes) do
            if ((not searchBoss(foe)) or (#foes == 1 and onlyBossIsLeft)) then --Only enemy zone
                if (preparingForFight(foe)) then
                    attemptsToFightBoss = 1;
                    return;
                end
            elseif (#foes == 1 and not onlyBossIsLeft) then
                debugStatus("Attempts: "..attempts);
                isAngle = not checkOnlyBossIsLeft();
                return;
            end
        end
    end
    --Foe not found or can't reach target
    if (not isAngle) then
        goToTheAngle();
    end
    swipeDiagonal()
end

function searchBoss(enemy)
    if ((bossElem == nil and (attemptsToFightBoss == 0 or countOfDefeatedFoes < limitOfDefeatedFoes))
            or (unableToReachTargetLocationCheck and enemy == nil)) then
        return false;
    end
    debugStatus("Search boss");
    local searchZone;
    if (allFoe == allLv) then
        searchZone = enemy == nil and battleArea or Region(enemy:getX() - 80, enemy:getY() - 90, 160, 130);
    else
        searchZone = enemy == nil and battleArea or Region(enemy:getX() - 120, enemy:getY() - 110, 160, 130);
    end
    local result = isEmpty(findAllMax({boss}, searchZone, _, _, bossColorAll));
    if (not result) then
        highlight(1, lastMatch[1]);
    end
    return not result;
end

function setBossVisible()
    debugStatus("Set boss visible");
    if (not searchBoss()) then
        goToTheAngle();
        resetAttempts();
        while (not searchBoss()) do
            swipeDiagonal();
        end
    end
end

function searchOrdinaryFoe()
    debugStatus("Search ordinary foe");
    if (standardSwipeCheck and attempts <= 0) then
        isAngle = false;
        standardSwipeCheck = false;
    elseif (attempts <= 0) then
        changeFoe();
        isAngle = false;
        standardSwipeCheck = true;
    end
    if (attemptsToFightBoss == 0) then
        return findAllMax(allFoe[1], battleArea, list, forbiddenRegs, allFoe[2], bossElem);
    else
        return findAllMax(allFoe[1], battleArea, list, forbiddenRegs, allFoe[2]);
    end
end

function preparingForFight(enemy)
    debugStatus("Preparing for fight");
    highlight(1, enemy);
    click(enemy);
    if (checkAccessiblePath()) then
        handleAmbush(enemy);
        if (attemptsToReachEnemy == 0) then
            return false;
        end
        fight();
        return true;
    end
    return false;
end

function fight()
    checkUnexpectedExitButton();
    checkShipsMorale();
    checkAutoBattle();
    click(battleButtonReg:getCenter());
    wait(0.5);
    snapshot();
    if (handleDockIsFull()) then
        wait(0.5);
        click(battleButtonReg:getCenter());
    end
    if (messageBoxReg:exists(yourShipsOutOfOil, 1)) then
        usePreviousSnap(false);
        scriptExit("Your ships out of oil");
    end
    usePreviousSnap(false);
    debugStatus("Fight");
    click(battleButtonReg:getCenter());
    wait(20 / speedRate);
    checkAutoBattle();

    if (manualBattleCheck) then
        manualFight();
    else
        debugStatus("Tap to continue 1");
        setScanIntervalPro(2);
        tapToContinueReg:exists(tapToContinue, 300);
        setScanIntervalPro(standardTimeInterval);
        highlight(1, _, tapToContinueReg);
        click(tapToContinueReg:getLastMatch());
    end

    debugStatus("Tap confirm 1");
    while (not confirmReg1:exists(confirm1, 0.5)) do
        tapConfirmBadFlag = switchReg:exists(switch, 0.5) or confirmReg2:exists(confirm2, 0.5);
        if (tapConfirmBadFlag) then
            break;
        end
        click(tapToContinueReg);
    end
    if (not tapConfirmBadFlag) then
        highlight(1, _, confirmReg1);
        click(confirmReg1:getCenter());
    end
    wait(2);
    handleUnexpectedConfirm();
    resetAttempts();
    countOfDefeatedFoes = countOfDefeatedFoes + 1;
end

function manualFight()
    debugStatus("Manual fight");
    setScanIntervalPro(acceleratedTimeInterval);
    while true do
        if (aviationCheck) then
            if (confirmReg1:exists(confirm1, 0.3 / speedRate)) then
                break;
            end
            click(aviationLoc);
        end
        if (torpedoCheck) then
            if (confirmReg1:exists(confirm1, 0.3 / speedRate)) then
                break;
            end
            click(torpedoLoc);
        end
        if (artilleryCheck) then
            if (confirmReg1:exists(confirm1, 0.3 / speedRate)) then
                break;
            end
            click(artilleryLoc);
            click(moveLoc);
            wait(3.5 / speedRate);
        end
    end
    setScanIntervalPro(standardTimeInterval);
end

function goToTheLeftAngle()
    debugStatus("Go to the left angle")
    for _ = 1, 2 do
        swipe(center, Location(center:getX() * 1.9, center:getY() * 1.9))
    end
    isAngle = true
end

function goToTheRightAngle()
    debugStatus("Go to the right angle")
    for _ = 1, 2 do
        swipe(center, Location(center:getX() * 0.1, center:getY() * 1.9))
    end
    isAngle = true
end

function goToTheAngle()
    if (standardSwipeCheck) then
        goToTheLeftAngle();
    else
        goToTheRightAngle();
    end
end

function changeFleet()
    switchReg:exists(switch, 1);
    highlight(1, _, switchReg);
    click(switchReg:getLastMatch());
    fleetChanged = true;
    wait(2);
end

function selectingMap()
    if (normalReg:exists(normal)) then
        normalCheck = true;
    end
    if (not mapSelected) then
        debugStatus("Selecting map");
        local _, locTable, _ = getTouchEvent();
        missionReg = Region(locTable:getX() - 15, locTable:getY() - 15, 30, 30);
        inProgressReg2 = Region(missionReg:getX() - 120, missionReg:getY() - 120, 260, 260);
        mapSelected = true;
    end
end

function logInBattle()
    debugStatus("Log in battle");
    setScanIntervalPro(acceleratedTimeInterval);
    if (not inProgressReg2:exists(inProgress2, 1)) then
        setScanIntervalPro(standardTimeInterval);
        click(missionReg);
        highlight(1, goButtonReg1:exists(goButton1));
        click(goButtonReg1:getLastMatch());
        wait(0.5);
        if (handleDockIsFull()) then
            click(missionReg);
            highlight(1, goButtonReg1:exists(goButton1));
            click(goButtonReg1:getLastMatch());
            wait(0.5);
        end
        selectFleet();
        highlight(1, goButtonReg2:exists(goButton2));
        click(goButtonReg2:getLastMatch());
    else
        highlight(1, _, inProgressReg2);
        click(missionReg);
        countOfDefeatedFoes = 5;
    end
    setScanIntervalPro(standardTimeInterval);
    wait(1);
end

function selectFleet()
    if (normalCheck) then
        return;
    end
    debugStatus("Selecting fleet");
    click(SelectFleetClear2);
    click(SelectFleetClear3);
    click(SelectFleetChoose1);
    click(selectFleetReg:exists(selectFleetAll[mobsKillerIndex], 0.3) or selectFleetReg:exists(selectFleetAllSelected[mobsKillerIndex], 0.3));
    if (bossKillerIndex ~= mobsKillerIndex) then
        wait(0.2);
        click(SelectFleetChoose2);
        click(selectFleetReg:exists(selectFleetAll[bossKillerIndex], 0.3) or selectFleetReg:exists(selectFleetAllSelected[bossKillerIndex], 0.3));
    end
    if (submarineIndex ~= 3) then
        wait(0.2);
        click(SelectFleetChoose3);
        click(selectFleetReg:exists(selectFleetAll[submarineIndex], 0.3) or selectFleetReg:exists(selectFleetAllSelected[submarineIndex], 0.3));
    end
end

function swipeDiagonal()
    debugStatus("SwipeDiagonal")
    if (standardSwipeCheck and attempts > 0) then
        swipe(center, Location(center:getX() * 0.75, center:getY() * 0.45));
    elseif (attempts > 0) then
        swipe(center, Location(center:getX() * 1.25, center:getY() * 0.45));
    end
    attempts = attempts - 1;
    showAttempts();
end

function changeFoe()
    debugStatus("Change foe");
    if (allFoe == allLv) then
        allFoe = allEnemyRank;
    else
        allFoe = allLv;
    end
    resetAttempts();
end