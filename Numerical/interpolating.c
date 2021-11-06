
/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c 
    Copyright (C) 2018  Ely

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/





/*

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and 
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :
       
sudo  apt-get  install  libx11-dev     

sudo  apt-get  install  xorg-dev

*/




/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,  
do the following :

cc  FPToolkitDemo.c   -lm  -lX11

*/


#include  "FPToolkit.c"
#include <stdbool.h>


bool collect_click(double point[]){
    G_rgb(0.310,0.325, 0.635);
    G_wait_click(point);
    if(point[0] < 800){
        G_fill_circle(point[0], point[1], 4);
        return true;
    }
    else{
    return false; //return false if click is in exit zone
    }
}

double laGrange_function(double x[], double y[], int t/*the variable x value */, int numPoints){
    double fx = 0;
    double frac = 0;

    for(int i = 0; i <= numPoints; ++i){
        
    double numerator = 1;
    double denominator = 1;
        //numerator
       for(int n = 0; n < numPoints; ++n){
           if(n == i){
               continue;
           }
           else{
               numerator *= (t-x[n]);
           }
       } 
       //denominator
       for(int d =0; d < numPoints; ++d){
           if(d == i){
               continue;
           }
           else{
               denominator *= (x[i] -x[d]);
           }
       }
    //    printf("DENOMINATOR: %lf\n", denominator);
       frac = numerator / denominator;
    //    printf("FRACTION: %lf", frac);
       fx += y[i] * frac;
    }
    //return fx val
    //then after return in main
    //print dot at variable x(for) and returned fx
    return fx;
}


int main(int argc, char *argv[])
{
   int    swidth, sheight ;
   double x[100], y[100] ; //arrays to hold x and y vals of inputted points
   double point[2];
   int i = 0;
   int j= 0;
   int numPoints = 0;
   double y_val = 0;
   double x_val = 0;


/*INITIALIZE SCREEN */

 // must do this before you do 'almost' any other graphical tasks 
   swidth = 810;  sheight = 800;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color
   G_rgb (0.749, 0.427, 0.616) ; // sunset
   G_clear () ;

   G_rgb(0,0,0); //black line
   G_line(800, 0, 800, sheight);



/* COMMAND LINE ARGS*/
//collect input either graphically or 

   if(argc != 2){
       printf("Enter the correct number of args\n\n");
   }
   else{
       //graphics input
       if(atoi(argv[1])==0){
           printf("OK lets do some graphics input\n\n");

        while(collect_click(point)== true){
             x[i] = point[0];
             y[i] = point[1];
             ++i;
             ++numPoints;
        }

        }
        //text input
       else if(atoi(argv[1]) == 1){
           int input =0;
           printf("How many points: ");
           scanf("%d", &input);

           for(j=0; j<input; ++j){
               printf("x: ");
               scanf("%lf", &x[i]);
               printf(" y: ");
               scanf("%lf", &y[i]);
               G_fill_circle(x[i], y[i], 4);
               ++numPoints;
           }
       }
       else{
           printf("Enter a valid arg");
       }
   }


    G_rgb(0,0,0); //black
    for(x_val = 0; x_val< 800; ++x_val){
        y_val = laGrange_function(x, y, x_val, numPoints);
        G_point(x_val, y_val);
    }

   int key ;   
   key =  G_wait_key() ; // pause so user can see results

//    G_save_image_to_file("demo.xwd") ;

}



