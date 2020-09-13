/*
 * data.h
 *
 *  Created on: Oct 15, 2018
 *      Author: ASUS
 */

#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <stdint.h>

typedef
    struct {
        // The fields are ordered to reduce memory over caused by struct-padding
        uint8_t       smile[8];
        uint8_t       sad[8];
        uint8_t       led_control[8];
        uint8_t       test_on[8];
        uint8_t       test_off[8];
        uint8_t       game_map[32];
    }
img_data;

volatile img_data data;

//void data_init(img_data data_);
//void array_copy(uint8_t a[], uint8_t b[]);

#endif /* LIB_DATA_H_ */
