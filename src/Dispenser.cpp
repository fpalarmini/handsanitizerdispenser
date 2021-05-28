#include "Dispenser.h"

/**
 * @brief Construct a new Dispenser:: Dispenser object
 * 
 */
Dispenser::Dispenser()
{
    m_pinPWMServoMotor = PINO_DEFAULT_PWM_SERVO;
    m_pinEchoSensorUltrasonic = PINO_DEFAULT_ECHO;
    m_pinTriggerSensorUltrasonic = PINO_DEFAULT_TRIGGER;
    m_distanciaEmCentimetrosParaAcionar = DISTANCIA_DEFAULT_PARA_VALIDAR_PRESENCA;
    m_quantidadeVezesAcionarDispenser = QUANTIDADE_DE_VEZES_ACIONA_DISPENSER_DEFAULT;
    m_pinLED = PINO_DEFAULT_LED;
    m_pinBuzzer = PINO_DEFAULT_BUZZER;
    m_possuiSensorTemperatura = false;
}

/**
 * @brief Destroy the Dispenser:: Dispenser object
 * 
 */
Dispenser::~Dispenser()
{
    delete servo;
    delete ultrasonic;
    delete sensorTemperatura;
}

/**
 * @brief Seta o pino do trigger do sensor HC-SR04
 * 
 * @param pinTrigger 
 */
void Dispenser::setPinTrigger(uint8_t pinTrigger)
{
    m_pinTriggerSensorUltrasonic = pinTrigger;
}

/**
 * @brief Seta o pino de Echo do sensor HC-SR04
 * 
 * @param pinEcho 
 */
void Dispenser::setPinEcho(uint8_t pinEcho)
{
    m_pinEchoSensorUltrasonic = pinEcho;
}

/**
 * @brief Seta o pino de PWM para acionar o servo motor
 * 
 * @param pinServo 
 */
void Dispenser::setPinPWMServo(uint8_t pinServo)
{
    m_pinPWMServoMotor = pinServo;
}

/**
 * @brief Seta o pino de LED para alarme de temperatura
 * 
 * @param pinLED
 */ 
void Dispenser::setPinLED(uint8_t pinLED)
{
    m_pinLED = pinLED;
}

/**
 * @brief Seta o pino de buzzer para alarme de temperatura
 *
 *  @param pinBuzzer
 */ 
void Dispenser::setPinBuzzer(uint8_t pinBuzzer)
{
    m_pinBuzzer = pinBuzzer;
}

/**
 * @brief Seta se possui sensor de temperatura para funcionar alarme
 *
 * @para possuiSensorTemperatura
 */ 
void Dispenser::setPossuiSensorTemperatura(bool possuiSensorTemperatura)
{
    m_possuiSensorTemperatura = possuiSensorTemperatura;
}

/**
 * @brief Seta a quantidade de vezes que irá acionar o dispenser quando detectar 
 * presença
 * 
 * @param quantidade 
 */
void Dispenser::setQuantidadeVezesAcionarDispenser(uint8_t quantidade)
{
    m_quantidadeVezesAcionarDispenser = quantidade;
}

/**
 * @brief Seta a distância em centímetros válida para acionar o dispenser
 * 
 * @param distanciaEmCentimetros 
 */
void Dispenser::setDistanciaEmCentimetrosParaAcionar(uint8_t distanciaEmCentimetros)
{
    m_distanciaEmCentimetrosParaAcionar = distanciaEmCentimetros;
}

/**
 * @brief Configura os sensores e servos utilizados no dispenser
 * 
 */
void Dispenser::configurarDispenser(void)
{
    configurarSensorUltrasonico();
    configurarServoMotor();

    if (m_possuiSensorTemperatura)
    {
	 pinMode(m_pinBuzzer, OUTPUT);
	 pinMode(m_pinLED, OUTPUT);
         configurarSensorTemperatura();
    }

}

/**
 * @brief Configura o sensor ultrassônico HC-SR04
 * 
 */
void Dispenser::configurarSensorUltrasonico(void)
{
    ultrasonic = new Ultrasonic(m_pinTriggerSensorUltrasonic, m_pinEchoSensorUltrasonic);
}

/**
 * @brief Configura o servo motor
 * 
 */
void Dispenser::configurarServoMotor(void)
{
    servo = new Servo();
}

/**
 * @brief Configura o sensor de temperatura
 */ 
void Dispenser::configurarSensorTemperatura(void)
{
    sensorTemperatura = new IRTherm();
    sensorTemperatura->begin();
    sensorTemperatura->setUnit(TEMP_C);
}

/**
 * @brief Aciona o dispenser de acordo com a quantidade de vezes previamente setada
 * 
 */
void Dispenser::acionarDispenser(void)
{
    bool flagAlertaTemperatura{ false };

    servo->attach(m_pinPWMServoMotor);  // attaches the servo on pin 9 to the servo object
    if (m_possuiSensorTemperatura)
    {
	if (sensorTemperatura->read())
        {
	    if (sensorTemperatura->object() > 37.5)
	    {
                flagAlertaTemperatura = true;
	        tone(m_pinBuzzer, 1500);
	        digitalWrite(m_pinLED, HIGH);
	    }
	}
    }
 
    for (int i = 0; i < m_quantidadeVezesAcionarDispenser; i++)
    {
        delay(500);                           // waits for the servo to get there
        servo->write(60);
        delay(500);
        servo->write(0);  
    }

    servo->detach();

    if (flagAlertaTemperatura)
    {
        noTone(m_pinBuzzer);
	digitalWrite(m_pinLED, LOW);
    }
}

/**
 * @brief Retorna se tem presença na frente do dispenser
 * 
 * @return true 
 * @return false 
 */
bool Dispenser::temMaosNaFrenteDoDispenser(void)
{
    float centimetrosDeDistancia;

    centimetrosDeDistancia = ultrasonic->convert(ultrasonic->timing(), Ultrasonic::CM);

  if (centimetrosDeDistancia < m_distanciaEmCentimetrosParaAcionar)
  {
      return true;
  }
  return false;
}
