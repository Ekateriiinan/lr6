#include "npc_factory.h"
#include <sstream>

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type, double x, double y, const std::string& name) {
    if (type == "Bear") {
        return std::make_unique<Bear>(x, y, name);
    } else if (type == "Vip") {
        return std::make_unique<Vip>(x, y, name);
    } else if (type == "Vihyhol") {
        return std::make_unique<Vihyhol>(x, y, name);
    }
    return nullptr;
}

std::unique_ptr<NPC> NPCFactory::loadFromString(const std::string& data) {
    std::istringstream iss(data);
    std::string type, name;
    double x, y;
    
    if (iss >> type >> x >> y) {
        std::getline(iss >> std::ws, name);
        return createNPC(type, x, y, name);
    }
    return nullptr;
}

std::string NPCFactory::saveToString(const NPC& npc) {
    std::ostringstream oss;
    oss << npc.getType() << " " << npc.getX() << " " << npc.getY() << " " << npc.getName();
    return oss.str();
}