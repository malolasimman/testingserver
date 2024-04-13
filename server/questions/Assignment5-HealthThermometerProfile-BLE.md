Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

*Be sure to take measurements with logging disabled to ensure your logging logic is not impacting current/time measurements.*

*Please include screenshots of the profiler window detailing each current measurement captured.  See the file Instructions to add screenshots in assignment.docx in the ECEN 5823 Student Public Folder.*

1. Provide screen shot verifying the Advertising period matches the values required for the assignment.
   <br>Answer: 259 ms (milli seconds)
   <br>Screenshot:  
    ![qn1](https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/868d6f50-c328-4fc5-8787-258f2ac5af11)


2. What is the average current between advertisements - i.e. when the MCU is sleeping in EM2. (Don't measure an interval with a LETIMER UF event)?
   <br>Answer: 3.01 uA (micro Amps)
   <br>Screenshot:  
   ![qn2](https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/6459cbae-ee45-4229-b111-637d9589c77e)

3. What is the peak current of an advertisement? 
   <br>Answer: 28.21 mA (milli Amps)
   <br>Screenshot:  
   ![qn_3](https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/d8e43971-3ab6-4e6a-91c3-72f73c024c5b)


4. Provide screen shot showing the connection interval setting. Does the connection interval match the values you requested in your slave(server) code, or the master's(client) values?.
   <br>Answer: 44.90 ms (milli seconds)
   <br>Screenshot: 
   ![qn_4](https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/ccc96d23-e520-4402-aae4-35fc5d12c741)


5. What is the average current between connection intervals - i.e. when the MCU is sleeping in EM2. (Don't measure an interval with a LETIMER UF event)?
   <br>Answer: 1.69 uA ( micro Amps)
   <br>Screenshot:  
   ![qn5](https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/82c2856d-b08d-43a6-be02-090ec8c3705d)


7. If possible, provide screen shot verifying the slave latency matches what was reported when you logged the values from event = gecko_evt_le_connection_parameters_id. 
   <br>Answer: I set my slave latency to 4 which is 4 * 75 = 300 ms, nut the slave latency from master client (gecko_evt_le_connection_parameters_id) is 0 and actual interval is 45 ms and observed the interval of 42.5 ms and observed slave latency is 0. From the this we can understand that connection interval is 45 milli-second with 0 slave latency.
   <br>Screenshot:  
   <img width="1439" alt="Screenshot 2024-02-22 at 9 24 10 PM" src="https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/9f7a820f-177e-41d3-9ddf-b55a0053f1e2">

   ![Screenshot 2024-02-22 at 8 38 26 PM (2)](https://github.com/CU-ECEN-5823/ecen5823-assignment5-malolasimman/assets/59477885/604c656f-6be3-4217-8ef1-112beea39e8c)


