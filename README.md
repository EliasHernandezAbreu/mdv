# Maximum diversity problem

Maximum diversity problem using greedy, GRASP, etc.

# Pseudo best mean diversity what?

Lets say, having two points, we need to add another 2 for completing the solution, so to
get to upper bound for the partial solution, we can get the maximum distance from any of
the points of the solution to another one, then pretending every new node we would add will
add that much diversity.

Its an upper bound because every node we add to the solution will add less and less diversity
each time, since we use greedy (sometimes grasp, which follows pretty much the same concept)
we already have the best diversity at the start of the problem.
