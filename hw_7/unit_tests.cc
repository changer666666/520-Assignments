#include "gtest/gtest.h"
#include "elma/elma.h"
#include "robot.h"
#include "BetterStateMachine.h"

using namespace std::chrono;
using namespace elma;

namespace {
   
    TEST(Robot, basic) {

        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade");   

    }

    TEST(Robot1, intrude) {

        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("reset"));
        EXPECT_EQ(robot.current().name(), "Wander");     
    }

    TEST(Robot2, proximity) {

        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");  
        m.emit(Event("reset"));
        EXPECT_EQ(robot.current().name(), "Make Noise");         
        m.emit(Event("reset"));
        EXPECT_EQ(robot.current().name(), "Wander"); 
    }

    TEST(Robot3, proximity) {

        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("battery low"));
        EXPECT_EQ(robot.current().name(), "Find Recharge Station");
        m.emit(Event("found recharge station"));
        EXPECT_EQ(robot.current().name(), "Recharge");  
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Wander");  
    }
    TEST(Robot4, battery2) {

        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");  
        m.emit(Event("battery low"));
        EXPECT_EQ(robot.current().name(), "Find Recharge Station");  
    }

    TEST(BSM1, watch) {
        Manager m;
        Mode off("off"), on("on");
        BetterStateMachine fsm("toggle switch");

        fsm.set_initial(off)
        .add_transition("switch", off, on)
        .add_transition("switch", on, off);
        fsm.to_json();
        std::cout << fsm.to_json().dump() << "\n";
    }

    TEST(BSM2, oven) {
        Manager m;
        Mode off("off"), on("on"), close_on("close_on"), close_off("close_off"), init("init");
        BetterStateMachine fsm("oven");

        fsm.set_initial(init)
        .add_transition("turn on", close_off, close_on)
        .add_transition("turn off", close_on, close_off)
        .add_transition("force open", close_on, off)
        .add_transition("switch", off, on)
        .add_transition("switch", on, off);
        fsm.to_json();
    }

}
