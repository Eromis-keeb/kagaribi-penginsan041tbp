#include QMK_KEYBOARD_H


#include "quantum.h"
#include "gpio.h"

static inline uint8_t scale(uint8_t c) {
    return (uint16_t)c * rgb_matrix_config.hsv.v / 255;
}


RGB current_rgb = {255, 128, 192};
RGB current_rgb2 = {255, 128, 192};
/* RGB current_rgb_lower = {255, 128, 192}; */
/* RGB current_rgb_raise = {255, 128, 192}; */
/* RGB current_rgb = {255, 128, 192}; */


#define SW1_PIN GP13
#define SW2_PIN GP12
#define SW3_PIN GP11


#define EECONFIG_COLOR_LO (uint32_t *)0x20
#define EECONFIG_COLOR_RA (uint32_t *)0x28


#define ROTARY_ROW 3
#define ROTARY_COL 3


static inline void eeconfig_update_kb_at(uint32_t *addr, uint32_t val) {
        eeprom_update_dword(addr,val);
}

static inline uint32_t eeconfig_read_kb_at(uint32_t *addr) {
  return eeprom_read_dword(addr);
}



void keyboard_pre_init_user(void) {

	setPinInputLow(SW1_PIN);
	setPinInputLow(SW2_PIN);
	setPinInputLow(SW3_PIN);
}

enum layer_number {
	_default = 0,
	_lo,
	_ra,
	_up,
	_do,
	_le,
	_ri,
    _fo
};


enum custom_keycodes {
 LED_PINK_lo = QK_KB_0,
 LED_GREEN_lo,
 LED_BLUE_lo,
 LED_WHITE_lo,
 LED_PURPLE_lo,
 LED_RED_lo,
 LED_YELLOW_lo,
 LED_ORANGE_lo,
 LED_CYAN_lo,
 LED_MAGENTA_lo,
 LED_GRAY_lo,
 LED_PINK_ra,
 LED_GREEN_ra,
 LED_BLUE_ra,
 LED_WHITE_ra,
 LED_PURPLE_ra,
 LED_RED_ra,
 LED_YELLOW_ra,
 LED_ORANGE_ra,
 LED_CYAN_ra,
 LED_MAGENTA_ra,
 LED_GRAY_ra

};

#define KC_PINK LED_PINK_lo
#define KC_GREE LED_GREEN_lo
#define KC_BLUE LED_BLUE_lo
#define KC_WHIT LED_WHITE_lo
#define KC_PURP LED_PURPLE_lo
#define KC_RED  LED_RED_lo
#define KC_YELL LED_YELLOW_lo
#define KC_ORAN LED_ORANGE_lo
#define KC_CYAN LED_CYAN_lo
#define KC_MAGE LED_MAGENTA_lo
#define KC_GRAY LED_GRAY_lo
#define KC_PINK2 LED_PINK_ra
#define KC_GREE2 LED_GREEN_ra
#define KC_BLUE2 LED_BLUE_ra
#define KC_WHIT2 LED_WHITE_ra
#define KC_PURP2 LED_PURPLE_ra
#define KC_RED2  LED_RED_ra
#define KC_YELL2 LED_YELLOW_ra
#define KC_ORAN2 LED_ORANGE_ra
#define KC_CYAN2 LED_CYAN_ra
#define KC_MAGE2 LED_MAGENTA_ra
#define KC_GRAY2 LED_GRAY_ra










