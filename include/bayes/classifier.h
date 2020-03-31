// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_
#include <bayes/model.h>
#include <cmath>


namespace bayes {
    class Classifier {
    public:
        vector<double> probabilities_of_class_in_labels;

        vector<double>posterior_probabilities;

        Model model;


        void SaveModelDataToFiles();

        void InitializeProbabilityOfClassInLabelsVector();

        double GetProbabilityFromMatrix(int row, int col, int num_class, int shade);

        double GetPosteriorProbabilityFromVector(Model model);

        int ReturnClassWithMaxPostProbability();

        int GetClassOfImage(Image image);

        double getAccuracyPercentage(Model mod, string image_file, string label_file, double smoothing);
    };

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

