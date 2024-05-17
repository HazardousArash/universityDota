#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include <string>
#include <map>

    class Assignment {
    public:
        Assignment(std::string name, int maxScore, std::string exp);
        Assignment();
        std::string getName() const;
        int getMaxScore() const;
        std::string getexp() const;  // New getter for the exp
        std::map<std::string, int> getStudentScores() const;
        void setName(std::string name);
        void setMaxScore(int maxScore);
        void setexp(std::string exp);  // New setter for the exp
        void setStudentScores(std::map<std::string, int> studentScores);
        void addScore(std::string studentUsername, int score);

    private:
        std::string name;
        int maxScore;
        std::string exp;  // New member variable for the exp
        std::map<std::string, int> studentScores;  // Maps a student's username to their score
    };
#endif