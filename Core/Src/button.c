#include "button.h"

vBUT BUTTONS[MAX_BUTTONS_QTD];

uint8_t Button_Qtd = 0;

void InitButton(GPIO_TypeDef* Button_GPIO_Port, uint16_t Button_GPIO_Pin)
{
    Button_Qtd++;
		if(Button_Qtd > MAX_BUTTONS_QTD)
		{
			return;
		}
    BUTTONS[Button_Qtd-1].GPIO_Port = Button_GPIO_Port;
    BUTTONS[Button_Qtd-1].GPIO_Pin = Button_GPIO_Pin;
}

uint8_t BUT_SIGNAL[MAX_BUTTONS_QTD], OLD_BUT_SIGNAL[MAX_BUTTONS_QTD], BUT_RISING_EDGE_DETECTED[MAX_BUTTONS_QTD];

void ScanButtons()
{
    for (uint8_t j = 0; j < Button_Qtd; j++)
    {
        BUT_SIGNAL[j] = HAL_GPIO_ReadPin(BUTTONS[j].GPIO_Port, BUTTONS[j].GPIO_Pin);

        /*detecta borda de descida*/
        if ((OLD_BUT_SIGNAL[j] == 1) && (BUT_SIGNAL[j] == 0))
        {
            OLD_BUT_SIGNAL[j] = BUT_SIGNAL[j];
            BUTTONS[j].StartTimer = 1;
            BUT_RISING_EDGE_DETECTED[j] = 0;
        }

        /*detecta borda de subida*/
        if ((OLD_BUT_SIGNAL[j] == 0) && (BUT_SIGNAL[j] == 1))
        {
            OLD_BUT_SIGNAL[j] = BUT_SIGNAL[j];
            BUTTONS[j].StartTimer = 0;
            BUT_RISING_EDGE_DETECTED[j] = 1;
        }

        if (BUTTONS[j].StartTimer == 1)
        {
            BUTTONS[j].Timer++;
        }

        if ((BUTTONS[j].Timer > LONG_CLICK_DEBOUNCE) && (BUT_RISING_EDGE_DETECTED[j] == 1))
        {
            BUTTONS[j].State = LONG_CLICK;
            BUTTONS[j].StartTimer = 0;
            BUTTONS[j].Timer = 0;
        }
        else if ((BUTTONS[j].Timer > MEDIUM_CLICK_DEBOUNCE) && (BUT_RISING_EDGE_DETECTED[j] == 1))
        {
            BUTTONS[j].State = MEDIUM_CLICK;
            BUTTONS[j].StartTimer = 0;
            BUTTONS[j].Timer = 0;
        }
        else if ((BUTTONS[j].Timer > SHORT_CLICK_DEBOUNCE) && (BUT_RISING_EDGE_DETECTED[j] == 1))
        {
            BUTTONS[j].State = SHORT_CLICK;
            BUTTONS[j].StartTimer = 0;
            BUTTONS[j].Timer = 0;
        }
        else
        {
            /*do nothing*/
        }
    }
}