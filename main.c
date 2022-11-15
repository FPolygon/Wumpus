
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int pit1, //Holds location for pit 1
pit2, //Holds location for pit 2
wumpus, //Holds location for the Wumpus
person, //Holds location for the player
bat1, //Holds location for bat 1
bat2, //Holds location for bat 2
arrow, //Holds location for the arrow, -1 if arrow is with player
status, //Holds status of the game (0 game is running, 1 the game is finished)
wasLastMoveS; //Exception for turn counter if the player's last move was shoot
char moveP; //Variable for move input
int t = 1; //Counter for moves at the left of move prompt


void displayCave(void) {
    printf("\n       ______18______             \n"
           "      /      |       \\           \n"
           "     /      _9__      \\          \n"
           "    /      /    \\      \\        \n"
           "   /      /      \\      \\       \n"
           "  17     8        10     19       \n"
           "  | \\   / \\      /  \\   / |    \n"
           "  |  \\ /   \\    /    \\ /  |    \n"
           "  |   7     1---2     11  |       \n"
           "  |   |    /     \\    |   |      \n"
           "  |   6----5     3---12   |       \n"
           "  |   |     \\   /     |   |      \n"
           "  |   \\       4      /    |      \n"
           "  |    \\      |     /     |      \n"
           "  \\     15---14---13     /       \n"
           "   \\   /            \\   /       \n"
           "    \\ /              \\ /        \n"
           "    16---------------20           \n"
           "\n");
} //Map of cave


void displayInstructions(void) {
    printf("Hunt the Wumpus:                                             \n"
           "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
           "room has 3 tunnels leading to other rooms.                   \n"
           "                                                             \n"
           "Hazards:                                                     \n"
           "1. Two rooms have bottomless pits in them.  If you go there you fall "
           "and die.   \n"
           "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
           "Usually he is \n"
           "   asleep. He will wake up if you enter his room. When you move into "
           "the Wumpus'\n"
           "   room, then he wakes and moves if he is in an odd-numbered room, "
           "but stays    \n"
           "   still otherwise.  After that, if he is in your room, he snaps "
           "your neck and  \n"
           "   you die!                                                          "
           "           \n"
           "                                                                     "
           "           \n"
           "Moves:                                                               "
           "           \n"
           "On each move you can do the following, where input can be upper or "
           "lower-case:  \n"
           "1. Move into an adjacent room.  To move enter 'M' followed by a "
           "space and       \n"
           "   then a room number.                                               "
           "           \n"
           "2. Enter 'R' to reset the person and hazard locations, useful for "
           "testing.      \n"
           "3. Enter 'C' to cheat and display current board positions.           "
           "           \n"
           "4. Enter 'D' to display this set of instructions.                    "
           "           \n"
           "5. Enter 'P' to print the maze room layout.                          "
           "           \n"
           "6. Enter 'G' to guess which room Wumpus is in, to win or lose the "
           "game!         \n"
           "7. Enter 'X' to exit the game.                                       "
           "           \n"
           "                                                                     "
           "           \n"
           "Good luck!                                                           "
           "           \n"
           " \n\n");
} //Shows instructions for game


