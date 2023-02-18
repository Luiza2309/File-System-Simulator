// GIUGLAN Luiza-Viorica 311CB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct _Director {
	char* nume;
	struct _Director* parinte;
	struct _Fisier* fisier;
	struct _Director* directories;
	struct _Director* st;
	struct _Director* dr;
} Director;

typedef struct _Fisier {
	char* nume;
	struct _Director* parinte;
	struct _Fisier* st;
	struct _Fisier* dr;
} Fisier;

void freeF(Fisier **a) {
    if(!(*a)) return;
    freeF(&(*a)->dr);
    freeF(&(*a)->st);
    free((*a)->nume);
    free(*a);
}

void freeD(Director **a) {
    if(!(*a)) return;
    freeD(&(*a)->directories);
    freeF(&(*a)->fisier);
    freeD(&(*a)->dr);
    freeD(&(*a)->st);
    free((*a)->nume);
    free(*a);
}

Director* CreareArbore() {
    Director* root = calloc(1, sizeof(struct _Director));
    // initializeaza arborele cu un director root
    if(!root) return NULL;
    root->nume = calloc(5, sizeof(char));
    strcpy(root->nume, "root");
    root->parinte = NULL;
    root->fisier = NULL;
    root->directories = NULL;
    root->st = NULL;
    root->dr = NULL;
    return root;
}

int find_director(Director* a, char* nume, int* ok) {
    if(!a) return 0;
	find_director(a->st, nume, ok);
	find_director(a->dr, nume, ok);
	if(strcmp(a->nume, nume) == 0) (*ok) = 1;
}

int find_fisier(Fisier* a, char* nume, int* ok) {
    if(!a) return 0;
	find_fisier(a->st, nume, ok);
	find_fisier(a->dr, nume, ok);
	if(strcmp(a->nume, nume) == 0) *ok = 1;
}

void touch(Director* a, char* nume) {
    Fisier* aux;
    Fisier* p;
    Fisier* n;
    int ok = 0;
    find_director(a->directories, nume, &ok);
    // verifica daca exista deja un director cu numele dat
    if(!ok) {
        if(a->fisier == NULL)  // daca arborele de fisiere e gol
        {
            a->fisier = calloc(1, sizeof(struct _Fisier));
            if(!a->fisier) return;
            a->fisier->nume = calloc(strlen(nume) + 1, sizeof(char));
            strcpy(a->fisier->nume, nume);
            a->fisier->dr = a->fisier->st = NULL;
            a->fisier->parinte = a;
            // seteaza parintele fisierului directorul curent
            return;
        }

        n = a->fisier;
        // parcurge arborele de fisiere pana cand gaseste
        // locul in care trebuie adaugat noul fisier
        while(n)
        {
            p = n;
            if(strcmp(nume, n->nume) == 0) {
                printf("File %s already exists!\n", nume);
                return;
            }
            if(strcmp(nume, n->nume) < 0) n = n->st;
            else n = n->dr;
        }

        aux = calloc(1, sizeof(struct _Fisier));
        if(!aux) return;
        aux->nume = calloc(strlen(nume) + 1, sizeof(char));
        if(!aux->nume) return;
        strcpy(aux->nume, nume);
        aux->st = aux->dr = NULL;
        aux->parinte = a;
        if(strcmp(nume, p->nume) < 0) p->st = aux;
        else p->dr = aux;
        // face ca fisierul precedent sa pointeze la cel nou adaugat
    } else {
        printf("Directory %s already exists!\n", nume);
    }
}

void mkdir(Director* a, char* nume) {
    Director* aux;
    Director* p;
    Director* n;
    int ok = 0;
    find_fisier(a->fisier, nume, &ok);
    // verifica daca exista deja un fisier cu numele dat
    if(!ok) {
        if(a->directories == NULL)  // daca arborele de directoare e gol
        {	
            a->directories = calloc(1, sizeof(struct _Director));
            if(!a->directories) return;
            a->directories->nume = calloc(strlen(nume) + 1, sizeof(char));
            strcpy(a->directories->nume, nume);
            a->directories->dr = a->directories->st = NULL;
            a->directories->parinte = a;
            return;
        }

        n = a->directories;
        // parcurge arborele de directoare pana cand gaseste
        // locul in care trebuie adaugat noul director
        while(n)
        {
            p = n;
            if(strcmp(nume, n->nume) == 0) {
                printf("Directory %s already exists!\n", nume);
                return;
            }
            if(strcmp(nume, n->nume) < 0) n = n->st;
            else n = n->dr;
        }

        aux = calloc(1, sizeof(struct _Director));
        if(!aux) return;
        aux->nume = calloc(strlen(nume) + 1, sizeof(char));
        if(!aux->nume) return;
        strcpy(aux->nume, nume);
        aux->st = aux->dr = NULL;
        aux->parinte = a;
        if(strcmp(nume, p->nume) < 0) p->st = aux;
        else p->dr = aux;
        // face ca directorul precedent sa pointeze la cel nou adaugat
    } else {
        printf("File %s already exists!\n", nume);
    }
}

