#include <drivers/keyboard.h>

static bool capsLock = false;
static bool shift = false;
static bool ctrl = false;
char key = 0, scanCode = 0;

static const char keymap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};
static char altChars(char ch) {
    switch (ch) {
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case ';': return ':';
        case '\'': return '"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        case '`': return '~';
        default: return ch;
    }
}

void kbHandler(registers *regs) {
    (void) regs;
    char buf[1];

    scanCode = inb(0x60);
    if (scanCode & 0x80) {
        scanCode &= 0x7F;
        switch (scanCode) {
        case SCAN_CODE_KEY_LEFT_SHIFT:
            shift = false;
            break;
        case SCAN_CODE_KEY_LEFT_CTRL:
            ctrl = false;
            break;
        }
    } else {
        switch (scanCode) {
        case SCAN_CODE_KEY_CAPS_LOCK:
            capsLock = !capsLock;
            break;
        case SCAN_CODE_KEY_LEFT_SHIFT:
            shift = true;
            break;
        case SCAN_CODE_KEY_LEFT_CTRL:
            ctrl = true;
            break;
        default:
            key = keymap[scanCode];

            if (scanCode == SCAN_CODE_KEY_BACKSPACE)
                key = '\b';
            else if (scanCode == SCAN_CODE_KEY_ENTER) 
                key = '\n';
            else if (scanCode == SCAN_CODE_KEY_TAB)
                key = '\t';

            else if (capsLock) {
                if (shift)
                    key = isAlpha(key) ? key : altChars(key);
                else
                    key = isAlpha(key) ? upper(key) : key;
            } else if (shift)
                key = isAlpha(key) ? upper(key) : altChars(key);

            buf[0] = key;
            write(buf);
            break;
        }
    }
}

void InitKb() {
    picUnmask(IRQ1_KEYBOARD);
    isrRegisterHandler(IRQ_BASE + IRQ1_KEYBOARD, kbHandler);
}
