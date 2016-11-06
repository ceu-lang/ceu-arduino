#include "_ceu_app.c.h"

#ifdef CEU_FEATURES_ISR
#include "wiring_private.h"
#ifdef __AVR
#include <avr/interrupt.h>
/*
 * ... Thus, normally interrupts will remain disabled inside the handler until
 *     the handler exits, ...
 * <http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html>
 */
#else
#error "Unsupported Platform!"
#endif

static volatile voidFuncPtr isrs[_VECTORS_SIZE];
#endif

static int is_terminating = 0;
static int has_async      = 0;
static u32 old;
static u32 pins_bits      = 0;

tceu_callback_ret ceu_callback (int cmd, tceu_callback_arg p1,
                                         tceu_callback_arg p2)
{
    tceu_callback_ret ret = { .is_handled=1 };
    switch (cmd) {
        case CEU_CALLBACK_TERMINATING:
            is_terminating = 1;
            break;
        case CEU_CALLBACK_ASYNC_PENDING:
            has_async = 1;
            break;

#ifdef CEU_FEATURES_ISR
        case CEU_CALLBACK_ISR_ENABLE: {
            if (p1.num == 1) {
                interrupts();
            } else {
                noInterrupts();
            }
            break;
        }
        case CEU_CALLBACK_ISR_ATTACH: {
            void(*f)() = (void(*)()) p1.ptr;
            int* args = (int*) p2.ptr;
            if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                attachInterrupt(args[0], f, args[1]);
            } else {
                isrs[args[0]] = f;
            }
            break;
        }
        case CEU_CALLBACK_ISR_DETACH: {
            int* args = (int*)p2.ptr;
            if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                detachInterrupt(args[0]);
            } else {
                isrs[args[0]] = NULL;
            }
            break;
        }
