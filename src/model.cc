// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <bayes/image.h>
using std::ifstream;
namespace bayes {

    bool Model::GetLabelsFromFile(string filepath) {
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
                training_labels.push_back(num_class);
            }
            return true;
    }

    bool Model::GetImagesFromFile(string filepath) {
        if (filepath.empty()) {
            return false;
        }
        std::ifstream read_file(filepath);
        if(!read_file) {
            cout << "Invalid file";
            return false;
        }
        while (!read_file.eof()) {
            Image image;
            string line;
            read_file >> image;
            training_image_objects.push_back(image);
        }
        return true;
    }
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

    double Model::ComputeProbOfFeature(int row, int col, int num_class, int shade) {
        int count_of_nums_of_class = 0;
        int count_of_shade_at_position = 0;
        for (long i = 0; i < training_labels.size(); i++) {
            if (training_labels.at(i) == num_class) {
                count_of_nums_of_class++;
            }

            Image image = training_image_objects.at(i);
            if (MostCommonShadeInFeature(row, col, image) == shade) {
                count_of_shade_at_position++;
            }
        }
        return (smoothing_factor + count_of_shade_at_position)
               / (2*smoothing_factor + count_of_nums_of_class);
    }


    double Model::ComputeProbabilityOfClassInLabels(int num_class) {
        int count_of_nums_of_class = 0;
        for (long i = 0; i < training_labels.size(); i++) {
            if (training_labels.at(i) == num_class) {
                count_of_nums_of_class++;
            }
        }
        return (double) count_of_nums_of_class / training_labels.size();
    }

    std::vector<double> Model::CreateProbabilityOfClassInLabelsVector() {
        vector<double> probabilities_of_class_in_labels;
        for (int i = 0; i < kNumClasses; i++) {
            double probability_of_class = ComputeProbabilityOfClassInLabels(i);
            probabilities_of_class_in_labels.push_back(probability_of_class);
        }
        return probabilities_of_class_in_labels;
    }

    void Model::setFeatureProbabilityArray(Image image) {
        for (int i = 0; i < kImageSize; i++) {
            for (int j = 0; j < kImageSize; j++) {
                for (int k = 0; k < kNumClasses; k++) {
                    int l = 0;
                    if (image.image_grid[i][j] == 1) {
                       l = 1;
                    }
                    probs_[i][j][k][l] = ComputeProbOfFeature(i, j ,k ,l);
                }
            }
        }
    }




}  // namespace bayes

