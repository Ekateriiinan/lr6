#include "npc.h"
#include "visitor.h"
#include <cmath>
#include <iostream>

NPC::NPC(double x, double y, std::string name) : x(x), y(y), name(name), alive(true) {}

double NPC::getX() const { return x; }
double NPC::getY() const { return y; }
std::string NPC::getName() const { return name; }
bool NPC::isAlive() const { return alive; }
void NPC::die() { alive = false; }

double NPC::distanceTo(const NPC& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

Bear::Bear(double x, double y, std::string name) : NPC(x, y, name) {}
std::string Bear::getType() const { return "Bear"; }
int Bear::getPower() const { return 10; }
int Bear::getRange() const { return 20; }
void Bear::accept(BattleVisitor& visitor, NPC& other) {
    if (auto bear = dynamic_cast<Bear*>(&other)) {
        visitor.visitBearBear(*this, *bear);
    } else if (auto vip = dynamic_cast<Vip*>(&other)) {
        visitor.visitBearVip(*this, *vip);
    } else if (auto vihyhol = dynamic_cast<Vihyhol*>(&other)) {
        visitor.visitBearVihyhol(*this, *vihyhol);
    }
}

Vip::Vip(double x, double y, std::string name) : NPC(x, y, name) {}
std::string Vip::getType() const { return "Vip"; }
int Vip::getPower() const { return 7; }
int Vip::getRange() const { return 15; }
void Vip::accept(BattleVisitor& visitor, NPC& other) {
    if (auto bear = dynamic_cast<Bear*>(&other)) {
        visitor.visitVipBear(*this, *bear);
    } else if (auto vip = dynamic_cast<Vip*>(&other)) {
        visitor.visitVipVip(*this, *vip);
    } else if (auto vihyhol = dynamic_cast<Vihyhol*>(&other)) {
        visitor.visitVipVihyhol(*this, *vihyhol);
    }
}

Vihyhol::Vihyhol(double x, double y, std::string name) : NPC(x, y, name) {}
std::string Vihyhol::getType() const { return "Vihyhol"; }
int Vihyhol::getPower() const { return 5; }
int Vihyhol::getRange() const { return 10; }
void Vihyhol::accept(BattleVisitor& visitor, NPC& other) {
    if (auto bear = dynamic_cast<Bear*>(&other)) {
        visitor.visitVihyholBear(*this, *bear);
    } else if (auto vip = dynamic_cast<Vip*>(&other)) {
        visitor.visitVihyholVip(*this, *vip);
    } else if (auto vihyhol = dynamic_cast<Vihyhol*>(&other)) {
        visitor.visitVihyholVihyhol(*this, *vihyhol);
    }
}