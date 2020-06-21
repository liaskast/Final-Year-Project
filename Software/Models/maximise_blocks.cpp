// File: maximise_blocks.cpp
// --------------------------------------------------------------------------
// This piece of code is the software the provided results 
// for the dissertation "Data Analysis with Mixed-Integer 
// Optimisation for Scheduling Royal Mail Deliveries" of 
// Athanasios Liaskas student of Imperial College London.
// The code utilised IBM ILOG CPLEX technology 
// as well as concepts discussed in "CuSPLIB:A Library of 
// Single-Machine Cumulative Scheduling Problems"
// of Tallys Yunes.

//Libraries required
#include <ilcplex/ilocplex.h>
#include <strstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>

// We define CPLEX environment.
ILOSTLBEGIN

int
main (void) {

  IloEnv env;
  using namespace std;

  try {
	   
	// **** Start: "Read data" ****

	cout << setprecision(2) << fixed; // Rounds all printed numbers to 2 s.f.

	ifstream filename;

	filename.open("main.dat");

    IloModel model(env);

    IloInt n, m;
    IloInt i, j = 0;

    // the sequence of the data that is read below is, #machines, #jobs, array containing the processing-times of blocks p_j
    // N.B. for the purposes of this problem, we solve a Multiprocesser Scheduling Problem where machine=duty, jobs=blocks

	filename >> m >> n;

    IloFloatArray S(env, n), F(env, m), P(env, m); // array #1 - duty start times,  array #2 - duty finish times, array #3 - processing times of blocks. All are placed in arrays, which we define in this line.

    filename >> P; // processing time of each atomic block is read in from the main.dat file

    filename.close();

    filename.open("start.dat");

    filename >> S; // Start time of duties are read in at the stage from the start.dat file

    filename.close();

    filename.open("end.dat");

    filename >> F; // End time of duties are read in at the stage from the end.dat file

    filename.close();

    /*// Comment out, in case we want to Print data to double check it was read correctly.
    for (j = 0; j < n; j++) {
      cout << P[j] << endl;
      cout << S[j] << endl;
      cout << F[j] << endl;
    }*/

    // **** End: "Read data" ****

    // **** Start Decision Variables ****

    // Declaration of the Decision variables that are going to be used.
    IloArray<IloBoolVarArray> x(env,n);
    IloNumVarArray Y(env);
    IloNum L = 8.417; // the L threshold utilised in the Maximise_Blocks and Minimise_Duties files.

    // Declaration of variable x_ij i.e. the variable that will contain 0 if block j is not executed by duty i, and 1 if block j is executed by duty i.
    for (j = 0; j < n; j++) {
      x[j] = IloBoolVarArray(env,m);
      for (i = 0; i < m; i++) {         
        x[j][i] = IloBoolVar(env);
      }
    }

    // Declaration of Y_i i.e. the variable that will end up containing the makespan.
    for (i = 0; i < m; i++) {
      Y.add(IloNumVar(env, 0.0, IloInfinity , ILOFLOAT));
    }

    // **** End Decision Variables ****

    // **** Start Constraints ****


    // sum_m x__ji = 1 - a block is executed once and only once
    for (j = 0; j < n; j++) {
      IloExpr expr(env);
      for (i = 0; i < m; i++)
        expr += x[j][i];
      model.add(expr <= 1);//Model 3
      expr.end();
    }

    // Model 2 - 3rd constraint & Model 3 - 2nd constraint
    
    // F_i-S_i = sum_j p_j*x__ji
    for (i = 0; i < m; i++) {
      IloExpr expr(env);
      for (j = 0; j < n; j++){
        expr += P[j]*x[j][i];         // In each x[j] vector, indices start at zero
      }

      if(F[i]-S[i] < 0){          // If case the time differnece is negative
    	  model.add(L >= expr); // Introducing a L threshold
      }
      else{
    	  model.add(L >= expr); // Introducing a L threshold
      }

      expr.end();
    }
    

    // **** End Constraints ****

    //  **** Start Objective Function ****

    // Declare objective containing variable 
    IloNumVar objective(env, 0.0, IloInfinity, ILOFLOAT, "objective");

    //Model 3 "Maximize Number of Blocks"
    
    IloExpr expr(env);
    for (j = 0; j < n; j++) {
      for (i = 0; i < m; i++)
        expr += x[j][i];
    }

    model.add(IloMaximize(env, expr));
	
    expr.end();

    //  **** End Objective Function ***

    //  **** Start Solving ****

    IloCplex cplex(model);
    IloTimer timer(env);

    //cplex.exportModel("model.lp"); // Exports in mathematical programming form the model implemented by the code above.

    cplex.setParam(IloCplex::TiLim, 120); // We set a "Time Limit" of 1000 seconds as the timeout for the running of the solver optimising our model.

    timer.start();

    if ( !cplex.solve() ) {
      env.error() << "Model failed." << endl;
      throw(-1);
    }

    timer.stop();

    //  **** End Solving ****

    //  **** Start Printing ****

    env.out() << "Solution status =  " << cplex.getStatus() << endl;
    env.out() << "Solution value  = " << cplex.getObjValue() << endl;
    env.out() << "Elapsed time = " << timer.getTime() << endl;

    IloNumArray valsY(env);
    IloNumArray valsX(env);
    cplex.getValues(valsY, Y); // We place in valsY the optimised value of the Decision Variable Y that containts the makespan.
    env.out() << "Values        = " << valsY << endl;

    // Finding out which machine (duty) each job (block) was executed.

    vector<vector<int> > executedby( m , vector<int> (0, 0));

    for (j = 0; j < n; j++) {
      cplex.getValues(valsX, x[j]); // We place in valsX the optimised value of the Decision Variable x
        for (i = 0; i < m; i++){
          if(valsX[i]>0){
            executedby[i].push_back(j);
          }
        }
    }

    double block_duration = 0;
    double duty_duration = 0;

    ofstream outputfile; //opening file where we will print.
    stringstream ss;
    ss<<L;
    string s;
    ss>>s;
    string str;

    for (i = 0; i < executedby.size(); i++){

      if(F[i]-S[i] < 0){          // In case the time difference is negative.
        duty_duration = F[i]+12-S[i]+12;
      }
      else{
        duty_duration = F[i]-S[i];
      }

      //cout << "duty: " << i+1 << " with start/end (" << S[i] <<", " << F[i] << ") D = " << duty_duration << " executed: ";

      block_duration = 0;

      for (j = 0; j < executedby[i].size(); j++) {

    	//cout << executedby[i][j]+1 <<" (" << P[executedby[i][j]] << "), ";

    	// Prints only the tasks executed by this duty comma separated (by having this and only this line printing all the rest commented out)
    	//cout << executedby[i][j]+1 <<", ";

    	// Prints only the durations of tasks executed by this duty comma separated (by having this and only this line printing all the rest commented out)
    	//cout << P[executedby[i][j]] <<", ";

        block_duration += P[executedby[i][j]]; // Summed into this are the durations of all blocks (jobs) that are executed by this duty (machine) i.e. new duty duration

      }

      //cout << " with duration " << abs(block_duration);
      //cout << " saving: " << abs(duty_duration-block_duration) << " hours";
      //cout << abs(duty_duration-block_duration); // Idle time calculation
      cout << abs(block_duration) << endl;

      /*str.append("/Users/thano.liaskas/git/FYP/example-4/src/Results/durations-","L=",s,".csv");
      outputfile.open();
      outputfile << abs(block_duration) << endl; // My shifts in Duties sheet of excel*/

    }

    outputfile.close();
    //  **** End Printing ****

  }
  catch (IloException& e) {
    cerr << "Concert exception: " << e << endl;
  }
  catch (...) {
    cerr << "Unknown exception" << endl;
  }

  env.end();
  return 0;

}
