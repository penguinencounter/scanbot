/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "turningstate.h"

extern AttackState attack;

TurningState::TurningState(State * parent, IRobot & robot) :
    RobotState("turning", parent, robot)
{}

bool TurningState::on_event(EncoderEvent & event)
{
    transition_to_state(&attack);
    return true;
}
