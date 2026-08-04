#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
//creating first main class
class User { //encapsulation
private:
    string username;
    string password;
    //function to sign up
public:
    void signUp() {
        cout << "SIGN UP TO ENTER THE PROGRAM";
        cout << "\nCreate Username:";
        cin >> username;
        cout << "Create Password:";
        cin >> password;
        cout << "Your account has been created successfully!";
    }
    //sign in function
    bool signIn() {
        string u, p;
        //entering your personal details according to your signup details
        cout << "\nSIGN IN:";
        cout << "Username:";
        cin >> u;
        cout << "Password:";
        cin >> p;
        if (u == username && p == password) {
            cout << "\nLogin Successful!";
            return true;
        }
        else {
            cout << "Invalid Username or Password!";
            return false;
        }
    }
};
//Second main class blue print of the program
class Question {
private:         //private members of variables cant be accessible without any encapsulation outside of class
    string text;
    vector<string> options; 
    vector<int> scores;
public:
    Question(string t, vector<string> o, vector<int> s) {  //creating constructor to get an access to the private values of the class
        text = t;
        options = o;
        scores = s;
    }
    void display() {
        cout << "\nEnter your question" << text << endl;
        for (int i = 0;i < options.size();i++) {
            cout << i + 1 << ". " << options[i] << endl;
        }
    }
    int getScore(int choice) {
        return scores[choice - 1];
    }
};
//Third class to manage the quiz
class Quiz {
private:
    vector<Question>questions;
    int totalScore;
    //we used vector values because vector is used to store multiple values for one answers
public:
    Quiz() {  //constructor
        totalScore = 0;
    }
    //creating a function to add questions in the quiz
    void addQuestion(Question q) {
        questions.push_back(q);
    }
    //creating a function to start the quiz
    void start() {
        int choice;
        //for loop for questions
        for (int i = 0; i < questions.size(); i++) {
            questions[i].display();
            //do-while loop for choices
            do {
                cout << " Choose (1-4): ";
                cin >> choice;
            } while (choice < 1 || choice>4);
            totalScore += questions[i].getScore(choice);
        }
    }
    //function to get totalscore
    int getTotalScore() {
        return totalScore;
    }
    //function to get maximum score
    int getMaxScore() {
        return questions.size() * 4;
    }
};
//creating assesment class
class Assessment {
protected:     //protecting values of this class
    int score;
    int maxScore;

public:
    Assessment(int s, int m) {    //constructor
        score = s;
        maxScore = m;
    }
    virtual void calculateResult() = 0;//abstraction
};

//Result class
class Result :public Assessment {   //Inheritance
public:
    Result(int s, int m) :Assessment(s, m) {}
    //creating function to calculate result
    void calculateResult() { //polymorphism
        float percentage = (float)score / maxScore * 100;
        //output for the result
        cout << "\nRESULT:";
        cout << "\nScore:" << score << "/" << maxScore;
        cout << "\nAnxiety Percentage:" << percentage << "%";
        //condition for anxiety level
        if (percentage <= 40)
            cout << "\nAnxiety Level: LOW";
        else if (percentage <= 70)
            cout << "\nAnxiety Level: MODERATE";
        else
            cout << "\nAnxiety Level: HIGH\n";
    }
};
//Suggestion class according to anxiety level
class Suggestion {
public:
    void showSuggestion(int score, int maxScore) {
        float percent = (float)score / maxScore * 100;
        //Study Suggestion According to calculator
        cout << "\nSTUDY SUGGESTIONS:";
        //Suggestion According to your level
        if (percent >= 70) {
            cout << "\nReduce study time this is creating more panic" << endl;
            cout << "Practice mind relaxation techniques" << endl;
            cout << "Eat Dark chocolate" << endl;
        }
        else if (percent >= 40) {
            cout << "Improve time management" << endl;
            cout << "Take short breaks" << endl;
            cout << "Avoid last-minute study" << endl;
        }
        else {
            cout << "Keep following your routine" << endl;
            cout << "\nStay consistent" << endl;
        }
    }
};
//class for feedback collecting from user
class Feedback {
private:
    int satisfactionLevel;
    string comment;
    //function to collect feedback
public:
    void collectFeedback() {
        cout << "\nFEEDBACK:";

        while (true) {
            try {
                cout << "\nRate your satisfaction (1-5): ";
                cin >> satisfactionLevel;
                if (cin.fail()) {
                    throw runtime_error("Invalid input! Please enter a number between 1 and 5.");
                }

                if (satisfactionLevel < 1 || satisfactionLevel > 5) {
                    throw out_of_range("Satisfaction level must be between 1 and 5.");
                }

                break; // valid input, exit loop
            }
            catch (exception& e) {
                cout << e.what() << endl;
                cin.clear();              // clear error flag
                cin.ignore(1000, '\n');   // discard invalid input
            }
        }

        cout << "Any comments (words only): ";
        cin.ignore(); // clear leftover newline
        getline(cin, comment);

        // Ensure comment is not just digits
        bool onlyDigits = true;
        for (char c : comment) {
            if (!isdigit(c) && !isspace(c)) {
                onlyDigits = false;
                break;
            }
        }

        if (onlyDigits) {
            cout << "Comment must contain words, not just numbers. Setting comment as 'No valid comment'.";
            comment = "No valid comment";
        }

        cout << "Thank you for your feedback!" << endl;
    }

    void displayFeedback() {
        cout << "\nUSER FEEDBACK: ";
        cout << "\nSatisfaction Level:" << satisfactionLevel << "/5";
        cout << "\nComment: " << comment;
    }
};
//MAIN FUNCTION
int main() {
    cout << "STUDY ANXIETY ASSESSMENT CALCULATOR" << endl;
    User student;
    student.signUp();
    //condition
    if (!student.signIn())
        return 0;
    //object for quiz
    Quiz quiz;
    vector<string> options;
    vector<int> scores;
    //choice
    options.push_back("Never");
    options.push_back("Rarely");
    options.push_back("Often");
    options.push_back("Always");
    //scores
    scores.push_back(1);
    scores.push_back(2);
    scores.push_back(3);
    scores.push_back(4);
    //Added Questions 
    quiz.addQuestion(Question("\nDo you feel stressed during studies?", options, scores));
    quiz.addQuestion(Question("\nDo exams disturb your sleep?", options, scores));
    quiz.addQuestion(Question("\nDo deadlines make you anxious?", options, scores));
    quiz.addQuestion(Question("\nDo you feel tired while studying?", options, scores));
    quiz.addQuestion(Question("\nDo you fear failure in exams?", options, scores));
    quiz.addQuestion(Question("\nDo you feel pressure to complete syllabus on time?", options, scores));
    quiz.addQuestion(Question("\nDo you compare your performance with others?", options, scores));
    quiz.addQuestion(Question("\nDo assignments increase your stress level?", options, scores));
    quiz.start();
    //getting result for the quiz
    Result result(quiz.getTotalScore(), quiz.getMaxScore());
    result.calculateResult();
    //give suggestions
    Suggestion s;
    s.showSuggestion(quiz.getTotalScore(), quiz.getMaxScore());
    //give feedback
    Feedback f;
    f.collectFeedback();
    f.displayFeedback();
    //end
    cout << "\nThank you for using Study Anxiety Calculator!" << endl;
    return 0;
}
