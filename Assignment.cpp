#include "Assignment.h"

Assignment::Assignment(std::string name, int maxScore, std::string exp) : name(name), maxScore(maxScore), exp(exp) {}

Assignment::Assignment() {}

std::string Assignment::getName() const { return name; }

int Assignment::getMaxScore() const { return maxScore; }

std::string Assignment::getexp() const { return exp; }  // New getter for the exp

std::map<std::string, int> Assignment::getStudentScores() const { return studentScores; }

void Assignment::setName(std::string name) { this->name = name; }

void Assignment::setMaxScore(int maxScore) { this->maxScore = maxScore; }

void Assignment::setexp(std::string exp) { this->exp = exp; }  // New setter for the exp

void Assignment::setStudentScores(std::map<std::string, int> studentScores) { this->studentScores = studentScores; }

void Assignment::addScore(std::string studentUsername, int score) {
    studentScores[studentUsername] = score;
}
