#include "visitor.h"
#include <iostream>

BattleLogicVisitor::BattleLogicVisitor(int range) : battleRange(range) {}

void BattleLogicVisitor::visitBearBear(Bear& attacker, Bear& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        if (attacker.getPower() > target.getPower()) {
            target.die();
        } else if (attacker.getPower() < target.getPower()) {
            attacker.die();
        } else {
            attacker.die();
            target.die();
        }
    }
}

void BattleLogicVisitor::visitBearVip(Bear& attacker, Vip& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        target.die();
    }
}

void BattleLogicVisitor::visitBearVihyhol(Bear& attacker, Vihyhol& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        target.die();
    }
}

void BattleLogicVisitor::visitVipBear(Vip& attacker, Bear& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        attacker.die();
    }
}

void BattleLogicVisitor::visitVipVip(Vip& attacker, Vip& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        if (attacker.getPower() > target.getPower()) {
            target.die();
        } else if (attacker.getPower() < target.getPower()) {
            attacker.die();
        } else {
            attacker.die();
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVipVihyhol(Vip& attacker, Vihyhol& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        target.die();
    }
}

void BattleLogicVisitor::visitVihyholBear(Vihyhol& attacker, Bear& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        target.die();
    }
}

void BattleLogicVisitor::visitVihyholVip(Vihyhol& attacker, Vip& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        attacker.die();
    }
}

void BattleLogicVisitor::visitVihyholVihyhol(Vihyhol& attacker, Vihyhol& target) {
    if (attacker.distanceTo(target) <= battleRange) {
        if (attacker.getPower() > target.getPower()) {
            target.die();
        } else if (attacker.getPower() < target.getPower()) {
            attacker.die();
        } else {
            attacker.die();
            target.die();
        }
    }
}