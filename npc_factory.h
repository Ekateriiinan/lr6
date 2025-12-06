#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include <memory>
#include <string>
#include "npc.h"

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, double x, double y, const std::string& name);
    static std::unique_ptr<NPC> loadFromString(const std::string& data);
    static std::string saveToString(const NPC& npc);
};

#endif