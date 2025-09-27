#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdint>

// --- Mocks ---

class MockMeasurementRecorder : public Device::IMeasurementRecorder
{
public:
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, notify, (Device::MeasurementType & measurement), (override));
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    MOCK_METHOD(bool, flush, (), (override));
};

// --- Test Fixture ---

class MeasurementDataStoreTest : public ::testing::Test
{
private:
    // All fields are now private
    std::unique_ptr<BusinessLogic::MeasurementDataStore> dataStore;
    MockMeasurementRecorder mockRecorder1;
    MockMeasurementRecorder mockRecorder2;
    MockMeasurementRecorder mockRecorder3;
    MockMeasurementRecorder mockRecorder4;

protected:
    void SetUp() override
    {
        dataStore = std::make_unique<BusinessLogic::MeasurementDataStore>();
    }

public:
    // Public getters to access private members
    BusinessLogic::MeasurementDataStore &getDataStore() { return *dataStore; }
    MockMeasurementRecorder &getMockRecorder1() { return mockRecorder1; }
    MockMeasurementRecorder &getMockRecorder2() { return mockRecorder2; }
    MockMeasurementRecorder &getMockRecorder3() { return mockRecorder3; }
    MockMeasurementRecorder &getMockRecorder4() { return mockRecorder4; }
};

// --- Initialize Tests ---

TEST_F(MeasurementDataStoreTest, Initialize_AllObserversSucceed_ReturnsTrue)
{
    EXPECT_CALL(getMockRecorder1(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), initialize()).WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_TRUE(getDataStore().initialize());
}

TEST_F(MeasurementDataStoreTest, Initialize_FirstObserverFails_ReturnsFalseAndStopsProcessing)
{
    ::testing::Sequence seq;

    EXPECT_CALL(getMockRecorder1(), initialize())
        .InSequence(seq)
        .WillOnce(::testing::Return(false));

    // Second observer should NOT be called due to early break
    EXPECT_CALL(getMockRecorder2(), initialize())
        .Times(0);

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_FALSE(getDataStore().initialize());
}

TEST_F(MeasurementDataStoreTest, Initialize_SecondObserverFails_ReturnsFalseAndStopsProcessing)
{
    ::testing::Sequence seq;

    EXPECT_CALL(getMockRecorder1(), initialize())
        .InSequence(seq)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(getMockRecorder2(), initialize())
        .InSequence(seq)
        .WillOnce(::testing::Return(false));

    // Third observer should NOT be called due to early break
    EXPECT_CALL(getMockRecorder3(), initialize())
        .Times(0);

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());
    getDataStore().addObserver(getMockRecorder3());

    EXPECT_FALSE(getDataStore().initialize());
}

TEST_F(MeasurementDataStoreTest, Initialize_NoObservers_ReturnsTrue)
{
    EXPECT_TRUE(getDataStore().initialize());
}

// --- Start Tests ---

TEST_F(MeasurementDataStoreTest, Start_AllObserversSucceed_ReturnsTrue)
{
    EXPECT_CALL(getMockRecorder1(), start()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), start()).WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_TRUE(getDataStore().start());
}

TEST_F(MeasurementDataStoreTest, Start_FirstObserverFails_ReturnsFalseAndStopsProcessing)
{
    ::testing::Sequence seq;

    EXPECT_CALL(getMockRecorder1(), start())
        .InSequence(seq)
        .WillOnce(::testing::Return(false));

    // Second observer should NOT be called due to early break
    EXPECT_CALL(getMockRecorder2(), start())
        .Times(0);

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_FALSE(getDataStore().start());
}

TEST_F(MeasurementDataStoreTest, Start_SecondObserverFails_ReturnsFalseAndStopsProcessing)
{
    ::testing::Sequence seq;

    EXPECT_CALL(getMockRecorder1(), start())
        .InSequence(seq)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(getMockRecorder2(), start())
        .InSequence(seq)
        .WillOnce(::testing::Return(false));

    // Third observer should NOT be called due to early break
    EXPECT_CALL(getMockRecorder3(), start())
        .Times(0);

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());
    getDataStore().addObserver(getMockRecorder3());

    EXPECT_FALSE(getDataStore().start());
}

TEST_F(MeasurementDataStoreTest, Start_NoObservers_ReturnsTrue)
{
    EXPECT_TRUE(getDataStore().start());
}

// --- AddObserver Tests ---

TEST_F(MeasurementDataStoreTest, AddObserver_AddsSingleObserver_ReturnsTrue)
{
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder1()));
}

TEST_F(MeasurementDataStoreTest, AddObserver_AddsMultipleObservers_ReturnsTrue)
{
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder1()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder2()));
}

