# Heuristic_Search
Scenario: optimization of a new planned city
A new large sports complex is being built in Delhi. It will have all the highest end equipment and
courts with lots of zones. A zone will house one type of court/equipment. Example, there will be
different zones for basketball courts, table tennis rooms, cardio gym, weight training, yoga
center, swimming pool and so on. Different sportspersons will have different typical schedules of
when they do swimming and when they practice in a court and so on.
Based on typical interest of sports persons and children in Delhi (example, more people want to
be cricketers than volleyball players), some zones will be used more and some will be used less.
Moreover, because it is a large complex, the zones are far from each other, so there will be
walking times involved from one zone to the other based on a user’s personalized schedule. Our
goal is to identify which zone should be at which part of the complex so that (on average) time
spent walking can be reduced.
For that, we assume that we have Z: a set of z zones numbered {1,2,…,z} and L: a set of l locations
numbered {1,2,..,l} such that (z<=l). We define two matrices T (lxl) and N (zxz). An entry tij will
represent the time taken to walk from location i to location j. On the other hand, the entry nxy
will represent the number of daily walks from zone x to zone y. Note that tij =tji , though this is
not true for matrix N. Also, tij =0 if i=j.
Your goal is to output a mapping from Z to L such that the total time walking in a day is minimized.
Input:
The first line has total processing time available in minutes.
The second line has z: the number of zones
The third line has l: the number of locations
Starting fourth line we have the matrix N one row at a time. Assume all times are non-negative integers.
Starting line 4+z, we have the matrix T one row at a time. Assume all entries to be non-negative integers.
Here is a sample input
2
3
4
2 5 3
2 4 1
3 4 5
0 3 4 1
3 0 4 1
4 4 0 8
1 1 8 0
Output:
Your algorithm should return the best allocation of zones to locations, such that one zone is in one location
and one location has only one zone. The output format is a sequence of Z unique numbers, all less than
equal to L. Example, if you decided that in the above problem zone 1 goes to location 2, zone 2 goes to
location 4 and zone 3 goes to location 1, you should output:
2 4 1
The total time to walk for this permutation is 30.
