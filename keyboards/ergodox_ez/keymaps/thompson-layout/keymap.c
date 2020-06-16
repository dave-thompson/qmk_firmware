#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
};

//////////////////
// Tap Dance Stuff
//////////////////

typedef struct {
  bool is_press_action;
  int state;
} tap;

// --Tap States
enum {
    SINGLE_TAP = 0,
    SINGLE_HOLD,
	DOUBLE_TAP,
	DOUBLE_HOLD
};

// --Tap Dance Keycodes
enum {
  SHIFT_OR_SYMBOL = 0
};

int cur_dance (qk_tap_dance_state_t *state);

void shiftorsymbol_finished (qk_tap_dance_state_t *state, void *user_data);
void shiftorsymbol_reset (qk_tap_dance_state_t *state, void *user_data);

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

static tap shiftorsymboltap_state = {
  .is_press_action = true,
  .state = 0
};

void shiftorsymbol_finished (qk_tap_dance_state_t *state, void *user_data) {
  shiftorsymboltap_state.state = cur_dance(state);
  switch (shiftorsymboltap_state.state) {
	// shift
    case SINGLE_TAP: set_oneshot_layer(1, ONESHOT_START); break;
    case SINGLE_HOLD: set_oneshot_layer(1, ONESHOT_START); break;
	// symbols
    case DOUBLE_TAP: set_oneshot_layer(4, ONESHOT_START); break;
	case DOUBLE_HOLD: set_oneshot_layer(4, ONESHOT_START); break;
  }
}

void shiftorsymbol_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (shiftorsymboltap_state.state) {
    case SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
	case DOUBLE_HOLD: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
  }
  shiftorsymboltap_state.state = 0;
}

// --Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [SHIFT_OR_SYMBOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shiftorsymbol_finished, shiftorsymbol_reset)
};


//////////////////
// Keymap Stuff
//////////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_0,                                     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TOGGLE_LAYER_COLOR,RGB_MOD,
    KC_ESCAPE,      KC_Q,           KC_D,           KC_R,           KC_W,           KC_B,           ST_MACRO_1,                                     KC_TRANSPARENT, KC_K,           KC_F,           KC_U,           KC_P,           KC_Z,           KC_TRANSPARENT,
    KC_TAB,         KC_A,           KC_S,           KC_H,           KC_T,           KC_G,                                                                           KC_Y,           KC_N,           KC_E,           KC_O,           KC_I,           KC_ENTER,
    KC_TRANSPARENT, KC_X,           KC_V,           KC_M,           KC_C,           KC_TRANSPARENT, KC_ENTER,                                       KC_TRANSPARENT, KC_TRANSPARENT, KC_L,           KC_COMMA,       KC_DOT,         KC_J,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LCTL(LGUI(KC_Q)),
                                                                                                    KC_BSPACE,      KC_LALT,        KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_LCTRL,       KC_TRANSPARENT,
                                                                                    TD(SHIFT_OR_SYMBOL),  OSL(5),         KC_LGUI,        KC_BSPACE,      KC_ENTER, LT(2,KC_SPACE)
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LSFT(KC_Q),     LSFT(KC_D),     LSFT(KC_R),     LSFT(KC_W),     LSFT(KC_B),     KC_TRANSPARENT,                                 KC_TRANSPARENT, LSFT(KC_K),     LSFT(KC_F),     LSFT(KC_U),     LSFT(KC_P),     LSFT(KC_Z),     KC_TRANSPARENT,
    KC_TRANSPARENT, LSFT(KC_A),     LSFT(KC_S),     LSFT(KC_H),     LSFT(KC_T),     LSFT(KC_G),                                                                     LSFT(KC_Y),     LSFT(KC_N),     LSFT(KC_E),     LSFT(KC_O),     LSFT(KC_I),     KC_TRANSPARENT,
    KC_TRANSPARENT, LSFT(KC_X),     LSFT(KC_V),     LSFT(KC_M),     LSFT(KC_C),     KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_L),     KC_QUOTE,       LALT(KC_MINUS), LSFT(KC_J),     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_ENTER
  ),
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_PLUS,        KC_3,           KC_MINUS,       KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_SLASH,       KC_8,           KC_ASTR,        KC_CIRC,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_1,           KC_2,           KC_4,           KC_5,           KC_LPRN,                                                                        KC_RPRN,        KC_6,           KC_7,           KC_9,           KC_0,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LABK,        KC_DLR,         KC_HASH,        KC_EQUAL,       KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_DOT,         KC_COMMA,       KC_PERC,        KC_RABK,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    TO(3),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_PLUS,        KC_3,           KC_MINUS,       KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_SLASH,       KC_8,           KC_ASTR,        KC_CIRC,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_1,           KC_2,           KC_4,           KC_5,           KC_LPRN,                                                                        KC_RPRN,        KC_6,           KC_7,           KC_9,           KC_0,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LABK,        KC_DLR,         KC_HASH,        KC_EQUAL,       KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_DOT,         KC_COMMA,       KC_PERC,        KC_RABK,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_ENTER
  ),
  [4] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LBRACKET,    KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_RBRACKET,    KC_UNDS,        KC_AMPR,        KC_AT,          KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,                                                                        KC_RPRN,        KC_QUOTE,       KC_QUES,        KC_EXLM,        KC_DQUO,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_BSLASH,      KC_GRAVE,       KC_PIPE,        KC_TILD,        KC_LCBR,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_RCBR,        LALT(KC_MINUS), KC_SCOLON,      KC_COLN,        KC_SLASH, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_ergodox_pretty(
    RESET,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LGUI(KC_N),     LGUI(KC_W),     KC_DOWN,        LGUI(KC_M),     LGUI(KC_I),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, LGUI(KC_LEFT),  KC_UP,          RGUI(KC_RIGHT), KC_TRANSPARENT, KC_TRANSPARENT,
    LGUI(KC_TAB),   LGUI(KC_A),     LGUI(KC_X),     LGUI(KC_C),     LGUI(KC_V),     LGUI(KC_B),                                                                     KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_BSPACE,      KC_TRANSPARENT,
    KC_TRANSPARENT, LGUI(KC_Z),     LGUI(LSFT(KC_Z)),LGUI(KC_P),     LGUI(KC_S),     LGUI(KC_U),     KC_TRANSPARENT,                                KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_BSLASH),LGUI(KC_U),     LALT(KC_RIGHT), LALT(KC_BSPACE),KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LSHIFT,      LGUI(KC_SPACE)
  ),
};


extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {249,228,255}, {249,228,255}, {249,228,255}, {249,228,255}, {154,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {154,255,255}, {105,255,255}, {105,255,255}, {14,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_F) SS_DELAY(1) SS_TAP(X_B) SS_DELAY(1) SS_TAP(X_W));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_I) SS_DELAY(1) SS_TAP(X_R) SS_DELAY(1) SS_TAP(X_F));

    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

  uint8_t layer = biton32(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};
