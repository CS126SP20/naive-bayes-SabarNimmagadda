// Copyright (c) 2020 Sabar Nimmagadda. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_
#include <bayes/model.h>
#include <cmath>
#include <nlohmann/json.hpp>
#include <fstream>


namespace bayes {

    class Classifier {

    public:
        //The vector containing all the posterior probabilities.
        vector<double>posterior_probabilities;

        //The model object used to access all its functions.
        Model model;

        /**
         * This function is called after the training is complete.
         * It is to save all of the training data into a file.
         * @param priors_file the file where the probabilities_of_priors vector is stored.
         * @param matrix_file the file that stores the matrix of feature probabilities.
         */
        void SaveModelDataToFiles(const string& priors_file, const string& matrix_file);

        /**
         * This function is called after the testing files are inputted.
         * It is used to read the files where the training data is stored.
         * @param priors_file the file where the probabilities_of_priors vector is stored.
         * @param matrix_file the file that stores the matrix of feature probabilities.
         */
        void LoadModelDataFromFiles(const string& priors_file, const string& matrix_file);

        /**
         * This function is used to access individual elements of the probs_ matrix.
         * It basically calculates the probability for a certain cell of a shade to be a specific number.
         * @param row the row of the grid.
         * @param col the column of the grid.
         * @param num_class the number this probability is being calculated for.
         * @param shade the shade this probability is being calculated for (shaded or not).
         * @return the probability  for a certain cell of the grid of a specific shade to be a specific number.
         */
        double GetProbabilityFromMatrix(int row, int col, int num_class, int shade);

        /**
         * This function returns the number for which
         * the posterior probability is the highest.
         * @return the number classification (0-9).
         */
        int ReturnClassWithMaxPostProbability();

        /**
         * This is the function which predicts which number an image represents.
         * @param image the image object which is being classified.
         * @return the class of the image (0-9).
         */
        int GetClassOfImage(Image image);

        /**
         * This function checks the percentage of a certain set of
         * images which correctly represent their corresponding labels.
         * @param mod the model object parameter which initialises the global model object
         * used in multiple called functions.
         * @param image_file the file in which the set of images are stored.
         * @param label_file the file in which the set of labels are stored.
         * @param smoothing the laplace factor used for calculation.
         * @return the accuracy percentage of the classifier.
         */
        double getAccuracyPercentage(Model mod, const string& image_file, const string& label_file, double smoothing);
    };

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

