#include <Arduino.h>
#include <IRremote.h>

// Variáveis do programa
const uint16_t pin_IR_LED = 5; // número do pino para ligar o transmissor IR
const uint16_t pinPotenciometro = A0; // Pino do potenciômetro
int tamanho;  // variável para guardar o número de bytes referente à cor enviada para a pulseira, necessário para a função IRSender

// Código de Cores que será enviado para a pulseira

uint16_t red1[]          = {1400, 1400, 700, 700, 700, 1400, 700, 2800, 700, 2100, 1400, 700, 700, 700, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t red2[]          = {1400, 1400, 700, 700, 700, 2100, 700, 2100, 700, 2800, 700, 700, 700, 700, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t green1[]             = {1400, 1400, 700, 700, 700, 700, 1400, 2800, 700, 1400, 700, 1400, 700, 1400, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t green2[]             = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 1400, 700, 1400, 700, 1400, 700, 1400, 700, 700, 700, 2100, 1400, 2800, 700};
uint16_t blue1[]              = {700, 700, 700, 2100, 1400, 1400, 700, 2100, 700, 1400, 700, 700, 700, 1400, 1400, 700, 700, 1400, 700, 700, 700, 700, 700, 700, 700, 2100, 700};
uint16_t blue2[]              = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 1400, 700, 700, 700, 700, 700, 700, 700, 700, 1400, 1400, 700, 2100, 700};
uint16_t magenta1[]           = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 2100, 1400, 2100, 700, 700, 700, 700, 1400, 2100, 700, 700, 700, 2100, 700};
uint16_t magenta2[]           = {700, 700, 700, 2100, 1400, 1400, 1400, 700, 1400, 1400, 700, 700, 700, 1400, 1400, 700, 700, 1400, 700, 2100, 700, 1400, 1400, 700, 700};
uint16_t magenta3[]           = {700, 700, 700, 2100, 1400, 1400, 1400, 700, 1400, 1400, 700, 700, 700, 1400, 1400, 700, 700, 1400, 700, 2100, 1400, 700, 1400, 700, 700};
uint16_t yellow1[]            = {1400, 1400, 700, 700, 700, 700, 1400, 2800, 700, 2100, 700, 700, 700, 1400, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t yellow2[]            = {700, 700, 700, 2100, 1400, 1400, 700, 2100, 700, 1400, 700, 700, 700, 2800, 1400, 1400, 700, 2100, 1400, 2800, 700};
uint16_t pink1[]              = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 2800, 1400, 1400, 700, 2100, 700, 700, 700, 2100, 700};
uint16_t pink2[]              = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 2100, 1400, 2800, 1400, 1400, 700, 2100, 700, 700, 700, 2100, 700};
uint16_t orange1[]           = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 2100, 700, 700, 700, 1400, 700, 700, 700, 1400, 700, 2100, 1400, 2800, 700};
uint16_t orange2[]           = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 2100, 1400, 2100, 700, 700, 700, 700, 1400, 2100, 1400, 2800, 700};
uint16_t white1[]             = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 2800, 1400, 1400, 700, 2100, 700, 1400, 700, 1400, 700};
uint16_t white2[]             = {700, 700, 700, 2100, 1400, 1400, 1400, 700, 1400, 1400, 700, 700, 700, 2800, 1400, 1400, 700, 700, 1400, 700, 700, 700, 1400, 700, 700};
uint16_t turquoise1[]          = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 1400, 700, 700, 1400, 1400, 700, 1400, 1400, 2800, 700, 700, 700, 2100, 700};
uint16_t turquoise2[]          = {700, 700, 700, 2100, 1400, 1400, 1400, 700, 1400, 1400, 700, 700, 700, 2100, 700, 700, 700, 1400, 700, 700, 700, 700, 700, 1400, 1400, 700, 700};
uint16_t turquoise3[]          = {700, 700, 700, 2100, 1400, 700, 700, 700, 700, 700, 1400, 1400, 700, 700, 700, 2100, 700, 700, 700, 1400, 700, 700, 700, 700, 1400, 700, 1400, 700, 700};
uint16_t off[]                = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() { // ajusta as configurações iniciais
  pinMode(pinPotenciometro, INPUT); // Configura o pino do potenciômetro como entrada
  IrSender.begin(pin_IR_LED); // Inicializa o pino do Arduino que enviará os dados
  IrSender.enableIROut(38);   // Define a frequência da portadora do sinal IR
} // fim das configurações iniciais

