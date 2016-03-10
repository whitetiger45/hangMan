#include "hangman.hxx"

using namespace std;

si main() 
{
    word guess;
    string line;
    tf playAgain = false, userHasCompletedARound = false;
    tf userWonRound = false;
    // tf survivorModeEnabled = false;
    tf inGame = false;
    l userResponse[1];
    l userGuess[1];
    si getWordAtLocation = 0, correctOrSameGuessCounter = 0, userSubMenuResponseI = 0, streak = 0;
    guess.setUserRecords();

    showTitle();

    gameModeMenu:

    if(!userHasCompletedARound)
        showMenu();
    else
        showMenuWithStatsOption();

    string userGameModeMenuResponse_str;
    cout << "User: "; cin >> userGameModeMenuResponse_str;

//reset the user already played one round variable before selecting a new game mode
    if(guess.userAlreadyPlayedOneRound())
        guess.setUserAlreadyPlayedOneRound();

    if(!isdigit(userGameModeMenuResponse_str[0]))
    {

        //cout << "User: "; cin >> userGameModeMenuResponse_str;
        cout << "\nYou must enter a valid menu option!!\n";
        goto gameModeMenu;
    }

    si userGameModeMenuResponse_I = 1;
    userGameModeMenuResponse_I = stoi(userGameModeMenuResponse_str);

    //update user mode menu response according to menu displayed
    if(userHasCompletedARound)
    {
        if(userGameModeMenuResponse_I == 4)
        {
            guess.getStats();
            goto gameModeMenu;
        }
        else if(userGameModeMenuResponse_I > 4)
            userGameModeMenuResponse_I--;
    }

    switch(userGameModeMenuResponse_I)
    {
        case 1:
                // survivorModeEnabled = true;
                guess.resetTries();
                
                correctOrSameGuessCounter = 0;
                userWonRound = false;
                guess.resetFirstGuessWasCorrectValue();
                                
                if(guess.timedModeEnabled())
                    guess.setTimedMode();
                else if(guess.regularModeEnabled())
                    guess.setRegularMode();

                if(!guess.survivorModeEnabled())
                {
                    guess.setSurvivorMode();
                }

                guess.resetFirstGuessLettersMap();
                guess.resetSurvivorModeScore();
                guess.resetAverageTimeDifferenceToGuessTracker();
                // cout << "\n***DEBUG\nSurvivor Mode Enabled (Should be): " << guess.survivorModeEnabled() << "\n***\n";
                
                if(guess.userAlreadyPlayedOneRound())
                    guess.setUserAlreadyPlayedOneRound();

                break;
        case 2:
                if(!guess.displayTimedModeRule())
                    guess.displayTimedModeRule();
                
                guess.resetTries();
                correctOrSameGuessCounter = 0;
                userWonRound = false;
                guess.resetFirstGuessWasCorrectValue();
                
                if(guess.survivorModeEnabled())
                    guess.setSurvivorMode();
                else if(guess.regularModeEnabled())
                    guess.setRegularMode();                

                if(!guess.timedModeEnabled())
                {
                    guess.setTimedMode();
                }

                guess.resetFirstGuessLettersMap();
                guess.resetTimedModeScore();
                guess.resetAverageTimeDifferenceToGuessTracker();
                // cout << "\n***DEBUG\nSurvivor Mode Enabled (Should not be): " << guess.survivorModeEnabled() << "\n***\n";
                if(guess.userAlreadyPlayedOneRound())
                    guess.setUserAlreadyPlayedOneRound();
                break;
        case 3:
                // survivorModeEnabled = false;
                guess.resetTries();
                correctOrSameGuessCounter = 0;
                userWonRound = false;
                guess.resetFirstGuessWasCorrectValue();

                if(guess.survivorModeEnabled())
                    guess.setSurvivorMode();
                else if(guess.timedModeEnabled())
                    guess.setTimedMode();

                if(!guess.regularModeEnabled())
                {
                    guess.setRegularMode();
                    guess.resetRegularModeGames();
                    guess.resetFirstGuessLettersMap();
                    guess.resetAverageTimeDifferenceToGuessTracker();
                }

                // cout << "\n***DEBUG\nSurvivor Mode Enabled (Should not be): " << guess.survivorModeEnabled() << "\n***\n";
                if(guess.userAlreadyPlayedOneRound())
                    guess.setUserAlreadyPlayedOneRound();
                break;
        case 4:
                guess.showRecords();
                goto gameModeMenu;
        case 5: 
                goto quit;
        default:
                cout << "\nInvalid entry!\n";
                goto gameModeMenu;
    }

    do
    { 
        si count = 1;
        srand(time(NULL));

        getWordAtLocation = rand() % 173139;
        ifstream dictionaryFile ("dictionaryFile/dictionary.txt");

        if(dictionaryFile.is_open())
        {
            while ( getline (dictionaryFile,line) && count != getWordAtLocation)
            {   
               count++;
            }
            guess.setWord(line);
            dictionaryFile.close();
        }

        do{


            main_menu:
            if(guess.survivorModeEnabled())
            {
                cout << endl;
                string sectionWrapper = "* Survivor Mode *";
                lineWrapper(sectionWrapper, '*');
                // cout << "Survivor Mode*\n";
                string sMode = "* Survivor Mode ";
                addWhiteSpaceAndEndlChar(sMode,sectionWrapper, sectionWrapper.length());
                lineWrapper(sectionWrapper, '*');
            }
            else if(guess.timedModeEnabled())
            {
                string sectionWrapper = "* Timed Mode *";
                string tMode = "* Timed Mode ";
                cout << endl;
                lineWrapper(sectionWrapper, '*');
                // cout << "Timed Mode*\n";
                addWhiteSpaceAndEndlChar(tMode, sectionWrapper, sectionWrapper.length());
                lineWrapper(sectionWrapper, '*');
            }
            else if(guess.regularModeEnabled())
            {
                string sectionWrapper = "* Regular Mode *";
                string rMode = "* Regular Mode ";
                cout << endl;
                lineWrapper(sectionWrapper, '*');
                // cout << "Regular Mode*\n";
                addWhiteSpaceAndEndlChar(rMode, sectionWrapper, sectionWrapper.length());
                lineWrapper(sectionWrapper, '*');
            }

            if(guess.getTriesLeft() == 0)
            {
                goto outOfTries;
            }

            const l * userGuessWord;
            string userSubMenuResponse_str;
            tf guessSinglel = true, userGuessedRightWord = false;
//-------------------------------------------------------------------------------------------------------
            if(!guess.userAlreadyPlayedOneRound() && guess.getGuessCount() == 0 )
            {
                showSubMenuWithReturnToGameModeOption();
                cout << "User: "; cin >> userSubMenuResponse_str;
                while(!isdigit(userSubMenuResponse_str[0]))
                {
                    cout << "\nYou must enter a valid menu option (1-8)\n";
                    showSubMenu(); cout << "User: "; cin >> userSubMenuResponse_str;
                }
            }
            else
            {
                showSubMenu();
                cout << "User: "; cin >> userSubMenuResponse_str;
                while(!isdigit(userSubMenuResponse_str[0]))
                {
                    cout << "\nYou must enter a valid menu option (1-7)\n";
                    showSubMenu(); cout << "User: "; cin >> userSubMenuResponse_str;
                }
            }


            userSubMenuResponseI = stoi(userSubMenuResponse_str);

            if(!userHasCompletedARound && userSubMenuResponseI == 7 && guess.getGuessCount() == 0 )
                goto gameModeMenu;
            else if(!userHasCompletedARound && userSubMenuResponseI == 8 && guess.getGuessCount() == 0 )
                goto quit;            
            else if(!userHasCompletedARound && guess.getGuessCount() > 0 && userSubMenuResponseI == 7)
                goto quit;
            else if(userHasCompletedARound && userSubMenuResponseI == 7 && guess.getGuessCount() == 0 )
                goto gameModeMenu;
            else if(userHasCompletedARound && userSubMenuResponseI == 8 && guess.getGuessCount() == 0 )
                goto quit;
//---------------------------------------------------------------------------------------------------------
            switch(userSubMenuResponseI)
            {
                case 1:
                {
                    caseOneStart:
                    string userGuess_str;
                    si userGuess_i = 1;

                    guess.startTimer();//start
                    askForLetter();
                    cout << "\n";
                    guess.displayHangMan();
                    cout << "Word: " << guess.incompleteWord() <<  "\n";

                    lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '~');
                    cout << "Guessed letters: {" << guess.getGuessedLetters() <<  "}\n";
                    lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '~');

                    cout << "U: "; cin >> userGuess_str;
                    
                    guess.stopTimer();//stop timer
                    guess.setAverageTimeDifferenceToGuessTracker();

                    //timed mode check
                    if(guess.timedModeEnabled())
                        if(!guess.userRespondedInTime())
                            goto endOfRoundMenu;

                    if(isdigit(userGuess_str[0]))
                    {
                        userGuess_i = stoi(userGuess_str);
                        if(userGuess_i == 1)
                            goto main_menu;
                        else
                            goto caseOneStart;
                    }
                    else if(userGuess_str.size() > 1)
                    {
                        cout << "\n**You entered more than one character...please enter only one letter**\n";
                        goto caseOneStart;
                    }
                    else if(!isalpha(userGuess_str[0]))
                    {
                        cout << "\n**You did not enter a valid character!**\n";
                        goto caseOneStart;
                    }
                    else
                    {
                        userGuess[0] = userGuess_str[0];
                    }
                    break;
                }
                case 2:
                {
                    caseTwoStart:
                    guessSinglel = false;
                    lineWrapper(string("\nUnfinished word: " + string(guess.showWord()) + "\n"), '*');
                    cout << "Unfinished word: " << guess.showWord() << "\n";

                    lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '-');
                    cout << "Guessed letters: {" << guess.getGuessedLetters() << "}\n";
                    lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '*');
                    cout << "\n";

                    askForSuspectedWord();
                    cin.ignore(); cout << "Enter the full word (Enter 1 to go back to main menu): ";
                    string userGuessWord_str;
                    cin >> userGuessWord_str;
                    if(isdigit(userGuessWord_str[0]))
                    {
                        si userGuessWord_i = stoi(userGuessWord_str);
                        if(userGuessWord_i == 1)
                            goto main_menu;
                        else
                            goto caseTwoStart;
                    }
                    else if(ispunct(userGuessWord_str[0]))
                    {
                        cout <<  "\n**You entered something that doesn't make sense...**\n";
                        goto caseTwoStart;
                    }
                    else
                        //cin.getline(userGuessWord, 256);
                        userGuessWord = userGuessWord_str.c_str();
                    for(auto c : userGuessWord_str)
                    {
                        tf alreadyGuessed = false;
                        if(!isalpha(c))
                          continue;
                        for(auto w : string(guess.getGuessedLetters()))
                        {
                            if(w == c)
                            {
                                alreadyGuessed = true;
                                break;
                            }
                        }
                        if(alreadyGuessed)
                        {
                            continue;
                        }
                        else if(!guess.guessLetter(c))
                        {
                            guess.subtractTry();
                        }
                        if(guess.getTriesLeft() == 0)
                        {
                          break;
                        }
                    }
                    if(guess.showWord() == guess.getWord() && userGuessWord == guess.getWord())
                    {
                        userWonRound = true;
                        userGuessedRightWord = true;
                        if(guess.survivorModeEnabled())
                            endOfRoundMessage(declareUserWinsRoundSurvivorMode);
                        else 
                            endOfRoundMessage(declareUserWinsRoundRegularMode);
                        goto userDiscoveredTheWord;
                    }
                    if(guess.getTriesLeft() != 0 && guess.showWord() != guess.getWord())
                    {
                        cout << "\nYou didn't get the word correct, but you got some letters correct...keep going!\n";
                        cout << "Unfinished word: " ;
                        for(auto c : string(guess.showWord()))
                            cout << c << " ";
                        cout << "\n"; 
                        goto main_menu;
                    }
                    else if(guess.getTriesLeft() == 0)
                        break;
                }
                case 3:
                {
                    cout << "\n";
                    lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '~');
                    cout << "Guessed letters: {" << guess.getGuessedLetters() <<  "}\n";
                    lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '~');
                }
                case 4:
                {
                    lineWrapper(string("Incomplete Word: " + string(guess.incompleteWord()) + "\n"), '~');
                    cout << "Incomplete Word: ";
                    for(auto c : string(guess.showWord()))
                        cout << c << " ";
                    cout << "\n"; 
                    lineWrapper(string("Incomplete Word: " + string(guess.incompleteWord()) + "\n"), '~');
                }
                case 5:
                {
                    lineWrapper(string("Tries left: " + to_string(guess.getTriesLeft()) + "\n"), '~');
                    cout << "Tries left: " << guess.getTriesLeft() << "\n";
                    lineWrapper(string("Tries left: " + to_string(guess.getTriesLeft()) + "\n"), '~');
                    cout << "\n";
                    goto main_menu;    
                }
                case 6:
                {
                    guess.displayHangMan();
                    cout << "\n";
                    goto main_menu;
                }
                case 7:
                {
                    goto quit;
                }
                default:
                {
                    cout << "\nYou must enter a valid option (1-7)\n";
                    goto main_menu;
                }
            }

            if(guess.getTriesLeft() == 0 || userWonRound)
                break;

            tf alreadyGuessed = false;

            for(auto c : guess.getGuessedLetters())
                if(userGuess[0] == c)
                    alreadyGuessed = true;

            if(!guess.guessLetter(userGuess[0]) && guessSinglel)
            {
                guess.subtractTry();
                guess.displayHangMan();
                lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '*');
                cout << "Guessed letters: {" << guess.getGuessedLetters() <<  "}\n";
                lineWrapper(string("\nGuessed letters: {" + guess.getGuessedLetters() +  "}"), '*');
                streak = 0;
            }
            else
            {
                if(!alreadyGuessed)
                    streak++;
                
                if(streak > guess.getMaxStreak())
                {
                    guess.setMaxStreak(streak);
                    if(guess.getMaxStreak() > guess.getUsersBestStreakOfAllTime())
                        cout << "\n*** New Streak Record ***\n";
                }
                guess.displayHangMan();
            }

            std::cout << "\nWord: " ;

            for(auto c : string(guess.showWord()))
                cout << c << " ";

            cout << "\n\nCurrent Streak: " << streak << "\n";

            if(guess.showWord() == guess.getWord())
            {
                userWonRound = true;

                if(guess.survivorModeEnabled())
                    endOfRoundMessage(declareUserWinsRoundSurvivorMode);
                else if(guess.timedModeEnabled())
                    endOfRoundMessage(declareUserWinsRoundTimedMode);
                else 
                    endOfRoundMessage(declareUserWinsRoundRegularMode);

                if(guess.checkIfFirstGuessWasCorrect())
                    guess.incrementFirstGuessToWonRoundConversionTracker();
            }
        }while(guess.getTriesLeft() != 0 && !userWonRound);

        outOfTries:

        if(guess.getTriesLeft() == 0)
        {
            endOfRoundMessage(declareOutOfGuesses);
        }

        userDiscoveredTheWord:

        raise(SIGINT);

        cout << guess.getWord() << "\n";

        endOfRoundMenu:

        if(guess.survivorModeEnabled())
        {
            if(userWonRound)
            {
                userResponse[0] = 'y';
                if( guess.getCurrentNumberOfGamesWonSurvivorMode() > guess.getRecordNumberOfGamesWonSurvivorMode() )
                    cout << "\n*** New Survivor Mode Record (Games Won) ***\n";

                if(!guess.userAlreadyPlayedOneRound())
                    guess.setUserAlreadyPlayedOneRound();
            }
            else
            {
                userResponse[0] = 'n';
                if(guess.userBeatTopThreeScoreSurvivorModeRecordsMap(guess.getCurrentNumberOfGamesWonSurvivorMode()))
                    guess.setUserSurvivorModeRecordsMap(guess.getCurrentNumberOfGamesWonSurvivorMode());
            }
        }
        //timed mode continue play
        else if(guess.timedModeEnabled())
        {
            if(!guess.userRespondedInTime())
            {
                declareOutOfTime(guess.getDifferenceBetweenGuessClocks(), guess.getWord());
                
                if(guess.userBeatTopThreeScoreTimedModeRecordsMap(guess.getCurrentNumberOfGamesWonTimedMode()))
                    guess.setUserTimedModeRecordsMap(guess.getCurrentNumberOfGamesWonTimedMode());
            }
            if(userWonRound)
            {
                userResponse[0] = 'y';
                if( guess.getCurrentNumberOfGamesWonTimedMode() > guess.getRecordNumberOfGamesWonTimedMode() )
                    cout << "\n*** New Timed Mode Record (Games Won) ***\n";
                
                if(!guess.userAlreadyPlayedOneRound())
                    guess.setUserAlreadyPlayedOneRound();
            }
            else
            {
                userResponse[0] = 'n';

                if(guess.userBeatTopThreeScoreTimedModeRecordsMap(guess.getCurrentNumberOfGamesWonTimedMode()))
                    guess.setUserTimedModeRecordsMap(guess.getCurrentNumberOfGamesWonTimedMode());
            }
        }
        else
        {

            userHasCompletedARound = true;

            if( guess.getCurrentNumberOfGamesWonRegularMode() > guess.getRecordNumberOfGamesWonRegularMode() )
                cout << "\n*** New Regular Mode Record (Games Won) ***\n";

            askPlayAgain();
            cin >> userResponse;
            if(isupper(userResponse[0]))
                userResponse[0] = tolower(userResponse[0]);

            while(!isalpha(userResponse[0]) || (userResponse[0] != 'n' && userResponse[0] != 'y' 
                                                && userResponse[0] != 's' && userResponse[0] != 'm') || (string(userResponse).size() > 1))
            {
                if(string(userResponse).size() > 1)
                    cout << "You entered more than one letter...please follow instructions.\n";
                else
                    cout << "You did not enter a valid response!\n";
                askPlayAgain();
                cin >> userResponse;
                if(isupper(userResponse[0]))
                    userResponse[0] = tolower(userResponse[0]);
            }
        }

        switch(userResponse[0])
        {
            case 'n':
                    playAgain = false;
                    break;
            case 'y':
                    playAgain = true;
                    break;
            case 's': 
                    guess.getStats();
                    goto endOfRoundMenu;
            case 'm':
                    goto gameModeMenu;
            default: 
                    cout << "\nInvalid entry!\n";
                    goto endOfRoundMenu;
        }
        if(playAgain)
        {
            guess.resetTries();
            correctOrSameGuessCounter = 0;
            userWonRound = false;
            guess.resetFirstGuessWasCorrectValue();
        }
    }while(playAgain);

    //scoreBoard();
    if(guess.survivorModeEnabled() && userSubMenuResponseI != 7)
    {
        guess.getStats();
        streak = 0;
        userHasCompletedARound = true;
        goto gameModeMenu;
    }
    else if(guess.timedModeEnabled() && userSubMenuResponseI != 7)
    {
        guess.getStats();
        streak = 0;
        userHasCompletedARound = true;
        goto gameModeMenu;
    }
    else 
        scoreBoardRegularMode();


    quit:
    
    return 0;
}
