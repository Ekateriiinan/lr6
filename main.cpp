#include "dungeon_editor.h"
#include "observer.h"
#include <iostream>

int main() {
    DungeonEditor editor;
    
    editor.addObserver(std::make_unique<ConsoleObserver>());
    editor.addObserver(std::make_unique<FileObserver>("log.txt"));
    
    editor.addNPC("Bear", 100, 100, "Mishka");
    editor.addNPC("Bear", 120, 110, "Potapych");
    editor.addNPC("Vip", 200, 200, "Screamer");
    editor.addNPC("Vip", 210, 190, "Croaker");
    editor.addNPC("Vihyhol", 300, 300, "Hohol");
    editor.addNPC("Vihyhol", 310, 290, "Vyhuhol");
    
    std::cout << "=== Initial State ===" << std::endl;
    editor.printAll();
    
    std::cout << "\n=== Starting Battle (range: 25) ===" << std::endl;
    editor.startBattle(25);
    
    std::cout << "\n=== After Battle ===" << std::endl;
    editor.printAll();
    
    editor.saveToFile("dungeon.txt");
    
    std::cout << "\n=== Loading from file ===" << std::endl;
    DungeonEditor editor2;
    editor2.loadFromFile("dungeon.txt");
    editor2.printAll();
    
    return 0;
}