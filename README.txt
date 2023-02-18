~ freeF ~
- elibereaza stanga, dreapta, numele fisierului si fisierul recursiv

~ freeD ~
- elibereaza stanga, dreapta, numele directorului si directorul recursiv

~ CreareArbore ~
- initializeaza arborele cu directorul root care are totul NULL

~ find_director ~
- cauta un anumit director in arborele directorului curent
- daca gaseste directorul se schimba valoarea variabilei
    ok pentru a putea fi vazut in afara rezultatul
- daca ok ramane 0 (valoarea lui ok cand este apelata functia)
    atunci directorul n-a fost gasit

~ find_fisier ~
- cauta un anumit fisier in arborele directorului curent
- daca gaseste fisierul se schimba valoarea variabilei
    ok pentru a putea fi vazut in afara rezultatul
- daca ok ramane 0 (valoarea lui ok cand este apelata functia)
    atunci fisierul n-a fost gasit

~ touch ~
- cauta daca exista deja un director cu numele dat in directorul curent
    si se afiseaza un mesaj in acest sens
- daca arborele de fisiere este gol se modifica pointerul
    din director (a->fisier) pentru a pointa la noul fisier
- daca exista deja fisiere in arbore, se parcurge arborele pana cand
    ajunge in locul in care trebuie adaugat fisierul
- se adauga fisierul si se creeaza legaturile in arbore
    (fisierul este la dreapta sau stanga precedentului)

~ mkdir ~
- cauta daca exista deja un fisier cu numele dat in directorul curent
    si se afiseaza un mesaj in acest sens
- daca arborele de directoare este gol se modifica pointerul
    din director (a->directories) pentru a pointa la noul director
- daca exista deja directoare in arbore, se parcurge arborele pana cand
    ajunge in locul in care trebuie adaugat directorul
- se adauga directorul si se creeaza legaturile in arbore
    (directorul este la dreapta sau stanga precedentului)

~ ls ~
- afiseaza ierarhia de directoare
- afiseaza ierarhia de fisiere

~ cd ~
- daca numele dat ca parametru este ".." returneaza parintele directorului, iar
    daca parintele este NULL se returneaza radacina
- se verifica daca directorul exista in ierarhie
- se parcurge ierarhia pana cand se gaseste directorul si il returneaza

~ pwd ~
- merge din parinte in parinte pana la root si se printeaza directorul curent

~ minim ~
- calculeaza minimul dintre fisiere

~ rm ~
- verifica daca fisierul exista
- parcurge ierarhia de fisiere pana cand il gaseste
- daca a gasit fisierul sunt 4 cazuri:
    - daca este frunza:
        - este radacina ierarhiei si se modifica pointerul directorului curent
        - se afla in dreapta/stanga fisierului precedent si se sterge legatura
        - sterge fisierul
    - daca fisierul nu are ramura din stanga
        - se muta arborele din dreapta fisierului in locul sau
        - daca e radacina ierarhiei se modifica pointerul directorului curent
        - este in dreapta/stanga fisierului precedent si se formeaza legatura
            cu arborele din dreapta fisierului de sters
        - se sterge fisierul
    - daca fisierul nu are ramura din dreapta
        - se muta arborele din stanga fisierului in locul sau
        - daca e radacina ierarhiei se modifica pointerul directorului curent
        - este in dreapta/stanga fisierului precedent si se formeaza legatura
            cu arborele din stanga fisierului de sters
        - se sterge fisierul
    - fisierul de sters are si dreapta si stanga
        - se calculeaza minimul din arborele din dreapta
        - se schimba numele fisierului de sters cu numele minimului
        - se apeleaza functia de rm pentru arborele din dreapta si cu numele
            minimului
        - intr-un final elementul de sters va ajunge sa fie frunza
        - astfel se pastreaza proprietatea de arbore binar de cautare

~ minim2 ~
- calculeaza minimul dintre directoare

~ rmdir ~
- verifica daca directorul exista
- parcurge ierarhia de directoare pana cand il gaseste
- daca a gasit directorul sunt 4 cazuri:
    - daca este frunza:
        - este radacina ierarhiei si se modifica pointerul directorului curent
        - se afla in dreapta/stanga directorului precedent si se sterge legatura
        - sterge directorul
    - daca directorul nu are ramura din stanga
        - se muta arborele din dreapta directorului in locul sau
        - daca e radacina ierarhiei se modifica pointerul directorului curent
        - este in dreapta/stanga directorului precedent si se formeaza legatura
            cu arborele din dreapta directorului de sters
        - se sterge directorul
    - daca directorul nu are ramura din dreapta
        - se muta arborele din stanga directorului in locul sau
        - daca e radacina ierarhiei se modifica pointerul directorului curent
        - este in dreapta/stanga directorului precedent si se formeaza legatura
            cu arborele din stanga directorului de sters
        - se sterge directorul
    - directorul de sters are si dreapta si stanga
        - se calculeaza minimul din arborele din dreapta
        - se schimba numele directorului de sters cu numele minimului
        - se apeleaza functia de rm pentru arborele din dreapta si cu numele
            minimului
        - intr-un final elementul de sters va ajunge sa fie frunza
        - astfel se pastreaza proprietatea de arbore binar de cautare

~ findD ~
- cauta daca exista directorul in directorul curent
- daca exista ii printeaza calea
- daca nu exista se cauta in stanga, in dreapta si
    in directoarele directorului curent

~ findF ~
- cauta daca exista fisierul in directorul curent
- daca exista ii printeaza calea
- daca nu exista se cauta in stanga, in dreapta si
    in fisierele directorului curent

~ go_root ~
- se duce din directorul curent in root