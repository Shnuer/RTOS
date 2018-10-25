#include <ch.h>
#include <hal.h>

PWMConfig pwm1servconf = {
                      .frequency = 500000,
                      .period = 10000,
                      .callback = NULL,
                      .channels = {
                                    {PWM_OUTPUT_DISABLED, NULL},
                                    {PWM_OUTPUT_DISABLED, NULL},
                                    {PWM_OUTPUT_DISABLED, NULL},
                                    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                      },
                      .cr2 = 0,
                      .dier = 0


};

PWMConfig pwm3conf = {
                      .frequency = 500000,
                      .period = 10000,
                      .callback = NULL,
                      .channels = {
                                    {PWM_OUTPUT_DISABLED, NULL},
                                    {PWM_OUTPUT_DISABLED, NULL},
                                    {PWM_OUTPUT_DISABLED, NULL},
                                    {PWM_OUTPUT_DISABLED, NULL},
                      },
                      .cr2 = 0,
                      .dier = 0


};
PWMDriver *pwmDriver_serv_1      = &PWMD2;
int Flag=0;
int Num_set=0;

void setMode1(void)
{
    pwmEnableChannel(pwmDriver_serv_1, 3, 400);
    palSetLine(LINE_LED1);
    palClearLine(LINE_LED2);

}

void setMode2(void)
{
    pwmEnableChannel(pwmDriver_serv_1, 3, 1200);
    palSetLine(LINE_LED2);
    palClearLine(LINE_LED1);


}


void Clik_button(void)
{

    if(palReadLine(LINE_BUTTON)==1)
        {

          chThdSleepMilliseconds(1);

          if(Flag==0)
          {


            if(palReadLine(LINE_BUTTON)==1)
            {

                Flag = 1;
                Num_set++;

                if(Num_set==1)
                {
                  setMode1();
                }

                else
                {
                  setMode2();
                  Num_set=0;
                }

            }
          }

        }

        else
        {
          Flag=0;
        }

}

int main(void)
{

    chSysInit();
    halInit();

    palSetPadMode(GPIOA,3, PAL_MODE_ALTERNATE(1));

    pwmStart( pwmDriver_serv_1 , &pwm1servconf );

    pwmEnableChannel(pwmDriver_serv_1, 3, 800);



    while (true)
    {

        Clik_button();

    }
}
