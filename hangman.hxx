#ifndef HANGMAN_HXX
#define HANGMAN_HXX

#include "utilities.hxx"

class word
{
    public: 
//-----------------------------------------------------------------------------------------------------------------------

        void setWord(std::string value)
        {
            m_guessCount = 0;
            m_guessedLetters[0] = '\0';
            std::size_t length = value.copy(m_word, value.length(), 0);
            m_word[length]='\0';
            m_wordLength = value.length();
            for(si i = 0; i < value.length(); i++)
                m_incompleteWord[i] = '_' ;

            m_incompleteWord[length] = '\0';

            trackDictionaryLetters(value);
            m_numberOfGames++;
        }
//-----------------------------------------------------------------------------------------------------------------------

        const l* showWord() const
        {
            return m_incompleteWord;
        }
//-----------------------------------------------------------------------------------------------------------------------

        std::string incompleteWord() const
        {
            std::string ret;
            for(auto c : std::string(m_incompleteWord))
            {
                ret = ret + " " + c;
            }
            return ret;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf guessLetter(l value)
        {
            if(isupper(value))
                value = tolower(value);

            if( getGuessedLetters() == "" )
            {
                trackFirstGuessAccuracy(value);
            }

            tf letterFound = false;

            for(si i = 0; i < m_wordLength; i++)
            {
                if(m_word[i] == value)
                {
                    m_incompleteWord[i] = value;
                    letterFound = true;
                }
            }

            for(si i = 0; i < m_guessCount; i++)
                if(m_guessedLetters[i] == value)
                {
                    std::cout << "\nYou already guessed that letter!\n";
                    return true;
                }

            m_triesLeft = (letterFound) ? m_triesLeft : m_triesLeft--;
            addlToGuessedLetters(value);

            return letterFound;
        }
//-----------------------------------------------------------------------------------------------------------------------

        std::string getGuessedLetters() const
        {
            return m_guessedLetters;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void addlToGuessedLetters(l value)
        {
            m_guessedLetters[m_guessCount++] = value;
            m_guessedLetters[m_guessCount] = '\0'; 
        }
//-----------------------------------------------------------------------------------------------------------------------

        std::string getWord() const
        {
            return m_word;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getTriesLeft() const
        {
            return m_triesLeft;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void subtractTry()
        {
            m_triesLeft--;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetTries()
        {
            m_triesLeft = 6;
            for(auto x : m_guessedLetters)
                x = ' ';
        }
//-----------------------------------------------------------------------------------------------------------------------

        void displayHangMan()
        {
                switch(m_triesLeft)
                {
                    case 6:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|    \n|     \n|           \n|______\n";
                            break;
                    case 5:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|     \n|          \n|______\n";
                            break;
                    case 4:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|     |\n|          \n|______\n";
                            break;
                    case 3:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|    /|\n|          \n|______\n";
                            break;
                    case 2:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|    /|\\ \n|        \n|______\n";
                            break;
                    case 1:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|    /|\\\n|    /     \n|______\n";
                            break;
                    case 0:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|    /|\\\n|    / \\  \n|______\n";
                            break;
                    default:
                            std::cout<< " ______\n";
                            std::cout<< "|     |\n|     o\n|    /|\\\n|    / \\  \n|______\n";
                }
        }
//-----------------------------------------------------------------------------------------------------------------------

        void trackDictionaryLetters(std::string dictionaryWord)
        {
                m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin();
                for(auto c: dictionaryWord)
                {
                    m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.find(c);
                    if(m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end())
                    {
                        m_dictionaryWordLettersMapIT->second++;
                    }
                    else
                        m_dictionaryWordLettersMap[c] = 1;
                     
                    if(m_dictionaryWordLettersMapIT->second > dictionaryLettersMapmostFrequentCount)
                        dictionaryLettersMapmostFrequentCount = m_dictionaryWordLettersMapIT->second;
                }
        }
//-----------------------------------------------------------------------------------------------------------------------

        std::string getMostFrequentLetterFromDictionaryWord()
        {
            std::string ret;
           for(m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin(); m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end(); m_dictionaryWordLettersMapIT++)
           {
               if(m_dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
               {
                   ret = "\nMost frequent letter(s) to appear in the dictionary words this session: ";
                   ret+= m_dictionaryWordLettersMapIT->first;
                   ret+= "\n# of times it appeard: " + std::to_string(m_dictionaryWordLettersMapIT->second) + "\n";
               }
           }
           return ret;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void printMostFrequentLettersFromDictionaryWord()
        {
            for(m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin(); m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end(); m_dictionaryWordLettersMapIT++)
            {
               if(m_dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
                   std::cout << "\nMost frequent letter(s) to appear in the dictionary words this session: " << m_dictionaryWordLettersMapIT->first << "\n# of times it appeard: " << m_dictionaryWordLettersMapIT->second << "\n";
            }
        }
//-----------------------------------------------------------------------------------------------------------------------

        si checkDictionaryMapLettersEqualToMaxCount()
        {
            si total = 0;
            for(m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin(); m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end(); m_dictionaryWordLettersMapIT++)
                if(m_dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
                    total++;
            return total;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setFirstGuessWasCorrectValue()
        {
            m_firstGuessWasCorrect = true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void trackFirstGuessAccuracy(l value)
        {
            std::map<si, std::string> firstGuessMessageMap;

            firstGuessMessageMap[0] = "\nExcellent start!\n";
            firstGuessMessageMap[1] = "\nGood guess!\n";
            firstGuessMessageMap[2] = "\nKeep it up!\n";
            firstGuessMessageMap[3] = "\nWow...nice!\n";
            m_firstGuessLettersMapIT = m_firstGuessLettersMap.begin();
            srand(time(NULL));

            for(auto c: getWord())
            {
               if(value == c)
               {               
                    m_letterWasInWord++;
                    std::cout << firstGuessMessageMap[rand() % 4];
                    setFirstGuessWasCorrectValue();
                    break;
               }
            }

            m_firstGuessLettersMapIT = m_firstGuessLettersMap.find(value);

            if(m_firstGuessLettersMapIT != m_firstGuessLettersMap.end())
            {
                m_firstGuessLettersMapIT->second++;
            }
            else
                m_firstGuessLettersMap[value] = 1;
             
            if(m_firstGuessLettersMapIT->second > m_firstGuessLettersMapCount)
                m_firstGuessLettersMapCount = m_firstGuessLettersMapIT->second;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void getFirstGuessAccuracy()
        {
            for(m_firstGuessLettersMapIT = m_firstGuessLettersMap.begin(); m_firstGuessLettersMapIT != m_firstGuessLettersMap.end(); m_firstGuessLettersMapIT++)
            {
                if(m_firstGuessLettersMapIT->second == m_firstGuessLettersMapCount)
                {
                    std::cout << "\nMost frequent letter(s) to be guessed first: " << m_firstGuessLettersMapIT->first << "\nNumber of times guessed first: "<< m_firstGuessLettersMapIT->second<<"\n";
                    std::cout << "\nFirst guess accuracy: " << std::setprecision(2) << (float)(m_letterWasInWord/m_numberOfGames) * 100 << "\% in " << std::setprecision(0) << m_numberOfGames << " game(s).\n";
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetFirstGuessLettersMap()
        {
  			m_firstGuessLettersMap.clear();
  			m_firstGuessLettersMapCount = 1;
            m_letterWasInWord = 0.00;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setMaxStreak(si currentStreak)
        {
            m_streak = currentStreak;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getMaxStreak()
        {
            return m_streak;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf checkIfFirstGuessWasCorrect() const
        {
            return m_firstGuessWasCorrect;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetFirstGuessWasCorrectValue()
        {
            m_firstGuessWasCorrect = false;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void incrementFirstGuessToWonRoundConversionTracker()
        {
            m_firstGuessToWonRoundConversionTracker++;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setRecordNumberOfGamesSurvivorMode(si newHighScore)
        {
            // m_recordNumberOfGamesWonSurvivorMode = newHighScore;
            setUserSurvivorModeRecordsMap(newHighScore);
            m_recordNumberOfGamesWonSurvivorMode = m_survivorModeRecords[0];
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setRecordNumberOfGamesRegularMode(si newHighScore)
        {
            m_recordNumberOfGamesWonRegularMode = newHighScore;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setRecordNumberOfGamesTimedMode(si newHighScore)
        {
            setUserTimedModeRecordsMap(newHighScore);
            m_recordNumberOfGamesWonTimedMode = m_timedModeRecords[0];
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getRecordNumberOfGamesWonSurvivorMode() const
        {
            return m_recordNumberOfGamesWonSurvivorMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getCurrentNumberOfGamesWonSurvivorMode() const
        {
            return userScoreSurvivorMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getRecordNumberOfGamesWonRegularMode() const
        {
            return m_recordNumberOfGamesWonRegularMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getCurrentNumberOfGamesWonRegularMode() const
        {
            return userScoreRegularMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getRecordNumberOfGamesWonTimedMode() const
        {
            return m_recordNumberOfGamesWonTimedMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getCurrentNumberOfGamesWonTimedMode() const
        {
            return userScoreTimedMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetSurvivorModeScore()
        {
            userScoreSurvivorMode = 0;
            m_numberOfGames = 0.00;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetTimedModeScore()
        {
            userScoreTimedMode = 0;
            m_numberOfGames = 0.00;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetRegularModeGames()
        {
            totalGames = 0;
            m_numberOfGames = 0.00;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setSurvivorMode()
        {   
            m_survivorModeEnabled = (m_survivorModeEnabled) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf survivorModeEnabled()
        {
            return m_survivorModeEnabled;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setTimedMode()
        {
            m_timedModeEnabled = (m_timedModeEnabled) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf timedModeEnabled()
        {
            return m_timedModeEnabled;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setDisplayedRulesOnce()
        {
            m_displayedRulesOnce = (m_displayedRulesOnce) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf alreadyDisplayedRulesOnce()
        {
            return m_displayedRulesOnce;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf displayTimedModeRule()
        { 
            if(alreadyDisplayedRulesOnce())
            	return alreadyDisplayedRulesOnce();

	        std::cout << std::endl;
	        lineWrapper(std::string("\nAttention: In this mode, you must make your guess within 5 seconds or you will lose the round\n"), '*');
	        std::cout << "\nAttention:\n\nIn this mode, you must make your guess within 5 seconds or you will lose the round.";
	        std::cout << "\nThe timer will start once you see 'U: ', and it will stop once you have entered a letter.\n\n";
	        lineWrapper(std::string("\nAttention: In this mode, you must make your guess within 5 seconds or you will lose the round\n"), '*');
	        setDisplayedRulesOnce();

            return alreadyDisplayedRulesOnce();
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf regularModeEnabled() const
        {
            return m_regularModeEnabled;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setRegularMode()
        {
            m_regularModeEnabled = (m_regularModeEnabled) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si setUsersBestStreakOfAllTime(si allTimeHighScore)
        {
            m_maxStreakOfAllTime = allTimeHighScore;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getUsersBestStreakOfAllTime() const
        {
            return m_maxStreakOfAllTime;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setUserRecords()
        {
            std::ifstream recordBook("hangManRecordBook.txt");
            std::string line;
            std::regex bestStreak("Best streak of all time: ([0-9]+)");
            std::regex mostGamesWonSurvivorMode("Record number of games won \\(Survivor\\): ([0-9]+)");
            std::regex mostGamesWonRegularMode("Record number of games won \\(Regular\\): ([0-9]+)");
            std::regex mostGamesWonRegularModeOld("Record number of games won: ([0-9]+)");
            std::regex mostGamesWonTimedMode("Record number of games won \\(Timed\\): ([0-9]+)");
            std::regex topThreeGamesWonTimedModeOld("([0-9])\\) ([0-9]+)");
            std::regex topThreeGamesWonTimedMode("T([0-9])\\) ([0-9]+)");  
            std::regex topThreeGamesWonSurvivorMode("S([0-9])\\) ([0-9]+)");  
            std::cmatch cm;
            std::string::size_type maxStreak_str;
            std::string::size_type recordNumberOfGamesSurvivorMode_str, recordNumberOfGamesSurvivorModeRank_str; 
            std::string::size_type recordNumberOfGamesRegular_str;
            std::string::size_type recordNumberOfGamesTimedMode_str, recordNumberOfGamesTimedModeRank_str;

            if(recordBook.is_open())
            {
                try 
                {
                    while(getline(recordBook,line))
                    {
                        // std::cout << "Line: " << line << "\n";
                        if(line == "")
                            continue;

                        if(std::regex_match ( line.c_str(), cm, bestStreak ))
                        {
                            std::string recordStreak_str = cm.str(1);
                            m_maxStreakOfAllTime = std::stoi (recordStreak_str, &maxStreak_str);
                            continue;
                        }
                        //get record number of games won survivor mode
                        if(std::regex_match ( line.c_str(), cm, mostGamesWonSurvivorMode ))
                        {
                            std::string recordWinsSurvivorMode_str = cm.str(1);
                            // setRecordNumberOfGamesSurvivorMode(std::stoi (recordWinsSurvivorMode_str , &recordNumberOfGamesSurvivorMode_str));
                            continue;
                        }

                        if(std::regex_match ( line.c_str(), cm, topThreeGamesWonSurvivorMode ))
                        {
                            std::string recordWinsSurvivorModeRank_str = cm.str(1);
                            std::string recordWinsSurvivorMode_str = cm.str(2);

                            si convertRecordToInt = std::stoi (recordWinsSurvivorMode_str , &recordNumberOfGamesSurvivorMode_str);
                            si convertRankToInt = std::stoi (recordWinsSurvivorModeRank_str , &recordNumberOfGamesSurvivorModeRank_str);
                            m_survivorModeRecords[convertRankToInt-1] = convertRecordToInt;
                            
                            if((convertRankToInt-1) == 0)
                                m_recordNumberOfGamesWonSurvivorMode = convertRecordToInt;

                            continue;
                        }


                        //get record number of regular games won
                        if(std::regex_match ( line.c_str(), cm, mostGamesWonRegularMode ))
                        {
                            // std::cout << "** Games Debug Regular: " << cm.str(0) << " **\n";
                            std::string recordWinsRegularMode_str = cm.str(1);
                            setRecordNumberOfGamesRegularMode(std::stoi (recordWinsRegularMode_str , &recordNumberOfGamesRegular_str));
                        }
                        else if(std::regex_match ( line.c_str(), cm, mostGamesWonRegularModeOld ))
                        {
                            std::string recordWinsRegularMode_str = cm.str(1);
                            setRecordNumberOfGamesRegularMode(std::stoi (recordWinsRegularMode_str , &recordNumberOfGamesRegular_str));
                        }

                        //get record number of timed games won
                        if(std::regex_match ( line.c_str(), cm, mostGamesWonTimedMode ))
                        {
                            std::string recordWinsTimedMode_str = cm.str(1);
                            if(getRecordNumberOfGamesWonTimedMode() == 0)
                                setRecordNumberOfGamesTimedMode(std::stoi (recordWinsTimedMode_str , &recordNumberOfGamesTimedMode_str));
                            continue;
                        }

                        //get record number of timed games won for map
                        // std::cout << "\nLine: " << line << "\n";
                        if(std::regex_match ( line.c_str(), cm, topThreeGamesWonTimedMode ))
                        {
                            // std::cout << "** Games Debug Timed: " << cm.str(1) << ", " << cm.str(2) << "\n";
                            std::string recordWinsTimedModeRank_str = cm.str(1);
                            std::string recordWinsTimedMode_str = cm.str(2);
                            // std::cout << "** Games Debug Timed Map: " << cm.str(1) << ") " << cm.str(2) <<"\n";
                            // setRecordNumberOfGamesTimedMode(std::stoi (recordWinsTimedMode_str , &recordNumberOfGamesTimedMode_str));
                            si convertRecordToInt = std::stoi (recordWinsTimedMode_str , &recordNumberOfGamesTimedMode_str);
                            si convertRankToInt = std::stoi (recordWinsTimedModeRank_str , &recordNumberOfGamesTimedModeRank_str);
                            m_timedModeRecords[convertRankToInt-1] = convertRecordToInt;
                            
                            if((convertRankToInt-1) == 0)
                                m_recordNumberOfGamesWonTimedMode = convertRecordToInt;

                            continue;
                        }
                        
                        if(std::regex_match ( line.c_str(), cm, topThreeGamesWonTimedModeOld ))
                        {
                            std::string recordWinsTimedModeRank_str = cm.str(1);
                            std::string recordWinsTimedMode_str = cm.str(2);

                            si convertRecordToInt = std::stoi (recordWinsTimedMode_str , &recordNumberOfGamesTimedMode_str);
                            si convertRankToInt = std::stoi (recordWinsTimedModeRank_str , &recordNumberOfGamesTimedModeRank_str);
                            m_timedModeRecords[convertRankToInt-1] = convertRecordToInt;
                            
                            if((convertRankToInt-1) == 0)
                                m_recordNumberOfGamesWonTimedMode = convertRecordToInt;

                            continue;
                        }
                    }
                 }catch(const std::invalid_argument& ia){}
            }
            recordBook.close();

            //if the records dont exist, intialize them
            if(getRecordNumberOfGamesWonTimedMode() == 0)
                setRecordNumberOfGamesTimedMode(0);
            if(getRecordNumberOfGamesWonRegularMode() == 0)
                setRecordNumberOfGamesRegularMode(0);
            if(getRecordNumberOfGamesWonSurvivorMode() == 0)
                setRecordNumberOfGamesSurvivorMode(0);
        }
//-----------------------------------------------------------------------------------------------------------------------

        void updateRecordBook()
        {
            std::string fileName("hangManRecordBook.txt");
            // setUserRecords();

            if(getMaxStreak() > getUsersBestStreakOfAllTime())
            {
                // if(userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
                // {
                //     setRecordNumberOfGamesSurvivorMode(userScoreSurvivorMode);
                // }
                
                if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
                    setRecordNumberOfGamesRegularMode(userScoreRegularMode);

                // if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                // {
                //     setRecordNumberOfGamesTimedMode(userScoreTimedMode);
                // }

                if(m_timedModeRecords.size() == 0)
                {
                    setUserTimedModeRecordsMap(0);
                }

                if(m_updatedTimedRecordsMap)
                    m_updatedTimedRecordsMap = false;
                //survivormode records map
                if(m_survivorModeRecords.size() == 0)
                    setUserSurvivorModeRecordsMap(0);
                
                if(m_updatedSurvivorRecordsMap)
                    m_updatedSurvivorRecordsMap = false;
                //initial indicator user broke a record
                setUserBrokeARecord();

                remove(fileName.c_str());
            }
            else if(userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
            {
                if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
                    setRecordNumberOfGamesRegularMode(userScoreRegularMode);

                // if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                // {
                //     setRecordNumberOfGamesTimedMode(userScoreTimedMode);
                //     // resetTimedModeScore();
                // }
                //mew record indicator
                if(m_timedModeRecords.size() == 0)
                {
                    setUserTimedModeRecordsMap(0);
                }

                if(m_updatedTimedRecordsMap)
                    m_updatedTimedRecordsMap = false;

                if(m_survivorModeRecords.size() == 0)
                    setUserSurvivorModeRecordsMap(0);
                
                if(m_updatedSurvivorRecordsMap)
                    m_updatedSurvivorRecordsMap = false;

                setUserBrokeARecord();

                remove(fileName.c_str());
            }
            else if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
            {
                if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                {
                    setRecordNumberOfGamesTimedMode(userScoreTimedMode);
                }

                if(m_timedModeRecords.size() == 0)
                {
                    setUserTimedModeRecordsMap(0);
                }

                if(m_updatedTimedRecordsMap)
                    m_updatedTimedRecordsMap = false;

                if(m_survivorModeRecords.size() == 0)
                    setUserSurvivorModeRecordsMap(0);
                
                if(m_updatedSurvivorRecordsMap)
                    m_updatedSurvivorRecordsMap = false;
                //new record indicator
                setUserBrokeARecord();

                remove(fileName.c_str());
            }
            else if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
            {
                //new record indicator
                if(m_timedModeRecords.size() == 0)
                {
                    setUserTimedModeRecordsMap(0);
                }

                if(m_updatedTimedRecordsMap)
                    m_updatedTimedRecordsMap = false;
                //survivormode records
                if(m_survivorModeRecords.size() == 0)
                    setUserSurvivorModeRecordsMap(0);

                if(m_updatedSurvivorRecordsMap)
                    m_updatedSurvivorRecordsMap = false;

                remove(fileName.c_str());
            }
            else if(m_timedModeRecords.size() == 0 || m_survivorModeRecords.size() == 0)
            {
                if(m_timedModeRecords.size() == 0)
                    setUserTimedModeRecordsMap(0);
                
                if(m_survivorModeRecords.size() == 0)
                    setUserSurvivorModeRecordsMap(0);

                remove(fileName.c_str());
            }
            else if(m_updatedTimedRecordsMap || m_updatedSurvivorRecordsMap)
            {
                if(m_updatedTimedRecordsMap)
                    m_updatedTimedRecordsMap = false;
                
                if(m_updatedSurvivorRecordsMap)
                    m_updatedSurvivorRecordsMap = false;

                remove(fileName.c_str());
            }
            else return;

            std::ofstream recordBook(fileName);
            if(recordBook.is_open())
            {
                if( getMaxStreak() > getUsersBestStreakOfAllTime() )
                    recordBook << "Best streak of all time: " << getMaxStreak() << "\n";
                else recordBook << "Best streak of all time: " << getUsersBestStreakOfAllTime() << "\n";

                if( userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
                    recordBook << "\nRecord number of games won (Survivor): " << userScoreSurvivorMode << "\n";
                else recordBook << "\nRecord number of games won (Survivor): " << getRecordNumberOfGamesWonSurvivorMode() << "\n";
                
                for(m_survivorModeRecordsIterator = m_survivorModeRecords.begin(); m_survivorModeRecordsIterator != m_survivorModeRecords.end(); m_survivorModeRecordsIterator++)
                {
                    recordBook << "S" << m_survivorModeRecordsIterator->first + 1 << ") " <<  m_survivorModeRecordsIterator->second << "\n";
                }

                if( userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
                    recordBook << "\nRecord number of games won (Regular): " << userScoreRegularMode << "\n";
                else recordBook << "\nRecord number of games won (Regular): " << getRecordNumberOfGamesWonRegularMode() << "\n";

                if( userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                    recordBook << "\nRecord number of games won (Timed): " << userScoreTimedMode << "\n";
                else recordBook << "\nRecord number of games won (Timed): " << getRecordNumberOfGamesWonTimedMode() << "\n";
            
                for(m_timedModeRecordsIterator = m_timedModeRecords.begin(); m_timedModeRecordsIterator != m_timedModeRecords.end(); m_timedModeRecordsIterator++)
                {
                    recordBook << "T"<< m_timedModeRecordsIterator->first + 1 << ") " <<  m_timedModeRecordsIterator->second << "\n";
                }
            }

            recordBook << "\n\n";
            using std::chrono::system_clock;
            system_clock::time_point today = system_clock::now();
            std::time_t tt;
            tt = system_clock::to_time_t ( today );
            recordBook << std::setw(80) << "Updated: " << ctime(&tt) << "\n";

            recordBook.close();

            setUserRecords();
        }
//-----------------------------------------------------------------------------------------------------------------------

        void showRecords()
        {
        	si i = getRecordNumberOfGamesWonSurvivorMode();
        	std::string sectionWrapper = "\nRecord number of games won: " + std::to_string(i) + "\n";
            std::cout << std::endl;
            lineWrapper(sectionWrapper, '*');
            // std::cout << "*\t High Scores\t     *\n";
            std::string title = "*        High Scores";
            addWhiteSpaceAndEndlChar(title, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');            // std::cout << "* Record number of games won *\n";
            std::string header1 = "* Record number of games won ";
            addWhiteSpaceAndEndlChar(header1, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');

            std::string tStr = "*        Timed: " + std::to_string(getRecordNumberOfGamesWonTimedMode());
            std::string rStr = "*        Regular: " + std::to_string(getRecordNumberOfGamesWonRegularMode());
            std::string sStr = "*        Survivor: " + std::to_string(getRecordNumberOfGamesWonSurvivorMode());
            std::string recordStreak = "*      Record streak: " + std::to_string(getUsersBestStreakOfAllTime());
	 		
            addWhiteSpaceAndEndlChar(tStr, sectionWrapper, i);
            
            // std::cout << "***DEBUG***\n";
            for(m_timedModeRecordsIterator = m_timedModeRecords.begin(); m_timedModeRecordsIterator != m_timedModeRecords.end(); m_timedModeRecordsIterator++)
            {
                std::string tMIStr = "*        " + std::to_string(m_timedModeRecordsIterator->first + 1) + std::string(") ") + std::to_string(m_timedModeRecordsIterator->second);
                addWhiteSpaceAndEndlChar(tMIStr, sectionWrapper, i);
            }

	 		addWhiteSpaceAndEndlChar(rStr, sectionWrapper, i);
	 		addWhiteSpaceAndEndlChar(sStr, sectionWrapper, i);
            for(m_survivorModeRecordsIterator = m_survivorModeRecords.begin(); m_survivorModeRecordsIterator != m_survivorModeRecords.end(); m_survivorModeRecordsIterator++)
            {
                std::string sMIStr = "*        " + std::to_string(m_survivorModeRecordsIterator->first + 1) + std::string(") ") + std::to_string(m_survivorModeRecordsIterator->second);
                addWhiteSpaceAndEndlChar(sMIStr, sectionWrapper, i);
            }

            lineWrapper(sectionWrapper, '*');            // std::cout << "* Record streak: " << getUsersBestStreakOfAllTime() << "*\n";
            addWhiteSpaceAndEndlChar(recordStreak, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');
        }
//-----------------------------------------------------------------------------------------------------------------------

        void startTimer()
        {
            time_t m_t = time(0);  
            m_userGuessClock = localtime( & m_t );
            m_clockMinuteBeforeGuess = m_userGuessClock->tm_min;
            m_clockSecondsBeforeGuess = m_userGuessClock->tm_sec;// get time now
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getSecondsBeforeGuess() const
        {
            return m_clockSecondsBeforeGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

       	si getMinuteBeforeGuess() const
        {
            return m_clockMinuteBeforeGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void stopTimer()
        {
            time_t m_t = time(0);  
            m_userGuessClock = localtime( & m_t );
            m_clockMinuteAfterGuess = m_userGuessClock->tm_min;
            m_clockSecondsAfterGuess = m_userGuessClock->tm_sec;// get time now
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getSecondsAfterGuess() const
        {
            return m_clockSecondsAfterGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getMinuteAfterGuess() const
        {
            return m_clockMinuteAfterGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getDifferenceBetweenGuessClocks() const
        {
            if((getMinuteAfterGuess() - getMinuteBeforeGuess()) == 0) 
            {
                return abs(getSecondsAfterGuess() - getSecondsBeforeGuess());
            }
            else
            {
            	si numberOfSecondsToMultiplySixtyBy = ( getMinuteAfterGuess() - getMinuteBeforeGuess() );
            	return abs( (( getSecondsAfterGuess() + ( numberOfSecondsToMultiplySixtyBy * 60 )) - getSecondsBeforeGuess() ) );
            }
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setAverageTimeDifferenceToGuessTracker() 
        {
            m_averageTimeDifferenceBetweenGuesses += getDifferenceBetweenGuessClocks();
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetAverageTimeDifferenceToGuessTracker() 
        {
            m_averageTimeDifferenceBetweenGuesses = 0;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getAverageTimeDifferenceToGuessTracker() const
        {
            return m_averageTimeDifferenceBetweenGuesses;
        }
//-----------------------------------------------------------------------------------------------------------------------

       	d getAverageTimeToGuessTracker() const
        {
        	// std::cout << "\nMguess count: " << m_guessCount << ", AverageTimeDifferenceToGuessTracker: " << getAverageTimeDifferenceToGuessTracker() << "\n";
         //    std::cout << "Average Time To Guess: " << (d) getAverageTimeDifferenceToGuessTracker() / (d) (m_guessCount) << "\n";
        	if(m_guessCount == 0 || getAverageTimeDifferenceToGuessTracker() == 0)
        		return getAverageTimeDifferenceToGuessTracker();
        	else
            	return ((d) getAverageTimeDifferenceToGuessTracker() / (d) (m_guessCount));
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf userRespondedInTime() const
        {
            if(getDifferenceBetweenGuessClocks() > 5)
            {
                return false;
            }
            else
                return true;
        }
//-----------------------------------------------------------------------------------------------------------------------
      
        void getStats()
        {   
            updateRecordBook();
            
            std::cout << std::endl; 
            if(regularModeEnabled())
                scoreBoardRegularMode();
            else if(survivorModeEnabled())
            	scoreBoard(userScoreSurvivorMode, m_numberOfGames);
            else
            	scoreBoard(userScoreTimedMode, m_numberOfGames);

            lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');

            std::cout << "**Stats**\n";

            if(userSetANewRecord())
            {
                std::cout << "\n*** You Set A New High Score ***\n";
                setUserBrokeARecord();
            }

            if(survivorModeEnabled())
                scoreBoardSurvivorMode();
            else if(timedModeEnabled())
                scoreBoardTimedMode();

            if(checkDictionaryMapLettersEqualToMaxCount() == 1)
                std::cout << getMostFrequentLetterFromDictionaryWord();
            else
                printMostFrequentLettersFromDictionaryWord();

            getFirstGuessAccuracy();

            std::cout << "\n# of times first guess was correct and you won the round: ";
            std::cout << m_firstGuessToWonRoundConversionTracker << "\n";

            std::cout << "\nAverage time to make a guess: " << std::setprecision(1) << getAverageTimeToGuessTracker() << " seconds\n";

            updateRecordBook();

            std::cout << "\nBest streak this session: " << getMaxStreak() << "\n";
            lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');
        }

//-----------------------------------------------------------------------------------------------------------------------
        
        si getGuessCount() const
        { 
            return m_guessCount;
        }
//-----------------------------------------------------------------------------------------------------------------------
        
        tf setUserAlreadyPlayedOneRound()
        { 
            m_userAlreadyPlayedOneRound = (m_userAlreadyPlayedOneRound) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------
        
        tf userAlreadyPlayedOneRound() const
        { 
            return m_userAlreadyPlayedOneRound;
        }
//-----------------------------------------------------------------------------------------------------------------------
        
        tf setUserBrokeARecord()
        { 
            m_userBrokeARecord = (m_userBrokeARecord) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------
        
        tf userSetANewRecord() const
        { 
            return m_userBrokeARecord;
        }
//-----------------------------------------------------------------------------------------------------------------------
    
        void setUserTimedModeRecordsMap(si userScore)
        { 
            // std::cout << "\nInside set user timed mode records map, user score: " << userScore << "\n";

            if(m_timedModeRecords.size() == 0)
            {
                if(getRecordNumberOfGamesWonTimedMode() != 0)
                {                    
                    m_timedModeRecords[0] = getRecordNumberOfGamesWonTimedMode();
                    // m_recordNumberOfGamesWonTimedMode = m_timedModeRecords[0];
                }
                else
                    m_timedModeRecords[0] = 0;

                m_timedModeRecords[1] = 0;
                m_timedModeRecords[2] = 0;
            }

            for(m_timedModeRecordsIterator = m_timedModeRecords.begin(); m_timedModeRecordsIterator != m_timedModeRecords.end(); m_timedModeRecordsIterator++)
            {
                if(userScore > m_timedModeRecordsIterator->second)
                {
                    if(m_timedModeRecordsIterator->first == 0)
                    {
                        m_timedModeRecords[m_timedModeRecordsIterator->first + 2] = m_timedModeRecords[m_timedModeRecordsIterator->first + 1];
                        m_timedModeRecords[m_timedModeRecordsIterator->first + 1] = m_timedModeRecords[m_timedModeRecordsIterator->first];                    
                    }
                    else if(m_timedModeRecordsIterator->first == 1)
                    {
                        m_timedModeRecords[m_timedModeRecordsIterator->first + 1] = m_timedModeRecords[m_timedModeRecordsIterator->first];                    
                    }

                    m_timedModeRecords[m_timedModeRecordsIterator->first] = userScore;
                    m_updatedTimedRecordsMap = true;
                    // std::cout << "\n*** You broke into the top 3 ***\n";
                    break;
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------------
    
        tf userBeatTopThreeScoreTimedModeRecordsMap(si userScore)
        { 

            for(m_timedModeRecordsIterator = m_timedModeRecords.begin(); m_timedModeRecordsIterator != m_timedModeRecords.end(); m_timedModeRecordsIterator++)
            {
                // std::cout << "\nInside top 3: " << m_timedModeRecordsIterator->first << ") " << m_timedModeRecordsIterator->second << ", user score : " << userScore << "\n";
                if(userScore > m_timedModeRecordsIterator->second)
                {
                    return true;
                }
            }

            return false;
        }
//-----------------------------------------------------------------------------------------------------------------------
 
        void setUserSurvivorModeRecordsMap(si userScore)
        { 
            // std::cout << "\nInside set user survivor mode records map, user score: " << userScore << "\n";

            if(m_survivorModeRecords.size() == 0)
            {
                if(getRecordNumberOfGamesWonSurvivorMode() != 0)
                {                    
                    m_survivorModeRecords[0] = getRecordNumberOfGamesWonSurvivorMode();
                    // m_recordNumberOfGamesWonTimedMode = m_survivorModeRecords[0];
                }
                else
                    m_survivorModeRecords[0] = 0;

                m_survivorModeRecords[1] = 0;
                m_survivorModeRecords[2] = 0;
            }

            for(m_survivorModeRecordsIterator = m_survivorModeRecords.begin(); m_survivorModeRecordsIterator != m_survivorModeRecords.end(); m_survivorModeRecordsIterator++)
            {
                if(userScore > m_survivorModeRecordsIterator->second)
                {
                    if(m_survivorModeRecordsIterator->first == 0)
                    {
                        m_survivorModeRecords[m_survivorModeRecordsIterator->first + 2] = m_survivorModeRecords[m_survivorModeRecordsIterator->first + 1];
                        m_survivorModeRecords[m_survivorModeRecordsIterator->first + 1] = m_survivorModeRecords[m_survivorModeRecordsIterator->first];                    
                    }
                    else if(m_survivorModeRecordsIterator->first == 1)
                    {
                        m_survivorModeRecords[m_survivorModeRecordsIterator->first + 1] = m_survivorModeRecords[m_survivorModeRecordsIterator->first];                    
                    }

                    m_survivorModeRecords[m_survivorModeRecordsIterator->first] = userScore;
                    m_updatedTimedRecordsMap = true;
                    // std::cout << "\n*** You broke into the top 3 ***\n";
                    break;
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------------
    
        tf userBeatTopThreeScoreSurvivorModeRecordsMap(si userScore)
        { 

            for(m_survivorModeRecordsIterator = m_survivorModeRecords.begin(); m_survivorModeRecordsIterator != m_survivorModeRecords.end(); m_survivorModeRecordsIterator++)
            {
                // std::cout << "\nInside top 3: " << m_survivorModeRecordsIterator->first << ") " << m_survivorModeRecordsIterator->second << ", user score : " << userScore << "\n";
                if(userScore > m_survivorModeRecordsIterator->second)
                {
                    return true;
                }
            }

            return false;
        }
//-----------------------------------------------------------------------------------------------------------------------
   private:

        tf m_survivorModeEnabled = false;
        tf m_timedModeEnabled = false;
        tf m_regularModeEnabled = false;
        l m_word[256];
        l m_incompleteWord[256];
        l m_guessedLetters[26];
        si m_guessCount;
        si m_wordLength = 0;
        si m_roundsWon = 0;
        si m_streak = 0;
        si m_maxStreakOfAllTime = 0;
        si m_recordNumberOfGamesWonSurvivorMode = 0;
        si m_recordNumberOfGamesWonRegularMode = 0;
        si m_recordNumberOfGamesWonTimedMode = 0;
        si m_triesLeft = 6;
        HangmanDictionary m_dictionary;

        LetterTrackingMap m_dictionaryWordLettersMap;
        LetterTrackingMapIT m_dictionaryWordLettersMapIT;
        si dictionaryLettersMapmostFrequentCount = 1;

        LetterTrackingMap m_firstGuessLettersMap;
        LetterTrackingMapIT m_firstGuessLettersMapIT;
        tf m_firstGuessWasCorrect = false;
        si m_firstGuessLettersMapCount = 1;
        d m_letterWasInWord = 0.00;
        d m_numberOfGames = 0.00;
        si m_firstGuessToWonRoundConversionTracker = 0;

        //average time per guessed letter tracker stuff
        guessTime m_userGuessClock;
        si m_clockSecondsBeforeGuess = 0;
        si m_clockSecondsAfterGuess = 0;
        si m_clockMinuteBeforeGuess = 0;
        si m_clockMinuteAfterGuess = 0;
        si m_averageTimeDifferenceBetweenGuesses = 0;

        //timed play stuff
        tf m_displayedRulesOnce;
        tf m_userAlreadyPlayedOneRound;

        tf m_userBrokeARecord;

        //record stuff
        RecordBookMap m_timedModeRecords;
        RecordBookMapIT m_timedModeRecordsIterator;
        tf m_updatedTimedRecordsMap = false;

        RecordBookMap m_survivorModeRecords;
        RecordBookMapIT m_survivorModeRecordsIterator;
        tf m_updatedSurvivorRecordsMap = false;

};

#endif // HANGMAN_HXX
