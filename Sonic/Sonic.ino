#include <hcsr04.h>
#include <SimpleKalmanFilter.h>

#define TRIG_PIN PB8
#define ECHO_PIN PB9

HCSR04 sonic(TRIG_PIN, ECHO_PIN);
SimpleKalmanFilter filter(5, 1.0, 0.01);
void setup()
{

	Serial.begin(115200);
}

void loop()
{
	float dis_measured = (float)(sonic.distanceInMillimeters());
	float dis_estimated = filter.updateEstimate(dis_measured);
	Serial.print(dis_measured);
	Serial.print(",");
	Serial.println(dis_estimated);
	delay(10);
}
