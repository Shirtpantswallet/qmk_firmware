#include QMK_KEYBOARD_H
#include "version.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define NO_TH ALGR(KC_T)
#define NO_ETH ALGR(KC_D)

enum custom_keycodes {
  RGB_SLD = SAFE_RANGE,  // can always be here
  TOGGLE_LAYER_COLOR,
  EPRM,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(KC_DELETE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LEFT,
                       KC_EQUAL, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_CAPSLOCK,
                       KC_MINUS, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,
                       KC_LSPO, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_AUDIO_MUTE,
                       KC_TRANSPARENT, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END,
                       KC_HOME, KC_PGDOWN,
                       KC_MEH, LT(1, KC_SPACE),
                       KC_TAB, KC_ESCAPE,

                       KC_RIGHT, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
                       KC_INSERT, KC_J, KC_L, KC_U, KC_Y, KC_SCOLON, KC_BSLASH,
                       KC_M, RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_QUOTE,
                       KC_DELETE, KC_K, KC_H, KC_COMMA, KC_DOT, KC_SLASH, KC_RSPC,
                       KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRANSPARENT,
                       KC_PGUP, KC_END,
                       KC_HYPR, KC_ESCAPE,
                       KC_BSPACE, LT(2, KC_ENTER)),

  [1] = LAYOUT_ergodox(KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, LGUI_T(KC_DELETE), LALT_T(KC_GRAVE), KC_LCPO, KC_RSPC, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_INSERT, LCTL(KC_BSLASH), KC_LBRACKET, KC_RBRACKET, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT,

                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_AUDIO_VOL_UP, KC_7, KC_8, KC_9, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_AUDIO_MUTE, RSFT_T(KC_4), RCTL_T(KC_5), RALT_T(KC_6), RGUI_T(KC_BSLASH), KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_AUDIO_VOL_DOWN, KC_1, KC_2, KC_3, KC_SLASH, KC_TRANSPARENT,
                       KC_0, KC_COMMA, KC_KP_DOT, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_BSPACE, KC_ENTER),

  [2] = LAYOUT_ergodox(KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                       DYN_REC_STOP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRANSPARENT,
                       DYN_MACRO_PLAY1, KC_MS_BTN4, KC_MS_BTN3, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN5,
                       DYN_REC_START1, KC_F6, KC_F7, KC_F8, KC_F14, KC_F10, KC_TRANSPARENT,
                       KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_BSPACE, KC_TRANSPARENT,
                       KC_TAB, KC_ENTER,

                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, DYN_MACRO_PLAY2,
                       KC_TRANSPARENT, KC_TRANSPARENT, KC_RSHIFT, KC_RCTRL, KC_RALT, KC_RGUI, DYN_REC_START2,
                       KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_TRANSPARENT, RESET,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT,
                       KC_TRANSPARENT, KC_TRANSPARENT),

};

bool process_record_user(uint16_t keycode,  keyrecord_t *record) {
  switch (keycode) {
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
  }
  if (!process_record_dynamic_macro(keycode,  record)) {
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
