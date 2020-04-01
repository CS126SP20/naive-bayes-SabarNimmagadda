// Copyright 2020 Sabar Nimmagadda. All rights reserved.

#include <bayes/classifier.h>
#include "bayes/image.h"
#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <utility>
#include <fstream>


namespace bayes {

    //This function saves all of the training data in 2 separate files.
    void Classifier::SaveModelDataToFiles(const string& priors_file, const string& matrix_file) {
        std::ofstream of;
        of.open(priors_file, std::ios::out);
        if (!of) {
            //prints out an error message.
            cout << "Something went wrong";
        }
        for (auto probs : model.prior_probabilities) {
            of << probs << std::endl;
        }
        of.close();
        of.open(matrix_file, std::ios::out);
        if (!of) {
            //prints out an error message.
            cout << "Something went wrong";
        }
        for (int i = 0; i < kImageSize; i++) {
            for (int j = 0; j < kImageSize; j++) {
                for (int k = 0; k < kNumClasses; k++) {
                    for (int l = 0; l < kNumShades; l++) {
                        of << model.probs_[i][j][k][l];
                    }
                }
            }
        }
        of.close();
    }

    //This function loads the training data from 2 separate files.
    void Classifier::LoadModelDataFromFiles(const string& priors_file, const string& matrix_file) {
        std::ifstream ifs;
        ifs.open(priors_file, std::ios::out);
        if (!ifs) {
            //prints out an error message.
            cout << "Something went wrong";
        }
        double probs;
        while (ifs >> probs) {
            //filling the vector line by line, since each line is a double
            //that represents the prior probability.
            model.prior_probabilities.push_back(probs);
        }
        ifs.close();
        ifs.open(matrix_file, std::ios::out);
        if (!ifs) {
            cout << "Something went wrong";
        }
        for (int i = 0; i < kImageSize; i++) {
            for (int j = 0; j < kImageSize; j++) {
                for (int k = 0; k < kNumClasses; k++) {
                    for (int l = 0; l < kNumShades; l++) {
                        double prob;
                        ifs >> prob;
                        model.probs_[i][j][k][l] = prob;
                    }
                }
            }
        }
        ifs.close();
    }

    //This function returns the probability at a certain position for a specific color and shade.
    double Classifier::GetProbabilityFromMatrix(int row, int col, int num_class, int shade) {
        return model.probs_[row][col][num_class][shade];
    }

    //This function returns the predicted class of a certain image (i.e the number it represents).
    int Classifier::GetClassOfImage(Image image) {
        for (int i = 0; i < kNumClasses; i++) {
            double post_prob = 0;
            post_prob += log(model.prior_probabilities.at(i));
            for (int row = 0; row < kImageSize; row++) {
                for (int col = 0; col < kImageSize; col++) {
                    int shade_of_cell = image.image_grid[row][col];
                    post_prob += log(GetProbabilityFromMatrix(row, col, kNumClasses, shade_of_cell));
                }
            }
            posterior_probabilities.push_back(post_prob);
        }
        return ReturnClassWithMaxPostProbability();
    }

    //This function represents the class with the highest posterior probability.
    int Classifier::ReturnClassWithMaxPostProbability() {
        double max = 0;
        int max_index = 0;
        for (int i = 0; i < 10; i++) {
             if (posterior_probabilities.at(i) > max) {
                 max = posterior_probabilities.at(i);
                 max_index = i;
             }
        }
        //So that the vector gets reset for the next image.
        posterior_probabilities.clear();
        //This is the class with the highest posterior probability.
        return max_index;
    }

    //This gets the accuracy percentage of how many numbers were correctly identified.
    double Classifier::getAccuracyPercentage(Model mod, const string& image_file, const string& label_file, double smoothing) {
        //Setting global variable of class to model parameter.
        model = std::move(mod);
        //This fills in the images and labels vectors.
        model.initialize(label_file, image_file, smoothing);
        int count_of_accurate_evals = 0;
        //Looping through all of the images.
        for (int image_index = 0; image_index < model.image_objects.size(); image_index++) {
            //The class the machine recognises the image to belong to.
            int computed_class = GetClassOfImage(model.image_objects.at(image_index));

            if (computed_class == model.labels.at(image_index)) {
                count_of_accurate_evals++;
            }
        }
        return (double) count_of_accurate_evals/model.image_objects.size() * 100;
    }




}  // namespace bayes

