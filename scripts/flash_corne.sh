#!/bin/bash
UF2=~/qmk_firmware/crkbd_rev1_v001_promicro_rp2040.uf2
MOUNT=/media/v/RPI-RP2

echo "Esperando que aparezca RPI-RP2... (haz doble tap en RESET ahora)"

while [ ! -d "$MOUNT" ]; do
    sleep 0.5
done

echo "Unidad detectada. Copiando firmware..."
cp "$UF2" "$MOUNT/"
echo "Listo. El teclado se reiniciará solo."
