In this program  we use  Workload Generation (Poisson Dist.) to figure out the actual number of arrivals which will give us an actual average of arrivals per second . First , through each iteration, we add up the value that is given by the Workload Generation (Poisson Dist.) into a variable. At the end of the for loop, we divide the  total amount of process by the variable that holds to the total arrive times to find out the actual number of arrivals per second.

 We will also  use the  Workload Generation (Exp. Dist.) to figure out the service times for each arrival. This equation will also allow us to figure out the actual service time average. We will add up all service times and store them in a variable. At the end of the for loop we will divide the total service time by the number of processes to get the actual average service time.
 
The image below shows the number of the current process the total arrival time of all processes , and the service time of the current process.
 
 ![image](https://user-images.githubusercontent.com/70728294/225653365-54c7c292-ac0c-4f58-a268-c16b2be18459.png)
 
 The next image shows the results of the generator.
 
 ![image](https://user-images.githubusercontent.com/70728294/225658985-dee73552-22f5-4fd1-a5ef-9716b0fdfc2e.png)

