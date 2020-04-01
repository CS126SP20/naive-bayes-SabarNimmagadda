// Copyright 2020 Sabar Nimmagadda. All rights reserved.

#include <bayes/model.h>
#include <fstream>
#include <bayes/image.h>

using std::ifstream;
namespace bayes {

    //This generates the label vector.
    //Made as a boolean for testing.
    bool Model::GetLabelsFromFile(const string& filepath) {
        if (filepath.empty()) {
            return false;
        }
        std::ifstream read_file(filepath);
        if(!read_file) {
            cout << "Invalid file";
            return false;
        }
        int num_class;
        while (read_file >> num_class) {
            labels.push_back(num_class);
        }
        return true;
    }

    //This creates the vector of images.
    //Made as a boolean for testing.
    bool Model::GetImagesFromFile(const string& filepath) {
        if (filepath.empty()) {
            return false;
        }
        std::ifstream read_file(filepath);
        if(!read_file) {
            cout << "Invalid file";
            return false;
        }
        string line;
        while (std::getline(read_file,line)){
            Image image;
            //This is the overloaded operator that generates the grid.
            read_file >> image;
            image_objects.push_back(image);
        }
        return true;
    }

    //This initializes the smoothing factor, and creates the vectors for labels and images.
    void Model::initialize(const string& label_file, const string& image_file, double smoothing) {
        smoothing_factor = smoothing;
        GetImagesFromFile(image_file);
        GetLabelsFromFile(label_file);
    }

    //This returns the most common shade in a certain feature.
    int Model::MostCommonShadeInFeature(int row, int col, Image image) {
        int whiteCount = 0;
        int shadedCount = 1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (image.image_grid[i][j] == 0) {
                    whiteCount++;
                } else {
                    shadedCount++;
                }
            }
        }
        if (whiteCount > shadedCount) {
            return 0;
        }
        return 1;
    }

    //Computes the likelihood of a feature being shaded or not.
    double Model::ComputeProbOfFeature(int row, int col, int num_class, int shade) {
        int count_of_nums_of_class = 0;
        int count_of_shade_at_position = 0;
        for (long i = 0; i < labels.size(); i++) {
            if (labels.at(i) == num_class) {
                count_of_nums_of_class++;
            }

            Image image = image_objects.at(i);
            if (MostCommonShadeInFeature(row, col, image) == shade) {
                count_of_shade_at_position++;
            }
        }
        return (smoothing_factor + count_of_shade_at_position)
               / (2*smoothing_factor + count_of_nums_of_class);
    }

    //This returns the probability of a number to be a label.
    double Model::ComputeProbabilityOfClassInLabels(int num_class) {
        int count_of_nums_of_class = 0;
        for (long i = 0; i < labels.size(); i++) {
            if (labels.at(i) == num_class) {
                count_of_nums_of_class++;
            }
        }
        return (double) count_of_nums_of_class / labels.size();
    }

    //This sets the prior_probabilities vector
    void Model::setPriorProbabilitiesVector() {

        for (int i = 0; i < kNumClasses; i++) {
            double probability_of_class = ComputeProbabilityOfClassInLabels(i);
            prior_probabilities.push_back(probability_of_class);
        }

    }

    //This sets the probs_ array.
    void Model::setFeatureProbabilityArray() {
        for (int i = 0; i < kImageSize; i++) {
            for (int j = 0; j < kImageSize; j++) {
                for (int k = 0; k < kNumClasses; k++) {
                    for (int l = 0; l < kNumShades; l++) {
                        probs_[i][j][k][l] = ComputeProbOfFeature(i, j ,k ,l);
                    }
                }
            }
        }
    }

    //This is used to training by accessing the training files.
    void Model::train(const string& image_file, const string& label_file, double smoothing) {
        smoothing_factor = smoothing;
        GetImagesFromFile(image_file);
        GetLabelsFromFile(label_file);
        setFeatureProbabilityArray();
        setPriorProbabilitiesVector();
    }




}  // namespace bayes

