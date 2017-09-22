{
#ifdef _CEU_INPUT_PIN_00_
    {
        int tmp = digitalRead(0);
#ifdef CEU_INPUT_PIN_00_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,0) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,0,tmp);
            ceu_input(CEU_INPUT_PIN_00, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_01_
    {
        int tmp = digitalRead(1);
#ifdef CEU_INPUT_PIN_01_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,1) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,1,tmp);
            ceu_input(CEU_INPUT_PIN_01, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_02_
    {
        int tmp = digitalRead(2);
#ifdef CEU_INPUT_PIN_02_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,2) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,2,tmp);
            ceu_input(CEU_INPUT_PIN_02, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_03_
    {
        int tmp = digitalRead(3);
#ifdef CEU_INPUT_PIN_03_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,3) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,3,tmp);
            ceu_input(CEU_INPUT_PIN_03, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_04_
    {
        int tmp = digitalRead(4);
#ifdef CEU_INPUT_PIN_04_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,4) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,4,tmp);
            ceu_input(CEU_INPUT_PIN_04, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_05_
    {
        int tmp = digitalRead(5);
#ifdef CEU_INPUT_PIN_05_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,5) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,5,tmp);
            ceu_input(CEU_INPUT_PIN_05, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_06_
    {
        int tmp = digitalRead(6);
#ifdef CEU_INPUT_PIN_06_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,6) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,6,tmp);
            ceu_input(CEU_INPUT_PIN_06, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_07_
    {
        int tmp = digitalRead(7);
#ifdef CEU_INPUT_PIN_07_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,7) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,7,tmp);
            ceu_input(CEU_INPUT_PIN_07, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_08_
    {
        int tmp = digitalRead(8);
#ifdef CEU_INPUT_PIN_08_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,8) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,8,tmp);
            ceu_input(CEU_INPUT_PIN_08, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_09_
    {
        int tmp = digitalRead(9);
#ifdef CEU_INPUT_PIN_09_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,9) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,9,tmp);
            ceu_input(CEU_INPUT_PIN_09, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_10_
    {
        int tmp = digitalRead(10);
#ifdef CEU_INPUT_PIN_10_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,10) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,10,tmp);
            ceu_input(CEU_INPUT_PIN_10, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_11_
    {
        int tmp = digitalRead(11);
#ifdef CEU_INPUT_PIN_11_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,11) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,11,tmp);
            ceu_input(CEU_INPUT_PIN_11, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_12_
    {
        int tmp = digitalRead(12);
#ifdef CEU_INPUT_PIN_12_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,12) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,12,tmp);
            ceu_input(CEU_INPUT_PIN_12, &tmp);
        }
    }
#endif
#ifdef _CEU_INPUT_PIN_13_
    {
        int tmp = digitalRead(13);
#ifdef CEU_INPUT_PIN_13_INVERT
        tmp = !tmp;
#endif
        if (bitRead(CEU_ARDUINO.pins_bits,13) != tmp) {
            bitWrite(CEU_ARDUINO.pins_bits,13,tmp);
            ceu_input(CEU_INPUT_PIN_13, &tmp);
        }
    }
#endif
}
