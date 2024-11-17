#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BusinessLogic/Inc/HmiBuilder.hpp"
#include "BusinessLogic/Interfaces/IHmiFactory.hpp"
#include "BusinessLogic/Interfaces/IHmiInputController.hpp"
#include "BusinessLogic/Interfaces/IHmiViewManager.hpp"
#include "BusinessLogic/Interfaces/IHmiDataModel.hpp"

namespace BusinessLogic
{
    class MockHmiDataModel : public IHmiDataModel
    {
        MOCK_METHOD(bool, initialize, (), (override));
        MOCK_METHOD(bool, start, (), (override));
        MOCK_METHOD(bool, stop, (), (override));
        MOCK_METHOD(bool, tick, (), (override));
    };

    class MockHmiInputController : public IHmiInputController
    {
        MOCK_METHOD(bool, initialize, (), (override));
        MOCK_METHOD(bool, start, (), (override));
        MOCK_METHOD(bool, stop, (), (override));
        MOCK_METHOD(bool, tick, (), (override));
    };

    class MockHmiViewManager : public IHmiViewManager
    {
        MOCK_METHOD(bool, initialize, (), (override));
        MOCK_METHOD(bool, start, (), (override));
        MOCK_METHOD(bool, stop, (), (override));
        MOCK_METHOD(bool, tick, (), (override));
    };

    class MockHmiFactory : public IHmiFactory
    {
    public:
        MOCK_METHOD(IHmiDataModel &, getDataModel, (), (override));
        MOCK_METHOD(IHmiInputController &, getInputController, (), (override));
        MOCK_METHOD(IHmiViewManager &, getHmiViewManager, (), (override));

        MOCK_METHOD(Driver::IDisplayDriver &, getDisplay, (), (override));
        MOCK_METHOD(Device::IDisplayBrightnessRegulator &, getDisplayBrightnessRegulator, (), (override));
        MOCK_METHOD(Device::IKeyboard &, getKeyboard, (), (override));
    };
}

namespace Device
{

    class MockDisplayBrightnessRegulator : public Device::IDisplayBrightnessRegulator
    {
    };

    class MockKeyboard : public Device::IKeyboard
    {
    };
}

namespace Driver
{
    class MockDisplayDriver : public Driver::IDisplayDriver
    {
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
    };
}

TEST(HmiBuilderTest, InitializeCallsHmiDataModel)
{
    BusinessLogic::MockHmiFactory mockFactory;
    BusinessLogic::MockHmiDataModel mockDataModel;
    BusinessLogic::MockHmiInputController mockInputController;
    BusinessLogic::MockHmiViewManager mockViewManager;

    EXPECT_CALL(mockFactory, getDataModel())
        .WillOnce(testing::ReturnRef(mockDataModel));
    EXPECT_CALL(mockFactory, getInputController())
        .WillOnce(testing::ReturnRef(mockInputController));
    EXPECT_CALL(mockFactory, getHmiViewManager())
        .WillOnce(testing::ReturnRef(mockViewManager));

    BusinessLogic::HmiBuilder builder(mockFactory);

    // We will add more specific tests if `initialize()` becomes more complex.
    EXPECT_TRUE(builder.initialize());
}

TEST(HmiBuilderTest, StartCallsHmiInputController)
{
    BusinessLogic::MockHmiFactory mockFactory;
    BusinessLogic::MockHmiDataModel mockDataModel;
    BusinessLogic::MockHmiInputController mockInputController;
    BusinessLogic::MockHmiViewManager mockViewManager;

    EXPECT_CALL(mockFactory, getDataModel())
        .WillOnce(testing::ReturnRef(mockDataModel));
    EXPECT_CALL(mockFactory, getInputController())
        .WillOnce(testing::ReturnRef(mockInputController));
    EXPECT_CALL(mockFactory, getHmiViewManager())
        .WillOnce(testing::ReturnRef(mockViewManager));

    BusinessLogic::HmiBuilder builder(mockFactory);

    EXPECT_TRUE(builder.start());
}

TEST(HmiBuilderTest, StopCallsHmiInputController)
{
    BusinessLogic::MockHmiFactory mockFactory;
    BusinessLogic::MockHmiDataModel mockDataModel;
    BusinessLogic::MockHmiInputController mockInputController;
    BusinessLogic::MockHmiViewManager mockViewManager;

    EXPECT_CALL(mockFactory, getDataModel())
        .WillOnce(testing::ReturnRef(mockDataModel));
    EXPECT_CALL(mockFactory, getInputController())
        .WillOnce(testing::ReturnRef(mockInputController));
    EXPECT_CALL(mockFactory, getHmiViewManager())
        .WillOnce(testing::ReturnRef(mockViewManager));

    BusinessLogic::HmiBuilder builder(mockFactory);

    EXPECT_TRUE(builder.stop());
}

TEST(HmiBuilderTest, TickCallsHmiInputController)
{
    BusinessLogic::MockHmiFactory mockFactory;
    BusinessLogic::MockHmiDataModel mockDataModel;
    BusinessLogic::MockHmiInputController mockInputController;
    BusinessLogic::MockHmiViewManager mockViewManager;

    EXPECT_CALL(mockFactory, getDataModel())
        .WillOnce(testing::ReturnRef(mockDataModel));
    EXPECT_CALL(mockFactory, getInputController())
        .WillOnce(testing::ReturnRef(mockInputController));
    EXPECT_CALL(mockFactory, getHmiViewManager())
        .WillOnce(testing::ReturnRef(mockViewManager));

    BusinessLogic::HmiBuilder builder(mockFactory);

    EXPECT_TRUE(builder.tick());
}
