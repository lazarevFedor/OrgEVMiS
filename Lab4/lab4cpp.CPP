#include "dos.h"
#include "conio.h"
#include "stdio.h"
int code();
int main() {
    int x = 1, y = 1, ch = 0;
    textbackground(BLACK);
    window(10, 5, 70, 15);
    clrscr();
    do {
        clrscr();
        gotoxy(x, y);
        putch('*');
        ch = code();
        switch (ch) {
        case 72: {
            while ((y - 1) >= 0) {
                y -= 1;
                clrscr();
                gotoxy(x, y);
                putch('*');
                delay(500);
            }
            break; }
        case 80: {
            while ((y + 1) <= (15 - 5)) {
                y += 1;
                clrscr();
                gotoxy(x, y);
                putch('*');
                delay(500);
            }
            break;  }
        }
    } while (ch != 27);
    return 0;
}
int code() {
    union REGS r;
    r.h.ah = 0x7;
    int86(0x21, &r, &r);
    return r.h.al;
}
