#pragma once

#define MASTER_LEFT

// Tap dance / Home Row Mods
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD          // activa el mod si se pulsa otra tecla antes de soltar

// Combos: ventana de tiempo para detectar dos teclas simultáneas
#define COMBO_TERM 50

// Auto Shift: solo números y símbolos (las letras se excluyen para no chocar con HRM)
#define AUTO_SHIFT_TIMEOUT 200
#define NO_AUTO_SHIFT_ALPHA

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
