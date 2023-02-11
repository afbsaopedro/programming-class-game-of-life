#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int boardX = 35, boardY = 35, simSpeed = 250, boardSet = 1, simSpeedSet = 1, statViewSet = 1, gen = 1;
int genStart = 0, genEnd;
char statView;

int countLiveCells(int board[boardX][boardY]) {
    int counter = 0;
    for (int i = 0; i < boardX; ++i) {
        for (int j = 0; j < boardY; ++j) {
            if (board[i][j] == 1) {
                counter++;
            }
        }
    }
    return counter;
}

void resetInitBoard(int board[boardX][boardY]){
    for (int i = 0; i < boardX; ++i) {
        for (int j = 0; j < boardY; ++j) {
            board[i][j] = 0;
        }
    }
}

void printGameBoard(int board[boardX][boardY]){
    for (int i = 0; i < boardX; ++i) {
        for (int j = 0; j < boardY; ++j) {
            if (board[i][j] == 0) {
                printf(". ");
            } else {
                printf("o ");
            }
        }
        printf("\n");
    }
}

//--------------------------------------------------------------------------------------------------------
// NOT UTILIZED FUNCTIONS / TESTING
// NOTE: was trying not to repeat code or at least optimized it IE instead of using
// so many if's I`d do it like you see here in these functions
int countCellsAround(int gameBoard[boardX][boardY]) {
    for (int i = -1; i < 1; ++i) {
        for (int j = -1; j < 2; ++j) {
            int counter = 0;
            if (gameBoard[i][j] == 1) {
                counter++;
            }
            if (gameBoard[0][0] == 1) {
                counter--;
            }
            return counter;
        }
    }
}

