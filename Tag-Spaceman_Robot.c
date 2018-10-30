#pragma config(Sensor, S3,     soundFront,				sensorSoundDB)
#pragma config(Sensor, S4,     frontTouch,         sensorTouch)
#pragma config(Sensor, S2,     backTouch,         sensorTouch)
#pragma config(Sensor, S1,     soundBack,     sensorSoundDB)
#pragma config(Motor,  motorB,          rightServo,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftServo,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorA,          theHammer,     tmotorNXT, PIDControl, encoder)


// Global Variables defined here

int distanceThreshold = 24;

int close_speed = 25;

int close_time = 900;

int driving_speed = 50;

int normal_speed = 70;

int slow_driving_speed = 30;

int active_driving = 1;

bool is_driving = true;

int soundThreshold = 70;

// hitThreshold is FRONT Sensor
int hitThreshold = 25;

// aThreshold is FRONT Sensor
int aThreshold = 25;

// bThreshold is BACK Sensor
int bThreshold = 25;

// if switcher == 0, turn left
// if switcher == 1, turn right
int switcher = 0;

int behavioral_state = 0;


// FUNCTIONS


void speak_loudly() {
	wait1Msec(100);
	PlaySound(soundUpwardTones);
	PlaySound(soundUpwardTones);
    PlaySound(soundException);
	wait1Msec(100);
}

void celebrate_noise() {
	wait1Msec(300);
	PlaySound(soundBeepBeep);
	PlaySound(soundDownwardTones);
	PlaySound(soundFastUpwardTones);
	wait1Msec(300);
}

void ring_bell() {

	motor[theHammer] = -40;
	wait1Msec(290);
	motor[theHammer] = 0;
	wait1Msec(300);
	motor[theHammer] = 20;
	wait1Msec(550);
	motor[theHammer] = 0;
	wait1Msec(300);
}



void turn(int rightSpeed, int leftSpeed)
{
  motor[rightServo] = -rightSpeed;	// set mtr_S1_C1_1 to speed, 'rightSpeed'
  motor[leftServo]  = -leftSpeed;   	// set mtr_S1_C1_2 to speed, 'leftSpeed'
}


void SetBothMotors(int speed)
{
  motor[leftServo] = -speed;
  motor[rightServo] = -speed;
}

void make_stop() {
	SetBothMotors(0);
  wait1Msec(500);
}

void turn_left() {
	turn(50, 0);
	wait1Msec(600);
	make_stop();
}

void turn_right() {
	turn(0, 50);
	wait1Msec(600);
	make_stop();
}

void turn_switch() {

	turn_left();

}

void rotate_in_place() {
	turn(-40, 40);
	wait1Msec(400);
	make_stop();
}

void quick_backup() {

	// back up a little to get away from what hit us
	SetBothMotors(-driving_speed);
 	wait1Msec(500);
 	motor(rightServo) = 0;
 	motor(leftServo) = 0;
 	wait1Msec(200);

}

void quicker_backup() {

	// back up a little to get away from what hit us
	SetBothMotors(-driving_speed);
 	wait1Msec(500);

}

void short_left() {
	turn(30, -30);
	wait1Msec(400);
	make_stop();
}

void quick_forward() {

	// back up a little to get away from what hit us
  SetBothMotors(driving_speed);
 	wait1Msec(500);

 	SetBothMotors(0);
 	wait1Msec(200);

}

void hide_somewhere() {

  SetBothMotors(driving_speed);

 	while(true) {

		if(SensorValue(frontTouch) == 1) {
			make_stop();
			quick_backup();
			wait1Msec(500);
			break;
		}
		else {
			// do nothing - just keep driving
			//return;
		}
		// note no code here to do anything is backTouch is pressed
		wait1Msec(300);
	}

	rotate_in_place();

}


// TASKS

// default function running when Robot is it - just moves forward
// this will be stopped when Robot needs to do something specific, then switched back on.
task Drive_Forward()
{
	wait1Msec(500);

	if(true) {
		SetBothMotors(normal_speed);

 		wait1Msec(200);
  }
  wait1Msec(200);
}


