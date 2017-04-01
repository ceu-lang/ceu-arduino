/*
 Find The Right Spot

 Game where one needs to find the correct spot in a sensor
 (used trimpot when testing, but could be substituted for any
 other analog sensor).

 If the player misses too many times or takes too long, he/she
 loses!

 Author: Guilherme Simas <github.com/guilhermesimas>

 Date: 01.apr.2017
 */

// Game settings
const int MAX_TIME = 30;
const int MAX_NUMBER_ATTEMPTS = 5;
const int TIME_WARNING_INTERVAL = 5;

// Inputs
const int BUTTON = 2;
const int SENSOR = A0;

// Pin used for generating random value
const int SEED_GENERATOR = A1;

// Variables changed in interrupt sections of code
volatile int position_raw = 0;
volatile bool buttonWasPressed;

// Control variables for game
int correct_position = 0;
int number_of_attempts = 0;
int time_elapsed = 0;
bool gameOver = false;

// Used for timing purposes
unsigned long previous_time = 0;

void setup() {
	// Input configuration
	pinMode( BUTTON, INPUT );
	pinMode( SENSOR, INPUT );
	pinMode ( SEED_GENERATOR, INPUT );

	// Setting up interrupt associated with button
	attachInterrupt( digitalPinToInterrupt( BUTTON ), buttonPressed, RISING );

	// Configuring Serial interface
	Serial.begin( 9600 );

	// Game instructions message
	Serial.println( "Try to find the correct position! You have 5 attempts and 30 seconds!" );

	// Getting random position (positions go from 0-8)
	randomSeed( analogRead( SEED_GENERATOR ) );
	correct_position = random( 8 );

	// Getting start time for timing purposes
	previous_time = millis();

}

void loop() {
	// Game control flag
	if ( !gameOver ) {
		// If interrupt ocurred
		if ( buttonWasPressed ) {
			// Gets the position the player submitted and
			// gives feedback accordingly
			buttonWasPressed = false;
			int position = treatValue( position_raw );
			int difference = correct_position - position;
			printHintMessage( difference );
			number_of_attempts++;
			// If player exceeded max attempts, game over
			if ( number_of_attempts == MAX_NUMBER_ATTEMPTS + 1 ) {
				gameOver = true;
			}
		}
		unsigned long current_time = millis();
		// If enough time elapsed, warn player of time
		if ( current_time - previous_time >= TIME_WARNING_INTERVAL * 1000 ) {
			previous_time = current_time;
			time_elapsed += TIME_WARNING_INTERVAL;
			// If time's up, game over
			if ( time_elapsed == current_time ) {
				gameOver = true;
			}
			Serial.print( MAX_TIME - time_elapsed );
			Serial.println( " seconds remaining!" );
		}
	}
}



// Interrupt handling routine
void buttonPressed() {
	// Debounce button (check state after to make sure it wasnt a false press)
	delay( 30 );
	int buttonState = digitalRead( BUTTON );
	if ( buttonState == LOW ) {
		return;
	}
	position_raw = analogRead( SENSOR );
	// Sets flag so main loop knows interrupt happened and values are ready
	buttonWasPressed = true;

}

// Data processing function
int treatValue( int raw_value ) {
	return raw_value >> 7;
}

void printVictoryMessage() {
	Serial.println( "Spot on! You won!" );
	printEndMessage();
}

void printEndMessage( ) {
	Serial.println( "<press reset button to play again>"  );
}

void printTimesUpMessage() {
	Serial.println( "Time's up! You lost!" );
	printEndMessage();

}

void printTooManyAttemptsMessage() {
	Serial.println( "Too many attemps! You lost!" );
	printEndMessage();

}

// Receives the signed difference between the correct position
// and the position the player submitted, giving feedback appropriately
void printHintMessage( int difference ) {
	if ( difference == 0 ) {
		printVictoryMessage();
		gameOver = true;
		return;
	}
	if ( difference < 0 ) {
		Serial.println( "Too far right!" );
		return;
	}
	Serial.println( "Too far left!" );
	return;
}
