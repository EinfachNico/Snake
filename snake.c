#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// eingabe für wadie Bewegung der Schlange
char input;
// Boolescher Wert ob essen auf dem Feld liegt (food = 0, essen nicht da)(food = 1, essen da)
int food = 0;
// Der Score ist gleichzeitig die aktuelle Länge der Schlange
int score = 1;
// Größe des Feldes
int fieldHeight = 0;
int fieldWidth = 0;
//Geschwindigkeit der Schlange
int speed = 0;
//Timer
int milisec = 0;
int second = 0;
int minute = 0;

// Mann kann die größe des Feldes bestimmen, es darf jedoch nicht kleiner als 5 sein
void selectFieldSize()
{
    while (fieldHeight != 5 && fieldHeight != 7 && fieldHeight != 9)
    {
        printf("Auf welchem Spielfeld wollen sie spielen?\n(k)lein  (m)ittel  (g)ross\n");
        char fieldInput = tolower(getch());
        switch (fieldInput)
        {
        case 'k':
            fieldHeight = 5;
            fieldWidth = 6;
            break;
        case 'm':
            fieldHeight = 7;
            fieldWidth = 8;
            break;
        case 'g':
            fieldHeight = 9;
            fieldWidth = 10;
            break;
        default:
            system("cls");
            printf("Falsche eingabe, bitte geben sie eine gueltige Eingabe ein.\n");
            break;
        }
    }

    fieldWidth += 2;
    fieldHeight += 2;
}

//Schwierigkeitsgrad wird ausgewählt
void selectSpeed(){
    
    
    while(speed == 0)
    {
        system("cls");
        printf("Auf welchen Schwierigkeitsgrad wollen sie spielen?\n(l)eicht  (m)ittel  (s)chwer\n");
        char speedEingabe = tolower(getch());
        switch (speedEingabe)
        {
        case 'l':
            speed = 1000;
            break;
        case 'm':
            speed = 500;
            break;
        case 's':
            speed = 250;
            break;
        default:
            system("cls");
            printf("Falsche Eingabe! Bitte geben sie eine gueltige Eingabe ein.\n");
            break;
        }
    }
}

// Der Spielrand wird mit '#' gefüllt
void generateField(char field[fieldHeight][fieldWidth])
{
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int z = 0; z < fieldHeight+1; z++)
        {
            if (z == 0 || z == fieldHeight || i == 0 || i == fieldHeight - 1)
            {
                field[i][z] = '#';
            }
            else
            {
                field[i][z] = ' ';
            }
        }
    }
}

// Schlange wird generiert. Die Schlange ist zu Beginn nur 1 gross und wird in der Mitte starten.
void generateSnake(char field[fieldHeight][fieldWidth], int snake[2][(fieldHeight - 2) * (fieldWidth - 2)])
{
    snake[0][0] = fieldHeight / 2;
    snake[1][0] = fieldHeight / 2;

    field[snake[0][0]][snake[1][0]] = '&';
}

// Das Essen wird zufällige im Feld platziert
void generateFood(char field[fieldHeight][fieldWidth])
{
    srand(time(NULL));
    int row, col;
    // Die zufällige Zahl für Reihe und Zeile soll generiert werden
    do
    {
        row = (rand() % fieldHeight - 2) + 1;
        col = (rand() % fieldWidth - 2) + 1;

        // falls die position nicht leer ist, wird eine neue Koordinate im Feld gesucht
    } while (field[row][col] != ' ');

    // Essen wird ins Feld platziert und food wird auf 1 gesetzt
    field[row][col] = '+';
    food = 1;
}

// Print funktion zum ausgeben des gesamten Feldes mit Score
void printField(char field[fieldHeight][fieldWidth])
{
    // Konsole wird gelöscht
    system("cls");
    // Score wird ausgegeben
    printf("Score: %d\t\tTimer: %d:%2.d\n\n", score, second/60, second);
    // Feld wird ausgegeben
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int z = 0; z < fieldHeight+1; z++)
        {
            printf("%c ", field[i][z]);
        }
        printf("\n");
    }
}

// Verlängerung der Schlange durch aufsammeln des Essens
void addSnakePoint(int snake[2][(fieldHeight - 2) * (fieldWidth - 2)], int row, int col)
{
    // Food wird auf 0 gesetzt und score wird um 1 erhöht
    food = 0;
    score++;

    // Neue Koordinate wird im Array initilisiert mit den übergebenen koordinaten
    snake[0][score] = row;
    snake[1][score] = col;
}

// Die lose() Funktion wird aufgerufen wenn das Spiel beendet wird.
void lose()
{
    // Gibt den Score nochmal aus und beendet das Spiel und gleichzeitig das komplette Programm.
    printf("\n\nDas Spiel ist vorbei!\nSie haben einen Score von %d erreicht.\n\n", score);
    scanf("%c");
    exit(0);
}

//Win Condition, beendet das game
void checkWin()
{
    if(score == (fieldHeight-2)*(fieldWidth-2)){
    	system("cls");
        printf("Herzlichen Glueckwunsch. Sie haben das Spiel gewonnen!\nIhr Score ist %d.", score);
        exit(0);
    }
}

