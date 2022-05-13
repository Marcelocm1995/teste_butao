#ifndef __BUTTON_H__
#define __BUTTON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void InitButton (GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin);
void ScanButtons(void);

#define MAX_BUTTONS_QTD 10

/*Define your buttons here*/
#define But1 BUTTONS[0]
#define But2 BUTTONS[1]
/* Etc....Butx BUTTONS[x+1] */

/*Define your debounces here*/
#define SHORT_CLICK_DEBOUNCE  100-1
#define MEDIUM_CLICK_DEBOUNCE 1500-1
#define LONG_CLICK_DEBOUNCE   3000-1

typedef struct
{
    uint8_t State;
    uint8_t StartTimer;
    uint16_t Timer;
    GPIO_TypeDef* GPIO_Port;
    uint16_t GPIO_Pin;
} vBUT;

typedef enum
{
    NO_CLICK = 0,
    SHORT_CLICK,
    MEDIUM_CLICK,
    LONG_CLICK
} BUTTON_STATES;

extern vBUT BUTTONS[];

#ifdef __cplusplus
}
#endif

#endif /* __BUTTON_H__ */
