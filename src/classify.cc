// Copyright (c) 2020 [Sabar Nimmagadda]. All rights reserved.

#include <bayes/classifier.h>
#include "bayes/image.h"
#include <bayes/model.h>

#include <string>
#include <cstdlib>
#include <iostream>




using std::cin;
using std::cout;
int main(int argc, char** argv) {
    string training_image_file;
    double smoothing_factor;
    double accuracy;
    string training_label_file;
    string image_file;
    string label_file;
    string input;
    bayes::Model model;
    bayes::Classifier classifier;
    cout << "Enter training file for images: ";
    cin >> training_image_file;
    cout << "\n Enter training file for labels: ";
    cin >> training_label_file;
    cout << "\n Enter smoothing factor: ";
    cin >> smoothing_factor;
    cout << "Saving model as files";
    model.train(training_image_file, training_label_file, smoothing_factor);
    classifier.SaveModelDataToFiles("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/priorvector",
            "/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/probmatrix");
    cout <<"\n  Would you like to load the trained model?";
    cin >> input;
    if (input != "yes") {
        cout << "File not loaded, ending program";
        EXIT_SUCCESS;
    }
    classifier.LoadModelDataFromFiles("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/priorvector",
                                    "/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/probmatrix");
    cout << "\n Loaded trained model";
    cout << "\n Enter file for images:  ";
    cin >> image_file;
    cout << "\n Enter file for labels: ";
    cin >> label_file;

    accuracy = classifier.getAccuracyPercentage(model, image_file, label_file, smoothing_factor);
    cout << "\n Your accuracy percent is: " << accuracy;

}
