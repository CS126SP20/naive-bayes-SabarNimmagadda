// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include "bayes/image.h"
#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <utility>


namespace bayes {
    void Classifier::SaveModelDataToFiles() {

    }
    void Classifier::InitializeProbabilityOfClassInLabelsVector() {
        probabilities_of_class_in_labels = model.CreateProbabilityOfClassInLabelsVector();
    }



    double Classifier::GetProbabilityFromMatrix(int row, int col, int num_class, int shade) {
        model.setFeatureProbabilityArray();
        return model.probs_[row][col][num_class][shade];
    }

    int Classifier::GetClassOfImage(Image image) {
        InitializeProbabilityOfClassInLabelsVector();
        for (int i = 0; i < kNumClasses; i++) {
            double post_prob = 0;
            post_prob += log(probabilities_of_class_in_labels.at(i));
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

    double Classifier::getAccuracyPercentage(Model mod, string image_file, string label_file, double smoothing) {
        //Setting global variable of class to model parameter.
        model = mod;
        //This fills in the images and labels vectors.
        model.initialize(std::move(label_file), std::move(image_file), smoothing);
        int count_of_accurate_evals = 0;
        //Looping through all of the images.
        for (int image_index = 0; image_index < model.training_image_objects.size(); image_index++) {
            //The class the machine recognises the image to belong to.
            int computed_class = GetClassOfImage(model.training_image_objects.at(image_index));

            if (computed_class == model.training_labels.at(image_index)) {
                count_of_accurate_evals++;
            }
        }
        return (double) count_of_accurate_evals/model.training_image_objects.size() * 100;
    }




}  // namespace bayes

