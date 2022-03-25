# Business-Search
A business search algorithm (k-nearest neighbors and range search) written in the C language. This program is an interactive navigation program using spatial census data (specifically the Melbourne Census of Land Use and Employment - CLUE dataset, found [here](https://data.melbourne.vic.gov.au/Business/Business-establishment-and-industry-classification/vesm-c7r2)). Interactive navigation tools like Google Maps and GPS navigation has become commonplace. Implementing this program in C allowed me to understand partly of how they work. 

This project enhanced my abilities with dynamic memory allocation and the application of advanced data structures to real world census data. By experimenting with the program and comparing results to theory, I deepened my understanding of the effects of the size of the problem as well as the algorithms used within the program to the overall computational complexity. Here is the [experimental report](https://github.com/EisakuDanielTanaka/Business-Search/blob/main/lab_report.pdf) I wrote. 

## The program
A k-dimensional (K-D) tree was applied to two business search functions, utilizing the City of Melbourne Census of Land Use and Employment (CLUE) dataset. First usage is to query a certain geographical coordinate, and locate a business that is nearest to the query point. The second usage is to query a geographical coordinate and select a spacial radius for the algorithm to find businesses from. Implementation in the C language came with the burden of freeing the entire constructed tree, but was an insightful project. Obviously, this algorithm has various real world applications going beyond a simple location search like you would with any map app. For instance if a natural disaster hits, such algorithm can be utilized to effectively and efficiently find the safest location for the citizens to evacuate to. 

## The algorithm (about K-D Trees)
A [k-dimensional tree (K-D tree)](https://en.wikipedia.org/wiki/K-d_tree) is a space-partitioning data structure, constructed by multi-dimensional keys. _The Algorithm Design Manual_(Skiena, 2012) discusses that a k-dimensional tree is useful because it automatically "decompose(s) space into a small number of cells", which allows for a efficient spacial search compared to a single dimensional key. 

As with any tree data structure, the construction of the K-D tree can heavily impact the complexity of its search algorithm. An experimentation of the 

## Usage
### Map functionality 1 - Nearest neighbor search
Compile the code using the make file (after cloning the repo and cd'ing to the src file).
```
$ make map1
```