// This task is the "brains" of the Robot's functioning.
// This monitors the front and back bump sensors and directs behavior accordingly.
// There are two main behavioral states - "it" and "not it"
task Bump_Watch()
{
	wait1Msec(300);

	// behavioral_state
	// 1 means "it" - Puck is "it" and must pursue other robots
	// 2 means "not it" - Puck is "not it" and must run/hide to avoid being tagged by the "it" robot

	while(true)
		{
			// Robot is  "not it"
			if(behavioral_state == 2) {
				// robot hides (function hide_somewhere) before starting this code. At this point it is sitting quietly "hiding" from the "it" robot.

				// Something presses Front Sensor
				//////////////////////////////////////////////
				// if bump is struck while there is a loud noise - could be a fellow robot!
		  	if(SensorValue(frontTouch) == 1)  {

		  	  wait1Msec(200);

		  	  int soundVal1 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal2 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal3 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal4 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal5 = SensorValue[soundFront];
		  	  wait1Msec(1000);


		  	  if((soundVal1 > aThreshold) || (soundVal2 > aThreshold) || (soundVal3 > aThreshold) || (soundVal4 > aThreshold) || (soundVal5 > aThreshold)) {
		  	  	ring_bell();
		  	  	// another round, just to be sure
		  	  	wait1Msec(700);

		  	  	int soundVal6 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal7 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal8 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal9 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal10 = SensorValue[soundFront];
		  	  	wait1Msec(1000);

		  	  	if((soundVal6 > aThreshold) || (soundVal7 > aThreshold) || (soundVal8 > aThreshold) || (soundVal9 > aThreshold) || (soundVal10 > aThreshold)) {
		  	  		ring_bell();
		  	  		// robot has been tagged. It is now "it"!
		  				wait1Msec(3000);
		  				speak_loudly();
		  				quick_backup();
		  				turn_switch();
		  				StartTask(Drive_Forward);
		  				behavioral_state = 1;
		  				continue;
						} else {
							// do nothing
						}
		  		} else {
		  			// do nothing
		  		}
		  	}


				//////////////////////////////////////////////

				// Something presses Back Sensor
				//////////////////////////////////////////////
				// if bump is struck while there is a loud noise - could be a fellow robot!
		  	if(SensorValue(backTouch) == 1)  {

		  	  wait1Msec(200);

		  	  int soundVal1 = SensorValue[soundBack];
		  	  wait1Msec(100);
		  	  int soundVal2 = SensorValue[soundBack];
		  	  wait1Msec(100);
		  	  int soundVal3 = SensorValue[soundBack];
		  	  wait1Msec(100);
		  	  int soundVal4 = SensorValue[soundBack];
		  	  wait1Msec(100);
		  	  int soundVal5 = SensorValue[soundBack];
		  	  wait1Msec(1000);


		  	  if((soundVal1 > bThreshold) || (soundVal2 > bThreshold) || (soundVal3 > bThreshold) || (soundVal4 > bThreshold) || (soundVal5 > bThreshold)) {
		  	  	ring_bell();
		  	  	// another round, just to be sure
		  	  	wait1Msec(700);

		  	  	int soundVal6 = SensorValue[soundBack];
		  	  	wait1Msec(100);
		  	  	int soundVal7 = SensorValue[soundBack];
		  	  	wait1Msec(100);
		  	  	int soundVal8 = SensorValue[soundBack];
		  	  	wait1Msec(100);
		  	  	int soundVal9 = SensorValue[soundBack];
		  	  	wait1Msec(100);
		  	  	int soundVal10 = SensorValue[soundBack];
		  	  	wait1Msec(1000);

		  	  	if((soundVal6 > bThreshold) || (soundVal7 > bThreshold) || (soundVal8 > bThreshold) || (soundVal9 > bThreshold) || (soundVal10 > bThreshold)) {
		  	  		ring_bell();

		  	  		// robot has been tagged. It is now "it"!
		  				wait1Msec(3000);
		  				speak_loudly();
		  				quick_backup();
		  				turn_switch();
		  				StartTask(Drive_Forward);
		  				behavioral_state = 1;
		  			continue;
						} else {
							// do nothing
						}
		  		} else {
		  			// do nothing
		  		}
		  	}


		  	wait1Msec(100);

			}
			//////////////////////////////////////////////



			// robot is "it"
			else if(behavioral_state == 1) {
				// Task Drive_Forward is running during this behavioral_state

				// Front Touch Sensor Triggered
		  	if(SensorValue(frontTouch) == 1) {
		  	// probably should change to either front or back sensor right?
		  	//if((SensorValue(backTouch) == 1) || SensorValue(frontTouch) == 1)) {

			  	StopTask(Drive_Forward);

			  	motor(rightServo) = 0;
 					motor(leftServo) = 0;
 					ring_bell();
					wait1Msec(600);
					//wait1Msec(1000);

					int soundVal1 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal2 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal3 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal4 = SensorValue[soundFront];
		  	  wait1Msec(100);
		  	  int soundVal5 = SensorValue[soundFront];

		  	  nxtDisplayBigTextLine(0, "%d, %d", soundVal1, soundVal2);
		  	  nxtDisplayBigTextLine(2, "%d, %d", soundVal3, soundVal4);
		  	  nxtDisplayBigTextLine(4, "%d", soundVal5);

					wait1Msec(1000);

		  	  if((soundVal1 > hitThreshold) || (soundVal2 > hitThreshold) || (soundVal3 > hitThreshold) || (soundVal4 > hitThreshold) || (soundVal5 > hitThreshold)) {
		  	  	ring_bell();
		  	  	wait1Msec(1000);

		  	  	int soundVal6 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal7 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal8 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal9 = SensorValue[soundFront];
		  	  	wait1Msec(100);
		  	  	int soundVal10 = SensorValue[soundFront];

		  	  	nxtDisplayBigTextLine(0, "%d, %d", soundVal6, soundVal7);
		  	  	nxtDisplayBigTextLine(2, "%d, %d", soundVal8, soundVal9);
		  	  	nxtDisplayBigTextLine(4, "%d", soundVal10);

		  	  	wait1Msec(200);

		  	  	if((soundVal6 > hitThreshold) || (soundVal7 > hitThreshold) || (soundVal8 > hitThreshold) || (soundVal9 > hitThreshold) || (soundVal10 > hitThreshold)) {

		  	  		celebrate_noise();
		  	  		quick_backup();
 					  	// spin in a circle in celebration
 					  	motor(rightServo) = -driving_speed;
 					  	celebrate_noise();
 					  	wait1Msec(1000);
 					  	make_stop();

 					  	hide_somewhere();
 					  	//StartTask(Wall_Follow);
 					  	// change behavioral_state - Robot is no longer it
 					  	behavioral_state = 2;
 					  	continue;

 						} else
 							wait1Msec(500);
 					} else
 						wait1Msec(500);
 					// listen block

					// The touch was a false alarm, back up, turn and continue to search for other robots to tag
 					quick_backup();
 					wait1Msec(500);
 					turn_switch();
 					StartTask(Drive_Forward);
 				}

				// else no bump sensors triggered, ok
				else {
					wait1Msec(100);
				}
			}
			// some undefined case
			else {
				make_stop();
				StopAllTasks();
		  }
	}
}


//=======================================================================================
//=======================================================================================

task main()
{

  // Is Robot It?
  // 2 = no, 1 = yes
  behavioral_state = 1;

  // code to wait until the sensor is triggered, to give handlers time to position robot as desired
  PlaySound(soundDownwardTones);
  wait1Msec(1000);

  // wait until the front touch sensor is touched
  while(true)
  {
  	if(SensorValue[frontTouch] == 1)
  	{
  		wait1Msec(300);
  		break;
  	}
  	wait1Msec(300);
  }

  wait1Msec(1000);

   if(behavioral_state == 1) {
      // Fox starts as "it"
  	  StartTask(Bump_Watch);
	  StartTask(Drive_Forward);
	} else {
	  // Fox starts as "not it"
	  hide_somewhere();
	  StartTask(Bump_Watch);
  }

  wait1Msec(1000);

  while(true)
  {
    wait1Msec(300);                                 // Allow for a short wait, freeing up the CPU for other tasks.

  }
  return;

}