void applyRules(int gameBoard[boardX][boardY], int auxBoard[boardX][boardY], int cellsAround) {
    int counter = countCellsAround(gameBoard);
    for (int i = 0; i < boardX; ++i) {
        for (int j = 0; j < boardY; ++j) {
            if (gameBoard[i][j] == 1 && (counter == 2 || counter == 3)) {
                auxBoard[i][j] = 1;
            } else if (gameBoard[i][j] == 1 && (counter < 2 || counter > 3)) {
                auxBoard[i][j] = 0;
            }
        }
    }
    counter = 0;
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void initGame() {

    int gameBoard[boardX][boardY], auxBoard[boardX][boardY],option, coordX, coordY, cellsAmount, cellAroundCounter = 0,
    currentLiveCells, maxCells = 0, minCells = 0, maxGen, minGen;

    gen = 0;

    resetInitBoard(gameBoard);
    resetInitBoard(auxBoard);

    do {
        system("cls");
        printGameBoard(gameBoard);

        if (statViewSet ==1 ) {
            printf("\nCurrent Generation: %d\n", gen);
            currentLiveCells = countLiveCells(gameBoard);
            printf("Live cells: %d\n", currentLiveCells);
            if (currentLiveCells > maxCells) {
                maxCells = currentLiveCells;
                maxGen = gen;
            }
            if (currentLiveCells < minCells) {
                minCells = currentLiveCells;
                minGen = gen;
            } else if (minCells == 0) {
                minCells = currentLiveCells;
                minGen = gen;
            }
            if (gen == 0) {
                minCells = currentLiveCells;
                maxCells = currentLiveCells;
            }
            printf("Maximum number of cells: %d (Generation: %d)\n", maxCells, maxGen);
            printf("Minimum number of cells: %d (Generation: %d)\n", minCells, minGen);
        }

        printf("\n [1] - Insert one cell              [2] - Insert N cells\n");
        printf(" [3] - Delete one cell              [4] - Delete N cells\n");
        printf(" [5] - Advance one generation       [6] - Advance N generations\n");
        printf(" [7] - Reset                        [8] - Test/Debug\n");
        printf(" [0] - Exit\n");
        printf("\nChoose your option number: ");
        fflush(stdin);
        scanf("%d", &option);
        switch (option) {
            case 0:
                break;
            case 1:
                printf("Enter the cell's coordinates (X, Y): ");
                fflush(stdin);
                scanf("%d, %d", &coordX, &coordY);
                gameBoard[coordX-1][coordY-1] = 1;
                currentLiveCells = countLiveCells(gameBoard);
                break;
            case 2:
                printf("How many cells would you like to enter?: ");
                fflush(stdin);
                scanf("%d", &cellsAmount);
                for (int i = 1; i <= cellsAmount; ++i) {
                    printf("Enter the cell's coordinates (X, Y): ");
                    fflush(stdin);
                    scanf("%d, %d", &coordX, &coordY);
                    gameBoard[coordX-1][coordY-1] = 1;
                }
                currentLiveCells = countLiveCells(gameBoard);
                break;
            case 3:
                printf("Enter the cell's coordinates (X, Y): ");
                fflush(stdin);
                scanf("%d, %d", &coordX, &coordY);
                gameBoard[coordX-1][coordY-1] = 0;
                currentLiveCells = countLiveCells(gameBoard);
                break;
            case 4:
                printf("How many cells would you like to delete?: ");
                fflush(stdin);
                scanf("%d", &cellsAmount);
                for (int i = 1; i <= cellsAmount; ++i) {
                    printf("Enter the cell's coordinates (X, Y): ");
                    fflush(stdin);
                    scanf("%d, %d", &coordX, &coordY);
                    gameBoard[coordX-1][coordY-1] = 0;
                }
                currentLiveCells = countLiveCells(gameBoard);
                break;
            case 5:
                for (int i = 0; i < boardX; ++i) {
                    for (int j = 0; j < boardY; ++j) {
                        int cellsAroundcounter = 0;
                        if (gameBoard[i-1][j-1] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i-1][j] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i-1][j+1] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i][j-1] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i][j+1] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i+1][j-1] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i+1][j] == 1) {
                            cellsAroundcounter++;
                        }
                        if (gameBoard[i+1][j+1] == 1) {
                            cellsAroundcounter++;
                        }
                        // birth law
                        if (gameBoard[i][j] == 0 && cellsAroundcounter == 3) {
                            auxBoard[i][j] = 1;
                        }
                        // survival law
                        if (gameBoard[i][j] == 1 && cellsAroundcounter == 3) {
                            auxBoard[i][j] = 1;
                        }
                        if (gameBoard[i][j] == 1 && cellsAroundcounter == 2) {
                            auxBoard[i][j] = 1;
                        }
                        // death law
                        if (gameBoard[i][j] == 1 && cellsAroundcounter >= 4) {
                            auxBoard[i][j] = 0;
                        }
                        if (gameBoard[i][j] == 1 && cellsAroundcounter < 2) {
                            auxBoard[i][j] = 0;
                        }
                        cellsAroundcounter = 0;
                    }
                }
                for (int i = 0; i < boardX; ++i) {
                    for (int j = 0; j < boardY; ++j) {
                        gameBoard[i][j] = auxBoard[i][j];
                    }
                }
                resetInitBoard(auxBoard);
                genStart = genStart + 1;
                gen = gen + 1;
                system("cls");
                printGameBoard(gameBoard);
                if (statViewSet ==1 ) {
                    printf("\nCurrent Generation: %d\n", gen);
                    currentLiveCells = countLiveCells(gameBoard);
                    printf("Live cells: %d\n", currentLiveCells);
                    if (currentLiveCells > maxCells) {
                        maxCells = currentLiveCells;
                        maxGen = gen;
                    }
                    if (currentLiveCells < minCells) {
                        minCells = currentLiveCells;
                        minGen = gen;
                    } else if (minCells == 0) {
                        minCells = currentLiveCells;
                        minGen = gen;
                    }
                    if (gen == 0) {
                        minCells = currentLiveCells;
                        maxCells = currentLiveCells;
                    }
                    printf("Maximum number of cells: %d (Generation: %d)\n", maxCells, maxGen);
                    printf("Minimum number of cells: %d (Generation: %d)\n", minCells, minGen);
                }
                Sleep(simSpeed);
                break;
            case 6:
                printf("How any generations would you like to advance?: ");
                fflush(stdin);
                scanf("%d", &genEnd);
                do {
                    for (int i = 0; i < boardX; ++i) {
                        for (int j = 0; j < boardY; ++j) {
                            int counter = 0;
                            if (gameBoard[i-1][j-1] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i-1][j] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i-1][j+1] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i][j-1] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i][j+1] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i+1][j-1] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i+1][j] == 1) {
                                counter = counter + 1;
                            }
                            if (gameBoard[i+1][j+1] == 1) {
                                counter = counter + 1;
                            }
                            // birth law
                            if (gameBoard[i][j] == 0 && counter == 3) {
                                auxBoard[i][j] = 1;
                            }
                            // survival law
                            if (gameBoard[i][j] == 1 && counter == 3) {
                                auxBoard[i][j] = 1;
                            }
                            if (gameBoard[i][j] == 1 && counter == 2) {
                                auxBoard[i][j] = 1;
                            }
                            // death law
                            if (gameBoard[i][j] == 1 && counter >= 4) {
                                auxBoard[i][j] = 0;
                            }
                            if (gameBoard[i][j] == 1 && counter < 2) {
                                auxBoard[i][j] = 0;
                            }
                            counter = 0;
                        }
                    }
                    for (int i = 0; i < boardX; ++i) {
                        for (int j = 0; j < boardY; ++j) {
                            gameBoard[i][j] = auxBoard[i][j];
                        }
                    }
                    resetInitBoard(auxBoard);
                    genStart = genStart + 1;
                    gen = gen + 1;
                    system("cls");
                    printGameBoard(gameBoard);
                    if (statViewSet ==1 ) {
                        printf("\nCurrent Generation: %d\n", gen);
                        currentLiveCells = countLiveCells(gameBoard);
                        printf("Live cells: %d\n", currentLiveCells);
                        if (currentLiveCells > maxCells) {
                            maxCells = currentLiveCells;
                            maxGen = gen;
                        }
                        if (currentLiveCells < minCells) {
                            minCells = currentLiveCells;
                            minGen = gen;
                        } else if (minCells == 0) {
                            minCells = currentLiveCells;
                            minGen = gen;
                        }
                        if (gen == 0) {
                            minCells = currentLiveCells;
                            maxCells = currentLiveCells;
                        }
                        printf("Maximum number of cells: %d (Generation: %d)\n", maxCells, maxGen);
                        printf("Minimum number of cells: %d (Generation: %d)\n", minCells, minGen);
                    }
                    Sleep(simSpeed);
                } while (genStart != genEnd);
                genStart = 0;
                break;
            case 7:
                resetInitBoard(gameBoard);
                gen = 0;
                maxCells = 0;
                minCells = 0;
                maxGen = 0;
                minGen = 0;
                break;
            case 8:
                gameBoard[0][0] = 1;
                gameBoard[1][1] = 1;

                gameBoard[2][2] = 1;
                gameBoard[3][3] = 1;
                gameBoard[2][3] = 1;
                gameBoard[3][2] = 1;

                gameBoard[4][4] = 1;
                gameBoard[5][5] = 1;
                gameBoard[4][5] = 1;
                gameBoard[5][4] = 1;

                gameBoard[10][10] = 1;
                gameBoard[10][11] = 1;
                gameBoard[10][12] = 1;

                gameBoard[15][15] = 1;
                gameBoard[16][15] = 1;
                gameBoard[17][15] = 1;

                gameBoard[28][29] = 1;
                gameBoard[29][28] = 1;
                gameBoard[29][29] = 1;
                gameBoard[29][30] = 1;
                gameBoard[30][29] = 1;

                gameBoard[3][30] = 1;
                gameBoard[4][30] = 1;
                gameBoard[3][31] = 1;
                gameBoard[4][31] = 1;

                gameBoard[5][28] = 1;
                gameBoard[6][28] = 1;
                gameBoard[5][29] = 1;
                gameBoard[6][29] = 1;
                break;
            default:
                printf("Invalid Option\n\n");
                system("pause");
                break;
        }
    } while (option != 0);
    system("pause");
}