// Bewegt die Schlange im Feld
void moveSnake(int snake[2][(fieldHeight - 2) * (fieldWidth - 2)], char field[fieldHeight][fieldWidth])
{
    // Prüft ob Tastatur gedrückt wird, wenn ja dann sollen die character eingelesen werden
    if (kbhit())
    {
        char new = getch();
        if (new == 'w' || new == 'a' || new == 's' || new == 'd')
            input = new;
    }
    // Der Input wird verglichen
    switch (input)
    {
    case 'w':
        // Einzelne Koordinaten der Schlange werden die voderen Koordinaten zugewiesen.
        for (int i = score; i > 0; i--)
        {
            snake[0][i] = snake[0][i - 1];
            snake[1][i] = snake[1][i - 1];
            field[snake[0][i]][snake[1][i]] = 'O';
        }
        // Falls auf dem nächste Feld auf dem die Schlange trifft das Essen liegt, dann wird die addSnakePoint() Funktion aufgerufen
        // Fall nicht, dann wird im Feld auf dem die letzte Koordinate der Schlange liegt gelöscht.
        if (field[snake[0][0] - 1][snake[1][0]] == '+')
            addSnakePoint(snake, snake[0][0], snake[1][0]);
        else
            field[snake[0][score]][snake[1][score]] = ' ';
        // Die Y-Koordinate com Kopf der Schlange wird um 1 verringert um sich nach oben zu bewegen
        snake[0][0] -= 1;
        break;

        // Folgende 3 Codeblöcke funktionieren gleich nur mit unterschiedlichen Richtungen
    case 'a':
        for (int i = score; i > 0; i--)
        {
            snake[0][i] = snake[0][i - 1];
            snake[1][i] = snake[1][i - 1];
            field[snake[0][i]][snake[1][i]] = 'O';
        }
        if (field[snake[0][0]][snake[1][0] - 1] == '+')
            addSnakePoint(snake, snake[0][0], snake[1][0]);
        else
            field[snake[0][score]][snake[1][score]] = ' ';
        snake[1][0] -= 1;
        break;

    case 's':
        for (int i = score; i > 0; i--)
        {
            snake[0][i] = snake[0][i - 1];
            snake[1][i] = snake[1][i - 1];
            field[snake[0][i]][snake[1][i]] = 'O';
        }
        if (field[snake[0][0] + 1][snake[1][0]] == '+')
            addSnakePoint(snake, snake[0][0], snake[1][0]);
        else
            field[snake[0][score]][snake[1][score]] = ' ';
        snake[0][0] += 1;
        break;

    case 'd':
        for (int i = score; i > 0; i--)
        {
            snake[0][i] = snake[0][i - 1];
            snake[1][i] = snake[1][i - 1];
            field[snake[0][i]][snake[1][i]] = 'O';
        }
        if (field[snake[0][0]][snake[1][0] + 1] == '+')
            addSnakePoint(snake, snake[0][0], snake[1][0]);
        else
            field[snake[0][score]][snake[1][score]] = ' ';
        snake[1][0] += 1;
        break;
    default:
        break;
    }

    // True, falls das Feld auf dem die Schlange sich bewegt nicht leer und kein Essen ist.
    // In dem Fall berührt die Schlange die Wand oder sich selbst. Das Spiel ist somit vorbei.
    if (field[snake[0][0]][snake[1][0]] != ' ' && field[snake[0][0]][snake[1][0]] != '+')
        lose();

    // Falls das Feld leer ist auf dem die Schlage sich bewegt, wird das Feld aktuallisiert und durch ein 'O' ersetzt,
    // welches die Schlange darstellt.
    field[snake[0][0]][snake[1][0]] = '&';
}

//Zählt sekunden, wie lange das Game läuft.
void timer()
{
    milisec += speed;
    if(milisec >= 1000)
    {
        milisec = 0;
        second++;
    }
    if(second == 60)
    {
        minute++;
        second = 0;
    }
}

// main funktion
int main()
{
    // Konsole wird zu Beginn gelöscht
    system("cls");
    // Feldgröße und schwierigkeitsgrad wird definiert und es wird das Feld erstellt.
    selectFieldSize();
    selectSpeed();
    char field[fieldHeight][fieldWidth];
    generateField(field);

    // Schlange wird erstellt
    int snake[2][(fieldHeight - 2) * (fieldWidth - 2)];
    generateSnake(field, snake);

    // Das Feld wird einmalig ausgegeben. Der Spieler kann das Feld und die Schlange sehen.
    // Das Essen wird erst beim starten generiert.
    printField(field);

    // Programm hält an und wartet bis der Nutzer eine Eingabe für die Schlange auswählt um zu starten
    printf("Druecken sie W, A, S oder D um zu starten.");
    while (input != 'w' && input != 'a' && input != 's' && input != 'd')
    {
        input = getch();
    }

    // Spiel startet in Endlosschleife, bis das Spiel von der lose() Funktion terminiert wird
    while (1)
    {    
        // Schlange bewegt sich
        moveSnake(snake, field);

        // Prüfe Win Condition
        checkWin();

        // Falls es kein Essen auf dem Feld gibt wird eins generiert
        if (food == 0)
            generateFood(field);

        // Das Feld wird ausgegeben
        printField(field);

        // Das Bild wird alle je nach Schwierigkeitsgrad aktuallierst.
        // Das ist ebenfalls die Geschwindigkeit der Schlange
        Sleep(speed);
        timer();
    }
    return 0;
}
