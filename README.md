# Final Year Project (FYP)

This repository contains the main deliverables and software designed to produce the results seen in the MEng Final Year Project with title: **"Data Analysis with Mixed-Integer Optimisation for Scheduling Royal Mail Deliveries"**. The [report](Report/final_report.pdf) is the main delivarable for this capstone project for my Electronic and Information Engineering degree from Imperial College London. The [presentation](Presentation/slides_pdf.pdf) is the second big deliverable that acts as a supporting document to the report.

## Deliverables 
- ### Report
The final version of the Dissertation Report can be found [here](Report/final_report.pdf).

- ### Presentation
A video recording of the [presentation](Presentation/slides_pdf.pdf) can be found [here](https://drive.google.com/file/d/1nsZAzNGbp6vyK989YXSHSLXST2vk3n8o/view?usp=sharing).

## Project Abstract
Industrial Operations Research is one of the original and most critical fields highlighting the effectiveness of the theory of optimisation when applied to real-world applications. This work investigates the efficacy of Mixed-Integer Optimisation techniques in scheduling the routes performed by Royal Mail's fleet of postal service vehicles. Our findings although theoretical are designed to be easily transferable to Royal Mail current operational infrastructure , to help the corporation fulfil its same-day mail delivery mandate. 

We show that the current scheduling practices are open to improvement on various aspects through solving Mathematical Programs that generate significantly more optimal schedules with respect to three objectives. We subsequently, select one of those optimal schedules and subject it to an uncertainty study. A Mail Transportation system such as the one run by Royal Mail is vulnerable from numerous aspects to uncertainty-related events. The purpose of the study is to determine the schedules' level of robustness against perturbations that resemble real-life disturbance occurrences. We conclude our project by studying two additional scheduling methodologies within the framework of Robust Optimisation to determine the methodology that best balances the provision of an efficient schedule that also remains robust under the influence of uncertainty.

## Acknowledgements
The first half of the dissertation was undertaken under the supervision of [Dr Ruth Misener](https://github.com/rmisener), while the remaining part was completed with help from [Dr Dimitrios Letsios](https://github.com/dimletsios).

 - I would like to thank [Dr Ruth Misener](https://github.com/rmisener) for her advice as well as for enabling my cooperation with Royal Mail by organising this project. 

 - I would also like to express my thanks to my supervisor [Dr Dimitrios Letsios](https://github.com/dimletsios) for his continuous support and guidance throughout my MEng Thesis.

*The dissertation was undertaken in consultation with Royal Mail's Data Science Group.*

## System Specifications
All computations are processed with a 6-core Intel Core i7 CPU running at 2.60GHz with a 16GB RAM memory on a macOS Catalina (version 10.15.4) machine. The models were implemented using C++11 that was compiled with the GNU Compiler Collection (GCC). The solutions were obtained through using the commerical solver CPLEX 12.9. Unless it is specifically stated, all solutions obtained are the optimal ones for the given objective function, set of constraints and decision variables.   

## Data Confidentiality Disclaimer
Our parntership with Royal Mail's Data Science Group does not permit the sharing of data for confidentiality purposes. As a result, folder [Data Files](Software/Data_Files_Example) contains templates that are provided to illustrate an exemplary structure of the data files utilised to generate the results in the [report](Report/final_report.pdf). A user could utilise the [models](Software/Models) by supplying their own data that obeys the structure of the data files in the [Data Files](Software/Data_Files_Example) folder.

