---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Olegase.
--- DateTime: 15.05.2019 15:31
---

function sosMission()
    if (not sosMissionCheck) then
        return;
    end
    local sosMissionTime = Timer();
    snapshot();
    local goHomePage = (not missionModeReg:exists(attack2, 0.5)) and (not checkCurrentInMission());
    usePreviousSnap(false);
    if (goHomePage) then
        goHome();
        wait(1);
        goMission();
        wait(1);
    end
    if (checkCurrentInMission()) then
        local tempCount = count;
        count = 1;
        battleMission(true);
        count = tempCount;
    end
    while (not sosMissionReg:exists(number0)) do
        click(sosMissionLoc);
        wait(0.5);
        if (not sosSignalGoReg:exists(go3, 1)) then
            click(searchSignalLcc);
            wait(3);
            confirmReg3:existsClick(confirm2);
        else
            highlight(1, _, sosSignalGoReg);
            click(sosSignalGoReg);
            wait(2);
        end
        missionReg = exists(submarine, 2);
        inProgressReg2 = (not missionReg) or Region(missionReg:getX() - 100, missionReg:getY() - 100, 220, 220);
        mapSelected = true;
        count = 1;
        battleMission(true);
        missionReg = nil;
        mapSelected = false;
    end
    print("SoS Signals: Minutes: "..string.format("%.2f", sosMissionTime:check() / 60));
end