void SRD_director(Director* a) {
	if(!a) return;
	if(!a->st && !a->dr) { printf("%s ", a->nume); return; }
	SRD_director(a->st);
	printf("%s ", a->nume);
	SRD_director(a->dr);
}

void SRD_fisier(Fisier* a) {
	if(!a) return;
	if(!a->st && !a->dr) { printf("%s ", a->nume); return; }
	SRD_fisier(a->st);
	printf("%s ", a->nume);
	SRD_fisier(a->dr);
}

void ls(Director* a) {
    SRD_director(a->directories);  // afiseaza ierarhia de directoare
    SRD_fisier(a->fisier);  // afiseaza ierarhia de fisiere
    printf("\n");
}

Director* cd(Director* a, char* nume) {
    if(strcmp(nume, "..") == 0) {
        if(a->parinte != NULL)
            return a->parinte;  // intoarce parintele
        return a;  // intoarce root
    }

    // verifica daca exista directorul
    int ok = 0;
    find_director(a->directories, nume, &ok);
    if(!ok) {
        printf("Directory not found!\n");
        return a;
    }
    else {  // daca exista directorul intra in el
        Director* aux = a->directories;
        while(aux) {
            if(strcmp(nume, aux->nume) == 0) return aux;
            if(strcmp(nume, aux->nume) < 0) aux = aux->st;
            else aux = aux->dr;
        }
    }
}

void pwd(Director* a) {
    if(a->parinte == NULL) {
        printf("/%s", a->nume);
        return;
    }
    pwd(a->parinte);  // merge din parinte in parinte pana la root
    printf("/%s", a->nume);  // printeaza directorul
}

Fisier* minim(Fisier* a) {
    // minimul dintre fisiere
    Fisier* n = a;
    while(n->st != NULL) n = n->st;
    return n;
}

void rm(Fisier* a, char* nume) {
    Fisier* aux = a;
    Fisier* precedent = aux;

    // verifica daca exista fisierul
    int ok = 0;
    find_fisier(a, nume, &ok);
    if(!ok) { printf("File %s doesn't exist!\n", nume); return; }
    if(!a) return;
    while(aux) {
        if(strcmp(nume, aux->nume) == 0)  // daca a gasit fisierul dorit
        {
            if(aux->st == NULL && aux->dr == NULL) {  // daca e frunza
                if(precedent == aux) {  // daca e radacina ierarhiei de fisiere
                    a->parinte->fisier = NULL;  // se face null ierarhia
                    precedent = NULL;
                } else {
                    if(precedent->dr) {
                        if(strcmp(precedent->dr->nume, nume) == 0) {
                            precedent->dr = NULL;
                            // sterge legatura catre fisier 
                        } else precedent->st = NULL;
                    } else {
                        if(precedent->st) {
                            if(strcmp(precedent->st->nume, nume) == 0) precedent->st = NULL;
                            else precedent->dr = NULL;
                        }
                    }
                }
                
                // sterge fisierul
                free(aux->nume);
                free(aux);
                aux = NULL;
                return;
            }
            if(aux->st == NULL) {  // daca stanga fisierului de sters e nula
                // se muta arborele din dreapta in locul fisierului
                Fisier* f = aux->dr;
                if(precedent == aux) {  // daca e radacina arborelui de fisiere
                    a->parinte->fisier = f;  // se schimba radacina arborelui
                    precedent = f;
                } else {
                    if(precedent->dr) {
                        if(strcmp(precedent->dr->nume, nume) == 0) {
                            precedent->dr = f;
                            // sterge legatura catre fisier
                        } else precedent->st = f;
                    } else {
                        if(precedent->st) {
                            if(strcmp(precedent->st->nume, nume) == 0) {
                                precedent->st = f;
                            } else precedent->dr = f;
                        }
                    }
                }

                // sterge fisierul
                free(aux->nume);
                free(aux);
                aux = NULL;
                return;
            }
            if(aux->dr == NULL) {  // daca dreapta fisierului de sters e nula
                Fisier* f = aux->st;
                if(precedent == aux) {  // daca e radacina arborelui de fisiere
                    a->parinte->fisier = f;  // se schimba radacina arborelui
                    precedent = f;
                } else {
                    if(precedent->dr) {
                        if(strcmp(precedent->dr->nume, nume) == 0) {
                            precedent->dr = f;
                            // sterge legatura catre fisier
                        } else precedent->st = f;
                    } else {
                        if(precedent->st) {
                            if(strcmp(precedent->st->nume, nume) == 0) {
                                precedent->st = f;
                            } else precedent->dr = f;
                        }
                    }
                }

                // sterge fisierul
                free(aux->nume);
                free(aux);
                aux = NULL;
                return;
            }

            // calculeaza minimul din dreapta fisierului de stres
            Fisier* min = minim(aux->dr);
            // schimba numele fisierului de sters cu cel al minimului
            strcpy(aux->nume, min->nume);
            // reapeleaza functia pana cand fisierul ajunge frunza si il sterge
            rm(aux->dr, min->nume);
            return;
        }
        if(strcmp(nume, aux->nume) < 0) {
            precedent = aux;  // precedentul ramane pe loc
            aux = aux->st;
            // fisierul cu care parcurg se duce in stanga sau dreapta
        } else {
            precedent = aux;
            aux = aux->dr;
        }
    }
}

