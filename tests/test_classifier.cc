// Copyright (c) 2020 Sabar Nimmagadda. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>
#include <bayes/image.h>

bayes::Model model;
bayes::Classifier classifier;
bayes::Image image;

TEST_CASE("Accuracy percentage test") {
    model.train("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/trainingimages",
            "/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/traininglabels", 0.1);
    REQUIRE(classifier.getAccuracyPercentage(model,"/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/testimages",
            "/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/testlabels", 0.1) >= 0.7);
}

TEST_CASE("Invalid Image File") {
    REQUIRE(!model.GetImagesFromFile("HAHAH"));
}

TEST_CASE("Invalid label file") {
    REQUIRE(!model.GetLabelsFromFile("HELLO"));
}

TEST_CASE("Empty file for model file") {
    REQUIRE(!model.GetImagesFromFile("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/priorvector"));
}

TEST_CASE("Empty file for label file") {
    REQUIRE(!model.GetLabelsFromFile("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/priorvector"));
}

TEST_CASE("Test for probility matrix") {
    model.train("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/trainingimages",
                "/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/traininglabels", 1);
    image = model.image_objects.at(0);
    REQUIRE(model.probs_[0][0][0][0] == 1);
}

TEST_CASE("Probability for Class in Labels test") {
    model.train("/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/data/digitdata/trainingimages",
                "/Users/sabarnimmagadda/CLionProjects/naive-bayes-SabarNimmagadda/tests/data/samplelabels", 1);
    REQUIRE(model.ComputeProbabilityOfClassInLabels(0) == 0.33);
}