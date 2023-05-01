#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
 typedef struct  { //stats for player
    int health;
    int attack;
    int heal;
    int defend;
}stats;
struct level{ // various levels for players  and posotions
    stats one;
    stats two;
    stats three;
    stats four;
    int x;
    int y;
}player;
typedef struct { //stats for encounters and positions
    int health;
    int attack;
    int heal;
    int slimetime;
    int x;
    int y;
}stat;
struct slime { //various levels for encounters
    stat one;
    stat two;
    stat three;
    stat big;
}slime;
typedef struct{ //positions for items
    int x;
    int y;
}coords;
struct item { //item tracking
   coords weapon;
   coords shield;
   coords potion;
}item;

void movement (int *x, int  *y, int map[9][8], int *slime1posx, int *slime1posy, int *slime2posx, int* slime2posy, int *slime3posx, int *slime3posy, int *bigposx, int *bigposy ,int invent[4], int *weaponposx, int *weaponposy, int *shieldposx, int *shieldposy, int *potionposx, int *potionposy);
void mapprint(int map[9][8]);
void inventory (int invent[4]);
void monstergen(int map[9][8], int *slime1posx, int *slime1posy, int *slime2posx, int *slime2posy, int *slime3posx, int *slime3posy, int *bigposx, int *bigposy);
void chestgen(int map[9][8], int *weaponposx, int *weaponposy, int *shieldposx, int *shieldposy, int *potionposx, int *potionposy);
void slimecombat1(int *playerhealth, int invent[4]);
void slimecombat2(int *playerhealth, int invent[4]);
void slimecombat3(int *playerhealth, int invent[4]);

        int main() {
            //map generation using ascii character values
            int map[9][8] = {70, 108, 97, 116, 108, 97, 110, 100,
                             178, 254, 254, 254, 254, 254, 254, 178,
                             178, 257, 32, 32, 32, 32, 32, 178,
                             178, 32, 32, 32, 286, 32, 32, 178,
                             178, 32, 32, 32, 32, 32, 32, 178,
                             178, 286, 32, 32, 32, 32, 32, 178,
                             178, 32, 32, 32, 32, 32, 286, 178,
                             178, 32, 32, 32, 32, 32, 32, 178,
                             178, 254, 254, 254, 254, 254, 254, 178};
            monstergen(map, &slime.one.x, &slime.one.y, &slime.two.x, &slime.two.y, &slime.three.x, &slime.three.y,
                       &slime.big.x, &slime.big.y);
            chestgen(map, &item.weapon.x, &item.weapon.y, &item.shield.x, &item.shield.y, &item.potion.x, &item.potion.y);

int inventory[4] = {0,0,0,0}; //assigning players inventory as empty
            //map printing and startup
            int i, j;
            printf("\t\tMove with:\n"
                   "\tUp = w/W\n"
                   "\tLeft = a/A\n"
                   "\tRight = d/D\n"
                   "\tDown = s/S\n "
                   "\tYou are:%c\n"
                   "\tWatch out for the slimes: %c & %c\n"
                   "\tThe big slime has extra loot!\n"
                   "\tThe forests:  %c\n "
                   "\tAre too thick for you traverse\n"
                   "\n\n\n\tPress any key to continue.\n ", 257, 167, 79, 286);
            getch();
            mapprint(map);
            //starting positions and stats
            player.one.health = 50;
            int Tcount = 0;
            player.x = 2, player.y = 1;
            int level = 1;

            while (Tcount != 1) {

                movement(&player.x, &player.y, map, &slime.one.x, &slime.one.y, &slime.two.x, &slime.two.y,
                         &slime.three.x, &slime.three.y, &slime.big.x, &slime.big.y, inventory ,&item.weapon.x, &item.weapon.y, &item.shield.x, &item.shield.y, &item.potion.x, &item.potion.y);

                if (map[player.x][player.y] == map[slime.one.x][slime.one.y]) {
                    if (level == 1) {
                        slimecombat1(&player.one.health, inventory);
                    }
                    if (level == 2) {
                        slimecombat2(&player.one.health, inventory);
                    }
                        if (level == 3) {
                            slimecombat3(&player.one.health,inventory);
                        }
                            slime.one.x = 0;
                            slime.one.y = 0;
                        level++;
                    }
                if (map[player.x][player.y] == map[slime.two.x][slime.two.y]) {
                    if (level == 1) {
                        slimecombat1(&player.one.health,inventory);
                    }
                    if (level == 2) {
                        slimecombat2(&player.one.health, inventory);
                    }
                    if (level == 3) {
                        slimecombat3(&player.one.health, inventory);
                    }
                    slime.two.x = 0;
                    slime.two.y = 0;
                    level++;
                }
                if (map[player.x][player.y] == map[slime.three.x][slime.three.y]) {
                    if (level == 1) {
                        slimecombat1(&player.one.health, inventory);
                    }
                    if (level == 2) {
                        slimecombat2(&player.one.health, inventory);
                    }
                    if (level == 3) {
                        slimecombat3(&player.one.health,inventory);
                    }
                    slime.three.x = 0;
                    slime.three.y = 0;
                    level++;
                }
                mapprint(map);
                }
            }




                    void movement(int *x, int *y, int map[9][8], int *slime1posx, int *slime1posy, int *slime2posx,
                                  int *slime2posy, int *slime3posx, int *slime3posy, int *bigposx, int *bigposy, int invent[4], int *weaponposx, int *weaponposy, int *shieldposx, int *shieldposy, int *potionposx, int *potionposy) {
                        char input;
                        input = _getch();
                        if((input == 105 || input == 73)){
                            inventory (invent);
                        }
                         if ((input == 119 || input == 87) && *x > 2) //move up
                        {
                            map[*x][*y] = 32;
                            *x = *x - 1;
                            map[*x][*y] = 257;
                            if (map[*x][*y] == map[5][1] || map[*x][*y] == map[3][4] ||
                                map[*x][*y] == map[6][6]) { //Obstacle
                                printf("\t\tThe forest is far too thick for you to pass\n");
                                map[*x][*y] = 286;
                                *x = *x + 1;
                                map[*x][*y] = 257;
                                mapprint(map);
                            }
                        } else if ((input == 97 || input == 65) && *y > 1) //move left
                        {
                            map[*x][*y] = 32;
                            *y = *y - 1;
                            map[*x][*y] = 257;
                            if (map[*x][*y] == map[5][1] || map[*x][*y] == map[3][4] ||
                                map[*x][*y] == map[6][6]) { //Obstacle
                                printf("\t\tThe forest is far too thick for you to pass\n");
                                map[*x][*y] = 286;
                                *y = *y + 1;
                                map[*x][*y] = 257;
                                mapprint(map);
                            }
                        } else if ((input == 83 || input == 115) && *x < 7) //move down
                        {
                            map[*x][*y] = 32;
                            *x = *x + 1;
                            map[*x][*y] = 257;
                            if (map[*x][*y] == map[5][1] || map[*x][*y] == map[3][4] ||
                                map[*x][*y] == map[6][6]) { //Obstacle
                                printf("\t\tThe forest is far too thick for you to pass\n");
                                map[*x][*y] = 286;
                                *x = *x - 1;
                                map[*x][*y] = 257;
                                mapprint(map);
                            }
                        } else if ((input == 68 || input == 100) && *y < 6) //move right
                        {
                            map[*x][*y] = 32;
                            *y = *y + 1;
                            map[*x][*y] = 257;
                            if (map[*x][*y] == map[5][1] || map[*x][*y] == map[3][4] ||
                                map[*x][*y] == map[6][6]) { //Obstacle
                                printf("\t\tThe forest is far too thick for you to pass\n");
                                map[*x][*y] = 286;
                                *y = *y - 1;
                                map[*x][*y] = 257;
                                mapprint(map);
                            }
                        }
                    }
                    void mapprint(int map[9][8]){
                        int i; int j;
                        system("cls");
                        for (i = 0; i < 9; i++) {
                            printf("\n\t\t");
                            for (j = 0; j < 8; j++) {
                                printf("%c", map[i][j]);
                            }
                        }
        }
                    void monstergen(int map[9][8], int *slime1posx, int *slime1posy, int *slime2posx, int *slime2posy,
                                    int *slime3posx, int *slime3posy, int *bigposx, int *bigposy){ //Monster spawning
                        int slime1 = 167, slime2 = 167, slime3 = 167, bigslime = 79;

                        time_t t;
                        srand((unsigned) time(&t)); //random seed choice
                        int seed;;
                        seed = rand() % 5;

                        //seed data
                        if (seed == 0) {
                            *slime1posx = 6;
                            *slime1posy = 5;
                            *slime2posx = 3;
                            *slime2posy = 3;
                            *slime3posx = 6;
                            *slime3posy = 4;
                            *bigposx = 7;
                            *bigposy = 5;
                            map[*slime1posx][*slime1posy] = slime1;
                            map[*slime2posx][*slime2posy] = slime2;
                            map[*slime3posx][*slime3posy] = slime3;
                            map[*bigposx][*bigposy] = bigslime;
                        } else if (seed == 1) {
                            *slime1posx = 3;
                            *slime1posy = 3;
                            *slime2posx = 2;
                            *slime2posy = 4;
                            *slime3posx = 4;
                            *slime3posy = 4;
                            *bigposx = 4;
                            *bigposy = 5;
                            map[*slime1posx][*slime1posy] = slime1;
                            map[*slime2posx][*slime2posy] = slime2;
                            map[*slime3posx][*slime3posy] = slime3;
                            map[*bigposx][*bigposy] = bigslime;
                        } else if (seed == 2) {
                            *slime1posx = 2;
                            *slime1posy = 4;
                            *slime2posx = 2;
                            *slime2posy = 3;
                            *slime3posx = 3;
                            *slime3posy = 5;
                            *bigposx = 6;
                            *bigposy = 3;
                            map[*slime1posx][*slime1posy] = slime1;
                            map[*slime2posx][*slime2posy] = slime2;
                            map[*slime3posx][*slime3posy] = slime3;
                            map[*bigposx][*bigposy] = bigslime;
                        } else if (seed == 3) {
                            *slime1posx = 3;
                            *slime1posy = 3;
                            *slime2posx = 6;
                            *slime2posy = 3;
                            *slime3posx = 5;
                            *slime3posy = 4;
                            *bigposx = 4;
                            *bigposy = 3;
                            map[*slime1posx][*slime1posy] = slime1;
                            map[*slime2posx][*slime2posy] = slime2;
                            map[*slime3posx][*slime3posy] = slime3;
                            map[*bigposx][*bigposy] = bigslime;
                        } else if (seed == 4) {
                            *slime1posx = 5;
                            *slime1posy = 3;
                            *slime2posx = 5;
                            *slime2posy = 5;
                            *slime3posx = 6;
                            *slime3posy = 6;
                            *bigposx = 3;
                            *bigposy = 3;
                            map[*slime1posx][*slime1posy] = slime1;
                            map[*slime2posx][*slime2posy] = slime2;
                            map[*slime3posx][*slime3posy] = slime3;
                            map[*bigposx][*bigposy] = bigslime;
                        }
                    }
                    void chestgen(int map[9][8], int *weaponposx, int *weaponposy, int *shieldposx, int *shieldposy, int *potionposx, int *potionposy){
                        int seed = rand() % 3;
                        if (seed == 0){
                            *weaponposx = 7;
                        *weaponposy = 1;
                        *shieldposx = 7;
                        *shieldposy = 6;
                        *potionposx = 2;
                        *potionposy = 6;}
                        else if   (seed == 1){
                            *weaponposx = 2;
                            *weaponposy = 6;
                            *shieldposx = 7;
                            *shieldposy = 1;
                            *potionposx = 7;
                            *potionposy = 6;}
                        else if   (seed == 2){
                            *weaponposx = 7;
                            *weaponposy = 6;
                            *shieldposx = 2;
                            *shieldposy = 6;
                            *potionposx = 7;
                            *potionposy = 1;}
                        map[*weaponposx][*weaponposy] = 127;
                        map[*shieldposx][*shieldposy] = 127;
                        map[*potionposx][*potionposy]= 127;
        }
                    void inventory (int invent[4]){
            if (invent[0] == 0 ||invent[1] == 0 || invent[2] == 0 || invent[3] == 0) {
                printf("\n\t\t Inventory is empty.\n");
            }else
                printf("\n\t\tInventory\n");
                if (invent[0] == 1){
                    printf("\t\tFather's Sword - x2 damage!\n");
                }
                else if (invent[1] == 1){
                    printf("\t\tMother's Shield - x2 block!\n");
                }
                else if (invent[2] == 1){
                    printf("\t\tGranny's Tea - x2 healing!\n");
                }
                else if (invent[3] == 1){
                            printf("\t\tKey of Frenchay - Unlocks The Great Chest!\n");
                        }




        }
                    void slimecombat1(int *playerhealth, int invent[4]) {
                        slime.one.health = 50;
                        player.one.heal = 10;
                        printf("\n\t\tThe slime attacks! It screeches at you!\n");
                        while (slime.one.health > 0) { ;
                            printf("__________________________________________________________________________________________________________\n");
                            printf("\t\tTHE SMALL SLIME HAS %dhp/50hp \tYOUR HEALTH IS %dhp/50hp\n\n\n\n"
                                   "\t\tYou ready your sword and shield. What would you like to do?\n\n"
                                   "\t\tPlease enter the appropriate letter:\n", slime.one.health, *playerhealth);
                            if (invent[0] == 1){
                                printf("\t\ta) Strike 10(20) - 20(40)(dmg)\n");}
                            else printf("\t\ta) Strike 10 - 20(dmg)\n");
                            if (invent[1] == 1){
                                printf("\t\tb) Defend with your shield 5(10) - 10(20)(blck)\n");}
                            else printf ("\t\tb) Defend with your shield 5 - 10(blck)\n");
                            if (invent[2] == 1){
                                printf("\t\tc) Drink from your potion healing 10(20)(hlth)\n");}
                            else printf ("\t\tc) Drink from your potion healing 10(hlth)\n\n");
                            slime.one.attack = rand() % 13 + 4;
                            slime.one.heal = rand() % 7 + 2;
                            slime.one.slimetime = 5 ;
                            if (invent[2] == 1){
                                player.one.heal = player.one.heal * 2;
                            }
                            player.one.attack = rand() % 11 + 10;
                            if (invent[0] == 1){
                                player.one.attack = player.one.attack * 2;
                            }
                            player.one.defend = rand() % 6 + 5;
                            if (invent[1] == 1){
                                player.one.defend = player.one.defend * 2;
                            }
                            char input;
                            int block = 0;
                            int slimetime = 0;
                            //Player Input
                            input = getch();
                            printf("__________________________________________________________________________________________________________\n");
                            if (input == 65 || input == 97) {
                                printf("\t\tYou lunge forward and slash!\n\t\tDealing %d(dmg)!\n\n", player.one.attack);
                                slime.one.health = slime.one.health - (player.one.attack - slimetime);
                            } else if (input == 66 || input == 98) {
                                printf("\t\tYou raise your shield preparing to defend\n\t\tBlocking %d(blck)!\n\n",
                                       player.one.defend);
                                block = block + player.one.defend;
                            } else if (input == 67 || input == 99) {
                                printf("\t\tYou take a big gulp of your potion!\n\t\tHealing %d(hlth)!\n\n",
                                       player.one.heal);
                                player.one.health = *playerhealth + player.one.heal;
                            } else
                                printf("\t\tNot a valid entry! The slime takes the opportunity to punish that mistake!\n\n");
                            printf("\t\tPress any key to continue\n");
                            printf("__________________________________________________________________________________________________________\n");
                            getch();
                            //Slime Input
                            if (slimetime > 0) {
                                slimetime = slimetime - 1;
                                printf("\t\tThe slimey ooze lowering your damage is reduced.\n \t\tYour damage is now reduced by %d\n"), slimetime;
                            }
                            int action;
                            action = rand() % 3;
                            if (action == 0) {
                                printf("\t\tThe slime throws itself into you!\n \t\tDealing %d(dmg)!\n\n",
                                       slime.one.attack);
                                if (block > 0)
                                    printf("\t\tYou block! Preventing %d(blck)!\n", block);
                                slime.one.attack = slime.one.attack - block;
                                printf("\t\tYou take %d(dmg) instead!\n", slime.one.attack);
                               if(slime.one.attack < 0){
                                   slime.one.attack = 0;}

                                player.one.health = *playerhealth - slime.one.attack;
                            } else if (action == 1) {
                                printf("\t\tThe slime spits a horrible sticky attack covering you head to toe!\n \t\tReducing your attack by %d!\n\n",
                                       slime.one.slimetime);
                                slimetime = slime.one.slimetime + slimetime;
                            } else if (action == 2) {
                                printf("\t\tThe slime seems to be squeezing itself!\n \t\tHealing %d(hlth)!\n\n",
                                       slime.one.heal);
                                slime.one.health = slime.one.health + slime.one.heal;
                            }
                            if (*playerhealth <= 0){
                                printf("\n\n\n\t\tYou died.... Try again!");
                                getch();
                            exit(0);}
                            printf("\t\tPress any key to continue\n");
                            printf("__________________________________________________________________________________________________________\n");
                            getch();
                        }
                        printf("\n\n\t\tThe slime dissolves away into the ground below!\n"
                               "\t\t You Level up! Congratulations! You combat options have gotten better but so have your enemies...\n\n");
                        printf("\t\tPress any key to continue\n");
                        printf("__________________________________________________________________________________________________________\n");
                    }
                    void slimecombat2(int *playerhealth, int invent[4]) {
                        slime.two.health = 100;
                        *playerhealth = *playerhealth + 25;
                        player.two.heal = 15;
                        printf("\n\t\tThe slime attacks! It screeches at you!\n");
                        while (slime.two.health > 0) { ;
                            printf("__________________________________________________________________________________________________________\n");
                            printf("\t\tTHE SMALL SLIME HAS %dhp/100hp \tYOUR HEALTH IS %dhp/75hp\n\n\n\n"
                                   "\t\tYou ready your sword and shield. What would you like to do?\n\n"
                                   "\t\tPlease enter the appropriate letter:\n", slime.two.health, *playerhealth);
                            if (invent[0] == 1) {
                                printf("\t\ta) Strike 15(30) - 40(80)(dmg)\n");
                            } else printf("\t\ta) Strike 15 - 40(dmg)\n");
                            if (invent[1] == 1) {
                                printf("\t\tb) Defend with your shield 10(20) - 20(40)(blck)\n");
                            } else printf("\t\tb) Defend with your shield 10 - 20(blck)\n");
                            if (invent[2] == 1) {
                                printf("\t\tc) Drink from your potion healing 15(30)(hlth)\n");
                            } else printf("\t\tc) Drink from your potion healing 15(hlth)\n\n");
                            slime.two.attack = rand() % 31 + 10;
                            slime.two.heal = rand() % 15 + 6;
                            slime.two.slimetime = 10 ;
                            if (invent[2] == 1){
                                player.two.heal = player.two.heal * 2;
                            }
                            player.two.attack = rand() % 11 + 10;
                            if (invent[0] == 1){
                                player.two.attack = player.two.attack * 2;
                            }
                            player.two.defend = rand() % 11 + 10;
                            if (invent[1] == 1){
                                player.two.defend = player.two.defend * 2;
                            }
                            char input;
                            int block = 0;
                            int slimetime = 0;
                            //Player Input
                            input = getch();
                            printf("__________________________________________________________________________________________________________\n");
                            if (input == 65 || input == 97) {
                                printf("\t\tYou lunge forward and slash!\n\t\tDealing %d(dmg)!\n\n", player.two.attack);
                                slime.two.health = slime.two.health - (player.two.attack - slimetime);
                            } else if (input == 66 || input == 98) {
                                printf("\t\tYou raise your shield preparing to defend\n\t\tBlocking %d(blck)!\n\n",
                                       player.two.defend);
                                block = block + player.two.defend;
                            } else if (input == 67 || input == 99) {
                                printf("\t\tYou take a big gulp of your potion!\n\t\tHealing %d(hlth)!\n\n",
                                       player.two.heal);
                                *playerhealth = *playerhealth + player.two.heal;
                            } else
                                printf("\t\tNot a valid entry! The slime takes the opportunity to punish that mistake!\n\n");
                            printf("\t\tPress any key to continue\n");
                            printf("__________________________________________________________________________________________________________\n");
                            getch();
                            //Slime Input
                            if (slimetime > 0) {
                                slimetime = slimetime - 3;
                                printf("\t\tThe slimey ooze lowering your damage is reduced.\n \t\tYour damage is now reduced by %d\n"), slimetime;
                            }
                            int action;
                            action = rand() % 3;
                            if (action == 0) {
                                printf("\t\tThe slime throws itself into you!\n \t\tDealing %d(dmg)!\n\n",
                                       slime.two.attack);
                                if (block > 0)
                                    printf("\t\tYou block! Preventing %d(blck)!\n", block);
                                slime.two.attack = slime.two.attack - block;
                                printf("\t\tYou take %d(dmg) instead!\n", slime.two.attack);
                                if (slime.two.attack < 0) {
                                    slime.two.attack = 0;
                                }

                                *playerhealth = *playerhealth - slime.two.attack;
                            } else if (action == 1) {
                                printf("\t\tThe slime spits a horrible sticky attack covering you head to toe!\n \t\tReducing your attack by %d!\n\n",
                                       slime.two.slimetime);
                                slimetime = slime.two.slimetime + slimetime;
                            } else if (action == 2) {
                                printf("\t\tThe slime seems to be squeezing itself!\n \t\tHealing %d(hlth)!\n\n",
                                       slime.two.heal);
                                slime.two.health = slime.two.health + slime.two.heal;
                            }
                            if (*playerhealth <= 0) {
                                printf("\n\n\n\t\tYou died.... Try again!");
                                getch();
                                exit(0);
                            }
                            printf("\t\tPress any key to continue\n");
                            printf("__________________________________________________________________________________________________________\n");
                            getch();
                        }
                        printf("\n\n\t\tThe slime dissolves away into the ground below!\n"
                               "\t\t You Level up! Congratulations!\n\n");
                        printf("\t\tPress any key to continue\n");
                        printf("__________________________________________________________________________________________________________\n");
                    }



                        void slimecombat3(int *playerhealth, int invent[4]) {
                            slime.three.health = 150;
                            player.three.heal = 20;
                            *playerhealth = *playerhealth + 25;
                            printf("\n\t\tThe slime attacks! It screeches at you!\n");
                            while (slime.three.health > 0) { ;
                                printf("__________________________________________________________________________________________________________\n");
                                printf("\t\tTHE SMALL SLIME HAS %dhp/50hp \tYOUR HEALTH IS %dhp/50hp\n\n\n\n"
                                       "\t\tYou ready your sword and shield. What would you like to do?\n\n"
                                       "\t\tPlease enter the appropriate letter:\n", slime.three.health, *playerhealth);
                                if (invent[0] == 1) {
                                    printf("\t\ta) Strike 20(40) - 60(120)(dmg)\n");
                                } else printf("\t\ta) Strike 20 - 60(dmg)\n");
                                if (invent[1] == 1) {
                                    printf("\t\tb) Defend with your shield 15(30) - 30(60)(blck)\n");
                                } else printf("\t\tb) Defend with your shield 15 - 30(blck)\n");
                                if (invent[2] == 1) {
                                    printf("\t\tc) Drink from your potion healing 20(40)(hlth)\n");
                                } else printf("\t\tc) Drink from your potion healing 20(hlth)\n\n");
                                slime.three.attack = rand() % 31 + 20;
                                slime.three.heal = rand() % 31 + 10;
                                slime.three.slimetime = 15 ;
                                if (invent[2] == 1){
                                    player.one.heal = player.one.heal * 2;
                                }
                                player.one.attack = rand() % 41 + 20;
                                if (invent[0] == 1){
                                    player.one.attack = player.one.attack * 2;
                                }
                                player.one.defend = rand() % 16 + 15;
                                if (invent[1] == 1){
                                    player.one.defend = player.one.defend * 2;
                                }
                                char input;
                                int block;
                                int slimetime = 0;
                                //Player Input
                                input = getch();
                                printf("__________________________________________________________________________________________________________\n");
                                if (input == 65 || input == 97) {
                                    printf("\t\tYou lunge forward and slash!\n\t\tDealing %d(dmg)!\n\n",
                                           player.three.attack);
                                    slime.three.health = slime.three.health - (player.three.attack - slimetime);
                                } else if (input == 66 || input == 98) {
                                    printf("\t\tYou raise your shield preparing to defend\n\t\tBlocking %d(blck)!\n\n",
                                           player.three.defend);
                                    block = 0;
                                    block = block + player.three.defend;
                                } else if (input == 67 || input == 99) {
                                    printf("\t\tYou take a big gulp of your potion!\n\t\tHealing %d(hlth)!\n\n",
                                           player.three.heal);
                                    player.three.health = *playerhealth + player.three.heal;
                                } else
                                    printf("\t\tNot a valid entry! The slime takes the opportunity to punish that mistake!\n\n");
                                printf("\t\tPress any key to continue\n");
                                printf("__________________________________________________________________________________________________________\n");
                                getch();
                                //Slime Input
                                if (slimetime > 0) {
                                    slimetime = slimetime - 3;
                                    printf("\t\tThe slimey ooze lowering your damage is reduced.\n \t\tYour damage is now reduced by %d\n"), slimetime;
                                }
                                int action;
                                action = rand() % 7;
                                if (action == 0 || action == 4) {
                                    slime.three.attack = slime.three.attack - block;
                                    if (slime.three.attack < 0) {
                                        printf("\t\tThe slime throws itself into you!\n \t\tDealing %d(dmg)!\n\n",
                                               slime.three.attack);
                                        if (block > 0)
                                            printf("\t\tYou block! Preventing %d(blck)!\n", block);
                                        slime.three.attack = slime.three.attack - block;
                                        printf("\t\tYou take %d(dmg) instead!\n", slime.three.attack);
                                        if (slime.three.attack < 0) {
                                            slime.three.attack = 0;
                                        }

                                        player.one.health = *playerhealth - slime.three.attack;
                                    }
                                    printf("\t\tThe slime throws itself into you!\n \t\tDealing %d(dmg)!\n\n",
                                           slime.three.attack);
                                    if (block > 0)
                                        printf("\t\tYou block! Preventing %d(blck)!\n", block);
                                    slime.three.attack = slime.three.attack - block;
                                    printf("\t\tYou take %d(dmg) instead!\n", slime.one.attack);
                                    if (slime.three.attack < 0) {
                                        slime.three.attack = 0;
                                    }

                                    player.one.health = *playerhealth - slime.three.attack;
                                } else if (action == 1 || action == 5|| action == 6) {
                                    printf("\t\tThe slime spits a horrible sticky attack covering you head to toe!\n \t\tReducing your attack by %d!\n\n",
                                           slime.three.slimetime);
                                    slimetime = slime.one.slimetime + slimetime;
                                } else if (action == 2 ) {
                                    printf("\t\tThe slime seems to be squeezing itself!\n \t\tHealing %d(hlth)!\n\n",
                                           slime.three.heal);
                                    slime.three.health = slime.three.health + slime.three.heal;
                                }
                                if (*playerhealth <= 0) {
                                    printf("\n\n\n\t\tYou died.... Try again!");
                                    getch();
                                    exit(0);
                                }
                                printf("\t\tPress any key to continue\n");
                                printf("__________________________________________________________________________________________________________\n");
                                getch();
                            }
                            printf("\n\n\t\tThe slime dissolves away into the ground below!\n"
                                   "\t\t You Level up! Congratulations!\n\n");
                            printf("\t\tPress any key to continue\n");
                            printf("__________________________________________________________________________________________________________\n");
                        }

