# Concept
This neural network takes an image of a constellation as input and returns what constellation it is. It can also work as an autoencoder. 

# How to Run
1. `cmake .`
2. `make`
3. `./starry config/config.json`. The config file can be altered to change topology of the network, 
or to change the path to the data for training, and other tweaks. 


# Resources
+ To set up the neural network in C++, ralampay's neural_network was immensely helpful.   
+ For testing, I used the [Image Constellation Dataset (Kaggle) from Basim Baqai] (https://www.kaggle.com/datasets/basimbaqai/image-constellation-dataset).  


# Potential Improvements
- allow the network to be able to process a picture with multiple constellations
- clean up the repo
- can change loss function to something more suited to this data or optimize learning rate
- need to make optimization because the epochs are running slowly