// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_
#include <bayes/model.h>
#include <cmath>
#include <nlohmann/json.hpp>
#include <fstream>


namespace bayes {
    class Classifier {
    public:
        vector<double>posterior_probabilities;

        Model model;

        void SaveModelDataToFiles(string priors_file, string matrix_file, Model model);

        void LoadModelDataFromFiles(string priors_file, string matrix_file, Model model);

        double GetProbabilityFromMatrix(int row, int col, int num_class, int shade);

        int ReturnClassWithMaxPostProbability();

        int GetClassOfImage(Image image);

        double getAccuracyPercentage(Model mod, const string& image_file, const string& label_file, double smoothing);



    };

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

