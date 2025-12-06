#include "dungeon_editor.h"
#include "npc_factory.h"
#include "battle_system.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

DungeonEditor::DungeonEditor() {}

bool DungeonEditor::isValidCoordinates(double x, double y) const {
    return x > 0 && x < 500 && y > 0 && y < 500;
}

void DungeonEditor::addNPC(std::unique_ptr<NPC> npc) {
    if (npc && isValidCoordinates(npc->getX(), npc->getY())) {
        npcs.push_back(std::move(npc));
    }
}

void DungeonEditor::addNPC(const std::string& type, double x, double y, const std::string& name) {
    auto npc = NPCFactory::createNPC(type, x, y, name);
    addNPC(std::move(npc));
}

void DungeonEditor::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                file << NPCFactory::saveToString(*npc) << std::endl;
            }
        }
        file.close();
    }
}

void DungeonEditor::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        npcs.clear();
        std::string line;
        while (std::getline(file, line)) {
            auto npc = NPCFactory::loadFromString(line);
            if (npc) {
                npcs.push_back(std::move(npc));
            }
        }
        file.close();
    }
}

void DungeonEditor::printAll() const {
    std::cout << "\n=== NPC List ===" << std::endl;
    std::cout << std::left << std::setw(10) << "Type" 
              << std::setw(15) << "Name" 
              << std::setw(10) << "X" 
              << std::setw(10) << "Y" 
              << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << std::left << std::setw(10) << npc->getType()
                      << std::setw(15) << npc->getName()
                      << std::setw(10) << npc->getX()
                      << std::setw(10) << npc->getY()
                      << std::setw(10) << "Alive" << std::endl;
        }
    }
}

void DungeonEditor::startBattle(int range) {
    BattleSystem battleSystem(npcs, observers, range);
    battleSystem.execute();
    removeDeadNPCs();
}

void DungeonEditor::addObserver(std::unique_ptr<KillObserver> observer) {
    observers.push_back(std::move(observer));
}

void DungeonEditor::notifyKill(const std::string& killer, const std::string& victim, 
                              const std::string& killerType, const std::string& victimType) {
    for (const auto& observer : observers) {
        observer->onKill(killer, victim, killerType, victimType);
    }
}

size_t DungeonEditor::getNPCCount() const {
    return npcs.size();
}

void DungeonEditor::removeDeadNPCs() {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(), 
                      [](const std::unique_ptr<NPC>& npc) { return !npc->isAlive(); }),
        npcs.end()
    );
}