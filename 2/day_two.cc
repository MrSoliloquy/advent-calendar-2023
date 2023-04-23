/**
 * @author Conor Rojas
 * @date 4/23/23
 * @brief The Evles are running a giant Rock Paper Scissors tournament.
 * The first column is what your opponent is going to play: A for Rock, B for Paper, and C for Scissors. The second column
 * is what you should play in response: X for Rock, Y for Paper, and Z for Scissors. The winner of the whole tournament is
 * the player with the highest score. Your total score is the sum of your scores for each round. The score for a single
 * round is the score for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score for the outcome
 * of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).
 *
 * Exercise 1: What would your total score be if everything goes exactly according to your strategy guide?
 * Exercise 2: Now, the second column says how the round needs to end: X means you need to lose, Y means you
 * need to end the round in a draw, and Z means you need to win. What would your total score be if everything 
 * goes exactly according to your strategy guide?"
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum class Selection {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 3,
};

enum class Result {
  LOST = 0,
  DRAW = 3,
  WON = 6,
};


void splitLine(std::string &line, char &opponent_play, char &my_play);

/**
 * @brief Reads a file and store the input in a pair vector
 * @return A vector of pairs
*/
std::vector<std::pair<char, char>> readFile() {
  std::fstream file;
  file.open("strategy.txt", std::ios::in);
  if (!file) {
    std::cerr << "The file could not be open!\n";
    exit(EXIT_FAILURE);
  }
  std::string line;
  char opponent_play, my_play;
  std::vector<std::pair<char, char>> plays;
  while (getline(file, line)) {
    splitLine(line, opponent_play, my_play);
    plays.emplace_back(std::make_pair(opponent_play, my_play));
  }
  return plays;
}

/**
 * @brief Stores in two different variables the opposing's player selection and your selection
 * @param line Line that stores both selections
 * @param opponent_play Char which will store the opponent's selection
 * @param my_play Char which will store your selection
*/
void splitLine(std::string &line, char &opponent_play, char &my_play) {
  std::stringstream plays_stream;
  plays_stream.str(line);
  plays_stream >> opponent_play >> my_play;
}

/**
 * (This solve the exercise 1)
 * @brief Converts the char given by the player to the corresponding play: Rock, paper o scissors
 * @param plays Pair vector that stores the char chosen by each player
 * @return Pair vector that stores the corresponding play
*/
std::vector<std::pair<Selection, Selection>> whats_on_your_hand(std::vector<std::pair<char, char>> &plays) {
  std::vector<std::pair<Selection, Selection>> play_selection;
  for (const auto play: plays) {
    Selection opponent_play, my_play;
    switch (play.first) {
      case 'A':
        opponent_play = Selection::ROCK;
        break;
      case 'B':
        opponent_play = Selection::PAPER;
        break;
      case 'C':
        opponent_play = Selection::SCISSORS;
        break;
      default:
        std::cerr << "Invalid play: " << play.first << std::endl;
        continue;
    }
    switch (play.second) {
      case 'X':
        my_play = Selection::ROCK;
        break;
      case 'Y':
        my_play = Selection::PAPER;
        break;
      case 'Z':
        my_play = Selection::SCISSORS;
        break;
      default:
        std::cerr << "Invalid play: " << play.second << std::endl;
        continue;
    }
    play_selection.emplace_back(std::make_pair(opponent_play, my_play));
  }
  return play_selection;
}

/**
 * (This solve the exercise 2)
 * @brief Converts the char given by the opposing player to the corresponding play: Rock, paper o scissors.
 * And converts your char in the play that satisfy the following: X means you need to lose, Y means you
 * need to end the round in a draw, and Z means you need to win.
 * @param plays Pair vector that stores the char chosen by each player
 * @return Pair vector that stores the corresponding play
 */
std::vector<std::pair<Selection, Selection>> whats_should_you_play(std::vector<std::pair<char, char>> &plays) {
  std::vector<std::pair<Selection, Selection>> play_selection;
  for (const auto play: plays) {
    Selection opponent_play, my_play;
    switch (play.first) {
      case 'A':
        opponent_play = Selection::ROCK;
        break;
      case 'B':
        opponent_play = Selection::PAPER;
        break;
      case 'C':
        opponent_play = Selection::SCISSORS;
        break;
      default:
        std::cerr << "Invalid play: " << play.first << std::endl;
        continue;
    }
    switch (play.second) {
      case 'X':
        if (opponent_play == Selection::ROCK) {
          my_play = Selection::SCISSORS;
        } else if (opponent_play == Selection::PAPER) {
          my_play = Selection::ROCK;
        } else {
          my_play = Selection::PAPER;
        }
        break;
      case 'Y':
        my_play = opponent_play;
        break;
      case 'Z':
        if (opponent_play == Selection::ROCK) {
          my_play = Selection::PAPER;
        } else if (opponent_play == Selection::PAPER) {
          my_play = Selection::SCISSORS;
        } else {
          my_play = Selection::ROCK;
        }
        break;
      default:
        std::cerr << "Invalid play: " << play.second << std::endl;
        continue;
    }
    play_selection.emplace_back(std::make_pair(opponent_play, my_play));
  }
  return play_selection;
}

/**
 * @brief Given the play of both players in each round, the sum of your total points is calculated
 * @param game Pair vector that stores each game
 * @return The sum your total points.
*/
int sumPoints(std::vector<std::pair<Selection, Selection>> &game) {
  int total_points{0};
  int draw_points = static_cast<int>(Result::DRAW);
  int lost_points = static_cast<int>(Result::LOST);
  int won_points = static_cast<int>(Result::WON);
  for (const auto value: game) {
    int points_on_your_hand = static_cast<int>(value.first);
    int points_on_my_hand = static_cast<int>(value.second);
    if (value.first == value.second) {
      total_points += (draw_points + points_on_my_hand);
    } else if ((value.first == Selection::ROCK && value.second == Selection::PAPER) || (value.first == Selection::PAPER && value.second == Selection::SCISSORS) || (value.first == Selection::SCISSORS && value.second == Selection::ROCK)) {
      total_points += (won_points + points_on_my_hand);
    } else {
      total_points += (lost_points + points_on_my_hand);
    }
  }
  return total_points;
}

int main() {
  std::vector<std::pair<char, char>> plays = readFile();
  std::vector<std::pair<Selection, Selection>> play_selection = whats_on_your_hand(plays);
  std::cout << "Your total points are: " << sumPoints(play_selection) << std::endl;
  std::vector<std::pair<Selection, Selection>> play_selection2 = whats_should_you_play(plays);
  std::cout << "Based on the information provided, now your total points are: " << sumPoints(play_selection2) << std::endl;
  return 0;
}