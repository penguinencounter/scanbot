/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "initstate.h"
#include "robotstatemachine.h"

extern InitState initialized;

RobotStateMachine::RobotStateMachine(State * parent, IRobot & robot) :
    RobotState("machine", parent, robot)
{}

Result RobotStateMachine::on_initialize()
{
    return transition_to_state(&initialized);
}