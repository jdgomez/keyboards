"""Genera widgets/art.c (LVGL 8, 1 bit) a partir de los sprites de Pokémon Oro
(2.ª generación) de sprites/, para la zona de imagen vertical de 68x140.
Origen de los PNG: https://github.com/PokeAPI/sprites (versions/generation-ii/gold).

Uso (desde esta carpeta): python3 sprites.py widgets/art.c [preview.png]"""
import os
import sys
from PIL import Image, ImageDraw

W, H = 68, 140  # vertical, tal como se ve en la pantalla
INK, PAPER = 0, 1  # 1 = blanco de la paleta (fondo claro, como la barra de estado)
HERE = os.path.dirname(os.path.abspath(__file__))


def sprite(name):
    """PNG de 4 tonos -> 1 bit: los dos tonos claros a papel, los oscuros a tinta."""
    im = Image.open(os.path.join(HERE, "sprites", name)).convert("L")
    levels = sorted(set(im.getdata()))
    light = set(levels[len(levels) // 2:])
    out = Image.new("1", im.size, PAPER)
    out.putdata([PAPER if v in light else INK for v in im.getdata()])
    return out


def canvas():
    im = Image.new("1", (W, H), PAPER)
    return im, ImageDraw.Draw(im)


def waves(d, y):
    for x0 in range(-6, W, 12):
        d.arc([x0, y, x0 + 12, y + 6], 180, 360, fill=INK)
    for x0 in range(0, W, 12):
        d.arc([x0, y + 6, x0 + 12, y + 12], 180, 360, fill=INK)


def frames():
    karp, gyara = sprite("magikarp.png"), sprite("gyarados.png")
    kx = (W - karp.width) // 2
    out = {}
    # Salpicadura: Magikarp bota sobre el agua
    for i, ky in enumerate((70, 52)):
        im, d = canvas()
        waves(d, 118)
        im.paste(karp, (kx, ky))
        out[f"magikarp_{i}"] = im
    im, d = canvas()
    im.paste(gyara, ((W - gyara.width) // 2, (H - gyara.height) // 2 + 6))
    out["gyarados"] = im
    return out


def to_c(name, im):
    mem = im.rotate(-90, expand=True)  # vertical -> memoria (140x68)
    w, h = mem.size
    stride = (w + 7) // 8
    data = []
    px = mem.load()
    for y in range(h):
        for bx in range(stride):
            b = 0
            for bit in range(8):
                x = bx * 8 + bit
                if x < w and px[x, y]:
                    b |= 0x80 >> bit
            data.append(b)
    rows = ",\n".join("    " + ", ".join(f"0x{b:02x}" for b in data[i:i + 16])
                      for i in range(0, len(data), 16))
    return f"""static const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST uint8_t {name}_map[] = {{
#if CONFIG_NICE_VIEW_WIDGET_INVERTED
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff,
#else
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
#endif
{rows}
}};

const lv_img_dsc_t {name} = {{
    .header.cf = LV_IMG_CF_INDEXED_1BIT,
    .header.always_zero = 0,
    .header.reserved = 0,
    .header.w = {w},
    .header.h = {h},
    .data_size = {8 + len(data)},
    .data = {name}_map,
}};
"""


if __name__ == "__main__":
    fr = frames()
    with open(sys.argv[1], "w") as f:
        f.write("/* Generado por sprites.py - no editar a mano */\n\n#include <lvgl.h>\n\n")
        f.write("\n".join(to_c(n, im) for n, im in fr.items()))
    if len(sys.argv) > 2:
        sheet = Image.new("L", (len(fr) * (W + 6), H), 128)
        for i, im in enumerate(fr.values()):
            sheet.paste(im.convert("L"), (i * (W + 6), 0))
        sheet.resize((sheet.width * 4, H * 4), Image.NEAREST).save(sys.argv[2])
