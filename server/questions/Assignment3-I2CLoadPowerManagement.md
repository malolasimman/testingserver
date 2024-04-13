Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

*Be sure to take measurements with logging disabled to ensure your logging logic is not impacting current/time measurements.*

*Please include screenshots of the profiler window detailing each current measurement captured.  See the file: Instructions to add screenshots in assignment.docx in the ECEN 5823 Student Public Folder.* 

1. What is the average current per period? (Remember, once you have measured your average current, average current is average current over all time. Average current doesn’t carry with it the units of the timespan over which it was measured).
   <br>Answer: 151.10 uA (micro amps)
   <br>Screenshot:  
   <img width="1440" alt="period-avg-current" src="https://github.com/CU-ECEN-5823/ecen5823-assignment3-malolasimman/assets/59477885/6ce03021-40d8-4633-ba64-9715d779ec0b">

   
2. What is the ave current from the time we sleep the MCU to EM3 until we power-on the 7021 in response to the LETIMER0 UF IRQ? 
   <br>Answer: 2.59 uA (micro amps)
   <br>Screenshot:  
   ![offtime-curr](https://github.com/CU-ECEN-5823/ecen5823-assignment3-malolasimman/assets/59477885/1ad2b4a7-9a2f-4d8d-b021-095267a8065f)

   
3. What is the ave current from the time we power-on the 7021 until the polled implementation of timerWaitUs() returns, indicating that the 7021's maximum time for conversion (measurement) has expired.
   <br>Answer: 4.34 mA (milli amps)
   <br>Screenshot:  
   <img width="1440" alt="ontime-curr" src="https://github.com/CU-ECEN-5823/ecen5823-assignment3-malolasimman/assets/59477885/27b6b653-fb79-443a-9739-29963755dec7">

   
4. How long is the Si7021 Powered On for 1 temperature reading?  
   <br>Answer: 100 ms (milli seconds)
   <br>Screenshot:  
   <img width="1440" alt="ontime-curr" src="https://github.com/CU-ECEN-5823/ecen5823-assignment3-malolasimman/assets/59477885/b6688860-f308-4e87-ab6f-1d04138a327f">

