#include <iostream>
#include <cstdlib>
#include "mylib.h"
using namespace std;
#define MAX 10
#define STEP 3

string POP = "Pop";
string PUSH = "Push";
string EXIT = "Exit";

int DISPLAY_COL_START = 31;
int MAX_WIDTH = MAX * (STEP + 1) - 1;
int DISPLAY_TOP = 3;
int DISPLAY_ROW = DISPLAY_TOP + 1;
int DISPLAY_BOTTOM = DISPLAY_ROW + 1;

int drawBar()
{
    // Khung bat dau
    gotoXY(DISPLAY_TOP, DISPLAY_COL_START - 1);
    cout << "┌";
    gotoXY(DISPLAY_BOTTOM, DISPLAY_COL_START - 1);
    cout << "└";

    // Khung ket thuc
    gotoXY(DISPLAY_TOP, DISPLAY_COL_START + MAX_WIDTH);
    cout << "┐";
    gotoXY(DISPLAY_BOTTOM, DISPLAY_COL_START + MAX_WIDTH);
    cout << "┘";

    // Khung ngang
    gotoXY(DISPLAY_TOP, DISPLAY_COL_START);
    for (int i = 0; i < MAX_WIDTH; i++)
        cout << "─";
    gotoXY(DISPLAY_BOTTOM, DISPLAY_COL_START);
    for (int i = 0; i < MAX_WIDTH; i++)
        cout << "─";

    for (int i = 0; i <= MAX; i++)
    {
        gotoXY(DISPLAY_ROW, DISPLAY_COL_START + i * (STEP + 1) - 1);
        cout << "│";
        if (i == 0 || i == MAX)
            continue;
        gotoXY(DISPLAY_TOP, DISPLAY_COL_START + i * (STEP + 1) - 1);
        cout << "┬";
        gotoXY(DISPLAY_BOTTOM, DISPLAY_COL_START + i * (STEP + 1) - 1);
        cout << "┴";
    }
    return 0;
}

int drawStartPointer(int index)
{
    int col = DISPLAY_COL_START - 1 + (STEP * index + index + 2);
    gotoXY(DISPLAY_TOP - 1, col);
    cout << "↓ start";
    return 0;
}

int drawEndPointer(int idx)
{
    int index = MAX - idx - 1;
    int col = DISPLAY_COL_START - 1 + (STEP * index + index + 2);
    gotoXY(DISPLAY_BOTTOM + 1, col);
    cout << "↑ end";
    return 0;
}

int drawChoice(bool isSelected, string text) {
    int TABLE_WIDTH = 23;

    cout << "│";
    if (isSelected) {
        cout << "→ ";
    } else {
        cout << "  ";
    }

    cout << text;

    int remaining = TABLE_WIDTH - 2 - text.length();
    for (int i = 0; i < remaining; i++) {
        cout << " ";
    }
    cout << "│\n";
    return 0;
}

struct Deque
{
    int arr[MAX];
    int front, back;
    Deque()
    {
        front = -1;
        back = -1;
    }

    bool isEmpty()
    {
        return (front == -1);
    }

    bool isFull()
    {
        return ((front == 0 && back == MAX - 1) || (front == back + 1));
    }

    void pushFront(int x)
    {
        if (isFull())
        {
            cout << "Deque full!\n";
            return;
        }
        if (isEmpty())
        {
            front = back = 0;
        }
        else if (front == 0)
        {
            front = MAX - 1;
        }
        else
        {
            front--;
        }
        arr[front] = x;
    }

    void pushBack(int x)
    {
        if (isFull())
        {
            cout << "Deque full!\n";
            return;
        }
        if (isEmpty())
        {
            front = back = 0;
        }
        else if (back == MAX - 1)
        {
            back = 0;
        }
        else
        {
            back++;
        }
        arr[back] = x;
    }

    void popFront()
    {
        if (isEmpty())
        {
            cout << "Deque empty!\n";
            return;
        }
        cout << "Removed front: " << arr[front] << endl;
        if (front == back)
        {
            front = back = -1;
        }
        else if (front == MAX - 1)
        {
            front = 0;
        }
        else
        {
            front++;
        }
    }

    void popBack()
    {
        if (isEmpty())
        {
            cout << "Deque empty!\n";
            return;
        }
        cout << "Removed back: " << arr[back] << endl;
        if (front == back)
        {
            front = back = -1;
        }
        else if (back == 0)
        {
            back = MAX - 1;
        }
        else
        {
            back--;
        }
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Deque empty!\n";
            return;
        }
        cout << "Deque: ";
        int i = front;
        while (true)
        {
            cout << arr[i] << " ";
            if (i == back)
                break;
            i = (i + 1) % MAX;
        }
        cout << endl;
    }

    void displayTerminal(){
        if(isEmpty()){
            return;
        }

        int i = front;
        drawStartPointer(back);
        while (true) {
            int index = (i - front + MAX) % MAX;
            int col = DISPLAY_COL_START + (STEP * index + index);
            gotoXY(DISPLAY_ROW, col);
            cout << arr[i];
            if (i == back) break;
            i = (i+1) % MAX;
        }
    }
};

int main()
{
    int choice = 0;
    vector<string> menu = {POP, PUSH, EXIT};
    int WIDHT = 26;
    Deque dq;

    while (true)
    {
        clearScreen();
        drawBar();
        dq.displayTerminal();

        gotoXY(2, 1);
        cout << "┌───────────────────────┐\n";
        cout << "│         Menu          │\n";
        cout << "├───────────────────────┤\n";
        for (int i = 0; i < (int)menu.size(); i++)
        {
            drawChoice(i == choice, menu[i]);
        }
        cout << "└───────────────────────┘\n";

        int key = getKey();
        if (key == 'U')
        {
            choice = (choice - 1 + menu.size()) % menu.size();
        }
        else if (key == 'D')
        {
            choice = (choice + 1) % menu.size();
        }
        else if (key == '\n')
        { // Enter
            gotoXY(7+(int)menu.size(), 1);
            if (menu[choice] == PUSH)
            {
                int value = 0;
                cout << "Nhập 1 số (<1000): ";
                cin >> value;
                dq.pushBack(value);
            }
            else if (menu[choice] == POP)
            {
                dq.popBack();
            }
            else if (menu[choice] == EXIT)
                break;
            // exit(0);
        }
    }
    return 0;
}
