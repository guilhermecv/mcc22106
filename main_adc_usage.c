#include <msp430.h>
#include "adc.h"
#include "lib/clock_system.h"

int main()
{
    /* Desliga Watchdog */
    WDTCTL = WDTPW + WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;
    P6DIR |= BIT6;

    init_clock_system();

    battery_voltage_t battery;

    adc_init(&battery);

    for (;;)
    {

        if (battery.cell_0 >= CELL_MAX_VOLTAGE
                | battery.cell_1 >= CELL_MAX_VOLTAGE)
        {
            /* Sobre tens�o em uma das c�lulas */
            P1OUT |= BIT0;
            P6OUT &= ~BIT6;
        }
        else if (battery.cell_0 < CELL_MIN_VOLTAGE
                | battery.cell_1 < CELL_MIN_VOLTAGE)
        {
            /* Sub tens�o em uma das c�lulas */
            P1OUT |= BIT0;
            P6OUT &= ~BIT6;
        }
        else
        {
            /* Tens�o dentro dos limites de opera��o */
            P6OUT |= BIT6;
            P1OUT &= ~BIT0;
        }

        __bis_SR_register(GIE);

    }
}

