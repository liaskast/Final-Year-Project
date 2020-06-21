# Final Year Project

This repository contains the software created to produce the results seen in the MEng Final Year Project with title: **"Data Analysis with Mixed-Integer Optimisation for Scheduling Royal Mail Deliveries"**. The report was the main delivarable for this capstone project for my Electronic and Information Engineering degree from Imperial College London. The presentation was the second big deliverable that acted as a supporting document to the report.

## Presentation
A video recording of the presentation can be found [here](https://drive.google.com/file/d/1GWNCE-ttuvUHjM8YBO-D7UrHKGpXaXwI/view?usp=sharing).

## System Specifications
All computations are processed with a 6-core Intel Core i7 CPU running at 2.60GHz with a 16GB RAM memory on a macOS Catalina (version 10.15.4) machine. The models were implemented using C++11 that was compiled with the GNU Compiler Collection (GCC). The solutions were obtained through using the commerical solver CPLEX 12.9. Unless it is specifically stated, all solutions obtained are the optimal ones for the given objective function, set of constraints and decision variables.   

## Abstract
Industrial Operations Research is one of the original and most critical fields highlighting the effectiveness of the theory of optimisation when applied to real-world applications. This work investigates the efficacy of Mixed-Integer Optimisation techniques in scheduling the routes performed by Royal Mail's fleet of postal service vehicles. Our findings although theoretical are designed to be easily transferable to Royal Mail current operational infrastructure , to help the corporation fulfil its same-day mail delivery mandate. 

We show that the current scheduling practices are open to improvement on various aspects through solving Mathematical Programs that generate significantly more optimal schedules with respect to three objectives. We subsequently, select one of those optimal schedules and subject it to an uncertainty study. A Mail Transportation system such as the one run by Royal Mail is vulnerable from numerous aspects to uncertainty-related events. The purpose of the study is to determine the schedules' level of robustness against perturbations that resemble real-life disturbance occurrences. We conclude our project by studying two additional scheduling methodologies within the framework of Robust Optimisation to determine the methodology that best balances the provision of an efficient schedule that also remains robust under the influence of uncertainty.
