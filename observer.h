#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <memory>

class KillObserver {
public:
    virtual ~KillObserver() = default;
    virtual void onKill(const std::string& killer, const std::string& victim, const std::string& killerType, const std::string& victimType) = 0;
};

class ConsoleObserver : public KillObserver {
public:
    void onKill(const std::string& killer, const std::string& victim, const std::string& killerType, const std::string& victimType) override;
};

class FileObserver : public KillObserver {
private:
    std::string filename;
    
public:
    FileObserver(const std::string& filename);
    void onKill(const std::string& killer, const std::string& victim, const std::string& killerType, const std::string& victimType) override;
};

#endif