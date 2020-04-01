// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include "bayes/image.h"
#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <utility>
#include <fstream>


namespace bayes {

    void saveModelDataToFiles(string priors_file, string matrix_file, Model model) {
        std::ofstream of;
        of.open(priors_file, std::ios::out);
        if (!of) {
            cout << "Something went wrong";
        }
        for (auto prior : model.probabilities_of_priors) {

        }
    }


    double Classifier::GetProbabilityFromMatrix(int row, int col, int num_class, int shade) {
        return model.probs_[row][col][num_class][shade];
    }

    int Classifier::GetClassOfImage(Image image) {
        for (int i = 0; i < kNumClasses; i++) {
            double post_prob = 0;
            post_prob += log(model.probabilities_of_priors.at(i));
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

