# Keyboard Configs

Keymaps personales para teclados split Corne (crkbd). Todos usan layout Dvorak.

## Configuraciones

| Directorio | Descripción |
|-----------|-------------|
| `001` | Config principal — Corne crkbd, mano izquierda como master |
| `001-reverse` | Igual que 001 pero con manos invertidas (fix de hardware) |
| `002` | Corne RP2040 — basada en 001, adaptada para crkbd/rev1 + RP2040 |
| `casum` | Config de un amigo — más tap dance, RGB por capa, tri-layer |

## Requisitos

```bash
pipx install qmk
qmk setup
sudo ~/qmk_firmware/util/install_udev.sh
```

Dependencias del sistema:

```bash
sudo apt-get install -y git avr-libc gcc-avr binutils-avr dfu-programmer \
  dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libhidapi-hidraw0 \
  avrdude dos2unix
```

## Compilar (002 — Corne RP2040)

Copia el directorio del keymap a QMK:

```bash
cp -r 002 ~/qmk_firmware/keyboards/crkbd/keymaps/v001
```

Compila:

```bash
~/.local/bin/qmk compile -kb crkbd/rev1 -km v001 -e CONVERT_TO=promicro_rp2040
```

El `.uf2` se genera en `~/qmk_firmware/crkbd_rev1_v001_promicro_rp2040.uf2`.

## Flashear (002 — Corne RP2040)

El teclado se flashea en modo bootloader mediante UF2 — aparece como una unidad USB llamada `RPI-RP2`.

Como el doble tap en RESET quita el teclado, usar el script incluido:

```bash
# 1. Ejecuta el script (queda esperando)
./scripts/flash_corne.sh

# 2. Haz doble tap rápido en el botón RESET de la mitad izquierda
#    El teclado se detecta, se copia el firmware y se reinicia solo
```

## Tildes y eñe

Todos los sistemas configurados con **English (US International)**. Con RALT en el pulgar derecho:

| Combinación | Resultado |
|-------------|-----------|
| RALT + a | á |
| RALT + e | é |
| RALT + i | í |
| RALT + o | ó |
| RALT + u | ú |
| RALT + n | ñ |

## Tap dance (002)

| Tecla | 1 tap | 2 taps |
|-------|-------|--------|
| TD_S | `;` | `:` |
| TD_Q | `'` | `"` |
| TD_M | `-` | `_` |
| TD_A | `@` | `#` |
| TD_J | `Space` | `Enter` |
