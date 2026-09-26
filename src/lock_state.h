#ifndef LOCK_STATE_H
#define LOCK_STATE_H

enum LockState
{
    LOCKED,
    GRANTED,
    DENIED,
    CHANGE_PIN
};

#endif // LOCK_STATE_H