#include <drivers/display.h>
#include <drivers/font.h>

const struct limine_framebuffer *buffer;

void write(int x, int y, uint32_t color, char* str) {
    const int size = 16 * 16 >> 3; // default font size
    const uint8_t* font = CGA16;
    int tempX = x, tempY = y;
    int target = 0;

    while (strlen(str)) {
        if (tempX >= (int) buffer->width) {
            tempY += size;
            tempX = x;
        } if (*str == '\n') {
            tempY += size;
            tempX = x;
            continue;
        }

        target = size * (*str++ - ' ');
        drawChar(tempX, tempY, 16, 16, color, (uint8_t*)(font + target));

        tempX += 16;
    }
}

void drawChar(int x, int y, int width, int height, uint32_t color, uint8_t* ch) {
	int size = width * height >> 3;
	int tempX = x, tempY = y;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 8; j++) {
            if (((tempY - y) == height) || (tempY > (int) buffer->height)) {
				return;
			} if ((tempX - x) == width) {
                tempX = x;
				tempY++;
			} if (ch[i] & (0x80 >> j))
			    drawPixel(tempX, tempY, color);
            tempX++;
		}
	}
}

void drawBitmap(int x, int y, int width, int height, uint32_t* data) {
    for (int currY = 0; currY < height; currY++) {
        for (int currX = 0; currX < width; currX++) {
            drawPixel(currX, currY, data[currX + width * currY]);

            if ((currX - x) == width) {
                currX = x;
                currY++;
            } if ((currY - y) == height)
                return;
        }
    }
}

void clearScr(uint32_t color) {
    for (uint64_t y = 0; y < buffer->height; y++)
        for (uint64_t x = 0; x < buffer->width; x++)
            drawPixel(x, y, color);
}

void drawPixel(uint64_t x, uint64_t y, uint32_t color) {
    if (buffer == NULL)
        return;

    volatile uint8_t *base = (volatile uint8_t *)(uintptr_t)buffer->address;
    uint64_t offset = y * buffer->pitch + x * (buffer->bpp >> 3);
    *(volatile uint32_t *)(base + offset) = color;
}

void InitVga(volatile struct limine_framebuffer_request fbRequest) {
    if (fbRequest.response == NULL || fbRequest.response->framebuffer_count < 1)
        haltCpu();

    buffer = fbRequest.response->framebuffers[0];
    clearScr(0xFFFFFF);
    write(0, 0, 0x00ff00, "OS has been successfully initiated...");
}