void settingsMenu() {

    int option;

    do {
        system("cls");
        printf("\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|                 Settings Menu                 |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|                                               |\n");
        printf("|   [1] - Set Board Size                        |\n");
        printf("|   [2] - Set Simulation Speed                  |\n");
        printf("|   [3] - Turn on/off Stat View                 |\n");
        printf("|                                               |\n");
        printf("|   [0] - Main Menu/Go back                     |\n");
        printf("|                                               |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf(" Board Size - X:%d Y:%d\n", boardX, boardY);
        printf(" Simulation Speed - %d milliseconds\n",simSpeed);
        if (statViewSet == 1) {
            printf(" Stat View - On\n");
        } else if (statViewSet == 0){
            printf(" Stat View - Off\n");
        }
        printf("\nChoose your option number: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                //Board Size Setting
                printf("\nSet your Board Size (X, Y): ");
                fflush(stdin);
                scanf("%d, %d", &boardX, &boardY);
                if (boardX >= 10 && boardY >= 10) {
                    boardSet = 1;
                    printf("\nBoard Size is has been set correctly");
                    Sleep(2*1000);
                } else {
                    boardSet = 0;
                    printf("\nBoth X and Y need to be higher than 10\n\n");
                    system("pause");
                }
                break;
            case 2:
                // Simulation Speed Setting
                printf("\nSet your Simulation Speed (milliseconds): ");
                fflush(stdin);
                scanf("%d", &simSpeed);
                if (simSpeed >= 250) {
                    simSpeedSet = 1;
                    printf("\nSimulation Speed is has been set correctly");
                    Sleep(2*1000);
                } else {
                    simSpeedSet = 0;
                    printf("\nSimulation Speed needs to be at least 250 milliseconds\n\n");
                    system("pause");
                }
                break;
            case 3:
                // Stat View Setting
                if (statViewSet == 0) {
                    printf("\nWould you like to turn Stat View on (Y/N)?: ");
                    fflush(stdin);
                    scanf("%c", &statView);
                    if (statView == 'y' || statView == 'Y') {
                        statViewSet = 1;
                        printf("\nStat view has been turned on");
                        Sleep(2*1000);
                    } else if (statView == 'n' || statView == 'N') {
                        statViewSet = 0;
                        printf("\nStat view is off");
                        Sleep(2*1000);
                    } else {
                        printf("\nInvalid Option\n\n");
                        system("pause");
                    }
                } else if (statViewSet == 1) {
                    printf("\nWould you like to turn Stat View off (Y/N)?: ");
                    fflush(stdin);
                    scanf("%c", &statView);
                    if (statView == 'y' || statView == 'Y') {
                        statViewSet = 0;
                        printf("\nStat view as been turned off");
                        Sleep(2*1000);
                    } else if (statView == 'n' || statView == 'N') {
                        printf("\nStat view is on");
                        Sleep(2*1000);
                    } else {
                        printf("\nInvalid Option\n\n");
                        system("pause");
                    }
                } else {
                    printf("\nInvalid Option\n\n");
                    system("pause");
                }
                break;
            default:
                printf("\nInvalid Option\n\n");
                system("pause");
        }

    } while (option != 0);
}

void rulesMenu() {
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|          The Rules of John Conway's Game of Life          |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("| In the Game of Life you have a two-dimensional grid of    |\n");
    printf("| cells where they are either populated or unpopulated and  |\n");
    printf("| every cell interacts with its eight neighbours, which are |\n");
    printf("| the cells that are horizontally, vertically, or diagonally|\n");
    printf("| adjacent. At each step in time, the following transitions |\n");
    printf("| occur:                                                    |\n");
    printf("|                                                           |\n");
    printf("|   1. Any live cell with fewer than two live neighbours    |\n");
    printf("| dies, as if by underpopulation;                           |\n");
    printf("|                                                           |\n");
    printf("|   2. Any live cell with two or three live neighbours      |\n");
    printf("| lives on to the next generation;                          |\n");
    printf("|                                                           |\n");
    printf("|   3. Any live cell with more than three live neighbours   |\n");
    printf("| dies, as if by overpopulation;                            |\n");
    printf("|                                                           |\n");
    printf("|   4. Any dead cell with exactly three live neighbours     |\n");
    printf("| becomes a live cell, as if by reproduction                |\n");
    printf("|                                                           |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    system("pause");
}

void patternLibraryMenu() {
    printf("//TO DO\n\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|                Pattern Library                |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|                                               |\n");
    printf("| Still Lifes                                   |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|                                               |\n");
    printf("| Oscillators                                   |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|                                               |\n");
    printf("| Spaceships                                    |\n");
    printf("|                                               |\n");
    printf("|                                               |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("WARNING: This is not an extensive list as more patterns exist\n\n");
    system("pause");
}

void startGameMenu() {

    int option;

    do {
        system("cls");
        printf("\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|                  Start Menu                   |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|                                               |\n");
        printf("|   [1] - Start Game                            |\n");
        printf("|                                               |\n");
        printf("|   [0] - Main Menu                             |\n");
        printf("|                                               |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("\n Current Settings:\n");
        printf(" * Board Size - X:%d Y:%d\n", boardX, boardY);
        printf(" * Simulation Speed - %d ms\n",simSpeed);
        if (statViewSet == 1) {
            printf(" * Stat View - On\n");
        } else if (statViewSet == 0) {
            printf(" * Stat View - Off\n");
        }
        printf("\n [2] - Change current settings");
        printf("\n [3] - Check Settings\n");

        printf("\nChoose your option number: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                if (boardSet == 1 && simSpeedSet == 1) {
                    system("cls");
                    initGame();
                } else {
                    printf("\nWARNING: Check your settings\n\n");
                    system("pause");
                }
                break;
            case 2:
                system("cls");
                settingsMenu();
                break;
            case 3:
                if (boardX < 10 || boardY < 10) {
                    printf("\nBoth X and Y need to be higher than 10\n");
                } else if (boardX >= 10 && boardY >= 10) {
                    printf("\nBoard Size is set correctly\n");
                }
                if (simSpeed < 250) {
                    printf("Simulation Speed needs to be at least 250 milliseconds\n\n");
                } else {
                    printf("Simulation Speed is set correctly\n\n");
                }
                system("pause");
                break;
            default:
                printf("\nInvalid Option\n\n");
                system("pause");
        }

    } while (option != 0);

}

void mainMenu() {

    int option;

    do {
        system("cls");
        printf("\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|                   Main Menu                   |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|                                               |\n");
        printf("|   [1] - Start Menu                            |\n");
        printf("|   [2] - Settings                              |\n");
        printf("|   [3] - Rules                                 |\n");
        printf("|   [4] - Pattern Library                       |\n");
        printf("|                                               |\n");
        printf("|   [0] - Quit Game                             |\n");
        printf("|                                               |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("\nChoose your option number: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                system("cls");
                startGameMenu();
                break;
            case 2:
                system("cls");
                settingsMenu();
                break;
            case 3:
                system("cls");
                rulesMenu();
                break;
            case 4:
                system("cls");
                patternLibraryMenu();
                break;
            default:
                system("cls");
                printf("Invalid Option\n\n");
                system("pause");
        }

    } while (option != 0);
}

int main() {
    mainMenu();
    return 0;
}
