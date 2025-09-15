#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdio>
#endif

using namespace std;

// Hàm clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H"; 
#endif
}

// Hàm đọc phím
int getKey() {
#ifdef _WIN32
    int c = _getch();
    if (c == 224) { // special key
        c = _getch();
        switch (c) {
            case 72: return 'U'; // Up
            case 80: return 'D'; // Down
            case 75: return 'L'; // Left
            case 77: return 'R'; // Right
        }
    }
    if (c == 13) return '\n'; // Enter
    return c;
#else
    char buf = 0;
    struct termios old = {};
    tcgetattr(STDIN_FILENO, &old);
    struct termios new_attr = old;
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
    read(STDIN_FILENO, &buf, 1);
    if (buf != '\033') {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        if (buf == '\n' || buf == '\r') return '\n';
        return buf;
    }
    char seq1 = 0, seq2 = 0;
    read(STDIN_FILENO, &seq1, 1);
    read(STDIN_FILENO, &seq2, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    if (buf == '\033') { // ESC
        char seq[2];
        if (seq1 == '[') {
            switch (seq2) {
                printf("Debug: seq[1] = %c\n", seq[1]);
                case 'A': return 'U'; // Up
                case 'B': return 'D'; // Down
                case 'C': return 'R'; // Right
                case 'D': return 'L'; // Left
            }
        }
    }
    if (buf == '\n' || buf == '\r') return '\n';
    return buf;
#endif
}

void gotoXY(int row, int col) {
#ifdef _WIN32
    // Windows API
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = col - 1; // Windows tính từ 0
    pos.Y = row - 1;
    SetConsoleCursorPosition(hConsole, pos);
#else
    // macOS/Linux: ANSI escape
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
#endif
}