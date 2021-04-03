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
#elif defined(TARGET_KEYCHRON_K1V4) // SN32F248B
#include "SN32F240B.h"
#define SN32_BOOTLOADER_ADDRESS 0x1FFF0301
#define BOOT0_GPIO SN_GPIO2
#define BOOT0_PIN 2
/* Backspace */
#define BLKEY_INPUT_GPIO SN_GPIO1
#define BLKEY_INPUT_PIN 5
#define BLKEY_OUTPUT_GPIO SN_GPIO3
#define BLKEY_OUTPUT_PIN 11

#else
#error Not configured for this target.
#endif
