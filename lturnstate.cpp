/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "lturnstate.h"
#include "rturnstate.h"

extern RTurnState rturn;

LTurnState::LTurnState(State * parent, IRobot & robot) :
    RobotState("lturn", parent, robot)
{}

Result LTurnState::on_entry() 
{
    m_robot.rotate_left(0, 250);
    return OK;
}

bool LTurnState::on_event(ProximityEvent & event)
{
    if (event.type == event.RIGHT) {
        transition_to_state(&rturn);
    }
    return true;
}
