#!/usr/bin/env python3
# Generate a simple .ico file containing 10x10 and 30x30 32-bit RGBA icons.

from pathlib import Path

output = Path(__file__).with_name('window_icon.ico')

# ICONDIR header
icon_dir = bytes([
    0x00, 0x00,  # Reserved
    0x01, 0x00,  # Type = ICON
    0x02, 0x00,  # Count = 2
])

# First image entry: 10x10, 32bpp
width1 = 10
height1 = 10
image1_size = 40 + width1 * height1 * 4 + ((width1 + 31) // 32) * 4 * height1
image1_offset = 6 + 16 * 2
entry1 = bytes([
    width1,
    height1,
    0x00,
    0x00,
    0x01, 0x00,
    0x20, 0x00,
]) + image1_size.to_bytes(4, 'little') + image1_offset.to_bytes(4, 'little')

# Second image entry: 30x30, 32bpp
width2 = 30
height2 = 30
image2_size = 40 + width2 * height2 * 4 + ((width2 + 31) // 32) * 4 * height2
image2_offset = image1_offset + image1_size
entry2 = bytes([
    width2,
    height2,
    0x00,
    0x00,
    0x01, 0x00,
    0x20, 0x00,
]) + image2_size.to_bytes(4, 'little') + image2_offset.to_bytes(4, 'little')

# BITMAPINFOHEADER for one image
def bitmap_header(w, h, size_image):
    return bytes([
        0x28, 0x00, 0x00, 0x00,                # Header size = 40
    ]) + w.to_bytes(4, 'little') + (h * 2).to_bytes(4, 'little') + bytes([
        0x01, 0x00,                              # Planes = 1
        0x20, 0x00,                              # Bit count = 32
        0x00, 0x00, 0x00, 0x00,                  # Compression = BI_RGB
    ]) + size_image.to_bytes(4, 'little') + bytes([
        0x13, 0x0B, 0x00, 0x00,                  # XPelsPerMeter = 2835
        0x13, 0x0B, 0x00, 0x00,                  # YPelsPerMeter = 2835
        0x00, 0x00, 0x00, 0x00,                  # Colors used
        0x00, 0x00, 0x00, 0x00,                  # Important colors
    ])

# Generate pixel data in BGRA order.
def pixel_data(w, h, b, g, r, a=255):
    row = bytes([b, g, r, a]) * w
    return row * h

# AND mask rows padded to 32-bit boundary.
def and_mask(w, h):
    mask_stride = ((w + 31) // 32) * 4
    return bytes(mask_stride * h)

image1 = bitmap_header(width1, height1, width1 * height1 * 4) + pixel_data(width1, height1, 0x00, 0x00, 0xFF) + and_mask(width1, height1)
image2 = bitmap_header(width2, height2, width2 * height2 * 4) + pixel_data(width2, height2, 0x00, 0x80, 0x00) + and_mask(width2, height2)

output.write_bytes(icon_dir + entry1 + entry2 + image1 + image2)
print(f'Wrote {output} ({len(output.read_bytes())} bytes)')
