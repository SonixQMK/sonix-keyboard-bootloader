#include <inttypes.h>

#include "proxy.h"
#include "config.h"

#define SECOND_STAGE_VECTOR (void*)0x200

/* Jumps to the next stage given its vector */
__attribute__((noreturn)) static void jump_vector(uint32_t *vector) {
    uint32_t sp = vector[0];
    uint32_t pc = vector[1];

    __asm__ volatile (
        "mov sp, %0\n"
        "bx %1\n" :: "r" (sp), "r" (pc)
    );

    __builtin_trap();
}

/* Check if the firmware is valid, same simple SP check as in stm32duino-bootloader */
static int firmware_valid(void) {
    uint32_t *vector = SECOND_STAGE_VECTOR;
    return (vector[0] & 0xFFFE0001) == 0x20000000;
}

/* Check if QMK asked us to reboot into bootloader mode */
static int bootloader_requested(void) {
    uint32_t *magic_address = (void*)0x20000780;

    /* "bldr" */
    if (*magic_address == 0x626c6472) {
        *magic_address = 0;
        return 1;
    }

    return 0;
}

static void delay(void) {
    for (int i = 0; i < 400; ++i) {
        __asm__ volatile("" ::: "memory");
    }
}

/* Check if the boot0 pin is low, same logic as in the bootloader */
static int boot0_low(void) {
    int first, second;

    /* Enable pull-up for P3.5 */
    BOOT0_GPIO->CFG &= ~(3 << (BOOT0_PIN * 2));
    delay();

    /* Read twice and compare */
    first = BOOT0_GPIO->DATA & (1 << BOOT0_PIN);
    delay();
    second = BOOT0_GPIO->DATA & (1 << BOOT0_PIN);

    /* Jump to ROM when we got a low value at least once */
    return first != second || !first;
}

/* Check if a keyboard key is held (specified in config.h) */
static int key_held(void) {
#ifdef BLKEY_INPUT_GPIO
    int res;

    /* Enable pull-up for the input pin */
    BLKEY_INPUT_GPIO->CFG &= ~(3 << (BLKEY_INPUT_PIN * 2));

#ifdef BLKEY_OUTPUT_GPIO
    /* Set up the output pin as output */
    BLKEY_OUTPUT_GPIO->MODE |= (1 << BLKEY_OUTPUT_PIN);

    delay();

    /* Send on the output */
    BLKEY_OUTPUT_GPIO->BCLR = (1 << BLKEY_OUTPUT_PIN);
#endif // BLKEY_OUTPUT_GPIO
    delay();

    /* Read the input */
    res = BLKEY_INPUT_GPIO->DATA & (1 << BLKEY_INPUT_PIN);

    #if defined(PIN_HIGH_WHEN_KEY_HELD)
    return res;
    #else
    return !res;
    #endif
#else
    return 0;
#endif // BLKEY_INPUT_GPIO
}

void _start(void) {
    if (!firmware_valid() || bootloader_requested() || boot0_low() || key_held()) {
        /* Jump to the embedded bootloader */
        void (*recovery)() = (void*)SN32_BOOTLOADER_ADDRESS;
        recovery();
    } else {
        /* Jump to the firmware */
        jump_vector(SECOND_STAGE_VECTOR);
    }
}

static void* vectors[0xC0/4] __attribute__((used, section (".vectors"))) = {
    [0] = (void*)0x20000800,   /* stack pointer */
    [1] = _start,              /* reset */
    [2] = exc_proxy,          /* NMI */
    [3] = exc_proxy,          /* HardFault */

    [11] = exc_proxy,         /* SVCall */

    [14] = exc_proxy,         /* PendSV */
    [15] = exc_proxy,         /* SysTick */

    [16] = exc_proxy,         /* IRQ0 */
    [17] = exc_proxy,         /* IRQ1 */
    [18] = exc_proxy,         /* IRQ2 */
    [19] = exc_proxy,         /* IRQ3 */
    [20] = exc_proxy,         /* IRQ4 */
    [21] = exc_proxy,         /* IRQ5 */
    [22] = exc_proxy,         /* IRQ6 */
    [23] = exc_proxy,         /* IRQ7 */
    [24] = exc_proxy,         /* IRQ8 */
    [25] = exc_proxy,         /* IRQ9 */
    [26] = exc_proxy,         /* IRQ10 */
    [27] = exc_proxy,         /* IRQ11 */
    [28] = exc_proxy,         /* IRQ12 */
    [29] = exc_proxy,         /* IRQ13 */
    [30] = exc_proxy,         /* IRQ14 */
    [31] = exc_proxy,         /* IRQ15 */
    [32] = exc_proxy,         /* IRQ16 */
    [33] = exc_proxy,         /* IRQ17 */
    [34] = exc_proxy,         /* IRQ18 */
    [35] = exc_proxy,         /* IRQ19 */
    [36] = exc_proxy,         /* IRQ20 */
    [37] = exc_proxy,         /* IRQ21 */
    [38] = exc_proxy,         /* IRQ22 */
    [39] = exc_proxy,         /* IRQ23 */
    [40] = exc_proxy,         /* IRQ24 */
    [41] = exc_proxy,         /* IRQ25 */
    [42] = exc_proxy,         /* IRQ26 */
    [43] = exc_proxy,         /* IRQ27 */
    [44] = exc_proxy,         /* IRQ28 */
    [45] = exc_proxy,         /* IRQ29 */
    [46] = exc_proxy,         /* IRQ30 */
    [47] = exc_proxy,         /* IRQ31 */
};
