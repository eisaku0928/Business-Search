# Business-Search
A business search algorithm (k-nearest neighbors and range search) written in the C language.

The program applies a K-dimensional tree in order to create business search functions, utilizing the City of Melbourne Census of Land Use and Employment (CLUE) dataset. First usage is to query a certain geographical coordinate, and locate a business that is nearest to the query point. The second usage is to query a geographical coordinate and select a spacial radius for the algorithm to find businesses from. Implementation in the C language came with the burden of freeing the entire constructed tree, but was an insightful project. Obviously, this algorithm has various real world applications going beyond a simple location search like you would with any map app. For instance if a natural disaster hits, such algorithm can be utilized to effectively and efficiently find the safest location for the citizens to evacuate to. 

# Big-O analysis procedure and results

# Usage of program
