## Geiger-Muller

Bora medir radiação?!

![Screenshot](imgs/a.png)

## Uma breve introdução...

### O que é radiação?
"Em física, radiação é a propagação de energia de um ponto a outro, seja no vácuo ou em qualquer meio material, podendo ser classificada como energia em trânsito, e podendo ocorrer através de uma onda eletromagnética ou partícula." - Texto retirado da [Wikipedia](https://pt.wikipedia.org/wiki/Radia%C3%A7%C3%A3o)

### Radiação ionizante
"Radiação ionizante é a radiação que possui energia suficiente para ionizar átomos e moléculas, ou seja, é capaz de arrancar um elétron de um átomo ou molécula." - Texto retirado da [Wikipedia](https://pt.wikipedia.org/wiki/Radia%C3%A7%C3%A3o_ionizante)

### Tipos de radiação que existem

| Radiação | Significado |
| ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| Alfa             | Radiação nuclear ionizante que apresenta dois prótons e dois nêutrons                                                                    |
| Beta             | Elétrons sem massa e com carga menos um                                                                                                  |
| Gama             | Ondas eletromagnéticas com carga nula                                                                                                    |
| X                | Ondas eletromagnéticas que possuem a capacidade de atravessar corpos de baixa densidade e são absorvidos por materiais de densidade maior|

### Instrumento de Aferição

<div style='text-align: justify;'> A principal função do contador de Geiger é detectar radiação na atmosfera, ele foi criado em 1908 pelo físico alemão Johannes Hans Geiger com o intuito de medir os níveis de radiação em corpos e no ambiente. Sua constituição conta com um tubo de argônio que ao ser atravessado por partículas radioativas alfa e beta se ioniza, causando o fechamento do circuito elétrico e acionando o contador de radiação. Sua importância se deve ao fato de auxiliar o trabalho de profissionais que utilizam a radiação em tratamentos de saúde e ainda é essencial no estudo de acidentes nucleares.<br><br></div>

### Unidade de medida (CPM)

<div style='text-align: justify;'> CPM é a contagem por minuto exibida no medidor do contador Geiger. Você pode às vezes ver contagem por segundo (CPS), mas pode facilmente converter o CPM para contagem por segundo (CPS), dividindo o seu valor por 60.<br><br></div>

<div style='text-align: justify;'> As medições de contagens por minuto são geralmente usadas para pegar o número de partículas ao redor, o que pode incluir partículas alfa ou beta. Em vez de mostrar a quantidade de radiação que algo está emitindo, os níveis de radiação do CPM informam quantos eventos de detecção o medidor capta. Portanto, o valor do CPM não mostra a quantidade ou a intensidade da radiação. O dispositivo que você está usando para medir a radiação também pode informar a taxa de dose, embora a conversão de CPM para taxa de dose varie com base em seu dispositivo específico e alguns outros fatores, como o tipo de radiação. Um medidor Geiger usa compensação de energia para criar uma leitura da dose.<br><br></div>

<div style='text-align: justify;'> Depois de obter a leitura de CPM de seu dispositivo, você precisa descobrir o que essa leitura significa. Quais são os níveis normais de radiação CPM e quais são os perigosos? Se você tiver seu contador Geiger calibrado para Cs137, o que a maioria está, 1 miliRad por hora equivaleria a 1.200 CPM em seu contador. Ao mesmo tempo, 1 microSievert por hora equivaleria a 120 CPM na leitura. Essas são unidades de medida mais universais que podem ajudá-lo a entender melhor sua exposição à radiação.<br><br></div>

<div style='text-align: justify;'> Uma leitura de CPM de pelo menos 100 é considerada um nível alarmante pela Rede de Radiação, embora o período de tempo que você fica exposto à radiação seja um fator importante. Se você está preocupado em permanecer dentro de níveis seguros de radiação, Ken Jorgustin explica no Blog de Sobrevivência Moderna que levaria 432 dias a um CPM de 100 para aumentar sua chance de desenvolver câncer para chances de 1 em 1.000. Com taxas de exposição mais altas, levaria menos tempo. Por exemplo, levaria apenas quatro dias para aumentar sua taxa para essas probabilidades se você fosse exposto a um nível de 10.000 CPM.<br><br></div>

<div style='text-align: justify;'> Ao usar um detector Geiger Mueller, você poderá ver facilmente as contagens por minuto de radiação em uma determinada área. Isso pode ajudá-lo a entender mais sobre seu ambiente e sua exposição.<br><br></div>

## Como é que se faz um Contador Geiger?

Este site tem como proposição ensinar uma maneira de montar um simples contador Geiger utilizando a plataforma Arduino.

### Materiais

- Arduino UNO

![Screenshot](imgs/a.jpeg)

- Módulo contador Geiger com Ampola

![Screenshot](imgs/b.jpeg)

- x3 Jumpers

![Screenshot](imgs/c.png)

### Eletrônica

<div style='text-align: justify;'> O componente de maior relevância para o projeto é o Módulo com Ampola, pois é essa ampola que permite a contagem da radiação do ambiente. Essa ampola consiste de um recipiente de vidro preenchido internamente por um gás inerte, o qual passa a conduzir eletricidade quando entra em contato com uma grande quantidade de energia, como as radiações alfa, beta e gama, por exemplo. Vale ressaltar que a maioria dos kits DIY (Faça Você Mesmo) já vêm com o circuito preparado de forma a facilitar a confecção de futuros projetos. Esse circuito elétrico instalado no módulo apresenta uma fonte de tensão, resistores, capacitores e transistores, como pode ser visualizado na seguinte representação:<br><br></div>

![Screenshot](imgs/cgm.png)

<div style='text-align: justify;'> A placa Arduino é responsável pela comunicação entre o circuito e o computador. Essa placa microcontroladora apresenta uma série de pinos de saída e de entrada, além de um processador capaz de rodar o código escrito. Nesse projeto, os pinos de 5V e o GND do Arduino serão ligados aos pinos de 5V e GND do módulo. Já o pino VIN do contador Geiger será ligado diretamente ao pino de interrupção D2 do Arduino.<br><br></div>

![Screenshot](imgs/cgm1.png)

O valor da radiação é contado em CPM e esse valor é exibido no monitor serial da IDE do Arduino.

### Código

- Declaração das variaveis

```cpp
#include <SPI.h>

#define LOG_PERIOD 15000     //Mínimo periodo em  millisegundos. Limite: 15000-60000.
#define MAX_PERIOD 60000    //Máximo periodo em  millisegundos
#define GM 2 //Pino do contador Geiger-Muller

unsigned long counts; //Realiza a contagem

unsigned long cpm;
unsigned int multiplier; 

unsigned long previousMillis;

void tube_impulse(){counts++;}
```

- Setup

```cpp
void setup() {
  //Seta as variaveis com os valores iniciais
  cpm = 0;
  counts = 0;
  previousMillis = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;         
  
  Serial.begin(9600);                                   

  pinMode(GM, INPUT);//Define o pino do módulo como 'input'(leitura)
  digitalWrite(GM, HIGH);//Define um valor inicial como ligado

  attachInterrupt(0, tube_impulse, FALLING);//Interrupção do pino do módulo 
}
```

- Main code

```cpp
void loop() {
  /*
    Caso não ocorra a interrupção e caso se o tempo decorrido seja superior ao valor minimo
    para o tempo necessário para contagem, é impresso o valor do CPM.
  */
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

## A radiação no meio ambiente

<div style='text-align: justify;'> A radiação emitida pelas partículas de determinados elementos químicos pode trazer sérios problemas para o meio ambiente. Esses efeitos já eram estudados durante o século XX, porém, após o lançamento das bombas nucleares em Hiroshima e Nagasaki e a contaminação radioativa resultante de alguns testes nucleares, os efeitos nocivos da radioatividade foram alvos de grande preocupação.<br><br></div>
	
<div style='text-align: justify;'> A exposição a altas doses de radiação ionizante por um período prolongado pode ter efeito carcinogênico e alterar o genoma do indivíduo, além de, em casos de doses muito elevadas, é possível a ocorrência de lesões na pele. Contudo, o maior problema surge a longo prazo, como pode ser visto no caso da usina de Chernobyl, região abandonada desde 1986, quando ocorreu um acidente na sua usina nuclear, liberando grandes quantidades de materiais radioativos para o solo, o ar e os rios da região.<br><br></div>

<div style='text-align: justify;'> Nesses casos de acidentes, as pessoas podem sofrer danos genéticos ou mais diretos. No caso dos danos aos genes, existe a possibilidade de ocorrência de deformações e mutações nos próprios indivíduos ou em seus descendentes, enquanto que os impactos nos corpos expostos diretamente queimaduras, tumores, câncer de órgãos, leucemia e problemas de fertilidade.<br><br></div>

<div style='text-align: justify;'> Os elementos de maior risco são o iodo e o césio radioativos, os quais se constituem de subprodutos da fissão nuclear do Urânio. Essas substâncias apresentam tempos de meia vida relativamente altos, o que causa a sua permanência no meio ambiente por longos períodos de tempo. O iodo-131 tem um tempo de meia vida de, aproximadamente, 8 dias, porém, no caso do césio-137, esse período de meia vida corresponde a cerca de 30 anos.<br><br></div>

<div style='text-align: justify;'> Vale ressaltar que a radiação não impede o crescimento de plantas e outros seres vivos nos ambientes cujos fatores abióticos foram contaminados, todavia, esses seres acabam absorvendo parte desse material, o qual vai adquirindo maior concentração no decorrer da cadeia alimentar por conta do processo biológico de magnificação trófica.</div>
