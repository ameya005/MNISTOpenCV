MNIST Dataset Unpacker:
=======================

Requires OpenCV 2.1 or greater

Generates images of the handwritten digit dataset using OpenCV. Also generates the labels for the testing and training dataset

Usage : 		

				./digitExtractor [] - extracts digits as images
				options: train - unpacks the training dataset indirectory "Train"
						 test - unpacks the test dataset in directory "Test"
						 
			   ./labelExtractor [] - extracts labels and stores them in a text file
			   	options: train - unpacks the training dataset
						 test - unpacks the test dataset				
Note: The folders have to be initially created. 		
			


