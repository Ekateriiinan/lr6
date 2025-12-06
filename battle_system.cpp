#include "battle_system.h"
#include "visitor.h"

BattleSystem::BattleSystem(std::vector<std::unique_ptr<NPC>>& npcs, 
                         std::vector<std::unique_ptr<KillObserver>>& observers, 
                         int range) 
    : npcs(npcs), observers(observers), battleRange(range) {}

void BattleSystem::execute() {
    BattleLogicVisitor visitor(battleRange);
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (npcs[i]->isAlive() && npcs[j]->isAlive()) {
                fight(*npcs[i], *npcs[j]);
            }
        }
    }
}

void BattleSystem::fight(NPC& npc1, NPC& npc2) {
    bool npc1AliveBefore = npc1.isAlive();
    bool npc2AliveBefore = npc2.isAlive();
    
    BattleLogicVisitor visitor(battleRange);
    npc1.accept(visitor, npc2);
    
    bool npc1AliveAfter = npc1.isAlive();
    bool npc2AliveAfter = npc2.isAlive();
    
    if (!npc1AliveAfter && npc2AliveAfter && npc1AliveBefore) {
        notifyKill(npc2.getName(), npc1.getName(), npc2.getType(), npc1.getType());
    } else if (!npc2AliveAfter && npc1AliveAfter && npc2AliveBefore) {
        notifyKill(npc1.getName(), npc2.getName(), npc1.getType(), npc2.getType());
    } else if (!npc1AliveAfter && !npc2AliveAfter && (npc1AliveBefore || npc2AliveBefore)) {
        notifyKill("Both", npc1.getName(), "Mutual", npc1.getType());
        notifyKill("Both", npc2.getName(), "Mutual", npc2.getType());
    }
}

void BattleSystem::notifyKill(const std::string& killer, const std::string& victim, 
                             const std::string& killerType, const std::string& victimType) {
    for (const auto& observer : observers) {
        observer->onKill(killer, victim, killerType, victimType);
    }
}