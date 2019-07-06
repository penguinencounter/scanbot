/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "idlestate.h"
#include "reversingstate.h"

extern IdleState idle;

ReversingState::ReversingState(State * parent, IRobot & robot) :
    RobotState("reversing", parent, robot)
{}

Result ReversingState::on_entry()
{
    m_robot.move_forward(-200, 350);
    return OK;
}

bool ReversingState::on_event(EncoderEvent & event)
{
    transition_to_state(&idle);
    return true;
}
