#include "framework/charles.h"
#include "assignments/assignment2.h"


//Names: Markus Abel and Björn Smith
//Student numbers: s1148847 and s1135336

// function that makes Charles turn around
void turn_around(){
    turn_left();
    turn_left();
}
// this function gets Charles into the final positsion
void end(){
    // the loop finds north
    while(!north()){
        turn_left();
    }
    // after finding norty it turns right which is the final position
    turn_right();
}

// helper function which detects if there is a wall on one side of the line of balls
// it takes a step if not, but we can safely assume that the wall is only on one side
void check_wall(){
    turn_left();
    if(in_front_of_wall()){
        turn_around();
        step();

    }
    else{
        step();
    }

}

void walk(){
    // main loop runs while Charles is on a ball
    while(on_ball()){
        //if statement that checks if charles is on a ball 
        // this is used when charles gets to the end of a line
        if(!in_front_of_wall()){
            step();
            //this if statement is activated when charles goes past the last ball in a line
            if(!on_ball()){
                //charles turns around and goes back to the last ball and checks if there a wall on one side
                
                turn_around();
                step();
                check_wall();

                //this if statement is used to check the other side and
                if(!on_ball()){
                    turn_around();
                    step();
                    //this if-else statement is used to quit the main loop when charles has gotten to the end
                    if(in_front_of_wall()){
                        turn_around();
                        step();

                    }
                    else{
                        step();
                    }
                }
            
            }
        }
        // if there is a wall in front chrales cheks the two sides
        else{
            
            check_wall();
            // after the check it goes the other way is there is a wall or no path
            if(!on_ball()){
                    turn_around();
                    step();
                    if(!in_front_of_wall()){
                        step();
                    }
            }
            
            

        }
        
    }
    
}



void test_agent() {
    

}

void path_agent() {
    
    walk();
    turn_around();
    step();
    end();
    

}

//helper function that makes chrales walk until it hits a wall
void step_loop(){
    while(!in_front_of_wall()){
        step();  
    }

}

void fill(){
    //makes the first step to get the path of the first wall
    step();

    //this loop runs until charles gets to the end of the map where there is no ball and a wall
    while(!in_front_of_wall()&& !on_ball()){

        //Charles first turns right and goes until hit hits the wall
        turn_right();
        step_loop();
        turn_around();
        
        //this loop puts balls the whole way while going back up
        while(!in_front_of_wall()){
            put_ball();
            step();
            
        }
        //puts the last ball and steps horizontally 
        put_ball();
        turn_right();
        step();

    }
    //after making stalactites or stalagmites charles goes the whole way down or up on the map
    turn_right();
    step_loop();
    turn_right();
    
}

// NOTE: this agent is executed twice in a row. See the PDF for more details.
void cave_agent() {
   
    fill();
   
}


