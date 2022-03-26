# Business-Search
![](https://github.com/EisakuDanielTanaka/Business-Search/blob/main/map.png)

A business search algorithm (k-nearest neighbors and range search) written in the C language. This program is an interactive navigation program using spatial census data (specifically the Melbourne Census of Land Use and Employment - CLUE dataset, found [here](https://data.melbourne.vic.gov.au/Business/Business-establishment-and-industry-classification/vesm-c7r2)). Interactive navigation tools like Google Maps and GPS navigation has become commonplace. Implementing this program in C allowed me to understand partly of how they work. 

This project enhanced my abilities with dynamic memory allocation and the application of advanced data structures to real world census data. By experimenting with the program and comparing results to theory, I deepened my understanding of the effects of the size of the problem as well as the algorithms used within the program to the overall computational complexity. Here is the [experimental report](https://github.com/EisakuDanielTanaka/Business-Search/blob/main/lab_report.pdf) I wrote. 

## The program
A k-dimensional (K-D) tree was applied to two business search functions, utilizing the City of Melbourne Census of Land Use and Employment (CLUE) dataset. First usage is to query a certain geographical coordinate, and locate a business that is nearest to the query point. The second usage is to query a geographical coordinate and select a spacial radius for the algorithm to find businesses from. Implementation in the C language came with the burden of freeing the entire constructed tree, but this was an insightful project. Such search algorithm has various real world applications going beyond a simple location search like you would with any map app. If a natural disaster hits, similar algorithms can be utilized to effectively and efficiently find the safest location for the citizens to evacuate to. 

## The algorithm (about K-D Trees) and usage
A [k-dimensional tree (K-D tree)](https://en.wikipedia.org/wiki/K-d_tree) is a space-partitioning data structure, constructed by multi-dimensional keys. _The Algorithm Design Manual_(Skiena, 2012) discusses that a k-dimensional tree is useful because it automatically "decompose(s) space into a small number of cells", which allows for a efficient spacial search compared to a single dimensional key. 

### Map functionality 1 - Nearest neighbor search
The first function is an interactive map of retrieving data about the nearest point of interest. By accepting (x, y) pair queries from ```stdin```, the code finds the closest business establishment to that location in the dataset, and outputs information about that establishment to an output file. In addition to outputting the data of businesses nearest to the queried coordinate(s), the number of key comparisons performed during the search are also printed to ```stdout```.

To do this, the ```map1``` program will construct a K-D tree to store information in the data file passed in the command line argument. Duplicates, i.e. businesses located at the same exact x, y coordinates are handled by chaining them together in a linked list connected to a single Node in the K-D tree. 

Queries in ```query.txt``` should be entered as x, y pairs separated by a space: ```x y```.

#### Example input

Compile the code using the makefile (after cloning the repo and cd'ing to the src file).
```
$ make map1
```

The program takes two command line arguments and a redirect input from a query file. 
```
$ ./map1 datafile outputfile < queryfile
```

Here is an example input that uses files readily available in this repo.
```
$ ./map1 data.csv out.txt < query.txt
```

Then ```out.txt``` will include information of the businesses located in the nearest geolocation of the query coordinates.

**Example output**:
```
144.959522 -37.800095 --> Census year: 2020 || Block ID: 240 || Property ID: 104466 || Base property ID: 104466 || CLUE small area: Carlton || Business address: Ground 161 Barry Street CARLTON VIC 3053 || Industry (ANZSIC4) code: 4511 || Industry (ANZSIC4) description: Cafes and Restaurants || x coordinate: 144.95928 || y coordinate: -37.80023 || Location: (-37.80023251, 144.9592811) || 
144.959522 -37.800095 --> Census year: 2020 || Block ID: 240 || Property ID: 104466 || Base property ID: 104466 || CLUE small area: Carlton || Business address: 235-253 Barry Street CARLTON 3053 || Industry (ANZSIC4) code: 4400 || Industry (ANZSIC4) description: Accommodation || x coordinate: 144.95928 || y coordinate: -37.80023 || Location: (-37.80023251, 144.9592811) || 
144.959522 -37.800095 --> Census year: 2020 || Block ID: 240 || Property ID: 104466 || Base property ID: 104466 || CLUE small area: Carlton || Business address: 155 Barry Street CARLTON VIC 3053 || Industry (ANZSIC4) code: 8102 || Industry (ANZSIC4) description: Higher Education || x coordinate: 144.95928 || y coordinate: -37.80023 || Location: (-37.80023251, 144.9592811) || 
144.959522 -37.800095 --> Census year: 2020 || Block ID: 240 || Property ID: 104466 || Base property ID: 104466 || CLUE small area: Carlton || Business address: 157 Barry Street CARLTON VIC 3053 || Industry (ANZSIC4) code: 6910 || Industry (ANZSIC4) description: Scientific Research Services || x coordinate: 144.95928 || y coordinate: -37.80023 || Location: (-37.80023251, 144.9592811) || 
144.959522 -37.800095 --> Census year: 2020 || Block ID: 240 || Property ID: 104466 || Base property ID: 104466 || CLUE small area: Carlton || Business address: Part Ground 161 Barry Street CARLTON VIC 3053 || Industry (ANZSIC4) code: 4244 || Industry (ANZSIC4) description: Newspaper and Book Retailing || x coordinate: 144.95928 || y coordinate: -37.80023 || Location: (-37.80023251, 144.9592811) || 
0 0 --> Census year: 2020 || Block ID: 5 || Property ID: 101345 || Base property ID: 101345 || CLUE small area: Melbourne (CBD) || Business address: Kiosk 12, Campbell Arcade MELBOURNE VIC 3000 || Industry (ANZSIC4) code: 4512 || Industry (ANZSIC4) description: Takeaway Food Services || x coordinate:  || y coordinate:  || Location:  || 
...
```

And the number of key comparisons are printed to ```stdout```, as the following:
```
144.959522 -37.800095 --> 139
0 0 --> 1783
```

### Map functionality 2 - Range Search
This is a function that allows the user to find all business establishments within some distance of a query point. The code will accept (x, y, radius) triplets from ```stdin``` (included in a query file), and outputs information of all businesses within the requested radius, and outputs the information about the establishments to an output file. When there are multiple businesses at the same location, all of these records are included in the output. If there are no businesses found within the specified radius, the program produces the word ```NOTFOUND``` as a result. In addition to outputting the data of businesses within the queried radius, the number of key comparisons performed during the search are also printed to ```stdout```.

#### Example input
Use the makefile to compile code.
```
$ make map2
```

Input is similar to function 1, but the query file containes queries entered as x, y, radius triplets separated by spaces ```x y r```:
```
$ ./map2 datafile outputfile < queryfile
```

Here is a recommended example usage:
```
$ ./map2 data.csv out.txt < query.txt
```

**Example output**
When queried the two coordinates of (), here is what is produced in ```out.txt```

```
144.959522 -37.800095 --> NOTFOUND
0 0 --> Census year: 2020 || Block ID: 5 || Property ID: 101345 || Base property ID: 101345 || CLUE small area: Melbourne (CBD) || Business address: Kiosk 12, Campbell Arcade MELBOURNE VIC 3000 || Industry (ANZSIC4) code: 4512 || Industry (ANZSIC4) description: Takeaway Food Services || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 2540 || Property ID: 618478 || Base property ID: 618478 || CLUE small area: Kensington || Business address: Pumping Station No.1 Smith Street KENSINGTON VIC 3031 || Industry (ANZSIC4) code: 2812 || Industry (ANZSIC4) description: Sewerage and Drainage Services || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 2385 || Property ID: 618527 || Base property ID: 618527 || CLUE small area: North Melbourne || Business address: Pumping Station No.5 Sutton Street NORTH MELBOURNE VIC 3051 || Industry (ANZSIC4) code: 2812 || Industry (ANZSIC4) description: Sewerage and Drainage Services || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 2385 || Property ID: 618476 || Base property ID: 618476 || CLUE small area: North Melbourne || Business address: Pumping Station No.2 330 Macaulay Road KENSINGTON VIC 3031 || Industry (ANZSIC4) code: 2812 || Industry (ANZSIC4) description: Sewerage and Drainage Services || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 1108 || Property ID: 678365 || Base property ID: 678365 || CLUE small area: Docklands || Business address: 125 Harbour Esplanade DOCKLANDS VIC 3008 || Industry (ANZSIC4) code: 9499 || Industry (ANZSIC4) description: Other Repair and Maintenance n.e.c. || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 931 || Property ID: 525698 || Base property ID: 525698 || CLUE small area: Parkville || Business address: Antenna Off Brens Drive, PARKVILLE VIC 3052 || Industry (ANZSIC4) code: 5809 || Industry (ANZSIC4) description: Other Telecommunications Services || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 931 || Property ID: 107423 || Base property ID: 107423 || CLUE small area: Parkville || Business address: Antenna Off Brens Drive, PARKVILLE VIC 3052 || Industry (ANZSIC4) code: 5809 || Industry (ANZSIC4) description: Other Telecommunications Services || x coordinate:  || y coordinate:  || Location:  || 
0 0 --> Census year: 2020 || Block ID: 901 || Property ID: 545572 || Base property ID: 545572 || CLUE small area: Parkville || Business address: Substation 146 Opposite 29-53 Ievers Street, PARKVILLE VIC 3052 || Industry (ANZSIC4) code: 2630 || Industry (ANZSIC4) description: Electricity Distribution || x coordinate:  || y coordinate:  || Location:  || 
...
```

The following is printed on ```stdout```:
```
144.959522 -37.800095 --> 21
0 0 --> 32
```



