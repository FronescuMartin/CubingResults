# CubingResults
Partea 1 proiect POO.
## Tema
Programul gestioneaza date legate de rezultatele mai multor concurenti la competitii de rezolvarea rapida a Cubului Rubik. In cadrul unor astfel de competitii exista 17 probe. La unele probe se fac 5 rezolvari, la altele 3. Pentru fiecare proba se tine cont de 2 tipuri de rezultate, single si average.  
* Single reprezinta cel mai bun timp dintre cei 3 sau 5 la proba respectiva
* Average reprezinta media dintre cei 3 timpi mijlocii (timpul cel mai rapid cat si cel mai lent nu se iau in calcul la aceasta medie) in cadrul probelor cu format de 5 rezolvari, sau media celor 3 timpi pentru probele cu 3 rezolvari.   

De asemenea, este stocat in baza de date daca un anumit rezultat contine un record la single sau la average, tipurile de recorduri fiind:
* NR (National Record)
* CR (Continental Record)
* WR (World Record)

Lista de probe este: 2x2, 3x3, 4x4, 5x5, 6x6, 7x7, Blindfolded, Fewest Moves Challenge, One Handed, Clock, Megaminx, Pyraminx, Skewb, Square-1, 4x4 Blindfolded, 5x5 Blindfolded, 3x3 Multi-Blind.
## Clasele
Programul utilizeaza 5 clase:
1. **Competitor**
2. **Result**
3. **Competition**
4. **Date**
5. **String**

### Competitor
Clasa Competitor este clasa cea mai importanta din acest program. Sunt stocate informatii legate de concurent, cum ar fi numele, varsta etc, dar si toate rezultatele obtinute. Acest lucru se realizeaza printr-un vector (alocat dinamic) de obiecte de tip Result. De asemenea sunt stocate cele mai bune rezultate pentru fiecare proba, in alti 2 vectori de tip Result (unul pentru single, altul pentru average). Obiectele de tip Competitor sunt stocate intr-un vector din main.
### Result
Clasa Result stocheaza timpii din cadrul unei probe, la o competitie. Fiind parte din clasa Competitor, nu are vreo data membru care sa faca referire la concurent. Sunt stocati cei 5 (sau 3) timpi obtinuti, cat si single-ul si average-ul (calculate ca mai sus). De asemenea este stocata printr-un enum si proba la care este obtinut acest rezultat, iar prin alte 2 enum-uri, tipul de record single respectiv average, al acestui rezultat (daca este vreun record), si un pointer catre competitia la care s-a obtinut acest rezultat.
### Competition
Aceasta clasa stocheaza informatii despre o competitie, adica numele acesteia, numarul de concurenti si data la care a avut loc (printr-un obiect de tip Date). Obiectele de tip Competition sunt stocate intr-un vector global, deoarece si obiectele de tip Result din cadrul unui obiect Competitor trebuie sa aiba acces la obiectele de tip Competition, pentru a putea pointa la competitia corespunzatoare rezultatului.
### Date
Tip de date pentru date calendaristice. Stocheaza ziua, data si luna.
### String
Stocheaza siruri de caractere prin alocare dinamica. Este de asemenea posibila utilizarea operatorului de concatenare pe string-uri.

## Functionalitati
* Poate stoca o lista de concurenti, fiecare avand o lista de rezultate (alocata dinamic). Fiecare rezultat este obtinut la o competitie, de aceea este stocata si o lista de competitii, global
* Calculeaza numarul de recorduri obtinute de un concurent
* Calculeaza average-ul si single-ul pentru fiecare rezultat obtinut
* Calculeaza cei mai buni timpi obtinuti de un concurent (atat single cat si average) in cadrul fiecarei probe la care a participat
* Calculeaza timpul mediu al unui concurent la fiecare proba la care a participat
* Meniul interactiv permite adaugarea de obiecte noi de tip Competitor, Result sau Competition, de la tastatura, cat si afisarea acestor obiecte create. Se pot apela si unele metode pe aceste obiecte create din cadrul meniului


