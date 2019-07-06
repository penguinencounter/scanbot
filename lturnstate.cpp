/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "lturnstate.h"
#include "rturnstate.h"
#include "idlestate.h"
#include "attackstate.h"
#include "reversingstate.h"

extern IdleState idle;
extern AttackState attack;
extern RTurnState rturn;
extern ReversingState reversing;

LTurnState::LTurnState(State * parent, IRobot & robot) :
    RobotState("lturn", parent, robot)
{}

Result LTurnState::on_entry() 
{
    m_robot.slow_l(300);
    return OK;
}

bool LTurnState::on_event(ProximityEvent & event)
{
    if (event.type == event.RIGHT) {
        transition_to_state(&rturn);
    }
    else if (event.type == event.NONE) {
        transition_to_state(&idle);
    }
    else if (event.type == event.AHEAD) {
        transition_to_state(&attack);
    }
    return true;
}

bool LTurnState::on_event(BoundaryAheadEvent &event)
{
    transition_to_state(&reversing);
    return true;
}

bool LTurnState::on_event(BoundaryLeftEvent &event)
{
    transition_to_state(&reversing);
    return true;
}

bool LTurnState::on_event(BoundaryRightEvent &event)
{
    transition_to_state(&reversing);
    return true;
}