void loop() { // loop de execução do programa principal
  // Leitura do valor do potenciômetro
  int valorPotenciometro = analogRead(pinPotenciometro);

  // Mapeia o valor do potenciômetro para escolher a cor
  if (valorPotenciometro == 0) { 
    tamanho = sizeof off / sizeof *off;
    IrSender.sendRaw(off, tamanho, 38);
  } 
  else if (valorPotenciometro < 51.15) { 
    tamanho = sizeof red1 / sizeof *red1;
    IrSender.sendRaw(red1, tamanho, 38);
  }
  else if (valorPotenciometro < 102.3) { 
    tamanho = sizeof red2 / sizeof *red2;
    IrSender.sendRaw(red2, tamanho, 38);
  }
  else if (valorPotenciometro < 153.45) { 
    tamanho = sizeof green1 / sizeof *green1;
    IrSender.sendRaw(green1, tamanho, 38);
  }
  else if (valorPotenciometro < 204.60) { 
    tamanho = sizeof green2 / sizeof *green2;
    IrSender.sendRaw(green2, tamanho, 38);
  }
  else if (valorPotenciometro < 255.75) {
    tamanho = sizeof blue1 / sizeof *blue1;
    IrSender.sendRaw(blue1, tamanho, 38);
  }
  else if (valorPotenciometro < 306.90) { 
    tamanho = sizeof blue2 / sizeof *blue2;
    IrSender.sendRaw(blue2, tamanho, 38);
  }
  else if (valorPotenciometro < 358.05) { 
   tamanho = sizeof magenta1 / sizeof *magenta1;
    IrSender.sendRaw(magenta1, tamanho, 38);
  }
  else if (valorPotenciometro < 409.20) { 
    tamanho = sizeof magenta2 / sizeof *magenta2;
    IrSender.sendRaw(magenta2, tamanho, 38);
  }
   else if (valorPotenciometro < 460.35) { 
    tamanho = sizeof magenta3 / sizeof *magenta3;
    IrSender.sendRaw(magenta3, tamanho, 38);
  }
  else if (valorPotenciometro < 511.50) { 
    tamanho = sizeof yellow1 / sizeof *yellow1;
    IrSender.sendRaw(yellow1, tamanho, 38);
  }
  else if (valorPotenciometro < 562.65) {
    tamanho = sizeof yellow2 / sizeof *yellow2;
    IrSender.sendRaw(yellow2, tamanho, 38);
  }
  else if (valorPotenciometro < 613.80) { 
    tamanho = sizeof pink1 / sizeof *pink1;
    IrSender.sendRaw(pink1, tamanho, 38);
  }
  else if (valorPotenciometro < 664.95) { 
    tamanho = sizeof pink2 / sizeof *pink2;
    IrSender.sendRaw(pink2, tamanho, 38);
  }
  else if (valorPotenciometro < 716.10) {
    tamanho = sizeof orange1 / sizeof *orange1;
    IrSender.sendRaw(orange1, tamanho, 38);
  }
  else if (valorPotenciometro < 767.25) { 
    tamanho = sizeof orange2 / sizeof *orange2;
    IrSender.sendRaw(orange2, tamanho, 38);
  }
  else if (valorPotenciometro < 818.40) { 
    tamanho = sizeof white1 / sizeof *white1;
    IrSender.sendRaw(white1, tamanho, 38);
  }
  else if (valorPotenciometro < 869.55) { 
    tamanho = sizeof white2 / sizeof *white2;
    IrSender.sendRaw(white2, tamanho, 38);
  }
  else if (valorPotenciometro < 920.70) {
    tamanho = sizeof turquoise1 / sizeof *turquoise1;
    IrSender.sendRaw(turquoise1, tamanho, 38);
  }
  else if (valorPotenciometro < 971.85) {
    tamanho = sizeof turquoise2 / sizeof *turquoise2;
    IrSender.sendRaw(turquoise2, tamanho, 38);
  }
  else if (valorPotenciometro < 1023) { 
    tamanho = sizeof turquoise3 / sizeof *turquoise3;
    IrSender.sendRaw(turquoise3, tamanho, 38);
  }


  

  delay(10); // Aguarde um tempo antes de ler novamente o potenciômetro
}
