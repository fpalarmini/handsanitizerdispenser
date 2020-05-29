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
}

/**
 * @brief Destroy the Dispenser:: Dispenser object
 * 
 */
Dispenser::~Dispenser()
{
    delete servo;
    delete ultrasonic;
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
 * @brief Aciona o dispenser de acordo com a quantidade de vezes previamente setada
 * 
 */
void Dispenser::acionarDispenser(void)
{
    servo->attach(m_pinPWMServoMotor);  // attaches the servo on pin 9 to the servo object

    for (int i = 0; i < m_quantidadeVezesAcionarDispenser; i++)
    {
        delay(500);                           // waits for the servo to get there
        servo->write(60);
        delay(500);
        servo->write(0);  
    }

    servo->detach();

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