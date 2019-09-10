#include <IRremote.h>
/* ir sensor's facing you (First check his datasheet):
 *  in my case:
 * - 1st pin connected to 5v
 * - 2nd pin connected to GND
 * - 3rd pin connected to Dpin 3 (PWM)
 */
int RECV_PIN = 3;//(PWM)
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(String(results.value, HEX));
    irrecv.resume();
  }
}
