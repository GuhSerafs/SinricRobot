/* ================== INTEGRANTES: ==================
 * Gustavo Duarte Serafim - R.A: 11054016
 * Matheus Ribeiro Barison Martins Silva - R.A: 11201721624
 * Pedro Henrique Pereira - R.A: 11109016
 * ================================================= */


#include <ESP8266WiFi.h>
#include <Sinric.h>
#include <SinricSwitch.h>

// Defines do projeto

#define SERIAL_BAUDRATE     115200

// Definição das portas p/ seleção das peças em BCD
#define BIT0  D0
#define BIT1  D1
#define BIT2  D2
#define BIT3  D3

// Definição das portas p/ sinais de controle
#define DIR D5
#define JOGAR D6

// Contante de qtde de peças
#define QTDE_PECAS 16

// Definição da API-KEY
#define API_KEY "define_yours"

// Definição da ID das peças
#define ID_PECA_01 "define_yours""
#define ID_PECA_02 "define_yours"
#define ID_PECA_03 "define_yours"
#define ID_PECA_04 "define_yours"
#define ID_PECA_05 "define_yours"
#define ID_PECA_06 "define_yours"
#define ID_PECA_07 "define_yours"
#define ID_PECA_08 "define_yours"
#define ID_PECA_09 "define_yours"
#define ID_PECA_10 "define_yours"
#define ID_PECA_11 "define_yours"
#define ID_PECA_12 "define_yours"
#define ID_PECA_13 "define_yours"
#define ID_PECA_14 "define_yours"
#define ID_PECA_15 "define_yours"
#define ID_PECA_16 "define_yours"

// Definição das IDs dos sinais de controle
#define ID_DIREITA "define_yours"
#define ID_ESQUERDA "define_yours"

// Definição auxiliar para inverter a lógica das 
// portas digitais na hora de acionar o relè.
// Como o relè é ativo em LOW, definimos:
// ON -> LOW
// OFF -> HIGH
#define OFF HIGH
#define ON LOW

// Delay para o status de aguardar... [ver status_jogada]
#define INTERVALO_AGUARDAR 1000

// Declaração da variável de controle da peça selecionada...
enum peca {
  pc_01, pc_02, pc_03, pc_04, pc_05, pc_06, pc_07, pc_08, pc_09, pc_10, pc_11, pc_12, pc_13, pc_14, pc_15, pc_16,
} peca_selecionada;

enum direcao {
  nenhuma, esquerda, direita
} direcao_jogada;

enum status_jogada {
  repouso, inicializar, aguardar, finalizar,
} stt_pc[QTDE_PECAS], stt_dir, stt_esq;

//Variáveis de tempo que serão usada para guardar o valor do instante em que cada comando será inicializado.
unsigned long int t_init[QTDE_PECAS]; 
unsigned long int t_init_dir;
unsigned long int t_init_esq;

// To Do: Put in your credentials
const char* ssid = "YOUR_SSID";
const char* pass = "YOUR_PWD";

// Declaração dos objetos (switches)
SinricSwitch *peca[QTDE_PECAS];
SinricSwitch *dir;
SinricSwitch *esq;

// IDS
char peca_ID[QTDE_PECAS][25] = {
  ID_PECA_01, ID_PECA_02, ID_PECA_03, ID_PECA_04, 
  ID_PECA_05, ID_PECA_06, ID_PECA_07, ID_PECA_08, 
  ID_PECA_09, ID_PECA_10, ID_PECA_11, ID_PECA_12, 
  ID_PECA_13, ID_PECA_14, ID_PECA_15, ID_PECA_16,
};

// callbacks dos switches
void pc_01_callback(const String& deviceId, bool state) {
  // Código do usuário
    if(state){
      stt_pc[pc_01] = inicializar;
    }else{
      stt_pc[pc_01] = finalizar;
    }
  //Retorna
}

void pc_02_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_02] = inicializar;
    }else{
      stt_pc[pc_02] = finalizar;
    }
}

void pc_03_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_03] = inicializar;
    }else{
      stt_pc[pc_03] = finalizar;
    }
}

void pc_04_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_04] = inicializar;
    }else{
      stt_pc[pc_04] = finalizar;
    }
}

void pc_05_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_05] = inicializar;
    }else{
      stt_pc[pc_05] = finalizar;
    }
}

void pc_06_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_06] = inicializar;
    }else{
      stt_pc[pc_06] = finalizar;
    }
}

void pc_07_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_07] = inicializar;
    }else{
      stt_pc[pc_07] = finalizar;
    }
}

void pc_08_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_08] = inicializar;
    }else{
      stt_pc[pc_08] = finalizar;
    }
}

void pc_09_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_09] = inicializar;
    }else{
      stt_pc[pc_09] = finalizar;
    }
}

void pc_10_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_10] = inicializar;
    }else{
      stt_pc[pc_10] = finalizar;
    }
}

void pc_11_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_11] = inicializar;
    }else{
      stt_pc[pc_11] = finalizar;
    }
}

void pc_12_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_12] = inicializar;
    }else{
      stt_pc[pc_12] = finalizar;
    }
}

void pc_13_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_13] = inicializar;
    }else{
      stt_pc[pc_13] = finalizar;
    }
}

void pc_14_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_14] = inicializar;
    }else{
      stt_pc[pc_14] = finalizar;
    }
}

void pc_15_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_15] = inicializar;
    }else{
      stt_pc[pc_15] = finalizar;
    }
}

void pc_16_callback(const String& deviceId, bool state) {
    if(state){
      stt_pc[pc_16] = inicializar;
    }else{
      stt_pc[pc_16] = finalizar;
    }
}

