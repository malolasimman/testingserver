Note: For all assignments and Energy Profiler measurements you’ll be taking this semester,  Peak measurements are instantaneous measurements taken at a specific point in time. In the Energy Profiler, this is accomplished by left-clicking at a location along the time axis.
Average measurements are measurements that are taken over a time-span. In the Energy Profiler, this is accomplished by left-clicking and dragging a region along the time axis.

Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.
<br> <br> <br>
**1. How much current does the system draw (instantaneous measurement) when a single LED is on with the GPIO pin set to StrongAlternateStrong?** <br>
   Answer: when the GPIO LED0 pin set to StrongAlternateStrong the single led draws instantaneous current of 5.41mA. <br>
   
![led0inststrong](https://github.com/CU-ECEN-5823/ecen5823-assignment1-malolasimman/assets/59477885/c1acee75-3718-4254-a899-438cbcbdf2b9)



<br> <br> <br>
**2. How much current does the system draw (instantaneous measurement) when a single LED is on with the GPIO pin set to WeakAlternateWeak?** <br>
   Answer: when the GPIO LED0 pin set to WeakAlternateWeak the single led draws instantaneous current of 5.40mA. <br>
   
![led0instweak](https://github.com/CU-ECEN-5823/ecen5823-assignment1-malolasimman/assets/59477885/bbec88ef-6f51-4625-87ef-2d36ff3a7f07)



<br> <br> <br>
**3. Is there a meaningful difference in current between the answers for question 1 and 2? Please explain your answer, referencing the main board schematic, WSTK-Main-BRD4001A-A01-schematic.pdf or WSTK-Main-BRD4002A-A06-schematic.pdf, and AEM Accuracy in the ug279-brd4104a-user-guide.pdf. Both of these PDF files are available in the ECEN 5823 Student Public Folder in Google drive at: https://drive.google.com/drive/folders/1ACI8sUKakgpOLzwsGZkns3CQtc7r35bB?usp=sharing . Extra credit is available for this question and depends on your answer.** <br>
   Answer: There is no difference in static current consumption of 5.40mA between questions 1 and 2. Even though the drive strength for StrongAlternateStrong is 10mA and WeakAlternateWeak is 1mA, it does not limit the static current consumption. StrongAlternateStrong and WeakAlternateWeak affect only the slew rate, not the static current.  <br>



</br> <br> <br>
**4. With the WeakAlternateWeak drive strength setting, what is the average current for 1 complete on-off cycle for 1 LED with an on-off duty cycle of 50% (approximately 1 sec on, 1 sec off)?** <br>
   Answer: For the WeakAlternateWeak drive strength setting, what is the average current for 1 complete on-off cycle for 1 LED with an on-off duty cycle of 50% is 5.12mA <br>
   
![led0avgweak](https://github.com/CU-ECEN-5823/ecen5823-assignment1-malolasimman/assets/59477885/4a22ade4-86df-4aef-af79-8a8fa13d0115)


<br> <br> <br>

**5. With the WeakAlternateWeak drive strength setting, what is the average current for 1 complete on-off cycle for 2 LEDs (both on at the time same and both off at the same time) with an on-off duty cycle of 50% (approximately 1 sec on, 1 sec off)?** <br>
   Answer: For the WeakAlternateWeak drive strength setting, what is the average current for 1 complete on-off cycle for 2 LEDs with an on-off duty cycle of 50% is 5.12mA.  <br>
   
![led01avgweak](https://github.com/CU-ECEN-5823/ecen5823-assignment1-malolasimman/assets/59477885/2577bfad-ad65-4b67-90fc-79f3d8df3ec0)



<br>

