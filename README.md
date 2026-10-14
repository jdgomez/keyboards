# Keyboard Configs

Keymaps personales para teclados split Corne (crkbd). Todos usan layout Dvorak.

## Configuraciones

| Directorio | Descripción                                                                                                    |
|------------|-----------------------------------------------------------------------------------------------------------------|
| `current`  | Configuración estable en uso (antes `003`). `current/qmk`: Corne RP2040 cableado. `current/zmk`: Corne nice!nano Bluetooth (FunkeeB). Dvorak, home row mods GACS, combos, auto shift, atajos de captura de pantalla de macOS |
| `legacy`   | Versiones antiguas conservadas por referencia, ya no se usan: `001` (config principal original, mano izquierda master), `001-reverse` (igual pero manos invertidas), `002` (adaptación intermedia a crkbd/rev1 + RP2040) |

Próxima versión prevista: `experimental` (aún no creada).

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

## Compilar (current/qmk - Corne RP2040)

Copia el directorio del keymap a QMK:

```bash
cp -r current/qmk/* ~/qmk_firmware/keyboards/crkbd/keymaps/v001
```

Compila:

```bash
~/.local/bin/qmk compile -kb crkbd/rev1 -km v001 -e CONVERT_TO=promicro_rp2040
```

El `.uf2` se genera en `~/qmk_firmware/crkbd_rev1_v001_promicro_rp2040.uf2`.

## Flashear (current/qmk - Corne RP2040)

El teclado se flashea en modo bootloader mediante UF2 — aparece como una unidad USB llamada `RPI-RP2`.

Como el doble tap en RESET quita el teclado, usar el script incluido:

```bash
# 1. Ejecuta el script (queda esperando)
./scripts/flash_corne.sh

# 2. Haz doble tap rápido en el botón RESET de la mitad izquierda
#    El teclado se detecta, se copia el firmware y se reinicia solo
```

## Compilar (current/zmk - Corne nice!nano Bluetooth)

Config ZMK v0.3.0 en `current/zmk` (nice!nano v2 + pantallas nice!view). El keymap
`current/zmk/config/corne.keymap` es un port de `current/qmk/keymap.c`: mantener ambos sincronizados.

Pantallas (shields propios en `current/zmk/module`):
- Izquierda, `nice_view_bongo`: el Bongo Cat del firmware de fábrica de FunkeeB
  ([finestedm/temper-zmkstudio](https://github.com/finestedm/temper-zmkstudio/tree/niceview-bongo),
  portado de LVGL 9 a LVGL 8 para ZMK v0.3.0). Batería, capa, WPM con gráfica y conexión; el gato
  toca con las pulsaciones de ambas mitades y se duerme tras 1 min sin uso.
- Derecha, `nice_view_magikarp`: batería y conexión como el de serie, y Magikarp chapoteando que
  evoluciona a Gyarados tras 1000 pulsaciones en esa mitad (se reinicia al dormir). Los sprites se
  generan con `sprites.py` en la carpeta del shield.

En GitHub: cada push que toque `current/zmk/` lanza el workflow `ZMK build`.
Los `.uf2` se descargan desde los artefactos del run.

En local, con Docker (los `.uf2` quedan en `current/zmk/out/`):

```bash
cd current/zmk
docker run --rm -u $(id -u):$(id -g) -e HOME=/tmp -v "$PWD":/w -w /w zmkfirmware/zmk-build-arm:3.5 sh -c '
  west init -l config; west update --fetch-opt=--filter=tree:0 && west zephyr-export &&
  west build -p -s zmk/app -d build -b nice_nano_v2 -- -DSHIELD="corne_left nice_view_adapter nice_view_bongo" -DZMK_CONFIG=/w/config -DZMK_EXTRA_MODULES=/w/module'
```

Para la mitad derecha: `-DSHIELD="corne_right nice_view_adapter nice_view_magikarp"`. El firmware queda en `build/zephyr/zmk.uf2`.

## Flashear (current/zmk)

1. Conectar por USB la mitad a flashear y hacer doble tap en RESET: aparece la unidad `NICENANO`.
2. Copiar el `.uf2` de esa mitad (`corne_left-*` o `corne_right-*`) a la unidad. Se reinicia sola.
3. Repetir con la otra mitad.

Si las mitades dejan de verse entre ellas: flashear `settings_reset-*.uf2` en ambas, después el firmware normal en ambas, y pulsar RESET en las dos a la vez.

Bluetooth: en la capa Media, fila inferior izquierda. `BT_SEL 0-2` elige equipo, `BT_CLR` olvida el emparejamiento activo, `OUT_USB` / `OUT_BLE` elige cable o Bluetooth.

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

## Tap dance (current)

| Tecla | 1 tap | 2 taps |
|-------|-------|--------|
| TD_S | `;` | `:` |
| TD_Q | `'` | `"` |
| TD_M | `-` | `_` |
