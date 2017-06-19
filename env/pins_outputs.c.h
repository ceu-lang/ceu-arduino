#ifdef _CEU_OUTPUT_AN_REQ_00_
case CEU_OUTPUT_AN_REQ_00:
    queue(0);
    analogRead_begin(0);
    break;
#endif
#ifdef _CEU_OUTPUT_AN_REQ_01_
case CEU_OUTPUT_AN_REQ_01:
    queue(1);
    analogRead_begin(1);
    break;
#endif
#ifdef _CEU_OUTPUT_AN_REQ_02_
case CEU_OUTPUT_AN_REQ_02:
    queue(2);
    analogRead_begin(2);
    break;
#endif
#ifdef _CEU_OUTPUT_AN_REQ_03_
case CEU_OUTPUT_AN_REQ_03:
    queue(3);
    analogRead_begin(3);
    break;
#endif
#ifdef _CEU_OUTPUT_AN_REQ_04_
case CEU_OUTPUT_AN_REQ_04:
    queue(4);
    analogRead_begin(4);
    break;
#endif
#ifdef _CEU_OUTPUT_AN_REQ_05_
case CEU_OUTPUT_AN_REQ_05:
    queue(5);
    analogRead_begin(5);
    break;
#endif
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

#ifdef _CEU_OUTPUT_PWM_00_
case CEU_OUTPUT_PWM_00:
    analogWrite(0, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_01_
case CEU_OUTPUT_PWM_01:
    analogWrite(1, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_02_
case CEU_OUTPUT_PWM_02:
    analogWrite(2, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_03_
case CEU_OUTPUT_PWM_03:
    analogWrite(3, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_04_
case CEU_OUTPUT_PWM_04:
    analogWrite(4, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_05_
case CEU_OUTPUT_PWM_05:
    analogWrite(5, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_06_
case CEU_OUTPUT_PWM_06:
    analogWrite(6, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_07_
case CEU_OUTPUT_PWM_07:
    analogWrite(7, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_08_
case CEU_OUTPUT_PWM_08:
    analogWrite(8, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_09_
case CEU_OUTPUT_PWM_09:
    analogWrite(9, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_10_
case CEU_OUTPUT_PWM_10:
    analogWrite(10, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_11_
case CEU_OUTPUT_PWM_11:
    analogWrite(11, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_12_
case CEU_OUTPUT_PWM_12:
    analogWrite(12, *((int*)p2.ptr));
    break;
#endif
#ifdef _CEU_OUTPUT_PWM_13_
case CEU_OUTPUT_PWM_13:
    analogWrite(13, *((int*)p2.ptr));
    break;
#endif
