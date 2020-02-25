#include "gtest/gtest.h"

#include <memory>
#include "Car.hpp"
#include "mocks/MockEngine.hpp"
#include "mocks/MockFuelTank.hpp"
#include "mocks/MockBattery.hpp"
#include "mocks/MockCurrentSensor.hpp"

TEST(test_battery, test_battery_actions)
{
    std::vector<int32_t> values = {12,35,458,69856,32,-65,-752,-6589,0,0,0};
    electrical::MockCurrentSensor dummy_sensor(values);
    electrical::Battery battery;
    battery.attach_sensor(dummy_sensor);

    for (uint32_t i = 0; i < values.size() ; i++)
    {
        auto expected_action = electrical::BatteryAction::idle;
        if(values[i] > 500)        {
            EXPECT_TRUE(battery.get_battery_action() == electrical::BatteryAction::charging);
        }
        else if (values[i] >= 0 && values[i] <= 500)
        {
            EXPECT_TRUE(battery.get_battery_action() == electrical::BatteryAction::idle);
        }
        else
        {
            EXPECT_TRUE(battery.get_battery_action() == electrical::BatteryAction::depleting);
        }
    }
}

TEST(test_battery, test_battery_fully_charged)
{
    std::vector<int32_t> charged_values = {0,0,0,200,400,500,600,700,800};
    electrical::MockCurrentSensor another_sensor(charged_values);
    electrical::Battery battery(60'000, electrical::Battery::get_max_voltage());

    battery.attach_sensor(another_sensor);

    for (uint32_t i = 0; i < charged_values.size() ; i++)
    {
        auto current_value = charged_values[i];
        if ( current_value <= 500)
        {
            EXPECT_TRUE(battery.is_charged()) << "value " << current_value << "makes the test fail! : battey should be charged!";
        }
        else
        {
            EXPECT_FALSE(battery.is_charged())<< "value " << current_value << "makes the test fail! : battey should not be charged!";
        }
    }
}



int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}