void setRoomConnections( int * **rooms) {
    *rooms = malloc(sizeof(int *) * 21); //Allocate space for 20 room pointers
    for(int i=0; i<21; i++) {
        (*rooms)[i] = malloc(sizeof(int) * 3); // Allocate space for 3 rooms
    }
    (*rooms)[0][0] = 2; (*rooms)[0][1] = 5; (*rooms)[0][2] = 8;            // Room 1
    (*rooms)[1][0] = 1; (*rooms)[1][1] = 3; (*rooms)[1][2] = 10;            // Room 2
    (*rooms)[2][0] = 2; (*rooms)[2][1] = 4; (*rooms)[2][2] = 12;        // Room 3
    (*rooms)[3][0] = 3; (*rooms)[3][1] = 5; (*rooms)[3][2] = 14;        // Room 4
    (*rooms)[4][0] = 1; (*rooms)[4][1] = 4; (*rooms)[4][2] = 6;        // Room 5
    (*rooms)[5][0] = 5; (*rooms)[5][1] = 7; (*rooms)[5][2] = 15;            // Room 6
    (*rooms)[6][0] = 6; (*rooms)[6][1] = 8; (*rooms)[6][2] = 17;        // Room 7
    (*rooms)[7][0] = 1; (*rooms)[7][1] = 7; (*rooms)[7][2] = 9;        // Room 8
    (*rooms)[8][0] = 8; (*rooms)[8][1] = 10; (*rooms)[8][2] = 18;            // Room 9
    (*rooms)[9][0] = 2; (*rooms)[9][1] = 9; (*rooms)[9][2] = 11;        // Room 10
    (*rooms)[10][0] = 10; (*rooms)[10][1] = 12; (*rooms)[10][2] = 19;        // Room 11
    (*rooms)[11][0] = 3; (*rooms)[11][1] = 11; (*rooms)[11][2] = 13;    // Room 12
    (*rooms)[12][0] = 12; (*rooms)[12][1] = 14; (*rooms)[12][2] = 20;    // Room 13
    (*rooms)[13][0] = 4; (*rooms)[13][1] = 13; (*rooms)[13][2] = 15;    // Room 14
    (*rooms)[14][0] = 6; (*rooms)[14][1] = 14; (*rooms)[14][2] = 16;    // Room 15
    (*rooms)[15][0] = 15; (*rooms)[15][1] = 17; (*rooms)[15][2] = 20;    // Room 16
    (*rooms)[16][0] = 7; (*rooms)[16][1] = 16; (*rooms)[16][2] = 18;    // Room 17
    (*rooms)[17][0] = 9; (*rooms)[17][1] = 17; (*rooms)[17][2] = 19;    // Room 18
    (*rooms)[18][0] = 11; (*rooms)[18][1] = 18; (*rooms)[18][2] = 20;    // Room 19
    (*rooms)[19][0] = 13; (*rooms)[19][1] = 16; (*rooms)[19][2] = 19;    // Room 20
    (*rooms)[20][0] = 0; (*rooms)[20][1] = 0; (*rooms)[20][2] = 0;    // Room UNUSED
} // Array of room connections


void exitGame(void) {
    printf("\nExiting Program ...\n");
    exit(0);
} //Exits the game


int randomValue(void) {
    int val = rand() % 20 + 1;
    return val;
} //Random number generator for assigning rooms. Returns the random number between 1 and 10


void setup(void) {
    person = randomValue();
    wumpus = randomValue();
    while (wumpus == person) {
        wumpus = randomValue(); //Sets unique random room for wumpus
    }
    pit1 = randomValue();
    while (pit1 == person || pit1 == wumpus) {
        pit1 = randomValue(); //Sets unique random room for pit 1
    }
    pit2 = randomValue();
    while (pit2 == person || pit2 == wumpus || pit2 == pit1){
        pit2 = randomValue(); //Sets unique random room for pit 2
    }
    bat1 = randomValue();
    while (bat1 == person || bat1 == wumpus || bat1 == pit1 || bat1 == pit2){
        bat1 = randomValue(); //Sets unique random room for bat 1
    }
    bat2 = randomValue();
    while (bat2 == person || bat2 == wumpus || bat2 == pit1 || bat2 == pit2 || bat2 == bat1){
        bat2 = randomValue(); //Sets unique random room for bat 2
    }
    arrow = randomValue();
    while (arrow == person || arrow == wumpus || arrow == pit1 || arrow == pit2 || arrow == bat1 || arrow == bat2){
        arrow = randomValue(); //Sets unique random room for the arrow
    }
    status = 0; // win checker
} //int Sets room assignment and checks for room repeats


