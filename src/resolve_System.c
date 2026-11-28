#include <math.h>
#include <assert.h>
#include "resolve_System.h"
#include "audio.h"

void resolveSystem_Update(World *world) {

    // Guard
    if (world->collisionPairBuffer < 1) {return;}
    
    for (uint32_t i = 0; i < world->collisionPairBuffer; i++) {
    // Skipping guard check for mask here, should be done in collision_System already...

    //--- Readability fix (compilern optimerar säkert bort denna skiten ändå, så enjoy 4 meine human eyes n brain...) ---
        
        //Hämta ID värdena från Entiteterna som ska 'behandlas'
        Entity RawA = world->collisionpairs[i].A;
        Entity RawB = world->collisionpairs[i].B;
        
        //isTrigger-check, done first to (SKIP) a bunch of unecessary computations:
        if (world->colliders[RawA].isTrigger || world->colliders[RawB].isTrigger) {
        assert((world->colliders[RawA].isTrigger != world->colliders[RawB].isTrigger));
            bool hasTrigger = world->colliders[RawA].isTrigger; 
            Entity isTrigger = hasTrigger ? RawA : RawB;
            if (world_DestroyEntity(world, isTrigger)) {
                audio_playSoundPitchVariation(monch);
            }
            continue; //<-- ! (Note: here's the skippy_boi hidin')
        }

        // (SKIP) if both are | immovable OR movable | we don't need to do any calculations...
        if (world->colliders[RawA].isImmovable == world->colliders[RawB].isImmovable) {continue;}

        bool CannotBeMoved = world->colliders[RawA].isImmovable;

        Entity movable   = CannotBeMoved ? RawB : RawA;
        Entity immovable = CannotBeMoved ? RawA : RawB;
        
        //Identifiera vilka collider_Components som ska 'behandlas' genom ID värdena
        collider_Component *movableCollider = &world->colliders[movable];
        collider_Component *immovableCollider = &world->colliders[immovable];

    //-------------------------------------------------------------------------------------------------------------------

    //RESOLVE MATH (Kids, don't do math, not even once)
/*     
        ASSUME BOTTOM LEFT IS THE ANCHOR POINT, (y - height) = DRAWING UPWARDS (raylib logic).
        
        Do math on each index-pair of A & B entities and resolve the transform.position AND ALSO assign that transform.position to their collisionBox.x -.y positions
            - how deep is the .x and .y overlap
            - which axis has the smallest overlap value
            - does + OR - push the movable entity away from the immovable entity
*/
        //Math to determine the center of each entity's collisionbox (half their width and height, based on position as well, should determine where the middle is):
            //Note: we use MINUS on the Y-axis, to adjust for the draw-UPWARDS logic (this is what I have to do to counter Raylib's baseline render logic)
            
            //STATIC and NOT the same as the dynamic center_ Vectors
            Vector2 halfSize_movableCollider   = {movableCollider->collisionBox.width * 0.5f, movableCollider->collisionBox.height * 0.5f};
            Vector2 halfSize_immovableCollider = {immovableCollider->collisionBox.width * 0.5f, immovableCollider->collisionBox.height * 0.5f};
            
            Vector2 center_movableCollider = {
                (movableCollider->collisionBox.x + halfSize_movableCollider.x), 
                (movableCollider->collisionBox.y - halfSize_movableCollider.y)
            };
            Vector2 center_immovableCollider = {
                (immovableCollider->collisionBox.x + halfSize_immovableCollider.x), 
                (immovableCollider->collisionBox.y - halfSize_immovableCollider.y)
            };

        //Logic/Purpose explained (movableCollider = A && immovableCollider = B):
            //negative result = A.x is positioned LEFT of B.x | positive result = A.x is positioned RIGHT of B.x
            //negative result = A.y is positioned ABOVE B.y   | positive result = A.y is positioned BELOW B.y
            Vector2 determineRelative = {(center_movableCollider.x - center_immovableCollider.x), (center_movableCollider.y - center_immovableCollider.y)};

        //Calculate overlap to determine how much transform.position needs to be re-adjusted to not (get stuck within)/(visually, render-overlap with) an immovable object
            Vector2 overlap = { //(minimum safe distance) - (Actual distance between centers) | typ: (static-värde safe limit) - (dynamic-värde current distance)
                (halfSize_movableCollider.x + halfSize_immovableCollider.x) - fabsf(determineRelative.x),
                (halfSize_movableCollider.y + halfSize_immovableCollider.y) - fabsf(determineRelative.y)
            };

        //Theoretically, should fix (a scenario of) colliding with two immovable objects roughly at the same time (by not getting stuck due to 'simultaneous' calculations)...
            if (overlap.x <= 0.0f || overlap.y <= 0.0f) {continue;}

        //HORIZONTAL PUSH //om jag stöter på future "snagging" mellan två immovable tiles kanske det kan lösas med att ändra till if (overlap.x + 0.01f < overlap.y) för att ge det en liten bias åt ena immovable entiteten
            if (overlap.x < overlap.y) { 
                if (determineRelative.x > 0) {
                    world->transforms[movable].position.x += overlap.x; //move right
                } else {
                    world->transforms[movable].position.x -= overlap.x; //move left
                }
        //VERTICAL PUSH
            } else if (overlap.y <= overlap.x) { 
                if (determineRelative.y > 0) {
                    world->transforms[movable].position.y += overlap.y; //move down
                    world->movements[movable].velocity.y = 0.0f;       //(PLATFORMER MODE)should stop accelarating through blocks
                } else {
                    world->transforms[movable].position.y -= overlap.y; //move up
                    world->movements[movable].isGrounded = true;       //(PLATFORMER MODE)
                    world->movements[movable].velocity.y = 0.0f;       //(PLATFORMER MODE)should stop accelarating through blocks
                }
            }

        movableCollider->collisionBox.x = world->transforms[movable].position.x;
        movableCollider->collisionBox.y = world->transforms[movable].position.y;
    }
}

void triggerMonchSound(){
}