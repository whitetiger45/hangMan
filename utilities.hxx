#ifndef UTILITIES_HXX
#define UTILITIES_HXX

#include <cctype>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <typeinfo>
#include <vector>
#include "hangman.hxx"

typedef bool tf;
typedef char l;
typedef double d;
typedef signed int si;
typedef unsigned int usi;
typedef struct tm * guessTime;
typedef std::map<l,si> LetterTrackingMap;
typedef std::map<l,si>::iterator LetterTrackingMapIT;
typedef std::vector<std::string> HangmanDictionary;
typedef std::map<si, si> RecordBookMap;
typedef std::map<si, si>::iterator RecordBookMapIT;

#define func(n, a) void show##n(){std::cout << a << "\n";}
func(Title, "\n\t   ***********\n\t   * Hangman *\n\t   ***********\n\t ______\n\t|     |\n\t|    \n\t|           o\n\t|          /|\\ \n\t|______    / \\\n\t*****************\n")
func(Menu, "\n\t Main Menu\n\t =========    \n     1: Survival Mode\n     2: Timed Mode\n     3: Regular Mode\n     4: High Scores\n     5: Quit\n")
func(MenuWithStatsOption, "\n\t Main Menu\n\t =========    \n     1: Survival Mode\n     2: Timed Mode\n     3: Regular Mode\n     4: Last Game Stats\n     5: High Scores\n     6: Quit\n")
func(SubMenu, "\nWhat would you like to do?\n_______________________________\n\n1) Guess Letter\n2) Guess Word\n3) See what letters you've guessed\n4) Show Unfinished Word\n5) How Many Incorrect Guesses Left?\n6) Display HangMan Board\n7) Exit App\n_______________________________\n")
func(SubMenuWithReturnToGameModeOption, "\nWhat would you like to do?\n_______________________________\n\n1) Guess Letter\n2) Guess Word\n3) See what letters you've guessed\n4) Show Unfinished Word\n5) How Many Incorrect Guesses Left?\n6) Display HangMan Board\n7) Return To Game Mode Menu\n8) Quit\n_______________________________\n")
#undef func

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "\nWhat letter would you like to guess?\n(Enter 1 to go back to main menu)")
func(PlayAgain, "\n(Type 's' to see your current stats and 'm' to return to mode selection menu)\nPlay again? [n/y/s/m]: ")
func(ForSuspectedWord, "What do you think the word is?")
#undef func

//------------------------------------------------------------------------------------------------------------------------
//scoreboard stuff
sig_atomic_t userScoreSurvivorMode = 0;
sig_atomic_t userScoreTimedMode = 0;
sig_atomic_t userScoreRegularMode = 0;
sig_atomic_t totalGames = 0;

#define func(n, a, b, c) void declare##n(int param){std::cout << a ; ++b; ++c;}
func(UserWinsRoundRegularMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreRegularMode, totalGames)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(UserWinsRoundSurvivorMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreSurvivorMode)
func(UserWinsRoundTimedMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreTimedMode)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(OutOfGuesses, "\nSorry, you are out of guesses...\n\nThe word was: ", totalGames)
#undef func

#define func(n, a, b, c) void declare##n(si param1, std::string param2){std::cout << a  << param1 << " seconds." << b <<  param2 << std::endl; ++c;}
func(OutOfTime, "\nYou took too long to answer...Game Over.\nTime to make last guess: ", "\n\nThe word was: ", totalGames)
#undef func

#define func(n, a, b) void score##n(){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << a << "  |            " << b << "                   |           " << std::setprecision(2) <<(d(d(a)/d(b)) * 100) << "\%      \n";}
func(BoardRegularMode, userScoreRegularMode, totalGames)
#undef func

#define func(n) void score##n(si modeScore, d gamesPlayed){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << modeScore << "  |            " << std::setprecision(0) << gamesPlayed << "                   |          " << std::setprecision(2) <<(d(d(modeScore)/d(gamesPlayed)) * 100) << "\%      \n";}
func(Board)
#undef func

#define func(n, a) void score##n(){ std::cout << std::fixed << "\nYou survived: " << a << " rounds\n";}
func(BoardSurvivorMode, userScoreSurvivorMode)
func(BoardTimedMode, userScoreTimedMode)
#undef func
//------------------------------------------------------------------------------------------------------------------------

auto lineWrapper = [](std::string lineToWrap, l c){for(si i = 0; i < lineToWrap.size(); i++)std::cout << c; std::cout << "\n";};

auto addWhiteSpaceAndEndlChar = 
[](std::string &appendStr, std::string wrapperString, si i)
    {
        while(appendStr.length() < wrapperString.length()-1)
        appendStr += " ";
        appendStr += "*";
        std::cout << appendStr << "\n";
    };

void (*result_handler)(si);
typedef void (*getResultFunc)(si);

void endOfRoundMessage(getResultFunc result)
{
    result_handler = signal(SIGINT, result);
}
//------------------------------------------------------------------------------------------------------------------------

l response[] = {'n', 'y', 's', 'm'};
enum {n, y};

#endif // UTILITIES