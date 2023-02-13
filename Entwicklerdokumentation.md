# Entwicklerdokumentation

## Beschreibung Snake
Snake ist ein kleines 2D Game. Man spielt eine Schlange in einem Feld. Im Feld wird jedes mal, wenn die Schlange ein essen aufisst, ein neues Essen generiert. Das Ziel des Spiels ist es so groß wie möglich zu werden, indem man das Essen aufisst.
Das Spiel ist zu Ende wenn die Schlange die maximale größe erreicht hat oder gegen eine Wand oder gegen sich selber bewegt.

## Funktionen
- `void selectFieldSize()`
- `void selectSpeed()`
- `void generateField(char field[fieldHeight][fieldWidth])`
- `void generateSnake(char field[fieldHeight][fieldWidth], int snake[2][(fieldHeight - 2) * (fieldWidth - 2)])`
- `void generateFood(char field[fieldHeight][fieldWidth])`
- `void printField(char field[fieldHeight][fieldWidth])`
- `void addSnakePoint(int snake[2][(fieldHeight - 2) * (fieldWidth - 2)], int row, int col)`
- `void lose()`
- `void checkWin()`
- `void moveSnake(int snake[2][(fieldHeight - 2) * (fieldWidth - 2)], char field[fieldHeight][fieldWidth])`
- `void timer()`
- `int main()`

---
---
## Beschreibung der einzelnen Funktionen
### `void selectFieldSize()`
>Die Funktion ist zur Bestimmung der Feldgröße zuständig.Es frägt den Nutzer nach drei vordefinierten größen. Der Nutzer bestimmt die Größe durch die Eingabe der Tastatur. Die ausgewählten größen werden in zwei Variablen `int fieldHeight` und `int fieldWidth` gespeichert

---

### `void selectSpeed()`
>Die Funktion bestimmt die Spielgeschwindigkeit des Spiels. Der Nutzer wird aufgefordert eine von drei Schwierigkeitsgraden auszuwählen. Der Nutzer wählt die Schwierigkeit durch die Tastatureingabe. Die ausgewählte geschwindigkeit wird in die Variable `int speed` gespeichert

---

### `void generateField(char field[fieldHeight][fieldWidth])`
>Das Feld wird mit der ausgewählten größe erstellt. Der Rand des Feldes wird zudem mit '#' Charakter gefüllt.

---

### `void generateSnake(char field[fieldHeight][fieldWidth], int snake[2][(fieldHeight - 2) * (fieldWidth - 2)])`
>Die Schlange wird im Feld generiert. Die Schlange besitzt ein eigenes 2 Dimensionales Array für die Speicherung der Koordinaten der Schlange. Das Feld der Schlange ist so groß, wie die maximale größe die die Schlange annehmen kann im Feld. Die Schlange wird in der Mitte vom Feld generiert.

---

### `void generateFood(char field[fieldHeight][fieldWidth])`
>Das Essen wir zufällig auf ein freies Feld generiert. Das Essen ist mit einem '+' Charakter gekennzeihnet.

---

### `void printField(char field[fieldHeight][fieldWidth])`
>In der Funktion wird der aktuell Score (Schlangengröße), der Timer und das ganze Feld in der Konsole gezeichnet.

---

### `void addSnakePoint(int snake[2][(fieldHeight - 2) * (fieldWidth - 2)], int row, int col)`
>Diese Funktion erweitert die Schlange und erhöt den Score um eins. Die übergebenen parameter `row`und `col` sind die neuen Koordinaten des dazukommenden Teiles der Schlange.

---

### `void lose()`
>Diese Funktion prüft jeden Zug ob die Schlange verloren hat. Dabei wird geprüft ob die Schlange sich auf eine Wand oder auf sich selber bewegt. Wenn dies der Fall ist wird das Programm beendet.

---

### `void checkWin()`
>In der Funktion wird geprüft ob man gewonnen hat. Gewonnen hat man wenn der Score die maximale Größe erreicht hat. Das Progamm wird beendet wenn der Spieler gewonnen hat.

---

### `void moveSnake(int snake[2][(fieldHeight - 2) * (fieldWidth - 2)], char field[fieldHeight][fieldWidth])`
>In der Funktion bewegt sich die Schlange im Feld. Dies ist mit der Tastatureingabe möglich. Mit 'w', 'a', 's' und 'd' kann man die Schlange bewegen. Falls keine Einagbe vom Nutzer erfolgt, wird die Schlange sich weiterhin in die zuletzt gelenkte Richtung bewegen.

---

### `void timer()`
>In dieser Funktion werden die Sekunden und Minuten gezählt. Diese wird mithilfe der `Speed` variable ermöglicht. Die `Speed` Variable ist die anzahl der Millisekunden wie lange das Programm schläft. 

---

### `int main()`
>In der Main Funktion werden alle anderen Funktionen aufgerufen um das Spiel zu generieren und zu starten. Das Spiel läuft in einer Unendlichschleife und wird durch die `lose()` oder `checkWin()` Funktion terminiert.