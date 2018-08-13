// CarLower Controler

// Direction Declaration *********************** {{{
//                        ^ y
//                        |
//                --------0--------> x
//                      z |
//                        |
// EO Direction Declaration ******************** }}}

// INCLUDE ************************************* {{{

#include "MCP23S17.h"


// EO_INCLUDE ************************************** }}}

// Definations ********************** {{{

// Not used, wheel distance on width and length, unit in mm
#define WIDTH 560
#define LENGTH 410

// Command definations
#define MOVE_STOP           Yosoro(0.0,0.0,0.0)
#define MOVE_FORWARD        Yosoro(0.0,fMoveVelocity,0.0)
#define MOVE_BACKWARD       Yosoro(0.0,-fMoveVelocity,0.0)
#define MOVE_LEFT_ROTATE    Yosoro(0.0,0.0,fMoveVelocity)
#define MOVE_RIGHT_ROTATE   Yosoro(0.0,0.0,-fMoveVelocity)
#define MOVE_LEFT_SHIFT     Yosoro(-fMoveVelocity,0.0,0.0)
#define MOVE_RIGHT_SHIFT    Yosoro(fMoveVelocity,0.0,0.0)
#define TRACKING       7

// EO Paramater Definations ******************** }}}

// Data Structure Definations ****************** {{{

enum Shu
{
	STOP,
	RC_FORWARD,
	RC_BACKWARD,
	RC_LEFT_ROTATE,
	RC_RIGHT_ROTATE,
	RC_LEFT_SHIFT,
	RC_RIGHT_SHIFT,
	TRACK,
};
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

// End of Data Structure Definations *********** }}}

// Global Variables **************************** {{{
Shu shuCurrentState = STOP;
char cCommand = '0';
float  fMoveVelocity = 0.2;
String sCommands[] = {"stop", "forward", "backward", "left_rotate", "right_rotate", "left_shift", "right_shift", "tracking"};
MCP tracker(0, PB7);
// EO Global Variables ************************* }}}

void Track();
void Kaiten(Hoiiru h, float value);
void Yosoro(float ekesi, float waii, float dabuyo);


// Debug Mode
void Debug();


// the setup function runs once when you press reset or power the board
void setup() {
	// Pin Initialization ****************** {{{
	// PWM pin defination ******************* {{{
	hidarimae.pwm = PA1;
	hidariushiro.pwm = PA0;
	migimae.pwm = PA7;
	migiria.pwm = PA6;
	// EO PWM pin defination **************** }}}

	// Dir pin defination ******************* {{{
	hidarimae.d1 = PA5;
	hidarimae.d2 = PA4;
	hidariushiro.d1 = PC13;
	hidariushiro.d2 = PC14;
	migimae.d1 = PB10;
	migimae.d2 = PB11;
	migiria.d1 = PB1;
	migiria.d2 = PB0;
	// End of Pin Definations *************** }}}

	// PWM Pin Initialization ************** {{{
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
	// EO PWM Pin Initialization *********** }}}

	// Serial Initialization *************** {{{
	// Debug Serial
	Serial.begin(115200);
	// Data Serial
	Serial2.begin(115200);
	// EO Serial Initialization ************ }}}
	tracker.begin();
	// EO Pin Initialization *************** }}}

	tracker.pinMode(0xFFFF);
	tracker.pullupMode(0xFFFF);
	tracker.inputInvert(0x0000);

	//**************** Test for Debug Mode ****************//
	Serial.setTimeout(5);
	Serial2.setTimeout(5);
}

// the loop function runs over and over again forever
void loop() {
	//delay(500);
	Serial.println("online");
	cCommand = Serial2.read();
	Serial.println("command: " + String(cCommand));
	if (isDigit(cCommand))  // IS a movement command
	{
		switch(cCommand)
		{
			case '0':
				MOVE_STOP;
				shuCurrentState = STOP;
				break;
			case '1':
				MOVE_FORWARD;
				shuCurrentState = RC_FORWARD;
				break;
			case '2':
				MOVE_BACKWARD;
				shuCurrentState = RC_BACKWARD;
				break;
			case '3':
				MOVE_LEFT_ROTATE;
				shuCurrentState = RC_LEFT_ROTATE;
				break;
			case '4':
				MOVE_RIGHT_ROTATE;
				shuCurrentState = RC_RIGHT_ROTATE;
				break;
			case '5':
				MOVE_LEFT_SHIFT;
				shuCurrentState = RC_LEFT_SHIFT;
				break;
			case '6':
				MOVE_RIGHT_SHIFT;
				shuCurrentState = RC_RIGHT_SHIFT;
				break;

			default:
				MOVE_STOP;
		}
	}
	else  // Is a action command.
	{
		switch(cCommand)
		{
			case 'T':
				shuCurrentState = TRACK;
				break;
		}
	}
	switch(shuCurrentState)
	{
		case TRACK:
				Track();
	}
	//Serial.println(sCommands[constrain(String(shuCurrentState).toInt(), 0, 7)]);
	//cCommand = '0';
}

void Track()
{
	int t = 0;
	for(int a = 4; a < 8; a++)
	{
		t |= tracker.digitalRead(a) & 0x01;
		t = t << 1;
	}
	t = t >> 1;
	t = t & 0x0F;
	if(t == 0x0F)
	{
		MOVE_STOP;
	}
	if((t == 0x0C) || (t == 0x08) || (t == 0x04))
	{
		MOVE_RIGHT_ROTATE;
	}
	if((t == 0x01) || (t == 0x02) || (t == 0x03))
	{
		MOVE_LEFT_ROTATE;
	}
	else 
	{
		MOVE_FORWARD;
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