const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_default] = LAYOUT(

       KC_ESC, 	 KC_Q,   KC_W,	  KC_E,	          KC_R,		     KC_T,  	KC_Y,          KC_U,  		   KC_I,	 	KC_O,  	 KC_P,	  KC_BSPC,
       KC_LCTL,	 KC_A, 	 KC_S,	  KC_D,		      KC_F,		     KC_G,  	KC_H,          KC_J,   	       KC_K,	 	KC_L,  	 KC_SCLN, KC_QUOT,
       KC_LSFT,	 KC_Z,   KC_X,	  KC_C,		      KC_V,		     KC_B,  	KC_N,          KC_M,      	   KC_COMM,   	KC_DOT,	 KC_SLSH, RSFT_T(KC_MINS),
                  	     KC_LGUI, LALT_T(KC_ESC), LT(1,KC_SPC),  	    	LT(2,KC_ENT),  LCTL_T(KC_TAB), MO(3)
    ),

    [_lo] = LAYOUT(

       KC_ESC, 	KC_1, 	        KC_2,	     KC_3,		     KC_4,	        	KC_5,  	        KC_6,        KC_7,  		 KC_8,	 	KC_9,  	     KC_0,	   KC_DEL,
       KC_LCTL,	LSFT(KC_6),  	LSFT(KC_7),	 LSFT(KC_8),	 LSFT(KC_9),		LSFT(KC_0),  	KC_LEFT,     KC_DOWN,        KC_UP,	 	KC_RIGHT,  	 KC_SCLN,  KC_BSPC,
       KC_LSFT,	LSFT(KC_1),  	LSFT(KC_2),	 LSFT(KC_3),	 LSFT(KC_4),		LSFT(KC_5),  	KC_BSLS,     KC_GRAVE,       KC_QUOT,   KC_DOT,	     KC_SLSH,  KC_TRNS,
                 	            KC_ESC,      LALT_T(KC_ESC), LT(1,KC_SPC),                      KC_MINS,     LCTL_T(KC_TAB), KC_LGUI
    ),

    [_ra] = LAYOUT(

       KC_F1, 	KC_F2, 	        KC_F3,	     KC_F4,		     KC_F5,	        	KC_F6,  	    KC_F7,         KC_F8,  		    KC_F9,	 	KC_F10,  	 KC_F11,   KC_F12,
       KC_LCTL,	LSFT(KC_1),  	LSFT(KC_2),	 LSFT(KC_3),	 LSFT(KC_4),		LSFT(KC_5),  	KC_MINS,       KC_EQL,          KC_PAST,	KC_PSLS,  	 KC_SCLN,  KC_BSPC,
       KC_LSFT,	LSFT(KC_6),  	LSFT(KC_7),	 LSFT(KC_8),	 LSFT(KC_9),		LSFT(KC_0),  	KC_BSLS,       KC_GRAVE,        KC_QUOT,    KC_DOT,	     KC_SLSH,  KC_TRNS,
                 	            KC_ESC,      LALT_T(KC_ESC),  KC_MINS,                          LT(2,KC_ENT),  LCTL_T(KC_TAB),  KC_LGUI
     ),


    [_up] = LAYOUT(

       KC_NO, 	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO, 	KC_NO,  KC_NO, 		KC_NO,	 	KC_NO, 	 KC_NO,	  KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,   	KC_NO,	 	KC_NO, 	 KC_NO,   KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,      KC_NO,   	KC_NO,	 KC_NO,   KC_NO,
                    	KC_NO,    KC_NO,	  KC_NO,  	        KC_NO,  KC_NO,	    KC_NO
    ),




    [_do] = LAYOUT(
       KC_F1, 	KC_F2, 	KC_F3,	  KC_F4,	  KC_F5,	KC_F6, 	KC_F7,  KC_F8, 		KC_F9,	 	KC_F10,  KC_F11,  KC_F12,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,   	KC_NO,	 	KC_NO, 	 KC_NO,   KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,     	KC_NO,   	KC_NO,	 KC_NO,   KC_NO,
                    	KC_NO,    KC_NO,	  KC_NO,  	        KC_NO,  KC_NO,	    KC_NO
   ),




    [_le] = LAYOUT(
       KC_1, 	KC_2, 	KC_3,	  KC_4,	      KC_5,	    KC_6, 	KC_7,   KC_8, 		KC_9,	 	KC_0, 	 KC_NO,	  KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,   	KC_NO,	 	KC_NO, 	 KC_NO,   KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,      KC_NO,   	KC_NO,	 KC_NO,   KC_NO,
                    	KC_NO,    KC_NO,	  KC_NO,  	        KC_NO,  KC_NO,	    KC_NO
    ),




    [_ri] = LAYOUT(

       KC_NO, 	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO, 	KC_NO,  KC_NO, 		KC_NO,	 	KC_NO, 	 KC_NO,	  KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,   	KC_NO,	 	KC_NO, 	 KC_NO,   KC_NO,
       KC_NO,	KC_NO, 	KC_NO,	  KC_NO,	  KC_NO,	KC_NO,  KC_NO,  KC_NO,     	KC_NO,   	KC_NO,	 KC_NO,   KC_NO,
                 	    KC_NO,    KC_NO,	  KC_NO,  	        KC_NO,  KC_NO,	    KC_NO

    ),

    [_fo] = LAYOUT(
       KC_PINK,  KC_GREE,  KC_BLUE,  KC_WHIT,	KC_PURP,  KC_RED,  KC_YELL,   KC_ORAN, 	 KC_CYAN,  KC_MAGE,  KC_GRAY,  KC_NO,
       KC_PINK2, KC_GREE2, KC_BLUE2, KC_WHIT2,  KC_PURP2, KC_RED2, KC_YELL2,  KC_ORAN2,  KC_CYAN2, KC_MAGE2, KC_GRAY2, KC_NO,
       KC_NO,    KC_NO,    KC_NO,	 KC_NO,	    KC_NO,	  KC_NO,   KC_NO,     KC_NO,     KC_NO,    KC_NO,	 KC_NO,    KC_NO,
                           KC_NO,    KC_NO,	    KC_NO,  	       KC_NO,     KC_NO,	 KC_NO
    )



    };


