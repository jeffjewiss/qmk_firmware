#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum custom_keycodes {
    M_NEXT_PANE = SAFE_RANGE,
    M_PREV_PANE,
    M_NEXT_TAB,
    M_PREV_TAB,
    M_NEXT_AGENT,
    M_PREV_AGENT,
    M_NEXT_WORKSPACE,
    M_PREV_WORKSPACE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up | Knob 2: Nav Dn/Up | Knob 3: App Next/Prev |
        | Press: Mute       | Press: Enter      | Press: Play/Pause     |
        | Prev Agent        | Hold: Layer 2     | Next Agent            |
        | Prev Pane         | Hyper ~           | Next Pane             |
     */
    [0] = LAYOUT(
        KC_MUTE,      KC_ENTER,      KC_MPLY,
        M_PREV_AGENT, MO(1),         M_NEXT_AGENT,
        M_PREV_PANE,  HYPR(KC_TILD), M_NEXT_PANE
    ),
    /*
        | QK_BOOT         | Esc | Media Play/Stop |
        | Prev Tab        |     | Next Tab        |
        | Prev Workspacce |     | Next Workspacce |
     */
    [1] = LAYOUT(
        QK_BOOT,          KC_ESC,  KC_SLEP,
        M_PREV_TAB,      _______, M_NEXT_TAB,
        M_PREV_WORKSPACE, _______, M_NEXT_WORKSPACE
    ),
};

void herdr_prefix(void) {
    register_code(KC_LCTL);
    tap_code(KC_SPC);
    unregister_code(KC_LCTL);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_NEXT_PANE:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            tap_code(KC_TAB);
        }
        break;

        case M_PREV_PANE:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
        }
        break;

        case M_NEXT_TAB:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            tap_code(KC_N);
        }
        break;

        case M_PREV_TAB:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            tap_code(KC_P);
        }
        break;

        case M_NEXT_WORKSPACE:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            register_code(KC_LCTL);
            tap_code(KC_GRAVE);
            unregister_code(KC_LCTL);
        }
        break;

        case M_PREV_WORKSPACE:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            register_code(KC_LCTL);
            tap_code(KC_MINUS);
            unregister_code(KC_LCTL);
        }
        break;

        case M_NEXT_AGENT:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            register_code(KC_LCTL);
            tap_code(KC_DOT);
            unregister_code(KC_LCTL);
        }
        break;

        case M_PREV_AGENT:
        if (record->event.pressed) {
            herdr_prefix();
        } else {
            register_code(KC_LCTL);
            tap_code(KC_COMMA);
            unregister_code(KC_LCTL);
        }
        break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    else if (index == _RIGHT) {
        /* if this doesn't work, try this next: https://docs.qmk.fm/feature_macros#super-alt%E2%86%AFtab */
        if (clockwise) {
            register_code(KC_LGUI);
            tap_code(KC_TAB);
            unregister_code(KC_LGUI);
        } else {
            register_code(KC_LGUI);
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
        }
    }
    return false;
}
