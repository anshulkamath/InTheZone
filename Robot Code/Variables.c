//VARIABLES - FOR POWER AND SENSOR VALUE POSITIONS

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
const int LIFT_MIN = 1426;
const int LIFT_MID = 0;
const int LIFT_MAX  = 0;
const int LIFT_DRIVER = 1742;

const int BAR_UP = 3350;
const int BAR_DOWN = 1870;

const int MOGO_UP = 0;
const int MOGO_DOWN = 0;

// Toggle Variables
bool barIsUp = true;
bool barIsManual = false;
bool intakeHold = false;
bool isFieldControl = true;
bool moGoIsManual = true;
bool moGoIsUp = true;
bool autoStackIsOn = false;

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
const int BlueStart =  0;
const int RedStart = 1365;
const int NoStart = 2730;

const int fivePtStart = 0;
const int tenPtStart = 1365;
const int twentyPtStart = 2730;

// LCD Variables
const int NUM_AUTONS = 2;
const int NUM_MENUS = 4;
bool gyroIsCalibrating = false;
string mainBattery, backupBattery;

// LCD Counters
int autonCount = -1;
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
