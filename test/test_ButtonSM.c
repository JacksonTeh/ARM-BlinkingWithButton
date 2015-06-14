#include "unity.h"
#include "ButtonSM.h"
#include "Message.h"
#include "mock_Button.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_buttonInitData_should_initialize_state_to_RELEASE_state(void)
{
	ButtonData buttonData;

    buttonInitData(&buttonData);
    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
}

void test_buttonSM_given_RELEASE_state_should_remain_RELEASE_state_if_button_not_pressed(void)
{
	ButtonData buttonData;

    buttonInitData(&buttonData);
    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);

    isButtonPressed_ExpectAndReturn(0);
    buttonSM(&buttonData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
}

void test_buttonSM_given_RELEASE_state_should_change_to_PRESS_state_if_button_pressed(void)
{
	ButtonData buttonData;

    buttonInitData(&buttonData);
    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);

    isButtonPressed_ExpectAndReturn(1);
    buttonSM(&buttonData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
}

void test_buttonSM_given_PRESS_state_should_remain_to_PRESS_state_if_button_is_pressed(void)
{
	ButtonData buttonData;

    buttonData.state = PRESS;

    isButtonPressed_ExpectAndReturn(1);
    buttonSM(&buttonData);

    TEST_ASSERT_EQUAL(buttonData.state, PRESS);
}

void test_buttonSM_given_PRESS_state_should_change_to_RELEASE_state(void)
{
	ButtonData buttonData;

    buttonData.state = PRESS;

    isButtonPressed_ExpectAndReturn(0);
    buttonSM(&buttonData);

    TEST_ASSERT_EQUAL(buttonData.state, RELEASE);
}