/* 8layers */
     /* uint8_t get_layer_state(void) { */
     /* uint8_t sw1 = gpio_read_pin(SW1_PIN) ? 0 : 1; */
     /* uint8_t sw2 = gpio_read_pin(SW2_PIN) ? 0 : 1; */
     /* uint8_t sw3 = gpio_read_pin(SW3_PIN) ? 0 : 1; */
     /* uint8_t sw4 = gpio_read_pin(SW4_PIN) ? 0 : 1; */

/* 4layers */
uint8_t get_layer_state(void) {
     uint8_t sw1 = gpio_read_pin(SW1_PIN) ? 0 : 1;
     uint8_t sw2 = gpio_read_pin(SW2_PIN) ? 0 : 1;
     uint8_t sw3 = gpio_read_pin(SW3_PIN) ? 0 : 1;


bool rotary_pressed = matrix_is_on(ROTARY_ROW,ROTARY_COL);


    /* bool rotary_pressed  = matrix_is_on(ROTARY_ROW,ROTARY_COL); */
if(sw1 && sw2 && sw3 && rotary_pressed) return 7;
    else if (!sw1 && !sw2 && !sw3) return 0;
    else if (sw1 && !sw2 && !sw3) return 4;
    else if (sw1 && sw2 && !sw3) return 5;
    else if (sw1 && sw2 && sw3) return 6;
    else if (!sw1 && sw2 && !sw3) return 4;
    else if (!sw1 && sw2 && sw3) return 5;
    else if (!sw1 && !sw2 && sw3) return 4;
    else return 0;


      /* // ONになっているスイッチの数をカウント */
     /* uint8_t base_layer = sw1 + sw2 + sw3;  // 0〜3 */

     /* // SW4がONなら +4 してカラーバリエーションのレイヤーにする */
     /* return base_layer; */
}