Director* minim2(Director* a) {
    // minimul dintre directoare
    Director* n = a;
    while(n->st != NULL) n = n->st;
    return n;
}

void rmdir(Director* a, Director* precedent, char* nume) {
    Director* aux = a;

    // verifica daca exista directorul
    int ok = 0;
    find_director(a, nume, &ok);
    if(!ok) {
        printf("Directory %s doesn't exist!\n", nume);
        return;
    }
    if(!a) return;
    while(aux) {
        if(strcmp(nume, aux->nume) == 0)  // daca a gasit directorul
        {
            if(aux->st == NULL && aux->dr == NULL) {  // daca e frunza
                if(aux == aux->parinte->directories) {
                    a->parinte->directories = NULL;
                    // ierarhia de directoare devine nula
                } else {
                    if(precedent->st) {
                        if(strcmp(precedent->st->nume, aux->nume) == 0) {
                            precedent->st = NULL;
                        } else precedent->dr = NULL;
                    }
                    else {
                        if(precedent->dr) {
                            if(strcmp(precedent->dr->nume, aux->nume) == 0) {
                                precedent->dr = NULL;
                            } else precedent->st = NULL;
                        }
                    }
                }

                // sterge directorul cu tot continutul lui
                freeD(&aux->directories);
                freeF(&aux->fisier);
                free(aux->nume);
                free(aux);
                aux = NULL;
                return;
            }
            if(aux->st == NULL) {
                Director* f = aux->dr;
                if(aux->parinte->directories == aux) {
                    // daca e radacina ierarhiei de directoare
                    a->parinte->directories = f;
                    precedent = f;
                } else {
                    if(precedent->st) {
                        if(strcmp(precedent->st->nume, aux->nume) == 0) {
                            precedent->st = f;
                        } else precedent->dr = f;
                    }
                    else {
                        if(precedent->dr) {
                            if(strcmp(precedent->dr->nume, aux->nume) == 0) {
                                precedent->dr = f;
                            } else precedent->st = f;
                        }
                    }
                }

                // sterge directorul cu tot continutul lui
                freeD(&aux->directories);
                freeF(&aux->fisier);
                free(aux->nume);
                free(aux);
                aux = NULL;
                return;
            }
            if(aux->dr == NULL) {
                Director* f = aux->st;
                if(aux->parinte->directories == aux) {
                    // daca e radacina ierarhiei de directoare
                    a->parinte->directories = f;
                    precedent = f;
                } else {
                    if(precedent->st) {
                        if(strcmp(precedent->st->nume, aux->nume) == 0) {
                            precedent->st = f;
                        } else precedent->dr = f;
                    }
                    else {
                        if(precedent->dr) {
                            if(strcmp(precedent->dr->nume, aux->nume) == 0) {
                                precedent->dr = f;
                            } else precedent->st = f;
                        }
                    }
                }

                // sterge directorul cu tot continutul lui
                freeD(&aux->directories);
                freeF(&aux->fisier);
                free(aux->nume);
                free(aux);
                aux = NULL;
                return;
            }

            // calculeaza minimul din partea dreapta a directorului de sters
            Director* min = minim2(aux->dr);
            // directorul de sters ia numele minimului
            strcpy(aux->nume, min->nume);
            // se repeta pana cand fisierul de sters devine frunza
            rmdir(aux->dr, aux, min->nume);
            return;
        }
        if(strcmp(nume, aux->nume) < 0) {
            precedent = aux;  // precedentul ramane pe loc
            aux = aux->st;
            // fisierul cu care parcurg se duce in stanga sau in dreapta
        } else {
            precedent = aux;
            aux = aux->dr;
        }
    }
}

