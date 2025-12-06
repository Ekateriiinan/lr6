#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <memory>
#include <vector>
#include "npc.h"
#include "visitor.h"
#include "observer.h"

class BattleSystem {
private:
    std::vector<std::unique_ptr<NPC>>& npcs;
    std::vector<std::unique_ptr<KillObserver>>& observers;
    int battleRange;
    
public:
    BattleSystem(std::vector<std::unique_ptr<NPC>>& npcs, 
                 std::vector<std::unique_ptr<KillObserver>>& observers, 
                 int range);
    
    void execute();
    
private:
    void fight(NPC& npc1, NPC& npc2);
    void notifyKill(const std::string& killer, const std::string& victim, 
                    const std::string& killerType, const std::string& victimType);
};

#endif