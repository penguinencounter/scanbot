/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "robot.h"

extern StartButtonEvent start_event;
extern TimerEvent timer_event;
extern BoundaryAheadEvent boundary_ahead_event;
extern BoundaryLeftEvent boundary_left_event;
extern BoundaryRightEvent boundary_right_event;
extern EncoderEvent encoder_event;
extern ProximityEvent proximity_event;

void IRobot::setup()
{
    end_time = 0;
    encoder_count = 0;

    // Set up gyro.
//    gyro.init();

    // Set up accelerometer.
    accelerometer.init();

    // Set up line sensors.
    boundary_sensor.initThreeSensors();

    // Set up proximity sensors. Choose one, or call init() with arguments.
    proximity_sensors.initFrontSensor();
//    proximity_sensors.initThreeSensors();
}

void IRobot::generate_events(EventQueue & q)
{
    // Check start button.
    if (start_button.getSingleDebouncedPress())
    {
        q.push(&start_event);
    }

    // Check timer.
    if (end_time && millis() >= end_time)
    {
        q.push(&timer_event);
        end_time = 0;
    }

    // Check boundary sensors.
    switch(boundary_detect())
    {
    case BOUNDARY_AHEAD:
        q.push(&boundary_ahead_event);
        break;
    case BOUNDARY_LEFT:
        q.push(&boundary_left_event);
        break;
    case BOUNDARY_RIGHT:
        q.push(&boundary_right_event);
        break;
    }

    // Check encoders.
    if (encoder_count && abs(encoders.getCountsLeft()) > encoder_count)
    {
        q.push(&encoder_event);
        encoder_count = 0;
    }

    // Check proximity sensors.
    proximity_sensors.read();
    uint8_t l_counts = proximity_sensors.countsFrontWithLeftLeds();
    uint8_t r_counts = proximity_sensors.countsFrontWithRightLeds();
    lcd.gotoXY(0, 1);
    lcd.print(l_counts);
    lcd.print(" ");
    lcd.print(r_counts);
    lcd.print(" ");
    bool detected = l_counts >= 1 || r_counts >= 1;
    if (detected) {
        // There's something there.
        if (l_counts < r_counts) {
            proximity_event.type = proximity_event.RIGHT;
            lcd.print("r");
            q.push(&proximity_event);
        }
        else if (l_counts > r_counts) {
            proximity_event.type = proximity_event.LEFT;
            lcd.print("l");
            q.push(&proximity_event);
        }
        else {
            proximity_event.type = proximity_event.AHEAD;
            lcd.print("a");
            q.push(&proximity_event);
        }
    }
    else
    {
        proximity_event.type = proximity_event.NONE;
        lcd.print("n");
        q.push(&proximity_event);
    }
    
}

//
// State Machine Interfaces
//
void IRobot::display(char const * msg)
{
    lcd.clear();
    lcd.write(msg, strlen(msg));
}

void IRobot::cancel_timer()
{
    end_time = 0;
}

void IRobot::start_timer(unsigned long timeout)
{
    end_time = millis() + timeout;
}

void IRobot::move_forward(int speed)
{
    motors.setSpeeds(speed, speed);
}

void IRobot::move_forward(int speed, long counts)
{
    motors.setSpeeds(speed, speed);
    encoder_count = counts;
    encoders.getCountsAndResetLeft();
}
void IRobot::move_stop()
{
    motors.setSpeeds(0, 0);
}

void IRobot::rotate_left(long degrees, int speed)
{
    encoder_count = degrees * encoder_counts_per_degree_rotation;
    encoders.getCountsAndResetLeft();
    motors.setSpeeds(-speed, speed);
}

void IRobot::rotate_right(long degrees, int speed)
{
    encoder_count = degrees * encoder_counts_per_degree_rotation;
    encoders.getCountsAndResetLeft();
    motors.setSpeeds(speed, -speed);
}

void IRobot::slow_l(int speed)
{
    motors.setSpeeds(speed / 2, speed);
}

void IRobot::slow_r(int speed)
{
    motors.setSpeeds(speed, speed / 2);
}

void IRobot::cancel_encoder()
{
    encoder_count = 0;
}

//
// Private methods.
//
Boundary IRobot::boundary_detect()
{
    // below threshold => boundary.
    // above threshold => ring.
    const unsigned int threshold = 500;

    unsigned int sensor_values[3];
    boundary_sensor.read(sensor_values);
    bool left_boundary = sensor_values[0] < threshold;
    bool center_boundary = sensor_values[1] < threshold;
    bool right_boundary = sensor_values[2] < threshold;

    Boundary boundary = NO_BOUNDARY;
    if (center_boundary || (left_boundary && right_boundary))
    {
        boundary = BOUNDARY_AHEAD;
    }
    else if (left_boundary)
    {
        boundary = BOUNDARY_LEFT;
    }
    else if (right_boundary)
    {
        boundary = BOUNDARY_RIGHT;
    }

    return boundary;
}