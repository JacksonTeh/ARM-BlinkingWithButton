#include <stdio.h>
#include "unity.h"
#include "LedSM.h"
#include "Message.h"
#include "mock_LED.h"
#include "mock_Time.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ledInitData_should_initialize_state_to_LED_OFF_state(void)
{
	LedData ledData;

    ledInitData(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
}

void test_ledSM_given_LED_OFF_state_should_remain_LED_OFF_state_if_msg_is_DO_NOTHING(void)
{
	LedData ledData;

    ledInitData(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);

    msg = DO_NOTHING;
    turnOffLED_Expect(PORTG, LED3);
    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
}

void test_ledSM_given_LED_OFF_state_should_change_to_LED_BLINKING_ON_state_if_msg_is_CHANGE_MODE(void)
{
	LedData ledData;

    ledInitData(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);

    msg = CHANGE_MODE;

    turnOffLED_Expect(PORTG, LED3);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_ON_state_should_remain_LED_ON_state_if_msg_is_DO_NOTHING(void)
{
	LedData ledData;

    ledData.state = LED_ON;
    msg = DO_NOTHING;

    turnOnLED_Expect(PORTG, LED3);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_ON_state_should_change_to_LED_OFF_state_if_msg_is_CHANGE_MODE(void)
{
	LedData ledData;

    ledData.state = LED_ON;
    msg = CHANGE_MODE;

    turnOnLED_Expect(PORTG, LED3);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_OFF);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_BLINKING_ON_state_should_remain_LED_BLINKING_ON_state_if_msg_is_DO_NOTHING(void)
{
	LedData ledData;

    ledData.state = LED_BLINKING_ON;
    ledData.time = 0;
    msg = DO_NOTHING;

    turnOnLED_Expect(PORTG, LED3);
    isTimerExpire_ExpectAndReturn(FIVE_HUND_MILISEC, &ledData.time, 0);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_BLINKING_ON_state_should_change_to_LED_ON_state_if_msg_is_CHANGE_MODE(void)
{
	LedData ledData;

    ledData.state = LED_BLINKING_ON;
    msg = CHANGE_MODE;

    turnOnLED_Expect(PORTG, LED3);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_BLINKING_ON_state_should_change_to_LED_BLINKING_OFF_state_if_timer_expired(void)
{
	LedData ledData;

    ledData.state = LED_BLINKING_ON;
    ledData.time = 0;
    msg = DO_NOTHING;

    turnOnLED_Expect(PORTG, LED3);
    isTimerExpire_ExpectAndReturn(FIVE_HUND_MILISEC, &ledData.time, 1);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_OFF);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_BLINKING_OFF_state_should_remain_LED_BLINKING_OFF_state_if_msg_is_DO_NOTHING(void)
{
	LedData ledData;

    ledData.state = LED_BLINKING_OFF;
    ledData.time = 0;
    msg = DO_NOTHING;

    turnOffLED_Expect(PORTG, LED3);
    isTimerExpire_ExpectAndReturn(FIVE_HUND_MILISEC, &ledData.time, 0);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_OFF);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_BLINKING_OFF_state_should_change_to_LED_ON_state_if_msg_is_CHANGE_MODE(void)
{
	LedData ledData;

    ledData.state = LED_BLINKING_OFF;
    msg = CHANGE_MODE;

    turnOffLED_Expect(PORTG, LED3);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_ON);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}

void test_ledSM_given_LED_BLINKING_OFF_state_should_change_to_LED_BLINKING_ON_state_if_timer_expired(void)
{
	LedData ledData;

    ledData.state = LED_BLINKING_OFF;
    ledData.time = 0;
    msg = DO_NOTHING;

    turnOffLED_Expect(PORTG, LED3);
    isTimerExpire_ExpectAndReturn(FIVE_HUND_MILISEC, &ledData.time, 1);

    ledSM(&ledData);
    TEST_ASSERT_EQUAL(ledData.state, LED_BLINKING_ON);
    TEST_ASSERT_EQUAL(msg, DO_NOTHING);
}