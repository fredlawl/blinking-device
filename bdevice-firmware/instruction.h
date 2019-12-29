#ifndef BDEVICE_FIRMWARE_INSTRUCTION_H
#define BDEVICE_FIRMWARE_INSTRUCTION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Instructions
 *
 * NOP ; 0000 0000b
 *  Does blank instruction that does nothing. Basically any non-matching
 *  instruction will automatically translate to a NOP instruction.
 *
 *
 * SET_STATE ; 0000 001-b
 *  Sets the state of the firmware. Useful for resetting & stopping the device.
 *
 *  example uses:
 *      Reset: 0x02; 0000 0010b
 *      Stop: 0x03; 0000 0011b
 *
 *
 * SET_MULTIPLIER ; 0001 ----b
 *  Useful for expanding the calculation range of SET_TIMER
 *  up to 255 (or 1 full byte worth of values).
 *
 *  eg. If I want a delay at 100 ticks, that can't be represented in 4 bits,
 *  so we'll use this multiplier as such:
 *      0x1a ; SET_MULTIPLIER 10 ticks
 *      0x2a ; SET_TIMER delay to 10 ticks
 *      Calculation of ticks for delay: 10 * 10 = 100 ticks
 *
 *  Setting the multiplier should be called before setting any timer
 *  functionality. If a timer is set once, any subsequent calls to SET_TIMER
 *  will use the same multiplier previously set.
 *
 *  NOTE: The multiplier must be at least 1. If a zeroed byte is passed, the
 *        multiplier is automatically set to 1.
 *
 *
 * SET_TIMER ; 001- ----b
 *  Sets the various timings of the device. ie. Set the number (frequency) of
 *  blinks to blink & the delay in ticks between each blink session.
 *
 *  example uses:
 *      Set delay to 10: 0x2a; 0010 1010b
 *      Set frequency to 10: 0x3a; 0011 1010b
 *
 *
 * SET_TICK_INTERVAL ; 1--- ----b
 *  Used with the SET_MULTIPLIER, there exist a large range of possibilities
 *  to set the tick. Tick works like this: millis() / tick_interval. The
 *  higher the interval, the longer in between blinks, longer delay after
 *  blinking is done, etc...
 *
 *  NOTE: Having a zero value is extremely not useful. Therefore, on zero value,
 *        the interval will be set to the default of 300.
 */

#define INST_NOP 0x0U

#define INST_SET_STATE 0x02U
#define INST_SET_STATE_MASK 0x01U
#define INST_SET_STATE_RESET 0x00U
#define INST_SET_STATE_STOP 0x01U

#define INST_SET_MULTIPLIER 0x10U
#define INST_SET_MULTIPLIER_TIME_MASK 0x0fU

#define INST_SET_TIMER 0x20U
#define INST_SET_TIMER_TIME_MASK 0x0fU
#define INST_SET_TIMER_TIMER_MASK 0x10U
#define INST_SET_TIMER_TIMER_SHIFT 4U
#define INST_SET_TIMER_TIMER_DELAY 0x00U
#define INST_SET_TIMER_TIMER_FREQUENCY 0x01U

#define INST_SET_TICK_INTERVAL 0x80U
#define INST_SET_TICK_INTERVAL_MASK 0x7fU

static inline int inst_is(unsigned char input, unsigned char instruction)
{
	return (input & instruction) == instruction;
}

static inline int inst_is_nop(unsigned char input)
{
	return inst_is(input, INST_NOP);
}

unsigned char inst_extract(unsigned char input)
{
	unsigned char pos = 0;
	if (!input) {
		return INST_NOP;
	}

	// Figure out the most significant bit
	while (input) {
		++pos;
		input >>= 1U;
	}

	// Since we have the position, return the extracted instruction
	return 1U << pos - 1U;
}

int inst_is_valid(unsigned char instruction)
{
	return inst_is_nop(instruction)
		|| inst_is(instruction, INST_SET_STATE)
		|| inst_is(instruction, INST_SET_MULTIPLIER)
		|| inst_is(instruction, INST_SET_TIMER)
		|| inst_is(instruction, INST_SET_TICK_INTERVAL);
}

#ifdef __cplusplus
}
#endif

#endif