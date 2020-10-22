#include <fstream>
#include <thread>
#include <mutex>

std::mutex mtx;
std::fstream fileStream;

void writeNumbers()
{
    //prevent other threads from entering their critical section
    mtx.lock();

    //write numbers to a file
    for (size_t i = 0; i < 20; ++i)
    {
        for (short currentNumber = 1; currentNumber <= 26; ++currentNumber)
            fileStream << currentNumber << ' ';
        fileStream << '\n';
    }
    
    //allow other threads to enter their critical section
    mtx.unlock();
}

void writeLetters()
{
    //prevent other threads from entering their critical section
    mtx.lock();

    //write letters to a file
    for (size_t i = 0; i < 20; i++)
    {
        for (char currentLetter = 'A'; currentLetter <= 'Z'; ++currentLetter)
            fileStream << currentLetter << ' ';
        fileStream << '\n';
    }
    
    //allow other threads to enter their critical section
    mtx.unlock();
}

int main()
{
    //open the file
    fileStream.open("synch.txt");

    //create the two threads that will run simultaneously
    std::thread threadA(writeNumbers);
    std::thread threadB(writeLetters);

    //send the two threads off to be processed
    threadA.join();
    threadB.join();

    //close the file
    fileStream.close();

    return 0;
}