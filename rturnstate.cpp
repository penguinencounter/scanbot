/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "rturnstate.h"
#include "lturnstate.h"

extern LTurnState lturn;

RTurnState::RTurnState(State * parent, IRobot & robot) :
    RobotState("rturn", parent, robot)
{}

Result RTurnState::on_entry() 
{
    m_robot.rotate_right(0, 250);
    return OK;
}

bool RTurnState::on_event(ProximityEvent & event)
{
    if (event.type == event.LEFT) {
        transition_to_state(&lturn);
    }
    return true;
}
