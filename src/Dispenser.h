#include "Servo.h"
#include "Ultrasonic.h"
#include <Arduino.h>

#define PINO_DEFAULT_TRIGGER                            12
#define PINO_DEFAULT_ECHO                               13
#define PINO_DEFAULT_PWM_SERVO                          9
#define QUANTIDADE_DE_VEZES_ACIONA_DISPENSER_DEFAULT    2
#define DISTANCIA_DEFAULT_PARA_VALIDAR_PRESENCA         5

class Dispenser
{

    private:
        Servo *servo;
        Ultrasonic *ultrasonic;
        uint8_t m_pinTriggerSensorUltrasonic;
        uint8_t m_pinEchoSensorUltrasonic;
        uint8_t m_pinPWMServoMotor;
        uint8_t m_quantidadeVezesAcionarDispenser;
        uint8_t m_distanciaEmCentimetrosParaAcionar;

        void configurarSensorUltrasonico(void);
        void configurarServoMotor(void);

    public:

        Dispenser();
        ~Dispenser();

        void setPinTrigger(uint8_t pinTrigger);
        void setPinEcho(uint8_t pinEcho);
        void setPinPWMServo(uint8_t pinServo);
        void setQuantidadeVezesAcionarDispenser(uint8_t quantidade);
        void setDistanciaEmCentimetrosParaAcionar(uint8_t distanciaEmCentimetros);

        void configurarDispenser(void);
        void acionarDispenser(void);
        bool temMaosNaFrenteDoDispenser(void);

};