#include <dos.h>
#include <conio.h>
#include <stdio.h>

int keypressed() {
    union REGS sdr;
    sdr.h.ah = 0x0B;
    int86(0x21, &sdr, &sdr);
    return sdr.h.al;
}

int code() {
    union REGS sdr;
    sdr.h.ah = 0x07;
    int86(0x21, &sdr, &sdr);
    return sdr.h.al;
}

void initMouse() {
    union REGS regs;
    regs.x.ax = 0;
    int86(0x33, &regs, &regs);
}

void showMouse() {
    union REGS regs;
    regs.x.ax = 1;
    int86(0x33, &regs, &regs);
}

void hideMouse() {
    union REGS regs;
    regs.x.ax = 2;
    int86(0x33, &regs, &regs);
}

void lockMouse() {
    hideMouse();
}

void unlockMouse() {
    showMouse();
}

void printMessage(const char* message) {
    while (*message) {
        putch(*message);
        message++;
    }
}

/*void clearBuffer() {
    while (keypressed()) {
        code();
    }
}*/

int main() {
    int ch = 0;

    initMouse();
    unlockMouse();

    clrscr();

    do {
        if (keypressed()) {
            ch = code();
            switch (ch) {
            case 77:
                lockMouse();
                printMessage("Mouse locked.\r\n");
                break;
            case 75:
                unlockMouse();
                printMessage("Mouse unlocked.\r\n");
                break;
            }
        }
        //clearBuffer();
        delay(100);
    } while (ch != 27);

    return 0;
}