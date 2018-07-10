// CarLower Controler

//************* Direction Declaration ***************//
//                        ^ y
//                        |
//                --------0--------> x
//                      z |
//                        |
//********** End of Direction Declaration ***********//


//************ Paramaters Definations ***************//

// Not used, wheel distance on width and length, unit in mm
#define WIDTH 560
#define LENGTH 410

//********** End of Paramater Definations ***********//

//********** Data Structure Definations *************//

enum Hoiiru
{
	HIDARIMAE,
	HIDARIUSHIRO,
	MIGIMAE,
	MIGIRIA
};

struct Hiirus
{
	int pwm;
	int d1;
	int d2;
}hidarimae, hidariushiro, migimae, migiria;

//******* End of Data Structure Definations *********//


void Kaiten(Hoiiru h, float value);
void Yosoro(float ekesi, float waii, float dabuyo);


// Debug Mode
void Debug();


// the setup function runs once when you press reset or power the board
void setup() {
	//************** Pin Definations **********************//
	// PWM pin defination
	hidarimae.pwm = PA1;
	hidariushiro.pwm = PA0;
	migimae.pwm = PA7;
	migiria.pwm = PA6;

	// Dir pin defination
	hidarimae.d1 = PA5;
	hidarimae.d2 = PA4;
	hidariushiro.d1 = PC13;
	hidariushiro.d2 = PC14;
	migimae.d1 = PB10;
	migimae.d2 = PB11;
	migiria.d1 = PB1;
	migiria.d2 = PB0;
	//********** End of Pin Definations *******************//

	//***************** PWM Pin Initialization ************//
	pinMode(hidarimae.pwm,  PWM);
	pinMode(hidariushiro.pwm,  PWM);
	pinMode(migimae.pwm,  PWM);
	pinMode(migiria.pwm,  PWM);

	pinMode(hidarimae.d1,  OUTPUT);
	pinMode(hidarimae.d2,  OUTPUT);
	pinMode(hidariushiro.d1,  OUTPUT);
	pinMode(hidariushiro.d2,  OUTPUT);
	pinMode(migimae.d1,  OUTPUT);
	pinMode(migimae.d2,  OUTPUT);
	pinMode(migiria.d1,  OUTPUT);
	pinMode(migiria.d2,  OUTPUT);
	//***************End of PWM Pin Initialization ********//

	//***************** Serial Initialization *************//
	// Debug Serial
	Serial.begin(9600);
	// Data Serial
	Serial2.begin(9600);
	//************** End of Serial Initialization *********//

	//**************** Test for Debug Mode ****************//
	Serial.setTimeout(5000);
	String message = Serial.readString();
	if (message == "")
	{

	}
	else
	{
	Serial.println("In Debug Mode");
	Debug();
	}
	Serial.setTimeout(100);
}

// the loop function runs over and over again forever
void loop() {
	char c = Serial2.read();
    if (c == '0')
	{
		Serial.println("stop");
		Yosoro(0.0, 0.0, 0.0);
		return;
	}
	if (c == '1')
	{
		Serial.println("forward");
		Yosoro(0.0, 0.2, 0.0);
		return;
	}
	if (c == '2')
	{
		Serial.println("backward");
		Yosoro(0.0, -0.2, 0.0);
		return;
	}
	if (c == '3')
	{
		Serial.println("left shift");
		Yosoro(-0.2, 0.0, 0.0);
		return;
	}
	if (c == '4')
	{
		Serial.println("right shift");
		Yosoro(0.2, 0.0, 0.0);
		return;
	}
	if (c == '5')
	{
		Yosoro(0.0, 0.0, 0.2);
		Serial.println("left rotate");
		return;
	}
	if (c == '6')
	{
		Yosoro(0.0, 0.0, -0.2);
		Serial.println("right rotate");
		return;
	}
}


void Yosoro(float ekesi, float waii, float dabuyo)
{
	float hidarimaev = 0.0;
	float hidariushirov = 0.0;
	float migimaev = 0.0;
	float migiriav = 0.0;

	hidarimaev		= waii - ekesi - dabuyo;
	hidariushirov	= waii + ekesi - dabuyo;
	migimaev		= waii + ekesi + dabuyo;
	migiriav		= waii - ekesi + dabuyo;

	Serial.print(hidarimaev);
	Serial.print("\t");
	Serial.print(hidariushirov);
	Serial.print("\t");
	Serial.print(migimaev);
	Serial.print("\t");
	Serial.println(migiriav);

	Kaiten(HIDARIMAE,  hidarimaev);
	Kaiten(HIDARIUSHIRO,  hidariushirov);
	Kaiten(MIGIMAE,  migimaev);
	Kaiten(MIGIRIA,  migiriav);
}

void Kaiten(Hoiiru h, float value)
{
	int pwm = 0;
	int d1 = 0;
	int d2 = 0;
	switch(h)
	{
		case HIDARIMAE:
			pwm = hidarimae.pwm;
			d1 = hidarimae.d1;
			d2 = hidarimae.d2;
			break;
		case HIDARIUSHIRO:
			pwm = hidariushiro.pwm;
			d1 = hidariushiro.d1;
			d2 = hidariushiro.d2;
			break;
		case MIGIMAE:
			pwm = migimae.pwm;
			d1 = migimae.d1;
			d2 = migimae.d2;
			break;
		case MIGIRIA:
			pwm = migiria.pwm;
			d1 = migiria.d1;
			d2 = migiria.d2;
			break;
	}

	if(value > 1.0)
	{
		value = 1.0;
	}
	if(value < -1.0)
	{
		value = -1.0;
	}
	int shinnokachi = (int)(abs(value) * 255);
	if(value > 0)
	{
		digitalWrite(d1,  HIGH);
		digitalWrite(d2,  LOW);
	}
	else if(value < 0)
	{
		digitalWrite(d1,  LOW);
		digitalWrite(d2,  HIGH);
	}
	else
	{
		digitalWrite(d1,  LOW);
		digitalWrite(d2,  LOW);
	}

	analogWrite(pwm, shinnokachi);
}

void Debug()
{
	 Serial.println("forward");
	 Yosoro(0.0,  0.2,  0.0);
	 delay(1000);
	 Yosoro(0.0,  0.0,  0.0);
	 delay(300);

	 Serial.println("backward");
	 Yosoro(0.0,  -0.2,  0.0);
	 delay(1000);
	 Yosoro(0.0,  0.0,  0.0);
	 delay(300);

	 Serial.println("right");
	 Yosoro(0.2,  0.0,  0.0);
	 delay(1000);
	 Yosoro(0.0,  0.0,  0.0);
	 delay(300);

	 Serial.println("left");
	 Yosoro(-0.2,  0.0,  0.0);
	 delay(1000);
	 Yosoro(0.0,  0.0,  0.0);
	 delay(300);

	 Serial.println("left rot");
	 Yosoro(0.0,  0.0,  0.2);
	 delay(1000);
	 Yosoro(0.0,  0.0,  0.0);
	 delay(300);

	 Serial.println("right rot");
	 Yosoro(0.0,  0.0,  -0.2);
	 delay(1000);
	 Yosoro(0.0,  0.0,  0.0);
	 delay(300);
}
