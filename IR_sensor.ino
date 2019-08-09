// IR Obstacle Collision Detection Module

int isObstaclePin = 7; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE

void setup() {
    pinMode(isObstaclePin, INPUT);
    Serial.begin(9600);
}

void loop() {
    isObstacle = digitalRead(isObstaclePin);
    if (isObstacle == LOW) {
        Serial.println("OBSTACLE!!, OBSTACLE!!");
    } else {
        //Serial.println("clear");
    }
    delay(20);
}