void cheating(void) {
    // Message for menu option C (cheating). Note that the printf() statement below always prints
    // 1, 2, 3, 4, 5, 6, 7
    printf( "Cheating! Game elements are in the following rooms: \n"
            "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
            "%4d %5d %6d %5d %5d %5d %5d \n\n",
            person,
            wumpus,
            pit1,
            pit2,
            bat1,
            bat2,
            arrow
    );
} //Prints response to 'C', lists locations of player, wumpus, and pits


void guessing(int guess) {
    if (guess == wumpus) {
        printf("You won!\n");
    } //Win statement

    else {
        printf("You lost.\n");
    } //Lose statement
    exitGame();
} //Function for checking if the players guess is right. Receives the user's guess and prints if the guess is correct or not


int moveCheck(int **rooms, int subject, int moveDst) {
    int temp = 0;
    for (int i = 0; i <= 2; i++) {
        if (rooms[subject-1][i] == moveDst) {
            temp++;
        } //If there is a valid room, the temp goes up indicating the destination is valid
    }
    if (temp > 0) {
        return 1; //Return 1 if destination is valid
    } else {
        return 0; //Return 0 if the destinations is not valid
    }
} //Function to check if the player's move request is valid. Receives the user's desired move and returns a 1 if the move is valid and 0 otherwise


void adjacentTest(int **rooms) {
    if (moveCheck(rooms, person, wumpus) == 1) {
        printf("You smell a stench. ");
    }  //Player is adjacent to wumpus

    if (moveCheck(rooms, person, pit1) == 1 || moveCheck(rooms, person, pit2) == 1) {
        printf("You feel a draft. ");
    } //Player is adjacent to pit
    if (moveCheck(rooms, person, bat1) == 1 || moveCheck(rooms, person, bat2) == 1) {
        printf("You hear rustling of bat wings. ");
    } //Player is adjacent to bat
} //Function to check if adjacent rooms contain a game element and prints corresponding lines


void wumpusCheck(int **rooms) {
    if (person == wumpus){
        if (wumpus % 2 == 0) {
            printf("You briefly feel a slimy tentacled arm as your neck is snapped. \n"
                   "It is over.\n");
            exitGame();
        } //Wumpus stays

        else {
            printf("You hear a slithering sound, as the Wumpus slips away. \n"
                   "Whew, that was close! \n");
            wumpus = rooms[person-1][0];
        } //Wumpus leaves
    }
} //Checks to see if player is with the wumpus


void pitCheck(void) {
    if (person == pit1 || person == pit2) {
        printf("Aaaaaaaaahhhhhh....   \n");
        printf("    You fall into a pit and die. \n");
        exitGame();
    }
} //Checks to see if the player is in a pit room


void batCheck(void) {
    if (person == bat1) {
        person = randomValue();
        int original = bat1;
        while (bat1 == original || bat1 == bat2 || bat1 == person){
            bat1 = randomValue();
        }
        // Message when bats transport player
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", person);
    } // If bat 1 is with the person
    else if(person == bat2){
        person = randomValue();
        int original = bat2;
        while (bat2 == original || bat2 == bat1 || bat2 == person){
            bat2 = randomValue();
        }
        // Message when bats transport player
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", person);
    } // If bat 2 is with the person
}


void arrowCheck(void) {
    if (person == arrow){
        // Player picks up arrow
        printf("Congratulations, you found the arrow and can once again shoot.\n");
        arrow = -1;
    }
} // Checks to see if the arrow is with the player and sets the arrow to -1 if true


void roomCheck(int **rooms) {
    wumpusCheck(rooms);
    pitCheck();
    batCheck();
    arrowCheck();
} // Perform all necessary checks of the room


