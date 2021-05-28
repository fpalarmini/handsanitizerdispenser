#include <Dispenser.h>

Dispenser dispenser;        // Cria um objeto Dispenser

void setup()
{
    Serial.begin(9600);
    dispenser.setDistanciaEmCentimetrosParaAcionar(5);
    dispenser.setPinEcho(13);
    dispenser.setPinTrigger(12);
    dispenser.setPinLED(8);
    dispenser.setPinBuzzer(10);
    dispenser.setPossuiSensorTemperatura(true);
    dispenser.setQuantidadeVezesAcionarDispenser(2);
    dispenser.configurarDispenser();
}

void loop()
{
    //verifica se há presença no sensor ultrasônico
    if (dispenser.temMaosNaFrenteDoDispenser())
    {
        Serial.println("Acionar dispenser!");
        //aciona o dispenser
        dispenser.acionarDispenser();
    }

    delay(500);
}
