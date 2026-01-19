#include <drivers/display.h>
#include <drivers/font.h>

const struct limine_framebuffer* buffer;
int posX = 0, posY = 0;

void write(char* str) {
    while (*str) {
        if (*str == '\n' || posX >= (int)buffer->width) {
            posY += 16;
            posX = 0;
            ++str;
            continue;
        } else if (*str == '\t') {
            posX += 16 * 4;
            ++str;
            continue;
        }

        drawChar(*str++, posX, posY, 0x000000);
        posX += 16;
    }
}

void drawBitmap(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t* data) {
    for (uint64_t currY = 0; currY < height; currY++) {
        for (uint64_t currX = 0; currX < width; currX++) {
            if ((currX - x) > width) {
                currX = x;
                currY++;
            } if ((currY - y) > height) {
                return;
            } if (currX >= buffer->width || currY >= buffer->height)
                return;

            drawPixel(currX, currY, data[currX + width * currY]);
        }
    }
}

void clearScr(uint32_t color) {
    for (uint64_t y = 0; y < buffer->height; y++)
        for (uint64_t x = 0; x < buffer->width; x++)
            drawPixel(x, y, color);
}

void drawChar(char ch, uint64_t x, uint64_t y, uint32_t color) {
    if (ch == '\b') {
        posX = (posX - 16 >= 0) ? (posX - 16) : 0;
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                drawPixel(posX + j, posY + i, 0xffffff);
        posX -= 16;
        return;
    }

    const int size = 16 * 16 >> 3;
    const uint8_t* font = CGA16;
    posX = x; posY = y;

    uint8_t* todo = (uint8_t*)(font + (size * (ch - ' ')));

    for (uint64_t row = 0; row < size; row++) {
        for (uint64_t col = 0; col < 8; col++) {
            if (((y - posY) == 16) || (y > buffer->height)) {
				return;
			} if ((x - posX) == 16) {
                x = posX;
                y++;
            } if (todo[row] & (0x80 >> col))
                drawPixel(x, y, color);
            x++;
        }
    }
}

void drawPixel(uint64_t x, uint64_t y, uint32_t color) {
    if (!buffer || x >= buffer->width || y >= buffer->height)
        return;

    uint8_t* base = (uint8_t *)buffer->address;
    uint64_t offset = y * buffer->pitch + x * (buffer->bpp >> 3);
    *(uint32_t *)(base + offset) = color;
}

void setPos(vgaPos cords) {
    posX = cords.x;
    posY = cords.y;
}

vgaPos getPos() {
    vgaPos cords = { posX, posY };
    return cords;
}

void InitVga(volatile struct limine_framebuffer_request fbRequest) {
    if (fbRequest.response == NULL || fbRequest.response->framebuffer_count < 1)
        haltCpu();

    buffer = fbRequest.response->framebuffers[0];
    clearScr(0xffffff);
}
