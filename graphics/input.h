#ifndef INPUT_H
#define INPUT_H

// ---------------------------------------------------------------------------
//                       BUTTON INPUT
// ---------------------------------------------------------------------------
#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R (1 << 8)
#define BUTTON_L (1 << 9)

#define BUTTONS (*(volatile u32 *)0x4000130)
#define KEY_DOWN(key, buttons) (~(buttons) & (key))

#define KEY_JUST_PRESSED(key, buttons, oldButtons) (KEY_DOWN((key), (buttons)) && !KEY_DOWN((key), (oldButtons)))

#endif