void shooting(int room) {
    if (room == wumpus){
        printf( "Wumpus has just been pierced by your deadly arrow! \n"
                "Congratulations on your victory, you awesome hunter you.\n");
        exitGame();
    } // Arrow killed Wumpus
    else if (room == person) {
        printf( "You just shot yourself.  \n"
                "Maybe Darwin was right.  You're dead.\n");
        exitGame();
    } // Arrow killed player
} // Prints corresponding text if player shoots and hits an element


void shootingRicochet(int room){
    if (room == wumpus){
        printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                "Accidental victory, but still you win!\n");
        exitGame();
    } // Arrow ricochets, and kills Wumpus
    else if (room == person) {
        printf( "You just shot yourself, and are dying.\n"
                "It didn't take long, you're dead.\n");
        exitGame();
    } // Arrow ricochets, and kills person
} // Prints corresponding text if player shoots and hits an element through ricochet


int main(void) {
    int **rooms;
    setRoomConnections(&rooms);
    srand(1);
    setup();

    while (status != 1) {
        printf("You are in room %d. ", person);
        if (wasLastMoveS != 1) {
            adjacentTest(rooms);
        }
        printf(
                "\n\n%d. Enter your move (or 'D' for directions): ", t); // prompt for user to enter their move

        scanf(" %c", &moveP); //Receives user move

        if (strcmp("D", &moveP) == 0 || strcmp("d", &moveP) == 0) {
            displayCave();
            displayInstructions();
        } // DIRECTIONS

        else if (strcmp("P", &moveP) == 0 || strcmp("p", &moveP) == 0) {
            displayCave();
        } // MAP

        else if (strcmp("C", &moveP) == 0 || strcmp("c", &moveP) == 0) {
            cheating();
        } // CHEAT

        else if (strcmp("G", &moveP) == 0 || strcmp("g", &moveP) == 0) {
            printf("Enter room (1..20) you think Wumpus is in: ");
            int guess;
            scanf("%d", &guess);
            guessing(guess);
        } // GUESS

        else if (strcmp("R", &moveP) == 0 || strcmp("r", &moveP) == 0) {
            printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");

            scanf("%d %d %d %d %d %d %d", &person, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow);
            printf("\n");
        } // RESET

        else if (strcmp("M", &moveP) == 0 || strcmp("m", &moveP) == 0) {
            int moveRoom;
            scanf("%d", &moveRoom);
            if (moveCheck(rooms, person, moveRoom) == 1) {
                person = moveRoom;
                t++; //Increases turn counter
                roomCheck(rooms);
            }
            else {
                printf("Invalid move.  Please retry. \n");
            }
        } // MOVE

        else if (strcmp("S", &moveP) == 0 || strcmp("s", &moveP) == 0) {
            t++;
            if (arrow != -1) {
                printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
            } // Arrow is not with the player
            else {
                printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
                int numOfRooms;
                wasLastMoveS++;
                scanf("%d", &numOfRooms);
                if (numOfRooms > 3){
                    printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
                    numOfRooms = 3;
                } // User enters more than 3 rooms to shoot arrow through
                int* ptr = (int*)malloc(numOfRooms*sizeof(int));
                ptr[0] = person;
                arrow = person;
                for (int i = 0; i < numOfRooms; i++) {
                    scanf("%d", &ptr[i]);
                    if (moveCheck(rooms, arrow, ptr[i]) == 1) {
                        arrow = ptr[i];
                        shooting(arrow);
                    } //Arrow path is valid
                    else {
                        arrow = rooms[arrow-1][0];
                        printf("Room %d is not adjacent.  Arrow ricochets...\n", ptr[i]);
                        shootingRicochet(arrow);
                    } //Arrow ricochets
                } // Checks if each room is adjacent, ricochets if not adjacent
                wumpus = rooms[wumpus-1][0];
                free(ptr);
            } //Sets location of arrow for each room
        } //Shooting arrows
        else if (strcmp("X", &moveP) == 0 || strcmp("x", &moveP) == 0) {
            exitGame();
        } // EXIT
    }
    free(rooms);
}