void direita_callback(const String& deviceId, bool state) {
    if(state){
      stt_dir = inicializar;
    }else{
      stt_dir = finalizar;
    }
}

void esquerda_callback(const String& deviceId, bool state) {
    if(state){
      stt_esq = inicializar;
    }else{
      stt_esq = finalizar;
    }
}


// WiFi setup
void setupWifi() {
  Serial.begin(115200); 
  delay(1000);
  Serial.printf("\r\nConnecting WiFi (%s)", ssid);

  WiFi.persistent(false);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("connected!\r\n");

  IPAddress localIP = WiFi.localIP();
  Serial.printf("IP address: %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

// Sinric setup
void setupSinric() {
  Serial.print("Connecting Sinric");
  Sinric.begin(API_KEY);
  while (!Sinric.isConnected()) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("connected!");

  // Cria os objetos Sinric Switches, cada um com sua ID
  for(int pc = pc_01; pc <= pc_16; pc++){
    peca[pc] = &Sinric.add<SinricSwitch>(peca_ID[pc]);
  }
  dir = &Sinric.add<SinricSwitch>(ID_DIREITA);
  esq = &Sinric.add<SinricSwitch>(ID_ESQUERDA);
    
  // Passa a referência da função de callback para cada switch
  peca[pc_01]->onPowerState(pc_01_callback);
  peca[pc_02]->onPowerState(pc_02_callback);
  peca[pc_03]->onPowerState(pc_03_callback);
  peca[pc_04]->onPowerState(pc_04_callback);
  peca[pc_05]->onPowerState(pc_05_callback);
  peca[pc_06]->onPowerState(pc_06_callback);
  peca[pc_07]->onPowerState(pc_07_callback);
  peca[pc_08]->onPowerState(pc_08_callback);
  peca[pc_09]->onPowerState(pc_09_callback);
  peca[pc_10]->onPowerState(pc_10_callback);
  peca[pc_11]->onPowerState(pc_11_callback);
  peca[pc_12]->onPowerState(pc_12_callback);
  peca[pc_13]->onPowerState(pc_13_callback);
  peca[pc_14]->onPowerState(pc_14_callback);
  peca[pc_15]->onPowerState(pc_15_callback);
  peca[pc_16]->onPowerState(pc_16_callback);
  dir->onPowerState(direita_callback);
  esq->onPowerState(esquerda_callback);
}

void setup() {
  delay(1000);
  Serial.begin(115200); 
  Serial.println();

  // Setup das saídas
  pinMode(BIT0, OUTPUT);
  pinMode(BIT1, OUTPUT);
  pinMode(BIT2, OUTPUT);
  pinMode(BIT3, OUTPUT);

  pinMode(DIR, OUTPUT);
  pinMode(JOGAR, OUTPUT);

  digitalWrite(BIT0, HIGH);
  digitalWrite(BIT1, HIGH);
  digitalWrite(BIT2, HIGH);
  digitalWrite(BIT3, HIGH);

  digitalWrite(DIR, HIGH);
  digitalWrite(JOGAR, HIGH);
  
  setupWifi();
  setupSinric();
}

void loop() {
  Sinric.handle();

  // Tarefa 2 - Realizar o protocolo p/ peças
  for (int pc = pc_01; pc <= pc_16; pc++) {
    switch (stt_pc[pc]) {
      case repouso:
        // Não faz nada...
        break;
      case inicializar:
        //Carregar o valor nas digitais
        t_init[pc] = millis();
        carregar_peca(pc);
        //Setar o JOGAR
        digitalWrite(JOGAR, ON);
        stt_pc[pc] = aguardar;
        break;
      case aguardar:
        //Aguarda o tempo necessário
        if (millis() - t_init[pc] > INTERVALO_AGUARDAR) stt_pc[pc] = finalizar;
        break;
      case finalizar:
        digitalWrite(JOGAR, OFF);
        carregar_peca(0); //Desliga todos os relês...
        //fauxmo.setState(nome_da_saida[pc], false, 0);
        stt_pc[pc] = repouso;
        break;
    }
  }

  // Tarefa 3 - Realizar o protocolo p/ esquerda ou direita
  switch (stt_dir) {
    case repouso:
      break;
    case inicializar:
      direcao_jogada = nenhuma;
      t_init_dir = millis();
      digitalWrite(DIR, ON);
      digitalWrite(JOGAR, ON);
      stt_dir = aguardar;
      break;
    case aguardar:
      if (millis() - t_init_dir > INTERVALO_AGUARDAR) stt_dir = finalizar;
      break;
    case finalizar:
      digitalWrite(JOGAR, OFF);
      digitalWrite(DIR, OFF);
      stt_dir = repouso;
      //fauxmo.setState(ID_DIREITA, false, 0);
      break;
  }

  switch (stt_esq) {
    case repouso:
      break;
    case inicializar:
      direcao_jogada = nenhuma;
      t_init_esq = millis();
      digitalWrite(DIR, OFF); //ESQ = ~DIR
      digitalWrite(JOGAR, ON);
      stt_esq = aguardar;
      break;
    case aguardar:
      if (millis() - t_init_esq > INTERVALO_AGUARDAR) stt_esq = finalizar;
      break;
    case finalizar:
      digitalWrite(JOGAR, OFF);
      //digitalWrite(DIR, OFF);
      stt_esq = repouso;
      //fauxmo.setState(ID_ESQUERDA, false, 0);
      break;
  }
}

void carregar_peca(int peca) {
  // Função responsável por receber o valor da peça e transformá-lo em
  //um valor binário nas saídas digitais.
  digitalWrite(BIT0, !(peca & 1));
  digitalWrite(BIT1, !(peca & 2));
  digitalWrite(BIT2, !(peca & 4));
  digitalWrite(BIT3, !(peca & 8));
}
