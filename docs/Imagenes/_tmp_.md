````mermaid
gantt
    title SOLINDAR - Gantt Diagram
    dateFormat YYYY-MM-DD
    axisFormat %

    section Firmware
    Medición de sensores                 :a1, 2018-12-31, 3d
    Crear interfaz del motor             :a2, 2018-12-31, 4d
    Crear interfaz Bluetooth             :a3, 2018-12-31, 4d
    Empaquetado / Envío de datos         :a4, after a3,   3d
    Pruebas y depuración                 :a5, 2018-12-31, 11d

    section Hardware
    Montaje de Hardware                  :h1, 2018-12-31, 2d
    Calibración                          :h3, after h1,   4d
    Pruebas al Motor                     :h2, after a2,   2d

    section Software
    Recepción de Trama / Desempaquetado  :s1, after a4,   4d
    Diseño de GUI                        :s1, 2018-12-31, 11d
    Graficación / Mapeo de datos         :s2, 2018-12-31, 11d
    Pruebas y depuración                 :s3, 2018-12-31, 11d
````
## Programa Principal

````flow
st=>start: Start
e=>end
op1=>operation: Inicialización:
• Periféricos
• Motor
• Bluetooth
op2=>operation: ReadyNewStep = True
sub1=>subroutine: Mover Motor
cond1=>condition: ¿ReadyNewStep?
io=>inputoutput: Medir sensores
op4=>operation: Medir sensores
sub2=>subroutine: Empaquetar Datos
op6=>operation: Enviar Datos a PC
op7=>operation: ReadyNewStep = False

st->op1->op2->cond1
cond1(yes)->sub1->io->sub2->op7(left)->cond1
cond1(no)->cond1
````

## Interrupciones
### Interrupción de timer para llevar velocidad del motor
````flow
st=>start: Timer Interrupt
e=>end
op1=>operation: ReadyNewStep = True

st->op1->e
````

### Interrupción externa para ajustar la posición cero del motor
````flow
st=>start: Extern Interrupt
e=>end
op1=>operation: StepCount = 0

st->op1->e
````

## Rutinas
### Rutina para mover el motor, se implementa un tope de giro para evitar dar una revolución
````flow
st=>subroutine: Mover Motor
e=>end: Return
cond1=>condition: ¿Sentido de giro horario?
cond2=>condition: ¿Se llegó al límite superior?
cond3=>condition: ¿Se llegó al límite inferior?
op1=>operation: Cambiar el sentido de giro a anti-horario
op2=>operation: Mover el motor
op3=>operation: Cambiar el sentido de giro a horario
op4=>operation: Avanzar motor sentido horario
op5=>operation: ReadyNewStep = True

st->cond1
cond1(yes)->cond2
cond1(no)->cond3
cond2(yes)->op1->op2->op5->e
cond2(no)->op2->op5->e
cond3(yes)->op3->op2->op5->e
cond3(no)->op2->op5->e
````