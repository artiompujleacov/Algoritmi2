# README

## Problema 1: Numarare

Pentru aceasta problema am folosit sortare topologica si programare dinamica.  
Pentru inceput am sortat topologic primul graf, iar pentru fiecare nod `u` cu 
vecin `v` in graful 1, am verificat daca acesta e vecin in graful 2 cu nodul `v`.
Daca este, se adauga numarul de drumuri in `dp` modulo `1000000007`.  
Complexitatea este `O(n^2 + m)`, `n` fiind numarul de noduri si `m` numarul de 
muchii.

## Problema 2: Trenuri

Am adaugat toate orasele intr-un graf, am folosit o functie recursiva care 
parcurge toti vecinii unui nod si calculeaza lungimea celui mai lung drum care 
merge din acel nod.  
Lungimea celui mai lung drum care începe din nodul curent este lungimea celui 
mai lung drum care incepe dintr-un vecin, plus unul.  
Complexitatea este `O(n)`, `n` fiind numarul de noduri.

## Problema 3: Drumuri

Pentru aceasta problema am folosit algoritmul Dijkstra care calculeaza distanta
minima de la un nod la toate celelalte noduri.  
Am construit doua grafuri, unul de la `u` la `v` si altul de la `v` la `u` 
(inversat).  
Am calculat distantele minime pentru `x` si `y` in graful simplu, si pentru 
`z` in graful inversat.  
Apoi, am cautat nodul `i` pentru care suma distantelor de la `x` la `i`, `y` 
la `i` si `i` la `z` este minima.  
Complexitatea este `O(n + m)`, `n` fiind numarul de noduri si `m` numarul de 
muchii.

## Problema 4: Scandal

Aceasta problema are o rezolvare similara cu 2-SAT problem, la care se aplica 
Kosaraju.  
Am mentionat sursa in fisierul cpp. Am facut un switch pentru care in dependenta 
de `c`, am adaugat muchiile in graf respectand conditiile problemei.  
Am aplicat pasul 1 din Kosaraju cu primul `dfs`, apoi al doilea pas cu `dfs`-ul 
numarul 2.  
Apoi am verificat daca raspunsul e satisfiabil, daca da, l-am adaugat in `result`.  
Complexitatea e `O(n + m)`, `n` fiind numarul de noduri si `m` numarul de muchii.

Artiom Pujleacov 325CB
