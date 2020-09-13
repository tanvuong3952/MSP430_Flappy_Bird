/*
 * sys_init.h
 *
 *  Created on: Oct 15, 2018
 *      Author: ASUS
 */

#ifndef _FLAPPY_H_
#define _FLAPPY_H_

#include "GPIO_CLOCK.h"
#include "SPI.h"
#include <stdio.h>
#include <stdint.h>

#define BTN_1       BIT3 // Port 2
#define BTN_2       BIT4 // Port 2
#define BTN_3       BIT5 // Port 2
#define trigger     BIT1;
#define echo        BIT0;
#define BTN2_1      BIT5 // Port 2
#define BTN2_2      BIT4 // Port 2
#define BTN2_3      BIT3 // Port 2

typedef
    struct {
        // The fields are ordered to reduce memory over caused by struct-padding
        uint8_t       begin_img[8];
        uint8_t       end_img[8];
        uint8_t       led_control[8];
        uint8_t       on_img[8];
        uint8_t       off_img[8];
        uint8_t       game_map[32];
        uint8_t       iState;
        uint8_t		  jump;
        uint8_t 	  bird[8];
        uint8_t 	  birdposition;
        uint8_t 	  birdposition1;

    }
sys_params_t;

volatile sys_params_t sys_params;

void sys_init(void);
void begin(volatile sys_params_t *params);
void end(volatile sys_params_t *params);
void play(volatile sys_params_t *params);
void position(uint8_t display_map[8]);
void init_timer(void);
void image_copy(uint8_t *a, uint8_t *b);
void map_copy(uint8_t *a, uint8_t *b);



#endif /* LIB_FLAPPY_H_ */
