/*
 * File:   CSC322Proj1.c
 * Author: Marcello395
 * Created on January 31, 2017, 6:06 PM


Hours spent;
2+1+1+4+1+3+1+1+1+2+1+11+8+9

Notes;
Clean features are super cumbersome, should've made an all inclusive Functions

Creature >9 are annoying

Need to learn gdb, nulls were tricky to find

 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Creature Structs w/ properties
typedef struct _Creature {
    int id;
    int cT;
    struct _Room *cL;

} Creature;

//Room Structs with properties
typedef struct _Room {
    int roomState;
    int id;
    struct _Room *n;
    struct _Room *s;
    struct _Room *e;
    struct _Room *w;


//creatures in a room
    struct _Creature* creatureArr[10];
} Room;

//Globals
int respect = 40;
Room * Rooms;
Creature * Creatures;
Creature* PC;

//Prototype Functions
int emptySpace(Room * Neighbor);
int moveCreature(Creature * C, Room * Neighbor);
void addCreature(Creature * C, Room * Neighbor);
void removeCreature(Creature * C, Room * currentRoom);
void cleanRoom(Creature * C);
void dirtyRoom();
void lookRoom();
void creatureRandmove(Creature * C);
void drillHole(Creature * C);

//---------

int emptySpace(Room * Neighbor) {
    int check = 0;
    for (int i = 0; i < 10; i++) {
        if (Neighbor->creatureArr[i] != NULL) {
            check++;
        }
    }
    if (check == 10) {
        return 0;
    }
    return 1;
}

//---------

int moveCreature(Creature * C, Room * Neighbor) {
    if (Neighbor == NULL) {
        printf("No neighbor in that direction \n");
        return 0;
    }
    if (!emptySpace(Neighbor)) {
        printf("No space available \n");
        return 0;
    }
    removeCreature(C, C->cL);
    addCreature(C, Neighbor);

    return 1;
}

//---------

void addCreature(Creature * C, Room * Neighbor) {
    for (int i = 0; i < 10; i++) {
        if (Neighbor->creatureArr[i] == NULL) {
            C->cL = Neighbor;
            Neighbor->creatureArr[i] = C;
            break;
        }
    }
}

//---------

void removeCreature(Creature * C, Room * currentRoom) {
    for (int j = 0; j < 10; j++) {
        if (currentRoom->creatureArr[j] != NULL) {
            if (C->cL->creatureArr[j]->id == C->id) {
                C->cL->creatureArr[j] = NULL;
                C->cL = NULL;
                break;
            }
        }
    }
}

//---------

void cleanRoom(Creature * PC) {
    if (PC->cL->roomState == 2) {
        PC->cL->roomState = 1;
    } else if (PC->cL->roomState == 1) {
        PC->cL->roomState = 0;
    }
}

//---------

void dirtyRoom(Creature * PC) {
    if (PC->cL->roomState == 0) {
        PC->cL->roomState = 1;
    } else if (PC->cL->roomState == 1) {
        PC->cL->roomState = 2;
    }
}

//---------

void lookRoom() {
    printf("You are in room %d, ", PC->cL->id);
    if (PC->cL->roomState == 0) {
        printf("room is clean. \n");
    } else if (PC->cL->roomState == 1) {
        printf("room is half dirty. \n");
    } else if (PC->cL->roomState == 2) {
        printf("room is dirty. \n");
    }

    if (PC->cL->n != NULL) {
        printf("Neighbors room %d to the North \n", PC->cL->n->id);
    }
    if (PC->cL->s != NULL) {
        printf("Neighbors room %d to the South \n", PC->cL->s->id);
    }
    if (PC->cL->e != NULL) {
        printf("Neighbors room %d to the East \n", PC->cL->e->id);
    }
    if (PC->cL->w != NULL) {
        printf("Neighbors room %d to the West \n", PC->cL->w->id);
    }

    printf("Room contains; \n");

    for (int z = 0; z < 10; z++) {

        if (PC->cL->creatureArr[z] != NULL) {

            if (PC->cL->creatureArr[z]->cT == 0) {
                printf("You\n");
            }
            if (PC->cL->creatureArr[z]->cT == 1) {
                printf("Animal %d \n", PC->cL->creatureArr[z]->id);
            }
            if (PC->cL->creatureArr[z]->cT == 2) {
                printf("Human %d \n", PC->cL->creatureArr[z]->id);
            }
        }
    }
}

//---------

void creatureRandmove(Creature * C) {
    int direction = rand() % 4;
    static int checker[4] = {0, 0, 0, 0};

    //--
    if (checker[0] == 1 && checker[1] == 1 && checker [2] == 1 && checker[3] == 1) {
        printf("%d leaves through the roof. \n", C->cL->id);
        drillHole(C);
    }
    else if (direction == 0) {
        if (C->cL->n != NULL) {
            printf("%d left to North room. \n", C->id);
            moveCreature(C, C->cL->n);
            if (C->cT == 1 && C->cL->roomState == 2) {
                cleanRoom(C);
            } else if (C->cT == 2 && C->cL->roomState == 0) {
                dirtyRoom(C);
            }
        } else {
            checker[0] = 1;
            creatureRandmove(C);
        }
    }        //--
    else if (direction == 1) {
        if (C->cL->s != NULL) {
            printf("%d left to South room. \n", C->id);
            moveCreature(C, C->cL->s);
            if (C->cT == 1 && C->cL->roomState == 2) {
                cleanRoom(C);
            } else if (C->cT == 2 && C->cL->roomState == 0) {
                dirtyRoom(C);
            }
        } else {
            checker[1] = 1;
            creatureRandmove(C);
        }
    }        //--
    else if (direction == 2) {
        if (C->cL->e != NULL) {
            printf("%d left to East room. \n", C->id);
            moveCreature(C, C->cL->e);
            if (C->cT == 1 && C->cL->roomState == 2) {
                cleanRoom(C);
            } else if (C->cT == 2 && C->cL->roomState == 0) {
                dirtyRoom(C);
            }
        } else {
            checker[2] = 1;
            creatureRandmove(C);
        }
    }        //--
    else if (direction == 3) {
        if (C->cL->w != NULL) {
            printf("%d left to West room. \n", C->id);
            moveCreature(C, C->cL->w);
            if (C->cT == 1 && C->cL->roomState == 2) {
                cleanRoom(C);
            } else if (C->cT == 2 && C->cL->roomState == 0) {
                dirtyRoom(C);
            }
        } else {
            checker [3] = 1;
            creatureRandmove(C);
        }
    }
}

//---------

void drillHole(Creature * C) {

    if (moveCreature(C, C->cL->n) == 0 && moveCreature(C, C->cL->s) == 0
            && moveCreature(C, C->cL->e) == 0 && moveCreature(C, C->cL->w) == 0) {

        removeCreature(C, C->cL);
    }
}

// Room intialization-----------------------------------------------------------

int main(void) {

    srand(time(NULL));
    int roomNums;
    scanf("%d", &roomNums);

    Room * Rooms = (Room*) malloc(sizeof (Room) * roomNums);

    int north, south, east, west;

    for (int i = 0; i < roomNums; i++) {

        scanf("%d %d %d %d %d \n", &Rooms[i].roomState, &north, &south, &east, &west);

        Rooms[i].id = i;

//--------
        if (north == -1) {
            Rooms[i].n = NULL;
        } else {
            Rooms[i].n = &Rooms[north];
        }
//--------
        if (south == -1) {
            Rooms[i].s = NULL;
        } else {
            Rooms[i].s = &Rooms[south];
        }
//--------
        if (east == -1) {
            Rooms[i].e = NULL;
        } else {
            Rooms[i].e = &Rooms[east];
        }
//--------
        if (west == -1) {
            Rooms[i].w = NULL;
        } else {
            Rooms[i].w = &Rooms[west];
        }
//--------
        for (int k = 0; k < 10; k++) {
            Rooms[i].creatureArr[k] = NULL;
        }
    }

//Creatures---------------------------------------------------------------------
    int creatureCount;

    scanf("%d", &creatureCount);

    Creature * Creatures = (Creature*) malloc(sizeof (Creature) * creatureCount);

    int creatureType, creatureLocation;

    for (int j = 0; j < creatureCount; j++) {

        scanf("%d %d \n", &creatureType, &creatureLocation);

        Creatures[j].id = j;

        Creatures[j].cT = creatureType;
        Creatures[j].cL = &Rooms[creatureLocation];

        if (creatureType == 0) {
            PC = &Creatures[j];
        }
        for (int k = 0; k < 10; k++) {
            if (Rooms[creatureLocation].creatureArr[k] == NULL) {
                Rooms[creatureLocation].creatureArr[k] = &Creatures[j];
                break;
            }
        }
    }

    for (int y = 0; y < roomNums; y++) {
        for (int z = 0; z < 10; z++) {
            if (Rooms[y].creatureArr[z] != NULL) {
            }
        }
    }

//User Input--------------------------------------------------------------------
    char options[16] = "";
    while (strcmp(options, "quit") && respect > 0 && respect <= 80 != 0) {
        scanf("%15s", options);
        printf("\n");

//Clean Command ----------------------------------------------------------------
        if (strcmp(options, "clean") == 0) {
            cleanRoom(PC);
            for (int i = 0; i < 10; i++) {

                if (PC->cL->creatureArr[i] != NULL) {

                    if (PC->cL->creatureArr[i]->cT == 1) {

                        if (PC->cL->roomState == 1) {
                            printf("Animal %d licks your face. \n", PC->cL->creatureArr[i]->id);
                            respect++;
                        }

                        if (PC->cL->roomState == 2) {
                            printf("Animal %d grumbles and wants to leave. \n", PC->cL->creatureArr[i]->id);
                            creatureRandmove(PC->cL->creatureArr[i]);
                            respect--;
                        }
                        else if (PC->cL->roomState == 0) {
                            printf("Animal %d licks your face. \n", PC->cL->creatureArr[i]->id);
                            respect++;
                        }
                    }
                    else if (PC->cL->creatureArr[i]->cT == 2) {
                        if (PC->cL->roomState == 1) {
                            printf("Human %d grumbles. \n", PC->cL->creatureArr[i]->id);
                            respect--;
                        }

                        if (PC->cL->roomState == 0) {
                            printf("Human %d grumbles and wants to leave. \n", PC->cL->creatureArr[i]->id);
                            creatureRandmove(PC->cL->creatureArr[i]);
                            respect--;
                        }
                        else if (PC->cL->roomState == 2) {
                            printf("Human %d cheers. \n", PC->cL->creatureArr[i]->id);
                            respect++;
                        }
                    }
                }
            }
            printf("Respect is now %d \n", respect);
        }
//Dirty Command ----------------------------------------------------------------
        else if (strcmp(options, "dirty") == 0) {
            dirtyRoom(PC);
            for (int i = 0; i < 10; i++) {

                if (PC->cL->creatureArr[i] != NULL) {

                    if (PC->cL->creatureArr[i]->cT == 1) {

                        if (PC->cL->roomState == 1) {
                            printf("Animal %d grumbles. \n", PC->cL->creatureArr[i]->id);
                            respect--;
                        }

                        if (PC->cL->roomState == 2) {
                            printf("Animal %d grumbles and wants to leave. \n", PC->cL->creatureArr[i]->id);
                            creatureRandmove(PC->cL->creatureArr[i]);
                            respect--;
                        }
                        else if (PC->cL->roomState == 0) {
                            printf("Animal %d licks your face. \n", PC->cL->creatureArr[i]->id);
                            respect++;
                        }
                    }
                    else if (PC->cL->creatureArr[i]->cT == 2) {
                        if (PC->cL->roomState == 1) {
                            printf("Human %d cheers. \n", PC->cL->creatureArr[i]->id);
                            respect++;
                        }

                        if (PC->cL->roomState == 0) {
                            printf("Human %d grumbles and wants to leave. \n", PC->cL->creatureArr[i]->id);
                            creatureRandmove(PC->cL->creatureArr[i]);
                            respect--;
                        }
                        else if (PC->cL->roomState == 2) {
                            printf("Human %d cheers. \n", PC->cL->creatureArr[i]->id);
                            respect++;
                        }
                    }
                }
            }
            printf("Respect is now %d \n", respect);
        }
//Look Command -----------------------------------------------------------------
        else if (strcmp(options, "look") == 0) {
            lookRoom();
        }
//Help Command -----------------------------------------------------------------
        else if (strcmp(options, "help") == 0) {
            printf("Available Commands: \n");
            printf("'look' to see current room's state, neighbors, and inhabitants.\n");
            printf("'north', 'south', 'east', 'west' to move in a respective direction.\n");
            printf("'clean' to clean a room or 'dirty' to mess up a room.\n");
            printf("'respect' to see your current respect level.\n");
            printf("'quit' to end the game.");
        }
//Move Commands ----------------------------------------------------------------

//------
        else if (strcmp(options, "north") == 0) {
            moveCreature(PC, PC->cL->n);
        }
//------
        else if (strcmp(options, "south") == 0) {
            moveCreature(PC, PC->cL->s);
        }
//------
        else if (strcmp(options, "east") == 0) {
            moveCreature(PC, PC->cL->e);
        }
//------
        else if (strcmp(options, "west") == 0) {
            moveCreature(PC, PC->cL->w);
        }
//------
        else if (strcmp(options, "respect") == 0) {
            printf("Respect is %d", respect);
        }
//Creature Commands-------------------------------------------------------------

        else {

            //Creature Clean----------------------------------------------------------------
            if (options[2] == 'c') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (int) options[0] - (int) '0' == PC->cL->creatureArr[i]->id)
                        cleanRoom(PC->cL->creatureArr[i]);

                    if (PC->cL->creatureArr[i] != NULL) {

                        if (PC->cL->creatureArr[i]->cT == 1) {

                            if (PC->cL->roomState == 1) {
                                printf("Animal %d licks your face a lot. \n", PC->cL->creatureArr[i]->id);
                                respect -= 3;
                            }

                            if (PC->cL->roomState == 2) {
                                printf("Animal %d grumbles a lot. \n", PC->cL->creatureArr[i]->id);
                                creatureRandmove(PC->cL->creatureArr[i]);
                                respect -= 3;
                            }
                            else if (PC->cL->roomState == 0) {
                                printf("Animal %d licks your face a lot.  \n", PC->cL->creatureArr[i]->id);
                                respect += 3;
                            }
                        }
                        else if (PC->cL->creatureArr[i]->cT == 2) {
                            if (PC->cL->roomState == 1) {
                                printf("Human %d grumbles a lot \n", PC->cL->creatureArr[i]->id);
                                respect -= 3;
                            }

                            if (PC->cL->roomState == 0) {
                                printf("Human %d grumbles a lot and crawls towards a door. \n", PC->cL->creatureArr[i]->id);
                                creatureRandmove(PC->cL->creatureArr[i]);
                                respect -= 3;
                            }
                            else if (PC->cL->roomState == 2) {
                                printf("Human %d cheers a lot! \n", PC->cL->creatureArr[i]->id);
                                respect += 3;
                            }
                        }
                    }
                }
                printf("Respect is now %d \n", respect);
            }
//Creature Dirty ---------------------------------------------------------------
            else if (options[2] == 'd') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (int) options[0] - (int) '0' == PC->cL->creatureArr[i]->id)
                        dirtyRoom(PC->cL->creatureArr[i]);

                    if (PC->cL->creatureArr[i] != NULL) {

                        if (PC->cL->creatureArr[i]->cT == 1) {

                            if (PC->cL->roomState == 1) {
                                printf("Animal %d grumbles a lot \n", PC->cL->creatureArr[i]->id);
                                respect -= 3;
                            }

                            if (PC->cL->roomState == 2) {
                                printf("Animal %d grumbles a lot. \n", PC->cL->creatureArr[i]->id);
                                creatureRandmove(PC->cL->creatureArr[i]);
                                respect -= 3;
                            }
                            else if (PC->cL->roomState == 0) {
                                printf("Animal %d licks your face a lot.  \n", PC->cL->creatureArr[i]->id);
                                respect += 3;
                            }
                        }
                        else if (PC->cL->creatureArr[i]->cT == 2) {
                            if (PC->cL->roomState == 1) {
                                printf("Human %d grumbles a lot. \n", PC->cL->creatureArr[i]->id);
                                respect -= 3;
                            }

                            if (PC->cL->roomState == 0) {
                                printf("Human %d grumbles a lot and crawls towards a door. \n", PC->cL->creatureArr[i]->id);
                                creatureRandmove(PC->cL->creatureArr[i]);
                                respect -= 3;
                            }
                            else if (PC->cL->roomState == 2) {
                                printf("Human %d cheers a lot. \n", PC->cL->creatureArr[i]->id);
                                respect += 3;
                            }
                        }
                    }
                }
                printf("Respect is now %d \n", respect);
            }
//Creature North ---------------------------------------------------------------
            else if (options[2] == 'n') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((int) options[0] - (int) '0') == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->n->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->n);
                    }
                }
            }
//Creature South ---------------------------------------------------------------
            else if (options[2] == 's') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((int) options[0] - (int) '0') == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->s->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->s);
                    }
                }
            }
//Creature East ---------------------------------------------------------------
            else if (options[2] == 'e') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((int) options[0] - (int) '0') == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->e->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->e);
                    }
                }
            }
//Creature West ----------------------------------------------------------------
            else if (options[2] == 'w') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((int) options[0] - (int) '0') == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->w->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->w);
                    }
                }
            }
//Creature >9 North ------------------------------------------------------------
            else if (options[3] == 'n') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((((int) options[0] - (int) '0') * 10) + ((int) options[1] - (int) '0')) == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->n->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->n);
                    }
                }
            }
//Creature >9 South ------------------------------------------------------------
            else if (options[3] == 's') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((((int) options[0] - (int) '0') * 10) + ((int) options[1] - (int) '0')) == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->s->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->s);
                    }
                }
            }
//Creature >9 East -------------------------------------------------------------
            else if (options[3] == 'e') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((((int) options[0] - (int) '0') * 10) + ((int) options[1] - (int) '0')) == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->e->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->e);
                    }
                }
            }
//Creature >9 West -------------------------------------------------------------
            else if (options[3] == 'w') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((((int) options[0] - (int) '0') * 10) + ((int) options[1] - (int) '0')) == PC->cL->creatureArr[i]->id)) {
                        printf("%d moves to room %d \n", PC->cL->creatureArr[i]->id, PC->cL->w->id);
                        moveCreature(PC->cL->creatureArr[i], PC->cL->w);
                    }
                }
            }
//Creature >9 Clean ------------------------------------------------------------
            else if (options[3] == 'c') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((((int) options[0] - (int) '0') * 10) + ((int) options[1] - (int) '0')) == PC->cL->creatureArr[i]->id)) {
                        cleanRoom(PC->cL->creatureArr[i]);

                        if (PC->cL->creatureArr[i] != NULL) {

                            if (PC->cL->creatureArr[i]->cT == 1) {

                                if (PC->cL->roomState == 1) {
                                    printf("Animal %d licks your face a lot. \n", PC->cL->creatureArr[i]->id);
                                    respect -= 3;
                                }

                                if (PC->cL->roomState == 2) {
                                    printf("Animal %d grumbles a lot. \n", PC->cL->creatureArr[i]->id);
                                    creatureRandmove(PC->cL->creatureArr[i]);
                                    respect -= 3;
                                }
                                else if (PC->cL->roomState == 0) {
                                    printf("Animal %d licks your face a lot.  \n", PC->cL->creatureArr[i]->id);
                                    respect += 3;
                                }
                            }
                            else if (PC->cL->creatureArr[i]->cT == 2) {
                                if (PC->cL->roomState == 1) {
                                    printf("Human %d grumbles a lot \n", PC->cL->creatureArr[i]->id);
                                    respect -= 3;
                                }

                                if (PC->cL->roomState == 0) {
                                    printf("Human %d grumbles a lot and crawls towards a door. \n", PC->cL->creatureArr[i]->id);
                                    creatureRandmove(PC->cL->creatureArr[i]);
                                    respect -= 3;
                                }
                                else if (PC->cL->roomState == 2) {
                                    printf("Human %d cheers a lot! \n", PC->cL->creatureArr[i]->id);
                                    respect += 3;
                                }
                            }
                        }
                    }
                    printf("Respect is %d \n", respect);
                }
            }
//Creature >9 Dirty ------------------------------------------------------------

            else if (options[3] == 'd') {
                for (int i = 0; i < 10; i++) {
                    if (PC->cL->creatureArr[i] != NULL && (((((int) options[0] - (int) '0') * 10) + ((int) options[1] - (int) '0')) == PC->cL->creatureArr[i]->id)) {
                        cleanRoom(PC->cL->creatureArr[i]);

                        if (PC->cL->creatureArr[i] != NULL) {

                            if (PC->cL->creatureArr[i]->cT == 1) {

                                if (PC->cL->roomState == 1) {
                                    printf("Animal %d grumbles a lot \n", PC->cL->creatureArr[i]->id);
                                    respect -= 3;
                                }

                                if (PC->cL->roomState == 2) {
                                    printf("Animal %d grumbles a lot. \n", PC->cL->creatureArr[i]->id);
                                    creatureRandmove(PC->cL->creatureArr[i]);
                                    respect -= 3;
                                }
                                else if (PC->cL->roomState == 0) {
                                    printf("Animal %d licks your face a lot.  \n", PC->cL->creatureArr[i]->id);
                                    respect += 3;
                                }
                            }
                            else if (PC->cL->creatureArr[i]->cT == 2) {
                                if (PC->cL->roomState == 1) {
                                    printf("Human %d grumbles a lot. \n", PC->cL->creatureArr[i]->id);
                                    respect -= 3;
                                }

                                if (PC->cL->roomState == 0) {
                                    printf("Human %d grumbles a lot and crawls towards a door. \n", PC->cL->creatureArr[i]->id);
                                    creatureRandmove(PC->cL->creatureArr[i]);
                                    respect -= 3;
                                }
                                else if (PC->cL->roomState == 2) {
                                    printf("Human %d cheers a lot. \n", PC->cL->creatureArr[i]->id);
                                    respect += 3;
                                }
                            }
                        }
                    }
                    printf("Respect is %d \n", respect);
                }
            }
        }
    }

//Win conditions ---------------------------------------------------------------
    if(respect >= 80){
      printf("you win! \n");
    }
    else if(respect <= 0){
      printf("you lose! \n");
    }

//Free memory

    free(Rooms);
    free(Creatures);
}
