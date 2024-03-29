/*
    Copyright 2019, Miles Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#pragma once

#include "robotstate.h"

class RTurnState : public RobotState
{
public:
    RTurnState(State * parent, IRobot & robot);

protected:
    Result on_entry() override;
    bool on_event(ProximityEvent & event) override;
    bool on_event(BoundaryAheadEvent & event) override;
    bool on_event(BoundaryLeftEvent & event) override;
    bool on_event(BoundaryRightEvent & event) override;
};
