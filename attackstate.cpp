/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "lturnstate.h"
#include "rturnstate.h"
#include "idlestate.h"

extern IdleState idle;
extern RTurnState rturn;
extern LTurnState lturn;

AttackState::AttackState(State * parent, IRobot & robot) :
    RobotState("attack", parent, robot)
{}

Result AttackState::on_entry() 
{
    
    m_robot.move_forward(200);
    return OK;
}

bool AttackState::on_event(ProximityEvent & event)
{
    if (event.type == event.RIGHT) {
        m_robot.move_stop();
        transition_to_state(&rturn);
    }
    else if (event.type == event.LEFT) {
        m_robot.move_stop();
        transition_to_state(&lturn);
    }
    else if (event.type == event.NONE) {
        m_robot.move_stop();
        transition_to_state(&idle);
    }
    return true;
}

bool AttackState::on_event(BoundaryAheadEvent & event) {
    m_robot.rotate_left(180, 200);
    return true;
}

bool AttackState::on_event(BoundaryLeftEvent & event) {
    m_robot.display("l!");
    m_robot.rotate_right(110, 200);
    return true;
}

bool AttackState::on_event(BoundaryRightEvent & event) {
    m_robot.rotate_left(110, 200);
    return true;
}

bool AttackState::on_event(EncoderEvent & event) {
    transition_to_state(&idle);
    return true;
}
