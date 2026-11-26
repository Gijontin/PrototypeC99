#include <math.h>
#include "resolve_System.h"

void resolveSystem_Update(World *world) {

    if (world->collisionPairBuffer < 1) {return;}
    
    for (uint32_t i = 0; i < world->collisionPairBuffer; i++) {
    //skipping mask check here because colliderSystem technically already filtered that out from the collisionPair's list

    //Readability fix (compilern optimerar säkert bort denna skiten ändå, så enjoy 4 meine human eyes n brain...)
        
        //Hämta ID värdena från Entiteterna som ska 'behandlas'
        Entity RawA = world->collisionpairs[i].A;
        Entity RawB = world->collisionpairs[i].B;

        //if both are | immovable OR movable | we don't need to do any calculations...
        if (world->colliders[RawA].isImmovable == world->colliders[RawB].isImmovable) {continue;}

        bool CannotBeMoved = world->colliders[RawA].isImmovable;

        Entity movable   = CannotBeMoved ? RawB : RawA;
        Entity immovable = CannotBeMoved ? RawA : RawB;
        
        //Identifiera vilka collider_Components som ska 'behandlas' genom ID värdena
        collider_Component *movableCollider = &world->colliders[movable];
        collider_Component *immovableCollider = &world->colliders[immovable];

    //-----------------------------------------------------------------------------------------------------------

    //RESOLVE MATH
        //do math on each index-pair of A & B entities and resolve the transform.position AND ALSO assign that transform.position to their collisionBox.x -.y positions
        
        //ASSUME BOTTOM LEFT IS THE ANCHOR POINT, (y - height) = DRAWING UPWARDS (raylib logic)

            // - how deep is the .x and .y overlap
            // - which axis has the smallest overlap value
            // - does + OR - push the movable entity away from the immovable entity

        //Math to determine the center of each entity's collisionbox (half their width and height, based on position as well, should determine where the middle is):
            float centerA_X = movableCollider->collisionBox.x + (movableCollider->collisionBox.width * 0.5f);
            float centerB_X = immovableCollider->collisionBox.x + (immovableCollider->collisionBox.width * 0.5f);
        
        //Note: we use MINUS here to draw UPWARDS (thanks to Raylib logic)
            float centerA_Y = movableCollider->collisionBox.y - (movableCollider->collisionBox.height * 0.5f);
            float centerB_Y = immovableCollider->collisionBox.y - (immovableCollider->collisionBox.height * 0.5f);

        //negative result = A is positioned LEFT of B | positive result = A is positioned RIGHT of B
            float determineRelative_X = centerA_X - centerB_X;
        //negative result = A is positioned ABOVE B   | positive result = A is positioned BELOW B
            float determineRelative_Y = centerA_Y - centerB_Y;

        //Calculate overlap to determine how much transform.position needs to be re-adjusted for
            float overlapX = ((movableCollider->collisionBox.width * 0.5f) + (immovableCollider->collisionBox.width * 0.5f)) - fabsf(determineRelative_X);
            float overlapY = ((movableCollider->collisionBox.height * 0.5f) + (immovableCollider->collisionBox.height * 0.5f)) - fabsf(determineRelative_Y);

        //Theoretically should fix colliding with two immovable objects roughly at the same time...
            if (overlapX <= 0.0f || overlapY <= 0.0f) {continue;}

        //Determine direction to re-adjust transform.position (smallest overlap = gets pushed)
        if (overlapX < overlapY) { //HORIZONTAL PUSH
            if (determineRelative_X > 0) {
                world->transforms[movable].position.x += overlapX; //move right
            } else {
                world->transforms[movable].position.x -= overlapX; //move left
            }
        } else if (overlapY <= overlapX) { //VERTICAL PUSH
            if (determineRelative_Y > 0) {
                world->transforms[movable].position.y += overlapY; //move down
                world->movements[movable].velocity.y = 0.0f; //should stop accelarating through blocks if platformer mode
            } else {
                world->transforms[movable].position.y -= overlapY; //move up
                world->movements[movable].isGrounded = true;
                world->movements[movable].velocity.y = 0.0f; //should stop accelerating through blocks if platformer mode
            }
        }

        movableCollider->collisionBox.x = world->transforms[movable].position.x;
        movableCollider->collisionBox.y = world->transforms[movable].position.y;
    }
}