Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

*Be sure to take measurements with logging disabled to ensure your logging logic is not impacting current/time measurements.*

*Please include screenshots of the profiler window detailing each current measurement captured.  See the file Instructions to add screenshots in assignment.docx in the ECEN 5823 Student Public Folder.* 


1. What is the average current per period? (Remember, once you have measured your average current, average current is average current over all time. Average current doesn’t carry with it the units of the timespan over which it was measured).
   <br>Answer: 20.20 uA (micro amps)
   <br>Screenshot:  
   ![qn1](https://github.com/CU-ECEN-5823/ecen5823-assignment4-malolasimman/assets/59477885/5986b436-5da8-488e-a6aa-fe03c7c2a357)


2. What is the ave current from the time we sleep the MCU to EM3 until we power-on the 7021 in response to the LETIMER0 UF IRQ?
   <br>Answer: 2.47 uA (micro amps)
   <br>Screenshot:  
    ![qn2](https://github.com/CU-ECEN-5823/ecen5823-assignment4-malolasimman/assets/59477885/283608d2-d027-46f7-a4d5-58fb94b2301a)


3. What is the ave current from the time we power-on the 7021 until we get the COMP1 IRQ indicating that the 7021's maximum time for conversion (measurement) has expired.
   <br>Answer: 529.62 uA (micro amps)
   <br>Screenshot:  
   ![qn3](https://github.com/CU-ECEN-5823/ecen5823-assignment4-malolasimman/assets/59477885/b96c8a39-b2fe-4650-8191-c021ad1ad987)


4. How long is the Si7021 Powered On for 1 temperature reading?
   <br>Answer: 100.4 ms (milli seconds)
   <br>Screenshot:  
    ![qn4](https://github.com/CU-ECEN-5823/ecen5823-assignment4-malolasimman/assets/59477885/3cd8fddf-f246-4a5b-9b25-795f56c5335c)


5. Given the average current per period from Q1, calculate the operating time of the system for a 1000mAh battery? - ignoring battery manufacturers, efficiencies and battery derating - just a first-order calculation.
   <br>Answer (in hours): The average current per period is 20.20uA, which is equivalent to 0.0202mA
                         so the operating time of the system for a 1000mAh battery is 1000/0.0202 = 49504.9504 hours. 
                           therefore operating time of the system for a 1000mAh battery is 49504.9504 hours.


   
6. How has the power consumption performance of your design changed since the previous assignment?
   <br>Answer: In my assignment 3 power consumption for the period is 499.41 uW (micro watts), while in assignment 4 it reduced to 66.79 uW (micro watts). From this analysis observed that power consumption is reduce by 86.62%. This significant difference in power consumption is because of timer interrupts and EM1 energy mode during the I2c transfer and EM3 at all other modes.
   


   


