#ifndef _COMON_H

#define ceu_out_isr_on()  interrupts()
#define ceu_out_isr_off() noInterrupts()

#define ceu_out_assert(v) ceu_sys_assert(v)
void ceu_sys_assert (int v) {
    if (!v) {
        ceu_out_isr_off();
        pinMode(13, OUTPUT);
        int v = 0;
        for (;;) {
            digitalWrite(13, v=!v);
            delayMicroseconds(10000);
            delayMicroseconds(10000);
            delayMicroseconds(10000);
            delayMicroseconds(10000);
            delayMicroseconds(10000);
        }
        ceu_out_isr_on();
    }
}

#define ceu_out_log(m,s) ceu_sys_log(m,s)
void ceu_sys_log (int mode, long s) {
    /* TODO: use Serial? */
}

#define ceu_out_emit_PIN00(v) digitalWrite( 0, v->_1)
#define ceu_out_emit_PIN01(v) digitalWrite( 1, v->_1)
#define ceu_out_emit_PIN02(v) digitalWrite( 2, v->_1)
#define ceu_out_emit_PIN03(v) digitalWrite( 3, v->_1)
#define ceu_out_emit_PIN04(v) digitalWrite( 4, v->_1)
#define ceu_out_emit_PIN05(v) digitalWrite( 5, v->_1)
#define ceu_out_emit_PIN06(v) digitalWrite( 6, v->_1)
#define ceu_out_emit_PIN07(v) digitalWrite( 7, v->_1)
#define ceu_out_emit_PIN08(v) digitalWrite( 8, v->_1)
#define ceu_out_emit_PIN09(v) digitalWrite( 9, v->_1)
#define ceu_out_emit_PIN10(v) digitalWrite(10, v->_1)
#define ceu_out_emit_PIN11(v) digitalWrite(11, v->_1)
#define ceu_out_emit_PIN12(v) digitalWrite(12, v->_1)
#define ceu_out_emit_PIN13(v) digitalWrite(13, v->_1)

#endif
