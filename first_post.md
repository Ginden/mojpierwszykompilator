Kolejne wpisy będą pod tagami #mojpierwszykompilator i #brainfuck
Będę używał pseudokodu, implementowanie funkcji o oczywistych nazwach też sobie odpuszczę.
Tak samo jak implementowanie klas o nazwach typu `bf.tokens.move_right`.
Osoby, które zaimplementują i opublikują omawiany jid w dowolnym języku mogą liczyć na wygraną w konkursie, czyli sześciopak dobrego piwa.


Zacznijmy od tego, czym jest Brainfuck.
Brainfuck to ezoteryczny język programowania, który ma jedynie 8 instrukcji:
`<>+-[].,`
Język operuje na taśmie (zwykle implementowanej jako tablica typu `char` o długości 30 tysięcy elementów; istnieją jednak implementacje, które stosują nieskończone taśmy czy ).
Można to zapisać jako:
`char[30000] tape; // Jakaś metoda wypełnienia jej zerami`
Istnieje też pointer, czyli obecna pozycja w kodzie.
`int pointer = 0;`

Dobrze, ale co z tego? Zastanówmy się, co robią kolejne instrukcje.
`>` - przesuwa wskaźnik na taśmie w prawo, czyli można to zapisać jako: `pointer += 1;`
`<` - przesuwa wskaźnik na taśmie w lewo, czyli można to zapisać jako: `pointer -= 1;`
Przesunięcie poza krawędź w lewo to `undefined behavior` i pozostaje zgodne z wolą implementującego.
`+` - zwiększa wartość w obecnej komórce o 1, czyli można to zapisać jako `tape[pointer] += 1`;
`-` - zmniejsza wartość w obecnej komórce o 1, czyli można to zapisać jako `tape[pointer] -= 1`;
Zmniejszenie poniżej 0 to `undefined behavior` i pozostaje zgodne z wolą implementującego. Część implementacji zawija się do 255, część rzuca błędem, część pozwala na liczby ujemne.
`[` - rozpoczyna pętlę, która wykonuje się dopóki wartość obecna na taśmie nie wyniesie 0. Można to zapisać jako `while(tape[pointer] != 0) {`
`]` - kończy pętlę, można to zapisać jako `}`
`.` - drukuje na wyjście znak ASCII o kodzie równy obecnej wartości komórki. Można to zapisać jako `print(String.fromAsciiCode(tape[pointer]));` 
`,` - pobiera z wejścia znak i ustawia obecną komórkę nań: `tape[pointer] = String.toAsciiCode(readInput(1));`

Każdy inny znak jest ignorowany.
Napisanie interpretera jest banalne, zostawiam to jako ćwiczenie.
Weźmy taki prosty kod:
`+++>+<
[->++++<]`
https://github.com/Ginden/mojpierwszykompilator/blob/master/simplest.bf
Po skompilowaniu wygląda on następująco:
https://github.com/Ginden/mojpierwszykompilator/blob/master/simplest_compiled.c (nie jest to C, ale oferuje jakieś kolorowanie składni na GitHubie).

Nie ma żadnego outputu, stan taśmy po uruchomieniu to:
`0,13`

Naszym celem (ogólnie) będzie stworzenie takiego kompilatora, który zoptymalizuje nam ten kod do 
`tape[0] = 0;
tape[1] = 13`

Pierwszym krokiem w tym celu będzie łączenie operatorów. Po co robić `pointer += 1; pointer += 1; pointer += 1;`, skoro można zastąpić to `pointer += 3`?

W tym celu musimy przejść się po efekcie parsowania programu. Na potrzeby **tego** wpisu zakładam, że byliście zbyt leniwi, by napisać parser, który tworzył by drzewo składniowe, a zrobiliście tylko listę tokenów.
Napisanie parsera obsługującego nieskończenie zagnieżdżone pętle wymaga odrobiny gimnastykowania się.
Ogólnie drogą na skróty mogłoby by być użycie jakiegoś narzędzia do generowania parserów, ale nie będziemy ich omawiać ze względu na zasadę NIH.

Mamy listę obiektów typu `bf.tokens.Token` (dalej: Token).
`[new bf.tokens.Program_Start, new bf.tokens.Increment, new bf.tokens.Increment, new bf.tokens.Increment, ...]`

Uwaga, ostrzeżenie - na potrzeby dalszych przykładów będziemy stosować elementy programowania funkcyjnego.
> A smart man once told me you can write any program as a sequence of map and reduce calls.
! Tak właściwie jest to nieprawda, bo można iterować po tablicach tylko w sposób ciągły, bez powrotu do poprzedniego elementu.

! Tak naprawdę dałoby się, tylko wymaga to O(n^2) pamięci i wymaga odrobiny sprytu. Metodę zrobienia tego zostawiam jako ćwiczenie.

W skrócie - metoda `map` tworzy nową tablicę, której elementy tworzone są przez zastosowanie funkcji do każdego elementu pierwotnej tablicy.
Metoda `filter` tworzy nową tablicę, której elementy przechodzą test wykonywany przez funkcję przekazaną jako argument.


Rozważmy następujący kod:
https://gist.github.com/Ginden/696eb2c8e2b7cad4ead1
Jak widać, operuje on na dwóch atrybutach, których pewnie nie zdefiniowaliście w swoich klasach - na `by` i `toRemove`.
Za pomocą `toRemove` zaznaczamy, które elementy chcemy przefiltrować (filtrowanie na bieżąco ma swoje wady, które ujawniają się przy bardziej zaawansowanych optymalizacjach; ich znalezienie zostawiam czytelnikowi jako ćwiczenie).
Jeśli następny element jest tej samej klasy co obecny, to zwiększamy wartość następnego elementu o wartość obecnego elementu.

Potem wystarczy zmienić metodę `toCode` na uwzględniającą wartość parametru `by` w zwracanym stringu i gotowe!

Jako dalszą optymalizację można wykorzystać tworzenie klas `Move` i `ChangeCellValue` zamiast `MoveRight`, `MoveLeft`, `Increment`, `Decrement`.

Pytanie testowe:
- co znaczy kod Brainfucka `[-]` i jak można go łatwo zoptymalizować?
#programowanie