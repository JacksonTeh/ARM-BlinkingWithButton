#include "unity.h"
#include "Message.h"
#include "ButtonSM.h"
#include "LedSM.h"
#include "mock_Button.h"
#include "mock_LED.h"
#include "mock_Time.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_message_passing_given_DO_NOTHING_and_LED_OFF_ledState_should_remain_LED_OFF(void)
{
	LedData ledData;
	ButtonData buttonData;

    ledInitData(&ledData);
    buttonInitData(&buttonData);

    isButtonPressed_ExpectAndReturn(0);

    buttonSM(&buttonData);

    turnOffLED_Expect();

    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
}

void test_message_passing_given_DO_NOTHING_and_LED_ON_ledState_should_remain_LED_ON(void)
{
	LedData ledData;
	ButtonData buttonData;

    ledData.state = LED_ON;
    buttonInitData(&buttonData);

    isButtonPressed_ExpectAndReturn(0);

    buttonSM(&buttonData);

    turnOnLED_Expect();

    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
}

void test_message_passing_for_intergrated_test(void)
{
	LedData ledData;
	ButtonData buttonData;

    ledInitData(&ledData);
    buttonInitData(&buttonData);

    //off to blink
    isButtonPressed_ExpectAndReturn(1);
    buttonSM(&buttonData);
    turnOffLED_Expect();
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);

    //blinking on to blinking off
    isButtonPressed_ExpectAndReturn(0);
    buttonSM(&buttonData);
    turnOnLED_Expect();
    isTimerExpire_ExpectAndReturn(FIVE_HUND_MILISEC, 0, 1);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_OFF);
    
    //blinking off to blinking on
    isButtonPressed_ExpectAndReturn(0);
    buttonSM(&buttonData);
    turnOffLED_Expect();
    isTimerExpire_ExpectAndReturn(FIVE_HUND_MILISEC, 0, 1);
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
    
    //blinking off to on
    ledData.state = LED_BLINKING_OFF;
    isButtonPressed_ExpectAndReturn(1);
    buttonSM(&buttonData);
    turnOffLED_Expect();
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
    
    //on to off
    isButtonPressed_ExpectAndReturn(0);
    buttonSM(&buttonData);
    turnOnLED_Expect();
    ledSM(&ledData);
    isButtonPressed_ExpectAndReturn(1);
    buttonSM(&buttonData);
    turnOnLED_Expect();
    ledSM(&ledData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
}