void findD(Director* a, char* nume, int* okay) {
    if(!a) return;

    // cauta daca exista directorul
    int ok = 0;
    find_director(a, nume, &ok);
    if(ok) {  // daca exista se printeaza calea
        printf("Directory %s found!\n", nume);
        pwd(a->parinte);
        printf("/%s\n", nume);
        *okay = 1;
        return;
    }
    findD(a->st, nume, okay);  // se cauta in stanga
    findD(a->dr, nume, okay);  // se cauta in dreapta
    findD(a->directories, nume, okay);  // se cauta in toate directoarele
}

void findF(Director* a, char* nume, int* okay) {
    if(!a) return;

    // cauta daca exista fisierul
    int ok = 0;
    find_fisier(a->fisier, nume, &ok);
    if(ok) {  // daca exista se printeaza calea
        printf("File %s found!\n", nume);
        pwd(a);
        printf("\n");
        *okay = 1;
        return;
    }
    findF(a->st, nume, okay);  // se cauta la stanga
    findF(a->dr, nume, okay);  // se cauta la dreapta
    findF(a->directories, nume, okay);  // se cauta in toate directoarele
}

void go_root(Director* a) {
    while(a->parinte != NULL) a = a->parinte;
}

int main() {
    // CITIREA
    char *linie = calloc(1000, sizeof(char));
    char *cerinta;

    Director* a = CreareArbore();
    Director* root = a;    
    while (fgets(linie, 1000, stdin))
    {
        linie[strcspn(linie, "\r")] = 0;
        linie[strcspn(linie, "\n")] = 0;
        cerinta = strtok(linie, " ");
        if (strcmp(cerinta, "touch") == 0)
        {
            cerinta = strtok(NULL, " ");
            touch(a, cerinta);
        }
        if (strcmp(cerinta, "mkdir") == 0)
        {
            cerinta = strtok(NULL, " ");
            mkdir(a, cerinta);
        }
        if (strcmp(cerinta, "ls") == 0)
        {
            ls(a);
        }
        if (strcmp(cerinta, "rm") == 0)
        {
            cerinta = strtok(NULL, " ");
            rm(a->fisier, cerinta);
        }
        if (strcmp(cerinta, "rmdir") == 0)
        {
            cerinta = strtok(NULL, " ");
            rmdir(a->directories, a->directories, cerinta);
        }
        if (strcmp(cerinta, "cd") == 0)
        {
            cerinta = strtok(NULL, " ");
            a = cd(a, cerinta);
        }
        if (strcmp(cerinta, "pwd") == 0)
        {
            pwd(a);
            printf("\n");
        }
        if (strcmp(cerinta, "find") == 0)
        {
            cerinta = strtok(NULL, " -");
            char tip = *cerinta;
            cerinta = strtok(NULL, " ");
            int okay;
            if(tip == 'f') {
                okay = 0;
                findF(root, cerinta, &okay);
                if(!okay) printf("File %s not found!\n", cerinta);
            }
            else {
                okay = 0;
                findD(root, cerinta, &okay);
                if(!okay) printf("Directory %s not found!\n", cerinta);
            }
        }
        if(strcmp(cerinta, "quit") == 0) break;
    }

    // DEZALOCARE
    freeD(&a->directories);
    freeF(&a->fisier);
    free(a->nume);
    free(a);
    free(linie);
}