void matrix_scan_user(void) {
	static uint8_t current_layer = 255;
	uint8_t new_layer = get_layer_state();

	if (new_layer != current_layer) {
		current_layer = new_layer;
		layer_move(new_layer);
	}

}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        switch (keycode) {

            case LED_PINK_lo:
                current_rgb = (RGB){255, 128, 192};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_GREEN_lo:
                current_rgb = (RGB){0, 255, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_BLUE_lo:
                current_rgb = (RGB){0, 0, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_WHITE_lo:
                current_rgb = (RGB){255, 255, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_PURPLE_lo:
                current_rgb = (RGB){128, 0, 128};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_RED_lo:
                current_rgb = (RGB){255, 0, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_YELLOW_lo:
                current_rgb = (RGB){255, 255, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_ORANGE_lo:
                current_rgb = (RGB){255, 128, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_CYAN_lo:
                current_rgb = (RGB){0, 255, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_MAGENTA_lo:
                current_rgb = (RGB){255, 0, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_GRAY_lo:
                current_rgb = (RGB){128, 128, 128};

                eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                return false;

            case LED_PINK_ra:
                current_rgb2 = (RGB){255, 128, 192};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_GREEN_ra:
                current_rgb2 = (RGB){0, 255, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_BLUE_ra:
                current_rgb2 = (RGB){0, 0, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_WHITE_ra:
                current_rgb2 = (RGB){255, 255, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_PURPLE_ra:
                current_rgb2 = (RGB){128, 0, 128};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_RED_ra:
                current_rgb2 = (RGB){255, 0, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_YELLOW_ra:
                current_rgb2 = (RGB){255, 255, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_ORANGE_ra:
                current_rgb2 = (RGB){255, 128, 0};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_CYAN_ra:
                current_rgb2 = (RGB){0, 255, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_MAGENTA_ra:
                current_rgb2 = (RGB){255, 0, 255};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;

            case LED_GRAY_ra:
                current_rgb2 = (RGB){128, 128, 128};

                eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                return false;



        }
    }
    return true;
}








bool rgb_matrix_indicators_user(void) {
	switch (get_highest_layer(layer_state)) {

		case _lo:
 		/* for (int i = 3; i <=5; i++) { */
	    	rgb_matrix_set_color(5,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
			/* rgb_matrix_set_color(5,RGB_BLUE); */
			rgb_matrix_set_color(4,RGB_BLACK);
			rgb_matrix_set_color(3,RGB_BLACK);
		/* } */

			break;

		case _ra:

 		/* for (int i = 3; i <= 5; i++) { */
	    	rgb_matrix_set_color(5,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
	    	rgb_matrix_set_color(4,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
			/* rgb_matrix_set_color(5,RGB_BLUE); */
			/* rgb_matrix_set_color(4,RGB_BLUE); */
			rgb_matrix_set_color(3,RGB_BLACK);

		/* } */

			break;

		case _up:

 		/* for (int i = 3; i <= 5; i++) { */
	    	rgb_matrix_set_color(5,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
	    	rgb_matrix_set_color(4,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
	    	rgb_matrix_set_color(3,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
			/* rgb_matrix_set_color(5,RGB_BLUE); */
			/* rgb_matrix_set_color(4,RGB_BLUE); */
			/* rgb_matrix_set_color(3,RGB_BLUE); */

		/* } */

			break;

		case _do:

 		/* for (int i = 3; i <= 5; i++) { */
			rgb_matrix_set_color(3,RGB_BLACK);
			rgb_matrix_set_color(4,RGB_BLACK);
	    	rgb_matrix_set_color(5,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			/* rgb_matrix_set_color(i,RGB_PURPLE); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(12,RGB_BLACK); */
			/* rgb_matrix_set_color(13,RGB_BLACK); */

		/* } */

			break;

		case _le:

 		/* for (int i = 3; i <= 5; i++) { */
	    	rgb_matrix_set_color(3,RGB_BLACK);
			rgb_matrix_set_color(4,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			rgb_matrix_set_color(5,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			/* rgb_matrix_set_color(i,RGB_PURPLE); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(12,RGB_BLACK); */
			/* rgb_matrix_set_color(13,RGB_BLACK); */

		/* } */

			break;

		case _ri:

 		/* for (int i = 3; i <= 5; i++) { */
			rgb_matrix_set_color(3,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			rgb_matrix_set_color(4,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			rgb_matrix_set_color(5,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			/* rgb_matrix_set_color(i,RGB_PURPLE); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(12,RGB_BLACK); */
			/* rgb_matrix_set_color(13,RGB_BLACK); */

		/* } */

			break;

		case _fo:

 		/* for (int i = 3; i <= 5; i++) { */
			rgb_matrix_set_color(3,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			rgb_matrix_set_color(4,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			rgb_matrix_set_color(5,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
			/* rgb_matrix_set_color(i,RGB_PURPLE); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(11,RGB_BLACK); */
			/* rgb_matrix_set_color(12,RGB_BLACK); */
			/* rgb_matrix_set_color(13,RGB_BLACK); */

		/* } */

			break;



	}

	return false;

}


 void keyboard_post_init_user(void) {
     if (!eeconfig_is_enabled()) {
        eeconfig_init();
     }
uint32_t packed_lo = eeconfig_read_kb_at(EECONFIG_COLOR_LO);
     current_rgb.r = (packed_lo >> 16) & 0xFF;
     current_rgb.g = (packed_lo >> 8) & 0xFF;
     current_rgb.b = packed_lo & 0xFF;


uint32_t packed_ra = eeconfig_read_kb_at(EECONFIG_COLOR_RA);
     current_rgb2.r = (packed_ra >> 16) & 0xFF;
     current_rgb2.g = (packed_ra >> 8) & 0xFF;
     current_rgb2.b = packed_ra & 0xFF;


    eeconfig_update_kb_at(EECONFIG_COLOR_LO, packed_lo);
    eeconfig_update_kb_at(EECONFIG_COLOR_RA, packed_ra);


 }





