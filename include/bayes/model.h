// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include "image.h"

#include <cstdlib>


namespace bayes {

constexpr size_t kNumClasses = 10;
// Shaded or not shaded.
constexpr size_t kNumShades = 2;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
class Model {

public:
    //This is a vector of image objects.
    std::vector<Image> image_objects;

    //This is the laplace smoothing factor, which is used in some computations.
    double smoothing_factor;

    //This is the vector of labels corresponding to the images.
    std::vector<int> labels;

    //This is the vector corresponding to the prior probabilities.
    std::vector<double> prior_probabilities;

    //This is the matrix that contains the probability of whether a specific pixel for a specific class is shaded or not.
    double probs_[kImageSize][kImageSize][kNumClasses][kNumShades];

    /**
     * This function is used to get data from the label and image files
     * and fill in the respective vectors.
     * It is called in the getAccuracyPercentage function of the Classifier.
     * @param label_file the file which has all the labels.
     * @param image_file the file which has all the images to be classified.
     * @param smoothing the laplace smoothing variable used in computation.
     */
    void initialize(const string& label_file, const string& image_file, double smoothing);

    /**
     * This is used to fill in the labels vector from a file.
     * @param filepath the file containing the labels.
     */
    void GetLabelsFromFile(const string& filepath);

    /**
     * This is used to fill in the image object vector from a file.
     * @param filepath the file containing the images to be classified.
     */
    void GetImagesFromFile(const string& filepath);

    /**
     * This computes the probability of whether
     * a specific pixel for a specific class is shaded or not.
     * @param row the row of the pixel.
     * @param col the column of the pixel.
     * @param num_class the label for which the probability is being computed.
     * @param color the shade for which the probability is being computed.
     * @return the probability for a specific class is shaded or not.
     */
    double ComputeProbOfFeature(int row, int col, int num_class, int color);

    /**
     * The most common shade in a feature, which is used in the ComputeProbOfFeature() function.
     * A feature is a part of the grid of row*col dimensions for a given image object.
     * @param rows one dimension of the feature.
     * @param col the second dimension of the feature.
     * @param image the image for which the most common shade is being determined.
     * @return the most common shade (0, or 1).
     */
    int MostCommonShadeInFeature(int rows, int col, Image image);

    /**
     * Finds the probability of a certain class to be in the training labels.
     * @param numberclass the class whose probability is being calculated.
     * @return the probability of a certain class to be in the training labels.
     */
    double ComputeProbabilityOfClassInLabels(int numberclass);

    /**
     * This fills in the probs_ matrix.
     */
    void setFeatureProbabilityArray();

    /**
     * This function sets the prior_probabilities vector.
     */
    void setPriorProbabilitiesVector();

    /**
     * This is called to train the program for classification.
     * It is called in the beginning of the execution of this program.
     * @param image_file the file of training images.
     * @param label_file the file of training labels.
     * @param smoothing the smoothing constant.
     */
    void train(const string& image_file, const string& label_file, double smoothing);


};

}  // namespace bayes

#endif  // BAYES_MODEL_H_