TEST_F(MeasurementDataStoreTest, AddObserver_ExceedsMaxObservers_ReturnsFalse)
{
    // Add max observers (assuming MaxObservers = 4)
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder1()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder2()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder3()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder4()));

    // Create a 5th recorder to exceed the limit
    MockMeasurementRecorder extraRecorder;
    EXPECT_FALSE(getDataStore().addObserver(extraRecorder));
}

// --- RemoveObserver Tests ---

TEST_F(MeasurementDataStoreTest, RemoveObserver_RemovesExistingObserver_ReturnsTrue)
{
    getDataStore().addObserver(getMockRecorder1());
    EXPECT_TRUE(getDataStore().removeObserver(getMockRecorder1()));
}

TEST_F(MeasurementDataStoreTest, RemoveObserver_RemovesNonExistentObserver_ReturnsFalse)
{
    EXPECT_FALSE(getDataStore().removeObserver(getMockRecorder1()));
}

TEST_F(MeasurementDataStoreTest, RemoveObserver_RemovesMiddleObserver_ShiftsRemainingObservers)
{
    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());
    getDataStore().addObserver(getMockRecorder3());

    // Remove middle observer
    EXPECT_TRUE(getDataStore().removeObserver(getMockRecorder2()));

    // Verify remaining observers still work
    EXPECT_CALL(getMockRecorder1(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder3(), initialize()).WillOnce(::testing::Return(true));
    // mockRecorder2 should NOT be called
    EXPECT_CALL(getMockRecorder2(), initialize()).Times(0);

    EXPECT_TRUE(getDataStore().initialize());
}

TEST_F(MeasurementDataStoreTest, RemoveObserver_RemoveAndReAdd_Works)
{
    getDataStore().addObserver(getMockRecorder1());
    EXPECT_TRUE(getDataStore().removeObserver(getMockRecorder1()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder1()));
}

// --- NotifyObservers Tests ---

TEST_F(MeasurementDataStoreTest, NotifyObservers_AllObserversSucceed_ReturnsTrue)
{
    Device::MeasurementType measurement{};

    EXPECT_CALL(getMockRecorder1(), notify(::testing::_))
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), notify(::testing::_))
        .WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_TRUE(getDataStore().notifyObservers(measurement));
}

TEST_F(MeasurementDataStoreTest, NotifyObservers_OneObserverFails_ReturnsFalseButCallsAll)
{
    Device::MeasurementType measurement{};

    // Both should be called even if one fails (no early break in notifyObservers)
    EXPECT_CALL(getMockRecorder1(), notify(::testing::_))
        .WillOnce(::testing::Return(false));
    EXPECT_CALL(getMockRecorder2(), notify(::testing::_))
        .WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_FALSE(getDataStore().notifyObservers(measurement));
}

TEST_F(MeasurementDataStoreTest, NotifyObservers_MultipleObserversFail_ReturnsFalse)
{
    Device::MeasurementType measurement{};

    EXPECT_CALL(getMockRecorder1(), notify(::testing::_))
        .WillOnce(::testing::Return(false));
    EXPECT_CALL(getMockRecorder2(), notify(::testing::_))
        .WillOnce(::testing::Return(false));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_FALSE(getDataStore().notifyObservers(measurement));
}

TEST_F(MeasurementDataStoreTest, NotifyObservers_NoObservers_ReturnsTrue)
{
    Device::MeasurementType measurement{};

    EXPECT_TRUE(getDataStore().notifyObservers(measurement));
}

TEST_F(MeasurementDataStoreTest, NotifyObservers_CallsAllObserversEvenAfterFailure)
{
    Device::MeasurementType measurement{};

    // All three should be called even though first fails
    EXPECT_CALL(getMockRecorder1(), notify(::testing::_))
        .WillOnce(::testing::Return(false));
    EXPECT_CALL(getMockRecorder2(), notify(::testing::_))
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder3(), notify(::testing::_))
        .WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());
    getDataStore().addObserver(getMockRecorder3());

    EXPECT_FALSE(getDataStore().notifyObservers(measurement));
}

// --- Integration Tests ---

TEST_F(MeasurementDataStoreTest, Integration_FullLifecycle_WorksCorrectly)
{
    Device::MeasurementType measurement{};

    // Add observers
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder1()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder2()));

    // Initialize
    EXPECT_CALL(getMockRecorder1(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getDataStore().initialize());

    // Start
    EXPECT_CALL(getMockRecorder1(), start()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), start()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getDataStore().start());

    // Notify
    EXPECT_CALL(getMockRecorder1(), notify(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), notify(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getDataStore().notifyObservers(measurement));

    // Remove one observer
    EXPECT_TRUE(getDataStore().removeObserver(getMockRecorder1()));

    // Notify again - only mockRecorder2 should be called
    EXPECT_CALL(getMockRecorder1(), notify(::testing::_)).Times(0);
    EXPECT_CALL(getMockRecorder2(), notify(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getDataStore().notifyObservers(measurement));
}