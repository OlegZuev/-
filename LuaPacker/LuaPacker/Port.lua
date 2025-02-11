---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Olegase.
--- DateTime: 01.05.2019 23:19
---

-- Функции для порта

function settingsBot()
    settingOverall();
    if (battleMissionCheck or dailyMissionCheck or sosMissionCheck) then
        settingsFight();
    end
    if (battleMissionCheck or sosMissionCheck) then
        settingsFleetSelect();
        settingsAlternativeMobsKiller()
        settingsCombat();
    end
    if (dailyMissionCheck) then
        settingsDaily();
    end
end

function settingOverall()
    dialogInit();
    addTextView("-- Select modes");
    newRow();
    addCheckBox("battleMissionCheck", "Battle", true);
    newRow();
    addCheckBox("dailyMissionCheck", "Daily", true);
    newRow();
    addCheckBox("sosMissionCheck", "SoS Signal", true);
    newRow();
    addTextView("-- Select extra options");
    newRow();
    addCheckBox("pro2Check", "Optimization (Pro2 only)", true);
    newRow();
    addCheckBox("Debug", "Debug mode(Highlight actions and show box status)", false);
    newRow();
    dialogShow("Azur Lane Bot v1.2");
    setScanIntervalPro(standardTimeInterval);
end

function settingsFight()
    dialogInit();
    addTextView("-- Select fight's options");
    newRow();
    addCheckBox("autoBattleCheck", "Checking AutoBattle", true);
    newRow();
    addCheckBox("delayedAutoBattleCheck", "Checking AutoBattle with delay in combat", true);
    newRow();
    addTextView("-- Manual fight");
    newRow();
    addCheckBox("aviationCheck", "Auto aviation skill activation", false);
    newRow();
    addCheckBox("torpedoCheck", "Auto torpedo skill activation", false);
    newRow();
    addCheckBox("artilleryCheck", "Auto artillery skill activation", false);
    newRow();
    addTextView("   Skill activation speed rate(1 = 100%)");
    addEditNumber("speedRate", 1.0);
    newRow();
    dialogShow("Fight's settings");
    manualBattleCheck = aviationCheck or torpedoCheck or artilleryCheck;
end

function settingsFleetSelect()
    dialogInit();
    addTextView("-- Index number of mobs killer fleet should be lower than boss killer one");
    newRow();
    addTextView("-- Select fleet for mobs fight");
    newRow();
    addRadioGroup("mobsKillerIndex", 1);
    addRadioButton("First fleet", 1);
    addRadioButton("Second fleet", 2);
    addRadioButton("Third fleet", 3);
    addRadioButton("Fourth fleet", 4);
    newRow();
    addTextView("-- Select fleet for boss fight");
    newRow();
    addRadioGroup("bossKillerIndex", 1);
    addRadioButton("First fleet", 1);
    addRadioButton("Second fleet", 2);
    addRadioButton("Third fleet", 3);
    addRadioButton("Fourth fleet", 4);
    newRow();
    addTextView("-- Select submarine");
    newRow();
    addRadioGroup("submarineIndex", 1);
    addRadioButton("First fleet", 1);
    addRadioButton("Second fleet", 2);
    addRadioButton("Off", 3);
    newRow();
    addCheckBox("alternativeMobsKillerIndexCheck", "Replace mobs killer fleet when morale go low", false);
    newRow();
    dialogShow("Fleet Select");
end

function settingsAlternativeMobsKiller()
    if (not alternativeMobsKillerIndexCheck) then
        return;
    end
    dialogInit();
    addTextView("-- Index number of additional mobs killer fleet should be lower than boss killer one");
    newRow();
    addTextView("-- Select additional fleet for mobs fight");
    newRow();
    if ((mobsKillerIndex ~= 1 and bossKillerIndex > 1)
            or (mobsKillerIndex == bossKillerIndex and mobsKillerIndex ~= 1)) then
        addCheckBox("FirstFleet", "First fleet", true);
        newRow();
    else
        FirstFleet = false;
    end
    if ((mobsKillerIndex ~= 2 and bossKillerIndex > 2)
            or (mobsKillerIndex == bossKillerIndex and mobsKillerIndex ~= 2)) then
        addCheckBox("SecondFleet", "Second fleet", true);
        newRow();
    else
        SecondFleet = false;
    end
    if ((mobsKillerIndex ~= 3 and bossKillerIndex > 3)
            or (mobsKillerIndex == bossKillerIndex and mobsKillerIndex ~= 3)) then
        addCheckBox("ThirdFleet", "Third fleet", true);
        newRow();
    else
        ThirdFleet = false;
    end
    if (mobsKillerIndex == bossKillerIndex) then
        addCheckBox("FourthFleet", "Fourth fleet", true);
        newRow();
    else
        FourthFleet = false;
    end
    dialogShow("Additional Fleet Select");
    alternativeMobsKillerIndex = {};
    additionalFleets = {FirstFleet, SecondFleet, ThirdFleet, FourthFleet};
    for i, elem in ipairs(additionalFleets) do
        if (elem) then
            table.insert(alternativeMobsKillerIndex, i);
        end
    end
    Number = 1;
end

function settingsCombat()
    dialogInit();
    newRow();
    addCheckBox("ignoreBossCheck", "Ignore boss", false);
    newRow();
    addCheckBox("runCounterCheck", "Run counter", false);
    newRow();
    addTextView("-- Which angle to move camera in absence of enemies first");
    newRow();
    addRadioGroup("angleFirst", 1);
    addRadioButton("Left angle", 1);
    addRadioButton("Right angle", 2);
    newRow();
    addTextView("  After how many defeated enemies begin search boss: ");
    addEditNumber("limitOfDefeatedFoes", 4);
    newRow();
    if (battleMissionCheck) then
        addTextView("  Count battles(0 = inf)");
        addEditNumber("count", 0);
        newRow();
    end
    dialogShow("Mission's settings");
    resetAttempts();
    standardSwipeCheck = (angleFirst == 1);
end

function goHome()
    debugStatus("Go home");
    while not dockReg:exists(dock1, 1) do
        if backReg:exists(back, 1) then
            highlight(1, _, backReg);
            click(backReg:getLastMatch());
        elseif backDormReg:exists(backDorm, 1) then
            highlight(1, _, backDormReg);
            click(backDormReg:getLastMatch());
        end
    end
    highlight(1, _, dockReg);
end

function goMission()
    debugStatus("Go mission");
    attackReg:exists(attack1, 1);
    highlight(1, _, attackReg);
    click(attackReg:getLastMatch());
end

function goOrdinaryBattle()
    goHome();
    wait(1);
    goMission();
    wait(1);
    battleMission();
end

function goDaily()
    goHome();
    wait(1);
    goMission();
    wait(1);
    dailyMission();
end