						
						REAL    REMAINDER

						CSE - 102 PROJECT

Author:
-------

	>>	2005011	Md. Tanvirul Islam Turad
	>>	2005026	Md. Jakaria Hossain

Project Details:
----------------
	
	It's an interactive tool for math lovers. It has 2 different parts. 
		1.	Graphing calculator
		2.	Ellastic Collision simulation

	1.	Graphing Calculator:
	````````````````````````
		
			To make or see the graphical representation of an equation, we can use this tool.
			
			Key Features:
			*************
				
				# User can see the coordinates of any position by left clicking , and hide by right clicking.

				# User can give input from keyboard as equation and see output or graph of that equation .

				# By clicking "Enter equation here" , user enters equation mode ( mode_eqn ). Now the program is ready to take input.

				# Co-efficients of that equation can be Negative or Decimal. 

				# After pressing "ENTER" , graph of that equation is shown.
 
				# There is 3 more options while an equation is selected.

					> Choosing different color.
					> That equation will be shown or not.
					> Moving ball of that equation.

				# Maximum number of equation is defined in the beginning of the code. User can add this number of equations.

				# User can SAVE one or more equations as a project giving a filename. That file is saved as text file.

				# User can also OPEN an existing project by entering the name of that file (without extension) . This filename must exist in the directory of the program.

					>	A project is saved in "fun.txt". You can open this file by entering "fun" as name of the file.

				# User can APPEND a project to another project or some equations by opening the project after another or entering some equation.

				# To CLEAR ALL the equations, press "CLEAR ALL".

				# ZOOMING is very easy in this program. User can click on '+' or '-' or 'RESET' to zoom in or out or reset zooming respectively.

						If no equation is selected, User can press '+' or '-' key to do zooming.

				# By clicking "BACK", all the equations given as input are deleted. And user returns to the homepage.

	
	2.	Ellastic Collision:
	`````````````````````````
			It is a simulation of colliding two bodies on a frictionless surface.

			Key Features:
			*************

				# Some values of Masses and initial velocities are given as default. At any moment clicking "RESET", return to this default values.

				# Colliding of the objects can be paused or resumed by clicking "PAUSE" or "RESUME" respectively.

				# User can change the values of Masses and inital velocities. 

				# Clicking "RESTART" returns to the initial values that user gave.

				# Velocities at any moment can be multiplied or divided by 2 by pressing '+' or '-' respectively.

				# Increasing or decreasing of Velocities after first collision may give wrong number of total collisions.

				# Number of collisions is counted each time of collisions.

				# Number of collisions is very special for the ratio of masses having a power of 100.

				# After entering any value, user MUST PRESS "ENTER".

				For better view,

				No. of collisions:			v2			m2			m1

					3					any			1			1
					31					any			100			1
					314					<= 1			10000			1
					3141					<= 0.1		1000000		1	
					31415					<= .01  		100000000		1
  

Special part of this project:
-----------------------------

	Some functions were made to do some special work. Here's in brief.

		# myatoi(char*)  
				>>	returns decimal value from string as well as negative value. 


		# make_point()	
				>>	makes an array of point from any 2nd degree arithmetic equation.

		# co_eff()	 	
				>>	extracts the co-efficients of an equation.

		# pos_from_int() 
				>>	makes a readable string from integer data got from mouse click.

		# trace_point() 
				>>	shows position of mouse click.

		# zooming is done only by changing the value of "z".

		# 	After all, this project is made for a resolution of 1280x720 px. 
			User can CHANGE screen resolution according to his/her choice. 


Conclusion:
-----------

	Graphing calculator was inspired by desmos.com and Ellastic Collision by a video of 3blue1brown channel on youtube.

