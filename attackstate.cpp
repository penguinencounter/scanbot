/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "lturnstate.h"
#include "rturnstate.h"
#include "idlestate.h"
#include "reversingstate.h"

extern IdleState idle;
extern RTurnState rturn;
extern LTurnState lturn;
extern ReversingState reversing;

AttackState::AttackState(State *parent, IRobot &robot) : RobotState("attack", parent, robot)
{
}

Result AttackState::on_entry()
{
    m_robot.move_forward(300);
    return OK;
}

bool AttackState::on_event(ProximityEvent &event)
{
    if (event.type == event.RIGHT)
    {
        transition_to_state(&rturn);
    }
    else if (event.type == event.LEFT)
    {
        transition_to_state(&lturn);
    }
    else if (event.type == event.NONE)
    {
    }
    return true;
}

bool AttackState::on_event(BoundaryAheadEvent &event)
{
    transition_to_state(&reversing);
    return true;
}

bool AttackState::on_event(BoundaryLeftEvent &event)
{
    transition_to_state(&reversing);
    return true;
}

bool AttackState::on_event(BoundaryRightEvent &event)
{
    transition_to_state(&reversing);
    return true;
}
