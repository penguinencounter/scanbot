/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "rturnstate.h"
#include "lturnstate.h"
#include "idlestate.h"
#include "attackstate.h"

extern IdleState idle;
extern LTurnState lturn;
extern AttackState attack;

RTurnState::RTurnState(State * parent, IRobot & robot) :
    RobotState("rturn", parent, robot)
{}

Result RTurnState::on_entry() 
{
    m_robot.rotate_right(0, 200);
    return OK;
}

bool RTurnState::on_event(ProximityEvent & event)
{
    if (event.type == event.LEFT) {
        transition_to_state(&lturn);
    }
    else if (event.type == event.NONE) {
        transition_to_state(&idle);
    }
    else if (event.type == event.AHEAD) {
        transition_to_state(&attack);
    }
    return true;
}
