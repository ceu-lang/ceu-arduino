#ifdef CEU_ISR__TIMER1_COMPA_vect_num
ISR(TIMER1_COMPA_vect)
{
    //static int v = 0;
    //digitalWrite(12, v=!v);
    if (isrs[TIMER1_COMPA_vect_num] != NULL) {
        isrs[TIMER1_COMPA_vect_num]();
    }
}
#endif

