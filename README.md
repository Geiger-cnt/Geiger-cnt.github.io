## Contador Geiger

Bora medir radiação?!

![Screenshot](imgs/a.png)

## Um pouco mais sobre

### O que é radiação?

"Em física, radiação é a propagação de energia de um ponto a outro, seja no vácuo ou em qualquer meio material, podendo ser classificada como energia em trânsito, e podendo ocorrer através de uma onda eletromagnética ou partícula." - Texto retirado da [Wikipedia](https://pt.wikipedia.org/wiki/Radia%C3%A7%C3%A3o).

### Radiação ionizante
"Radiação ionizante é a radiação que possui energia suficiente para ionizar átomos e moléculas, ou seja, é capaz de arrancar um elétron de um átomo ou molécula. " - Texto retirado da [Wikipedia](https://pt.wikipedia.org/wiki/Radia%C3%A7%C3%A3o_ionizante)

### Tipos de radiação que existem

| Radiação | Significado |
| ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| Alfa             | Radiação nuclear ionizante que apresenta dois prótons e dois nêutrons                                                                    |
| Beta             | Elétrons sem massa e com carga menos um                                                                                                  |
| Gama             | Ondas eletromagnéticas com carga nula                                                                                                    |
| X                | Ondas eletromagnéticas que possuem a capacidade de atravessar corpos de baixa densidade e são absorvidos por materiais de densidade maior|

### Instrumento de Aferição

A principal função do contador de Geiger é detectar radiação na atmosfera,  ele foi criado em 1908 pelo físico alemão Johannes Hans Geiger com o intuito de medir os níveis de radiação em corpos e no ambiente. Sua constituição conta com um tubo de argônio que ao ser atravessado por partículas radioativas alfa e beta se ioniza, causando o fechamento do circuito elétrico e acionando o contador de radiação. Sua importância se deve ao fato de auxiliar o trabalho de profissionais que utilizam a radiação em tratamentos de saúde e ainda é essencial no estudo de acidentes nucleares.

### Unidade de medida (CPM)

## Como é que se faz um Contador Geiger?

Este site tem como proposição ensinar uma maneira de montar um simples contador Geiger utilizando a plataforma Arduino.

### Materiais
- Arduino UNO
- Módulo contador Geiger com Âmpola

### EletrÔnica

### Código

- Declaração das variaveis

```cpp
#include <SPI.h>

#define LOG_PERIOD 15000     //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 60000    //Maximum logging period
#define GM 2

unsigned long counts;

unsigned long cpm;
unsigned int multiplier; 

unsigned long previousMillis;

void tube_impulse(){counts++;}
```

- Setup

```cpp
void setup() {
  cpm = 0;
  counts = 0;
  previousMillis = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;         
  
  Serial.begin(9600);                                   

  pinMode(GM, INPUT);
  digitalWrite(GM, HIGH);

  attachInterrupt(0, tube_impulse, FALLING);
}
```
- Main code
```cpp
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > LOG_PERIOD) {
    previousMillis = currentMillis;
    cpm = counts * multiplier;

    Serial.print(cpm);
    Serial.write(' ');

    counts = 0;
  }
}
```
- [Código completo](https://github.com/Geiger-cnt/Geiger-cnt.github.io/blob/main/geiger/geiger.ino)
