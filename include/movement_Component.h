#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "raylib.h"

typedef struct {
    Vector2 velocity;
    Vector2 externalVelocity;  //dash n shid
    Vector2 direction;         //input.c got da player shit for this...

    float speed;               //entity base_line shid
    float speedMultiplier;
    float friction;            // (covers acceleration as well) like ramp or ramp down speed when running and stuff
    
//optional (toggable by gravity being above 0 value?) platformer logic
    float gravity;             //might not use...
    float jumpForce;
    float maxFallSpeed;

    bool canMove;
    bool isGrounded;           //gravity related to check if on floor or up in air for some logic shid...
    bool wantsToJump;
} movement_Component;

#endif