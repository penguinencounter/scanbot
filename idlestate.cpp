/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "idlestate.h"
#include "lturnstate.h"
#include "rturnstate.h"

extern LTurnState lturn;
extern RTurnState rturn;

IdleState::IdleState(State * parent, IRobot & robot) :
    RobotState("idle", parent, robot)
{}

Result IdleState::on_entry()
{
    m_robot.rotate_left(0, 200);
}

bool IdleState::on_event(ProximityEvent & event)
{
    if (event.type == event.LEFT) {
        // transition to l_Turn
        transition_to_state(&lturn);
    }
    else if (event.type == event.RIGHT) {
        // transition to r_turn
        transition_to_state(&rturn);
    }
    else {
        return false;
    }
    return true;
}