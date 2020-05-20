#include QMK_KEYBOARD_H

/*uint16_t get_tapping_term(uint16_t keycode) {
	switch (keycode) {
		case LT(1,KC_SPC):
			return TAPPING_TERM - 50;
		case LT(2,KC_ENT):
			return TAPPING_TERM - 50;
		default:
			return TAPPING_TERM;
	}
}*/

enum planck_layers {
	_COLEMAK,
	_LOWER,
	_RAISE
};

enum planck_keycodes {
	COLEMAK = SAFE_RANGE,
	LOWER,
	RAISE,
	DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = KEYMAP(KC_EQL, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS,
				 KC_MINS, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_QUOT,
				 KC_LSPO, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
				 KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TAB, LT(_LOWER,KC_SPC), LT(_RAISE,KC_ENT), KC_BSPC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
	[_LOWER] = KEYMAP(KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_ESC, KC_NO, KC_VOLU, KC_7, KC_8, KC_9, KC_NO, KC_NO,
				 KC_CAPS, LGUI_T(KC_DEL), LALT_T(KC_GRV), LCTL_T(KC_LPRN), LSFT_T(KC_RPRN), KC_NO, KC_MUTE, RSFT_T(KC_4), RCTL_T(KC_5), RALT_T(KC_6), RGUI_T(KC_BSLS), KC_NO,
				 KC_NO, KC_NO, KC_INS, KC_LBRC, KC_RBRC, KC_NO, KC_VOLD, KC_1, KC_2, KC_3, KC_SLSH, KC_NO,
				 KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_ENT, KC_0, KC_COMM, KC_DOT, KC_NO, KC_NO),
	[_RAISE] = KEYMAP(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO,
				 DYN_MACRO_PLAY1, KC_BTN4, KC_BTN3, KC_BTN1, KC_BTN2, KC_BTN5, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, DYN_MACRO_PLAY2,
				 DYN_REC_START1, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, DYN_REC_START2,
				 DYN_REC_STOP, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (!process_record_dynamic_macro(keycode, record)) {
		return false;
	}
	return true;
}
