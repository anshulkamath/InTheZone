//VARIABLES - FOR POWER AND SENSOR VALUE POSITIONS
#pragma once;

// Motor Powers
int lDrivePwr = 0, rDrivePwr = 0;
int rLiftPwr = 0, lLiftPwr = 0;
int barPwr = 0;
int mGoalPwr = 0;
int intakePwr = 0;

// Control Variables
int driveTarget = 0;
int liftTarget = 0;

// Sensor Values - CONSTANTS
const int LIFT_MIN = 1456;
const int LIFT_MID = 0;
const int LIFT_MAX  = 0;
const int LIFT_DRIVER = 1950;
const int LIFT_STATIONARY = 0;

const int BAR_UP = 3680;
const int BAR_DOWN = 1955;

const int MOGO_UP = 2225;
const int MOGO_THROW = 1720;
const int MOGO_DOWN = 650;

const int INTAKE_HOLD = 20;

// Toggle Variables
bool barIsUp = true;
bool barIsManual = false;
bool intakeIsHolding = false;
bool isFieldControl = true;
bool moGoIsManual = true;
bool mGoalIsUp = true;
bool autoStackIsOn = false;
bool longDelay = false;

bool driveIsActive = true;
bool liftIsActive = true;
bool barIsActive = true;
bool moGoIsActive = true;
bool intakeIsActive = true;

// Auton Function Variables
bool isOpposite = false;
bool isRunning = false;
int turnRange = 10;
int driveRange = 15;

// Auton Variables
const int NO_CONES = 1600;
const int ONE_CONE = 1750;

// LCD Variables
const int NUM_AUTONS = 2;
const int NUM_MENUS = 4;
bool gyroIsCalibrating = false;
bool centerPressed = false;
string mainBattery, backupBattery;

// LCD Counters
int autonCount = 0;
int lcdCount = 1;
int color = -1;
int side = -1;
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

// AutoStack Control Variables
int cones = 0;
int conesDriver = 0;

// AutoStack arrays
const int size = 10;
int conesHeight[size];
int coneDown[size];

// Datalog Definitions
#define   DATALOG_SERIES_0    0
#define   DATALOG_SERIES_1    1
#define   DATALOG_SERIES_2    2
#define   DATALOG_SERIES_3    3
#define   DATALOG_SERIES_4    4
#define   DATALOG_SERIES_5    5
#define   DATALOG_SERIES_6    6
#define   DATALOG_SERIES_7    7
