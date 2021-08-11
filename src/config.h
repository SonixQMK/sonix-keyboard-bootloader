#pragma once

#if defined(TARGET_GENERIC)
#include "SN32F260.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0009
#define BOOT0_GPIO SN_GPIO3
#define BOOT0_PIN 5
#elif defined(TARGET_WOMIER_K66) // SN32F260
#include "SN32F260.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0009
#define BOOT0_GPIO SN_GPIO3
#define BOOT0_PIN 5
/* Backspace */
#define BLKEY_INPUT_GPIO SN_GPIO1
#define BLKEY_INPUT_PIN 1
#define BLKEY_OUTPUT_GPIO SN_GPIO2
#define BLKEY_OUTPUT_PIN 8
#elif defined(TARGET_GANSS_GK87PRO) // SN32F260
#include "SN32F260.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0009
#define BOOT0_GPIO SN_GPIO3
#define BOOT0_PIN 5
/* Spacebar */
#define BLKEY_INPUT_GPIO SN_GPIO2
#define BLKEY_INPUT_PIN 8
#define BLKEY_OUTPUT_GPIO SN_GPIO0
#define BLKEY_OUTPUT_PIN 12
#elif defined(TARGET_KEMOVE_DK63) // SN32F248B
#include "SN32F240B.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0301
#define BOOT0_GPIO SN_GPIO2
#define BOOT0_PIN 2
/* Backspace */
#define BLKEY_INPUT_GPIO SN_GPIO1
#define BLKEY_INPUT_PIN 5
#define BLKEY_OUTPUT_GPIO SN_GPIO3
#define BLKEY_OUTPUT_PIN 7
#elif defined(TARGET_KEYCHRON_K6_RGB) // SN32F248B
#include "SN32F240B.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0301
#define BOOT0_GPIO SN_GPIO2
#define BOOT0_PIN 2
/* Escape */
#define BLKEY_INPUT_GPIO SN_GPIO0
#define BLKEY_INPUT_PIN 8
#define BLKEY_OUTPUT_GPIO SN_GPIO3
#define BLKEY_OUTPUT_PIN 11
#elif defined(TARGET_KEYCHRON_C1_WHITE) // SN32F260
#include "SN32F260.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0009
#define BOOT0_GPIO SN_GPIO3
#define BOOT0_PIN 5
/* Escape */
#define BLKEY_INPUT_GPIO SN_GPIO2
#define BLKEY_INPUT_PIN 3
#define BLKEY_OUTPUT_GPIO SN_GPIO0
#define BLKEY_OUTPUT_PIN 0
/* Key matrix is active high */
#define BLKEY_ACTIVE_HIGH
/* Custom GPIO init.
 * Assume all registers are in the reset state. So pull-ups are not enabled.
 * Drive QX's (P0.0-P0.15 & P3.0) low, otherwise they will be high due the high-side transistor base current.
 * QX's cannot be high otherwise any key on the BLKEY_INPUT_PIN row will enter the bootloader */
#define BLKEY_CUSTOM_GPIO_INIT { \
    /* Register       Value       Mask     */  \
    {&SN_GPIO0->MODE, 0x0000FFFF, 0xFFFFFFFF}, \
    {&SN_GPIO3->MODE, 0x00000001, 0x00010001}, \
}
#else
#error Not configured for this target.
#endif
