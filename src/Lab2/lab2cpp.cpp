#include <iostream>
#include <Windows.h>
#include <string>
#include <winuser.h>

using namespace std;

// Функция для установки позиции курсора
void gotoxy(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

// Функция для создания окна
void createWindow(int X1, int Y1, int X2, int Y2) {
    gotoxy(X1 - 1, Y1 - 1);
    for (int x = X1 - 1; x < X2 + 2; x++)
        cout << '*';
    gotoxy(X1 - 1, Y2 + 1);
    for (int x = X1 - 1; x < X2 + 2; x++)
        cout << '*';
    for (int y = Y1; y <= Y2 + 1; y++) {
        gotoxy(X1 - 1, y);
        cout << '*';
    }
    for (int y = Y1; y <= Y2 + 1; y++) {
        gotoxy(X2 + 1, y);
        cout << '*';
    }
}

// Функция для установки цвета консоли
void consoleColor(int tColor, int bgColor) {
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOuput, ((bgColor << 4) + tColor));
}

// Функция для скроллинга окна
void scrollWindow(int X1, int Y1, int X2, int Y2) {
    HWND hWnd = GetConsoleWindow();
    RECT rect = { X1, Y1, X2, Y2 };
    ScrollWindowEx(hWnd, 0, -1, &rect, NULL, NULL, NULL, SW_INVALIDATE);
}

// Функция для вывода цветов
void printColors(int x1, int y1, int x2, int y2, unsigned delay, int step) {
    const int maxLines = (y2 - y1) / step + 1;
    const string colorNames[] = {
            "black","blue","green","cyan","red","magenta","brown","lightgray","darkgray","lightblue","lightgreen",
                               "lightcyan","lightred","lightmagenta","yellow","white"
    };
    const string colorNumbers[] = {
            "black","blue","green","cyan","red","magenta","brown","lightgray","darkgray","lightblue","lightgreen",
            "lightcyan","lightred","lightmagenta","yellow","white"
    };

    // Рисование окна один раз
    consoleColor(15, 0);
    createWindow(x1, y1, x2, y2);

    for (int bgIndex = 0; ; bgIndex = (++bgIndex) % 16) {
        for (int textIndex = 0; textIndex < 16; ++textIndex) {
            int tempBg = bgIndex, tempText = textIndex;

            // Вывод строк с цветами
            for (int line = 0; line < maxLines; ++line) {
                if (y2 - line * (step + 1) >= y1 && y2 - line * (step + 1) <= y2) {
                    // Очистка строки перед выводом
                    consoleColor(15, 0); // Сброс цвета на белый по умолчанию
                    gotoxy(x1, y2 - line * (step + 1));
                    for (int i = 0; i < x2 - x1 + 1; ++i) {
                        cout << ' ';
                    }
                    consoleColor(tempText, tempBg);
                    gotoxy(x1, y2 - line * (step + 1));
                    cout << colorNumbers[tempBg] << ' ' << colorNames[tempText];
                }

                // Обновление временных индексов цветов
                if (tempText == 0 && tempBg!= 0) {
                    tempBg--;
                    tempText = 15;
                } else if (tempText == 0 && tempBg == 0) {
                    break;
                } else {
                    tempText--;
                }
            }

            // Скроллинг окна
            scrollWindow(x1, y1, x2, y2); // Scroll up

            // Пауза между выводами
            Sleep(delay);
        }
    }
}

int main() {
    SetConsoleCP(65001); // Кодировка для РУ символов
    SetConsoleOutputCP(65001);

    const unsigned T = 300; // Шаг времени между отправкой сообщений (в МилиСекундах)
    const int S = 1; // Шаг строк между отправкой

    // Размеры окна
    const int X1 = 10;
    const int Y1 = 5;
    const int X2 = 70;
    const int Y2 = 15;

    printColors(X1, Y1, X2, Y2, T, S);

    return 0;
}
