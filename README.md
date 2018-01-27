# Graph Coloring

The Graph coloring is a NP-Complete problem and a special case of the graph labeling problem. To simply describe it we can say that is a way of coloring the vertices of a graph such that no two adjacent vertices share the same color, this process is called vertex coloring.

<img src="https://github.com/JuanjoMrt/Graph-Coloring/blob/master/resources/Myciel3_oin.png" width="472" height="384" />


### Graphs
The graphs used in this problem where Graphs based on the Mycielski transformation. These graphs are difficult to solve because they are triangle free (clique number 2) but the coloring number increases in problem size. 
These graph are from Michael Trick ([myciel3](http://mat.gsia.cmu.edu/COLOR/instances/myciel3.col "myciel3"), [myciel4](http://mat.gsia.cmu.edu/COLOR/instances/myciel4.col "myciel4") and [myciel5](http://mat.gsia.cmu.edu/COLOR/instances/myciel5.col "myciel5")) from [this](http://mat.gsia.cmu.edu/COLOR/instances.html#XXMYC "Graphs") website.


Do you want to see the results?, Just read the [report](https://github.com/JuanjoMrt/Graph-Coloring/blob/master/resources/Report.pdf "Report") or 

## Run it yourself
You will need:

* `g++`
* `c++11`

Once you are in the project folder
```sh
$ make
$ ./bin/main
```
And just follow the instructions

### Understand the results
The result in each algorithm will be the best solution, if the algorithm did not have time to find the best solution it will display the best found so far.
In case that the algorithm did not have time to find the best solution you may want to increase the number of iterations or make some kind of [modification](#Modifications).

Also it will be displayed the time in nanoseconds that the algorithm takes and the number of total iterations, in case that the best solution is not found, the number of maximum iterantions will be equal to the total number of iterations.


## Modifications
In the main function you will find a switch to select the method you will like to try.
Feel free to change as you want the parameters that are below the `Values for the .... ALgorithm` in order to see new results or try different tests. By default the graph myciel3 and myciel4 are adjusted automatically to find the best solution.
```cpp
    //Genetic Algorithm 
    
    //Values for the Genetic Algorithm
    max_iterations = 100000; 
    int n_individuals = 20;
    double p_best = 40.0, p_cross = 40.0,p_mutation = 20.0; 
    int min_colors = 0;
```

## License
[MIT](https://github.com/JuanjoMrt/Graph-Coloring/blob/master/LICENSE)

