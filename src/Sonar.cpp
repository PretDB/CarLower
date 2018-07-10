#include <hcsr04.h>
#include <SimpleKalmanFilter.h>

#include "Point.h"
#include "Vector.h"


#ifdef TRIG_PIN
#ifdef ECHO_PIN
HCSR04 sonic(TRIG_PIN, ECHO_PIN);
#else
#error ECHO_PIN NOT DEFIEND
#endif
#else
#error TRIG_PIN NOT DEFIEND
#endif

SimpleKalmanFilter filter(5, 1.0, 0.01);


void loop()
{
	float dis_measured = (float)(sonic.distanceInMillimeters());
	float dis_estimated = filter.updateEstimate(dis_measured);
	Serial.print(dis_measured);
	Serial.print(",");
	Serial.println(dis_estimated);
	delay(10);
}
