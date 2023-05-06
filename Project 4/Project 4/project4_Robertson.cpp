/* FILE NAME: project4_Robertson.cpp
* AUTHOR: Brantley Robertson
* SOURCES: I only used the hint that Dr. Li gave.
* ////////////////////////////////////////////////////////////////////////////////////////////
* // TO COMPILE THIS FILE ENTER THIS COMMAND: g++ -std=c++11 project4_Robertson.cpp //
* ////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;


int num_of_questions = 3;
int totalPoints = 0;

//Structure for creating a linked list that holds a trivia question,answer and point amount.
struct triva_node {
	string question;
	string answer;
	int point;
	triva_node* next;
};

//creates a pointer to triva_node.
typedef triva_node* ptr_node;

//Prototypes
void init_question_list(ptr_node& q_list);

void add_question(ptr_node& q_list);

int ask_question(ptr_node q_list, int num_ask);

void Unit_Test();

//creates two versions.
//#define UNIT_TESTING
#define triva_quiz


int main() {
	ptr_node node_list = new triva_node;
	ptr_node node_list_beginning = new triva_node;
	string user_input = "";
	//Creates a new trivia game /
	//Sets up three original questions/
	//Sets up loop for user to input his or her own questions.
	//Quiz questions are stored in linked list.
#ifdef triva_quiz
	init_question_list(node_list);
	node_list_beginning = node_list;

	cout << "*** Welcome to Brantley's trivia quiz game ***\n";

	add_question(node_list);

	while (true) {
		cout << "Continue? (yes/no) ";
		getline(cin, user_input);
		if (user_input == "yes" || user_input == "Yes" || user_input == "YES") {
			add_question(node_list);
			user_input = "";
		}
		else if (user_input == "no" || user_input == "No" || user_input == "NO") {
			break;
		}
		else {
			cout << "Please enter Yes or No." << endl;
		}
	}

	//This is start of Trivia quiz game.
	ask_question(node_list_beginning, num_of_questions);
	cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***";
	return 0;

#endif

	//Method for testing
#ifdef UNIT_TESTING
	Unit_Test();
	return 0;
#endif
}


//initializes the quiz to have these three questions inputted into the linked list.
void init_question_list(ptr_node& q_list) {
	ptr_node Q2 = new triva_node;
	ptr_node Q3 = new triva_node;

	string bob;
	ptr_node Q1 = q_list;
	Q1->question = "How long was the shortest war on record?";
	Q1->answer = "38";
	Q1->point = 100;
	Q1->next = Q2;

	Q2->question = "What was the Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
	Q2->answer = "Bank of Italy";
	Q2->point = 50;
	Q2->next = Q3;

	Q3->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
	Q3->answer = "Wii Sports";
	Q3->point = 20;
	Q3->next = NULL;
}


//gives user the option to add a question to the linked list.
//question is added to the end of the linked list.
void add_question(ptr_node& q_list) {
	string points;
	int convertedPoints;
	ptr_node new_ptr = new triva_node;

	while (q_list->next != NULL) {
		q_list = q_list->next;
	}

	cout << "Enter a new question: ";
	getline(cin, new_ptr->question);

	cout << "Enter an answer: ";
	getline(cin, new_ptr->answer);

	cout << "Enter award points: ";
	getline(cin, points);

	convertedPoints = stoi(points);
	new_ptr->point = convertedPoints;
	q_list->next = new_ptr;
	new_ptr->next = NULL;
	num_of_questions++;
}


//Checks for null value
//Ask the user trivia questions and starts the game
int ask_question(ptr_node q_list, int num_ask) {

	ptr_node cur_ptr = q_list;
	string user_answer = "";

	if (q_list == NULL)
		return 0;
	if (num_ask < 1) {
		cout << "Warning - the number of trivia to be asked must equal to or be larger than 1.";
		return 0;
	}
	else if (num_of_questions < num_ask) {
		cout << "Warning - There is only " << num_of_questions << " trivia in the list.";
		return 0;
	}
	else {
		for (int x = 0; x < num_ask; x++) {
			cout << "Question: " << cur_ptr->question << endl;
			cout << "Answer: ";

			getline(cin, user_answer);

			if (user_answer.compare(cur_ptr->answer) == 0) {
				cout << "Your answer is correct. You receive " << cur_ptr->point << " points." << endl;
				totalPoints += cur_ptr->point;
				cout << "Your total points: " << totalPoints << endl;
				cur_ptr = cur_ptr->next;
			}
			else {
				cout << "Your answer is wrong. The correct answer is: " << cur_ptr->answer << endl;
				cout << "Your total points: " << totalPoints << endl;
				cur_ptr = cur_ptr->next;
			}
		}
		return 0;
	}
}


//Test cases to check whether the methods work.
void Unit_Test() {
	ptr_node node_list = new triva_node;
	totalPoints = 0;
	init_question_list(node_list);

	cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
	ask_question(node_list, 0);
	cout << "\nCase 1 Passed\n\n";

	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
	ask_question(node_list, 1);
	assert(totalPoints == 0);
	cout << "\nCase 2.1 Passed\n\n";

	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
	ask_question(node_list, 1);
	assert(totalPoints == 100);
	totalPoints = 0;
	cout << "\nCase 2.2 Passed\n\n";

	cout << "Unit Test Case 3: Ask all the questions in the linked list." << endl;
	ask_question(node_list, 3);
	totalPoints = 0;
	cout << "\nCase 3 Passed\n\n";

	cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
	ask_question(node_list, 5);
	cout << "\nCase 4 Passed\n\n";

	cout << "\n\n*** End of the Debugging Version ***";
}