#endif

        case CEU_CALLBACK_OUTPUT:
            switch (p1.num) {
#ifdef _CEU_OUTPUT_PIN_00_
                case CEU_OUTPUT_PIN_00:
                    digitalWrite(0, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_01_
                case CEU_OUTPUT_PIN_01:
                    digitalWrite(1, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_02_
                case CEU_OUTPUT_PIN_02:
                    digitalWrite(2, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_03_
                case CEU_OUTPUT_PIN_03:
                    digitalWrite(3, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_04_
                case CEU_OUTPUT_PIN_04:
                    digitalWrite(4, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_05_
                case CEU_OUTPUT_PIN_05:
                    digitalWrite(5, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_06_
                case CEU_OUTPUT_PIN_06:
                    digitalWrite(6, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_07_
                case CEU_OUTPUT_PIN_07:
                    digitalWrite(7, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_08_
                case CEU_OUTPUT_PIN_08:
                    digitalWrite(8, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_09_
                case CEU_OUTPUT_PIN_09:
                    digitalWrite(9, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_10_
                case CEU_OUTPUT_PIN_10:
                    digitalWrite(10, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_11_
                case CEU_OUTPUT_PIN_11:
                    digitalWrite(11, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_12_
                case CEU_OUTPUT_PIN_12:
                    digitalWrite(12, *((int*)p2.ptr));
                    break;
#endif
#ifdef _CEU_OUTPUT_PIN_13_
                case CEU_OUTPUT_PIN_13:
                    digitalWrite(13, *((int*)p2.ptr));
                    break;
#endif
            }
            break;
        default:
            ret.is_handled = 0;
    }
    return ret;
}

void setup () {
#ifdef _CEU_INPUT_PIN_00_
    pinMode( 0, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_00_
    pinMode( 0, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_01_
    pinMode( 1, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_01_
    pinMode( 1, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_02_
    pinMode( 2, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_02_
    pinMode( 2, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_03_
    pinMode( 3, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_03_
    pinMode( 3, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_04_
    pinMode( 4, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_04_
    pinMode( 4, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_05_
    pinMode( 5, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_05_
    pinMode( 5, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_06_
    pinMode( 6, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_06_
    pinMode( 6, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_07_
    pinMode( 7, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_07_
    pinMode( 7, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_08_
    pinMode( 8, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_08_
    pinMode( 8, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_09_
    pinMode( 9, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_09_
    pinMode( 9, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_10_
    pinMode(10, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_10_
    pinMode(10, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_11_
    pinMode(11, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_11_
    pinMode(11, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_12_
    pinMode(12, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_12_
    pinMode(12, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN_13_
    pinMode(13, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN_13_
    pinMode(13, OUTPUT);
#endif
    old = millis();
    //Serial.begin(9600);
    ceu_start();
}

void loop ()
{
    while (!is_terminating)
    {
noInterrupts();
        /* ASYNC */
        if (has_async) {
            has_async = 0;
            ceu_input(CEU_INPUT__ASYNC, NULL);
        }

        /* WCLOCK */
        {
            u32 now = micros();
            s32 dt = now - old;     // no problems with overflow
            ceu_input(CEU_INPUT__WCLOCK, &dt);
            old = now;
        }

        /* PINS */
        {
#ifdef _CEU_INPUT_PIN_00_
            int tmp = digitalRead(0);
            if (bitRead(pins_bits,0) != tmp) {
                bitWrite(pins_bits,0,tmp);
                ceu_input(CEU_INPUT_PIN_00, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_01_
            int tmp = digitalRead(1);
            if (bitRead(pins_bits,1) != tmp) {
                bitWrite(pins_bits,1,tmp);
                ceu_input(CEU_INPUT_PIN_01, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_02_
            int tmp = digitalRead(2);
            if (bitRead(pins_bits,2) != tmp) {
                bitWrite(pins_bits,2,tmp);
                ceu_input(CEU_INPUT_PIN_02, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_03_
            int tmp = digitalRead(3);
            if (bitRead(pins_bits,3) != tmp) {
                bitWrite(pins_bits,3,tmp);
                ceu_input(CEU_INPUT_PIN_03, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_04_
            int tmp = digitalRead(4);
            if (bitRead(pins_bits,4) != tmp) {
                bitWrite(pins_bits,4,tmp);
                ceu_input(CEU_INPUT_PIN_04, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_05_
            int tmp = digitalRead(5);
            if (bitRead(pins_bits,5) != tmp) {
                bitWrite(pins_bits,5,tmp);
                ceu_input(CEU_INPUT_PIN_05, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_06_
            int tmp = digitalRead(6);
            if (bitRead(pins_bits,6) != tmp) {
                bitWrite(pins_bits,6,tmp);
                ceu_input(CEU_INPUT_PIN_06, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_07_
            int tmp = digitalRead(7);
            if (bitRead(pins_bits,7) != tmp) {
                bitWrite(pins_bits,7,tmp);
                ceu_input(CEU_INPUT_PIN_07, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_08_
            int tmp = digitalRead(8);
            if (bitRead(pins_bits,8) != tmp) {
                bitWrite(pins_bits,8,tmp);
                ceu_input(CEU_INPUT_PIN_08, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_09_
            int tmp = digitalRead(9);
            if (bitRead(pins_bits,9) != tmp) {
                bitWrite(pins_bits,9,tmp);
                ceu_input(CEU_INPUT_PIN_09, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_10_
            int tmp = digitalRead(10);
            if (bitRead(pins_bits,10) != tmp) {
                bitWrite(pins_bits,10,tmp);
                ceu_input(CEU_INPUT_PIN_10, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_11_
            int tmp = digitalRead(11);
            if (bitRead(pins_bits,11) != tmp) {
                bitWrite(pins_bits,11,tmp);
                ceu_input(CEU_INPUT_PIN_11, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_12_
            int tmp = digitalRead(12);
            if (bitRead(pins_bits,12) != tmp) {
                bitWrite(pins_bits,12,tmp);
                ceu_input(CEU_INPUT_PIN_12, &tmp);
            }
#endif
#ifdef _CEU_INPUT_PIN_13_
            int tmp = digitalRead(13);
            if (bitRead(pins_bits,13) != tmp) {
                bitWrite(pins_bits,13,tmp);
                ceu_input(CEU_INPUT_PIN_13, &tmp);
            }
#endif
        }
interrupts();
    }
    ceu_stop();
    while (1);
}

