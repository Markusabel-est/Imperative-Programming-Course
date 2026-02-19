#include "framework/charles.h"
#include "assignments/bonus1.h"

/*Defining the variables x and y which will be the
row length and column length respectively*/

void test_agent() {

}
// This turns the character around
void turnAround(){
    turn_left();
    turn_left();
}

/* This finds the first instance of the wall to 
start the main portion of the program*/
void findWall(){
    while(!in_front_of_wall()){ 
        step();
        /* Character turns right in order to face 
        the wall if it touches the first ball */
        if(on_ball()){ 
            turn_right();
        }
    }
    turn_left();
}

/*Character moves around the wall placing balls 
During each step it checks for the location of the wall 
Method ends once the character is touching an already placed ball*/
void aroundWall(){
    while(!on_ball()){
        put_ball();
        turn_right();
        if(in_front_of_wall()){
            turn_left();
        }
        step();
    }
}

/*This method returns the character to the starting place*/
void goBack(){
    turn_left();
    step();
    while(!in_front_of_wall()){
        step();
        if(on_ball()){
            turn_left();
        }
    }
    turnAround();
}

// This is the main method that runs the helper methods
void block_agent() {
    findWall();
    aroundWall();
    goBack();
}



/*This method places balls and one at a time starting from outside in 
until the whole row is filled and the character is in the middle*/
void placeRow(){
    while(!on_ball()){
        while(!on_ball() && !in_front_of_wall()){
            step();
        }
        if(on_ball()){
            turnAround();
            step();
        }
        if(in_front_of_wall()){
            turnAround();
        }
        put_ball();
        step();
        if(on_ball()){
            turnAround();
            step();
        }
    }
}

/*This method runs the helper methods in the correct 
order to place each row and finally find the center*/
void find_center_agent() {
    placeRow();
    turn_left();
    if(north()){
        turn_left();
        turn_left();
    }
    step();
    placeRow();
    if(north()){
        turn_right();
    }
    else{
        turn_left();
    }

}

/*This method gets balls until the character reaches the next wall*/
void PUBallsWall(){
    while(!in_front_of_wall()){
        step();
        get_ball();
    }
}

// Walks to the next wall ahead
void toNextWall(){
    while(!in_front_of_wall() && !on_ball()){
        step();
    }
}

/*This method uses the same formula as the placing method but instead it picks up balls. 
This is only used for the top row*/
void getRow(){
    while(on_ball()){
        while(on_ball() && !in_front_of_wall()){
            step();
        }
        if(!on_ball()){
            turnAround();
            step();
        }
        if(in_front_of_wall()){
            turnAround();
        }
        get_ball();
        step();
        if(!on_ball()){
            turnAround();
            step();
        }
    }
}

/*This method uses the necessary helper methods 
in order to clean up the balls*/
void clean_up_agent() {
    turn_right();
    PUBallsWall();
    turnAround();
    toNextWall();
    //This loop just gets the balls above the middle ball but before the wall
    while(!in_front_of_wall()){
        step();
        if(!in_front_of_wall()){
            get_ball();
        }
    }
    turn_left();
    toNextWall();
    turnAround();
    getRow();
    turn_left();
    if(north()){
        turn_left();
        turn_left();
    }
    while(!on_ball()){
        step();
    }
    turn_left();
}
