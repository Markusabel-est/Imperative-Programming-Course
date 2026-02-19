#include "framework/charles.h"
#include "assignments/assignment1.h"

void test_agent() {

}

void string_agent() {
    // Main loop for method; only runs if charles is standing on top of a ball
    while(on_ball()){

        // if...else... condition to dictate the movement of charles
        if(in_front_of_wall()){ 
            // turn right at the corners
            turn_right();
        }

        else{
            // collect the balls take 1 step if not in front of the wall
            get_ball();
            step();
            
        }

    }
}

void chaos_agent() {
    // charles steps until he reaches a ball
    while(!on_ball()){
        step();
    }
    // once charles reaches the first ball, this loop activates
    while(on_ball()){
        // checking for wall collision, if in front of a wall, charles will turn
        if(in_front_of_wall()){
            get_ball();
            turn_right();
            step();
            turn_right();
                
        }
        // collect ball and step
        get_ball();
        step();
        
        /* after charles collects the ball, this segment will check for if after the step, 
         charles is not on a ball. if true, charles will turn around*/ 
        if(!on_ball()){
            turn_right();
            turn_right();
            //charles will go back through the empty row until he reaches the wall and then he will turn onto the next row
            while(!in_front_of_wall()){
                step();
            }
            turn_right();
            step();
            turn_right();
        }
    }
    // once charles has collected every ball, this loop will run
    while(!in_front_of_wall()){
        // charles will walk towards the left wall
        step();
        // this checks if when charles reaches a wall, if he is facing north, that means he reached his initial position
        if(in_front_of_wall() && north()){
            // charles will face east
            turn_right();
            break; // this breaks the loop and ends the simulation
        }
        // if charles is not facing north when he reaches a wall, he will just turn right and continue until the next wall
        if(in_front_of_wall()){
            turn_right();
        }
    }
}

        

