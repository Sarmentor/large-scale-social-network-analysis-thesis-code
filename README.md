# large-scale-social-network-analysis-thesis-code

Throughout this document we present an in depth study and analysis of very large scale social networks. Besides the explanation of how to use and install several tools available, we explain in detail the basis of these tools. 
Several algorithms will be used to give the reader knowledge of different tools and technique results. Using tools like Graphlab or using Hadoop and Hadoop Map Reduce based tools like Pegasus or Giraph we will compute some important metrics. We will also use an optimized tool for graph analysis, it is called Snap (Stanford Network Analysis Platform). Although this tool is not inherently a parallel computing one, it can serve as a reference for non parallel graph analysis software. Several metrics will be computed for several different size networks including a case study using data previously achieved from the CrunchBase databases. One of this particular Crunchbase network has relationships between technological companies and financial organizations. Another network is also derived from Crunchbase databases with relationships between persons and technological companies.  
Finally, using parallel computing paradigm, two distinct algorithms will be implemented, a community detection algorithm and also a similarity ranking algorithm. Both algorithms behavior will also be subject of studies with test networks.

Please follow the link to the thesis for more information:

https://www.researchgate.net/publication/259943219_Large_Scale_Social_Networks_Analysis

Some more notes about the code:

/*###############################################################################
#		Community Label Propagation Algorithm 				                              #
#		from Soman and Narang (2011).					                                      #
#										                                                            #
#	Implementation version with Green-Marl Language				                        #
#	by Rui Sarmento								                                                #
#	for "Large Scale Social Network Analysis"				                              #
#	Master Thesis - 2013							                                            #
#										                                                            #
################################################################################*/


To use the developed Community Algorithm code follow this procedure:

1 - Install Green-Marl software in your Hardware (follow instructions on thesis Document)

2 - Copy communities-algo.gm file to $(top)/apps/src Green-Marl folder

3 - Copy communities-algo_main.cc file to $(top)/apps/output_cpp/src Green-Marl folder

4 - go to $(top)/apps/ folder and add the name of the algorithm ("communities-algo")
    to the file Programs.mk (for more information on this please see Green-Marl webpages and guide manuals)
	
5 - on the $(top)/apps folder run the command "make gen"

6 - on the $(top)/apps folder run the command "make bin"

7 - go to $(top)/apps/output_cpp/bin folder and run "./communities-algo"

8 - Note: Edge Lists of your data should be on the point 7 folder

9 - Note: Algorithm only accepts non weighted edge lists

10 - Enjoy the software

/*###############################################################################
#		Similarity Ranking Algorithm 					                                      #
#		Jeh and Widom (2002)						                                            #
#										                                                            #
#	Implementation version with Green-Marl Language				                        #
#	by Rui Sarmento								                                                #
#	for "Large Scale Social Network Analysis"				                              #
#	Master Thesis - 2013							                                            #
#										                                                            #
################################################################################*/


To use the developed SimRank code follow this procedure:

1 - Install Green-Marl software in your Hardware (follow instructions on thesis Document)

2 - Copy simrank.gm file to $(top)/apps/src Green-Marl folder

3 - Copy simrank_main.cc file to $(top)/apps/output_cpp/src Green-Marl folder

4 - go to $(top)/apps/ folder and add the name of the algorithm ("simrank")
    to the file Programs.mk (for more information on this please see Green-Marl webpages and guide manuals)
	
5 - on the $(top)/apps folder run the command "make gen"

6 - on the $(top)/apps folder run the command "make bin"

7 - go to $(top)/apps/output_cpp/bin folder and run "./simrank"

8 - Note: Edge Lists of your data should be on the point 7 folder

9 - Note: Algorithm only accepts non weighted edge lists

10 - Enjoy the software



