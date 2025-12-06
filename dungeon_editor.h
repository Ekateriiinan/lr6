#ifndef DUNGEON_EDITOR_H
#define DUNGEON_EDITOR_H

#include <vector>
#include <memory>
#include <string>
#include "npc.h"
#include "observer.h"

class DungeonEditor {
private:
    std::vector<std::unique_ptr<NPC>> npcs;
    std::vector<std::unique_ptr<KillObserver>> observers;
    
    bool isValidCoordinates(double x, double y) const;
    
public:
    DungeonEditor();
    
    void addNPC(std::unique_ptr<NPC> npc);
    void addNPC(const std::string& type, double x, double y, const std::string& name);
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    void printAll() const;
    
    void startBattle(int range);
    
    void addObserver(std::unique_ptr<KillObserver> observer);
    void notifyKill(const std::string& killer, const std::string& victim, const std::string& killerType, const std::string& victimType);
    
    size_t getNPCCount() const;
    void removeDeadNPCs();
};

#endif