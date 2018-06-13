#ifndef COMMON_H
#define COMMON_H

#include "stdint.h"

#define MENU_ID 0
#define XOX_ID 1
#define CONNECT4_ID 2
#define PINGBOSS_ID 3
#define HANGMAN_ID 4
#define TAIKO 5

struct packet{
    uint8_t start;
    uint8_t app_id;
    union{
        struct initial{
            uint8_t playerId;
        } initial;
        struct menu_data{
            uint8_t currentItem;
            uint8_t isSelected;
            uint8_t isAccepted;
            uint8_t _cursor;
        }menu;
        struct xox_data{
            uint8_t cell_states[9];
            uint8_t scorep1;
            uint8_t scorep2;
            uint8_t position;
            uint8_t isClicked;
            uint8_t turn;
            uint8_t winRound;
            uint8_t winGame;
        }xox;
        struct{
            uint8_t p1_cells[6];
            uint8_t p2_cells[6];
            uint8_t scoreP1;
            uint8_t scoreP2;
            uint8_t position;
            uint8_t is_clicked;
            uint8_t turn;
            uint8_t roundWon;
            uint8_t x1;
            uint8_t y1;
            uint8_t x2;
            uint8_t y2;
        }connect_four;
        struct {
            uint8_t p1pos;
            uint8_t p2pos;
            uint8_t bossPos;
            uint8_t bossHp;
            uint8_t pressedButton;

            //Shots elemanlarinin ilk 4 biti x koordinati sonraki 4 biti y koordinati
            uint8_t bossBullets[10];  //x koordinati 0 ise dizi elemani bos/atis yok
            uint8_t p1Bullets[5];   //x koordinati 0 ise dizi elemani bos/atis yok
            uint8_t p2Bullets[5];    //x koordinati 0 ise dizi elemani bos/atis yok
          } ping_boss;
        uint8_t _[30];
    }data;
};

struct xox{
    int cursor;
    int stamp;
    int position;
    int f;
    int winner[3];
    int reset;
};

struct pingboss{
    float p1;
    float p2;
    float boss;
    float p1Bullets[5];
    int p1Y[5];
    float p2Bullets[5];
    int p2Y[5];
    float bossL[5];
    int bossLY[5];
    float bossR[5];
    int bossRY[5];
    bool p1State;
    bool p2State;
    int bossHP;
};
#endif // COMMON_H
