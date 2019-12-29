#include <Arduino.h>
#include "instruction.h"

#define BAUD_RATE 115200UL
#define DEFAULT_TICK_INTERVAL 300UL

static size_t __current_time;
static size_t __previous_time;

static int __frequency_count;
static int __duration_count;
static bool __do_blink;
static unsigned char __delay;
static unsigned char __frequency;
static unsigned char __multiplier;
static unsigned int __tick_interval;

void reset_counters()
{
	__frequency_count = 0;
	__duration_count = 0;
}

void reset_state()
{
	__frequency_count = 0;
	__duration_count = 0;
	__do_blink = true;
	__delay = 10;
	__frequency = 10;
	__multiplier = 1;
	__tick_interval = DEFAULT_TICK_INTERVAL;
}

#ifdef DEBUG
inline void print_blink(int led_state) {
	if (led_state == LOW)
		return;

	Serial.print("Blink ");
	Serial.print(((unsigned) __frequency_count >> 1U) + 1);
	Serial.println();
}

inline void print_state(unsigned char instruction, unsigned char input)
{
	unsigned char is_frequency;
	unsigned char should_reset;

	is_frequency = ((input & INST_SET_TIMER_TIMER_MASK) >>
		INST_SET_TIMER_TIMER_SHIFT) == INST_SET_TIMER_TIMER_FREQUENCY;

	should_reset = (input & INST_SET_STATE_MASK) == INST_SET_STATE_RESET;

	Serial.print("Instruction: ");
	Serial.print(instruction);
	Serial.println();

	if (inst_is(instruction, INST_SET_TIMER)) {
		if (!is_frequency) {
			Serial.println("Delay set");
		} else {
			Serial.println("Frequency set");
		}
	}

	if (inst_is(instruction, INST_SET_STATE)) {
		if (should_reset) {
			Serial.println("Resetting...");
		} else {
			Serial.println("Stopping...");
		}
	}

	Serial.print("Delay: ");
	Serial.print(__delay);
	Serial.println();

	Serial.print("Frequency: ");
	Serial.print(__frequency);
	Serial.println();

	Serial.print("Multiplier: ");
	Serial.print(__multiplier);
	Serial.println();

	Serial.print("Tick interval: ");
	Serial.print(__tick_interval);
	Serial.println();
}
#else
inline void print_state(unsigned char instruction, unsigned char input) {}
inline void print_blink(int led_state) {}
#endif

void handle_instruction(unsigned char instruction, unsigned char input)
{
	unsigned char time;
	unsigned char is_frequency;
	unsigned char should_reset;

	switch (instruction) {
		case INST_SET_STATE:
		case INST_SET_TIMER:
		case INST_SET_TICK_INTERVAL:
			reset_counters();
			break;

		default: break;
	}

	switch (instruction) {
		case INST_SET_STATE:
			should_reset = (input & INST_SET_STATE_MASK) ==
				INST_SET_STATE_RESET;

			if (should_reset) {
				reset_state();
			} else {
				digitalWrite(LED_BUILTIN, LOW);
				__do_blink = false;
			}

			break;

		case INST_SET_MULTIPLIER:
			time = input & INST_SET_MULTIPLIER_TIME_MASK;

			// We do not want this set to zero
			if (!time) {
				time = 1U;
			}

			__multiplier = time;

			break;

		case INST_SET_TIMER:
			time = input & INST_SET_TIMER_TIME_MASK;
			is_frequency = ((input & INST_SET_TIMER_TIMER_MASK)
				>> INST_SET_TIMER_TIMER_SHIFT) ==
					INST_SET_TIMER_TIMER_FREQUENCY;

			if (!is_frequency) {
				__delay = time * __multiplier;
			} else {
				__frequency = time * __multiplier;
			}

			break;

		case INST_SET_TICK_INTERVAL:
			time = input & INST_SET_TICK_INTERVAL_MASK;
			if (!time) {
				__tick_interval = DEFAULT_TICK_INTERVAL;
				break;
			}

			__tick_interval = time * __multiplier;

			break;

		default: break;
	}

	print_state(instruction, input);
}

void read_input()
{
	unsigned char instruction;
	unsigned char *inst;
	int readByte;

	if (Serial.available()) {
		readByte = Serial.read();
		if (readByte >= 0) {
			inst = (unsigned char *) &readByte;
			instruction = inst_extract(*inst);
			if (inst_is_valid(instruction)) {
				handle_instruction(instruction, *inst);
			}
		}
	}
}

void run_program()
{
	int led_state;
	short frequency = (short) (__frequency << 1U);

	__current_time = millis();
	if ((__current_time - __previous_time) > __tick_interval) {
		__previous_time = __current_time;

		if (!__do_blink) {
			return;
		}

		if (__frequency_count++ < frequency) {
			led_state = digitalRead(LED_BUILTIN) ^ 0x1;
			digitalWrite(LED_BUILTIN, led_state);
			print_blink(led_state);
		} else {
			digitalWrite(LED_BUILTIN, LOW);

			if (__duration_count++ > __delay) {
				reset_counters();
			}
		}
	}
}

void setup()
{
	reset_state();
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	Serial.begin(BAUD_RATE);
}

void loop()
{
	read_input();
	run_program();
}