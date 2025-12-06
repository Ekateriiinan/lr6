#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>

class BattleVisitor;

class NPC {
protected:
    double x;
    double y;
    std::string name;
    bool alive;

public:
    NPC(double x, double y, std::string name);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual void accept(BattleVisitor& visitor, NPC& other) = 0;
    virtual int getPower() const = 0;
    virtual int getRange() const = 0;

    double getX() const;
    double getY() const;
    std::string getName() const;
    bool isAlive() const;
    void die();
    double distanceTo(const NPC& other) const;
};

class Bear : public NPC {
public:
    Bear(double x, double y, std::string name);
    std::string getType() const override;
    void accept(BattleVisitor& visitor, NPC& other) override;
    int getPower() const override;
    int getRange() const override;
};

class Vip : public NPC {
public:
    Vip(double x, double y, std::string name);
    std::string getType() const override;
    void accept(BattleVisitor& visitor, NPC& other) override;
    int getPower() const override;
    int getRange() const override;
};

class Vihyhol : public NPC {
public:
    Vihyhol(double x, double y, std::string name);
    std::string getType() const override;
    void accept(BattleVisitor& visitor, NPC& other) override;
    int getPower() const override;
    int getRange() const override;
};

#endif