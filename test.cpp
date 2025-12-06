#include "gtest/gtest.h"
#include "npc.h"
#include "npc_factory.h"
#include "dungeon_editor.h"
#include "observer.h"
#include <filesystem>

TEST(NPCTest, CreationAndBasics) {
    Bear bear(10, 20, "Misha");
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getName(), "Misha");
    EXPECT_EQ(bear.getX(), 10);
    EXPECT_EQ(bear.getY(), 20);
    EXPECT_TRUE(bear.isAlive());
    EXPECT_EQ(bear.getPower(), 10);
    EXPECT_EQ(bear.getRange(), 20);
}

TEST(NPCTest, DistanceCalculation) {
    Bear bear1(0, 0, "B1");
    Bear bear2(3, 4, "B2");
    EXPECT_DOUBLE_EQ(bear1.distanceTo(bear2), 5.0);
}

TEST(NPCTest, Death) {
    Bear bear(10, 20, "Misha");
    bear.die();
    EXPECT_FALSE(bear.isAlive());
}

TEST(FactoryTest, NPCCreation) {
    auto bear = NPCFactory::createNPC("Bear", 10, 20, "Misha");
    EXPECT_NE(bear, nullptr);
    EXPECT_EQ(bear->getType(), "Bear");
    
    auto vip = NPCFactory::createNPC("Vip", 30, 40, "Screamer");
    EXPECT_NE(vip, nullptr);
    EXPECT_EQ(vip->getType(), "Vip");
    
    auto vihyhol = NPCFactory::createNPC("Vihyhol", 50, 60, "Hohol");
    EXPECT_NE(vihyhol, nullptr);
    EXPECT_EQ(vihyhol->getType(), "Vihyhol");
    
    auto invalid = NPCFactory::createNPC("InvalidType", 0, 0, "Test");
    EXPECT_EQ(invalid, nullptr);
}

TEST(FactoryTest, Serialization) {
    Bear bear(10.5, 20.5, "Misha The Bear");
    std::string saved = NPCFactory::saveToString(bear);
    
    auto loaded = NPCFactory::loadFromString(saved);
    EXPECT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->getType(), "Bear");
    EXPECT_EQ(loaded->getX(), 10.5);
    EXPECT_EQ(loaded->getY(), 20.5);
    EXPECT_EQ(loaded->getName(), "Misha The Bear");
}

TEST(DungeonTest, BasicOperations) {
    DungeonEditor editor;
    
    editor.addNPC("Bear", 100, 100, "Misha");
    editor.addNPC("Vip", 200, 200, "Screamer");
    
    EXPECT_EQ(editor.getNPCCount(), 2);
    
    editor.addNPC("Bear", 600, 600, "Invalid"); 
    EXPECT_EQ(editor.getNPCCount(), 2); 
}

TEST(DungeonTest, FileOperations) {
    const std::string filename = "test_dungeon.txt";
    
    DungeonEditor editor1;
    editor1.addNPC("Bear", 100, 100, "Misha");
    editor1.addNPC("Vip", 200, 200, "Screamer");
    editor1.saveToFile(filename);
    
    DungeonEditor editor2;
    editor2.loadFromFile(filename);
    EXPECT_EQ(editor2.getNPCCount(), 2);
    
    std::filesystem::remove(filename);
}

TEST(BattleTest, BearVsVip) {
    DungeonEditor editor;
    
    editor.addNPC("Bear", 100, 100, "Bear1");
    editor.addNPC("Vip", 105, 105, "Vip1"); 
    
    EXPECT_EQ(editor.getNPCCount(), 2);
    
    editor.startBattle(50);

    EXPECT_EQ(editor.getNPCCount(), 1);
}

TEST(ObserverTest, FileObserver) {
    const std::string logfile = "test_log.txt";
    
    FileObserver observer(logfile);
    observer.onKill("Bear1", "Vip1", "Bear", "Vip");
    
    EXPECT_TRUE(std::filesystem::exists(logfile));
    
    std::filesystem::remove(logfile);
}