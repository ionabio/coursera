// A single file is used for simplicity of review. However could be split in two

//the code is written in easy to read, but efficiency is not prioritized as a result
//for example a royal flush is a straight flush with an ace, but the code checks for both in separate functions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NumCards 52
#define NumSamples 1000000 

// Data Types
typedef enum suits
{
    diamond = 1,
    club = 2,
    heart = 3,
    spade = 4
} suits;

typedef struct card
{
    short pips; // 1 ..10, 11 = J , 12 = Q , 13 = K
    suits suit; // 'spade', 'diamond;
} card;

typedef enum handType
{
    none = 0,
    pair = 1,
    twoPair = 2,
    threeOfAKind = 3,
    straight = 4,
    flush = 5,
    fullHouse = 6,
    fourOfAKind = 7,
    straightFlush = 8,
    royalFlush = 9
} handType;

// I have used declration of functions below to make a summary of what are the main functions
void generateCards(card* cards);
void shuffle(card* cards); // we shuffle the cards by swapping two random cards NumSamples times
handType checkHandType(card* deck); //this function calls the rest of the functions to check for hand type and then the result is aggrigated in main
void printOutputs(int count[], double probability[], int sum_c, double sum_p);

int main(void){
    srand(time(NULL));

    int count[10] = {0};// count of each hand type
    double probability[10] = {0.0};// probability of each hand type

    card cards[NumCards];
    generateCards(cards);
    for(int i = 0; i < NumSamples; ++i )
    {
        shuffle(cards);
        handType hand = checkHandType(cards);
        ++count[hand];
    }
    // SUMS are mainly to control that the values sum up correctly (as in we don't count twice or miss any)
    int sum_c = 0;
    double sum_p = 0;
    for (int i = 0; i < 10; ++i)
    {
        probability[i] = (double)count[i] / NumSamples;
        sum_c += count[i];
        sum_p += probability[i];
    }
    
    printOutputs(count, probability, sum_c, sum_p);

    return 0;
}

// General deck operations

void generateCards(card* cards)
{
    for (suits s = diamond; s <= spade; ++s)
    {
        for (int i = 1; i <= 13; ++i)
        {
            int index = i - 1 + (s - 1) * 13;
            cards[index].pips = i;
            cards[index].suit = s;
        }
    }
}

void shuffle(card* cards)
{
    for (int i = 0; i < NumCards; ++i)
    {
        int j = rand() % NumCards;
        card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

int card2int(card c)
{
    return (c.suit - 1) * 13 + c.pips - 1;
}
//

// Hand checking functions
// Note that these functions only work on sorted cards by their index in deck


bool checkRoyalFlush(card cards[]){
    //Check for royal flush
    // The check tries to find 5 cards of 1, 10, J, Q, K and then checks if they are all of the same suit
    int hand[5] = {-1, -1, -1, -1 ,-1};
    for (int i = 0; i < 3; ++i)
    {
        // 1 should show up in first 3 cards
        if(cards[i].pips == 1)
        {
            suits s = cards[i].suit;
            hand[0] = i;
            // if we found an ace then we need to find four straight starting from 10 in remaining cards
            for (int j = i+1; j<4; ++j)
            {
                if(cards[j].pips == 10 && cards[j].suit == s)
                {
                    hand[1] = j;
                    // if we found 10 then we need to find three straight starting from J in remaining cards
                    for (int k = j+1; k<5; ++k)
                    {
                        if(cards[k].pips == 11 && cards[k].suit == s)
                        {
                            hand[2] = k;
                            // if we found J then we need to find two straight starting from Q in remaining cards
                            for (int l = k+1; l<6; ++l)
                            {
                                if(cards[l].pips == 12 && cards[l].suit == s)
                                {
                                    hand[3] = l;
                                    // if we found Q then we need to find one straight starting from K in remaining cards
                                    for (int m = l+1; m<7; ++m)
                                    {
                                        if(cards[m].pips == 13 && cards[m].suit == s)
                                        {
                                            hand[4] = m;
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
       
    }
    return false;
}

bool checkStraightFlush(card* cards)
{
    //Check for straight flush
    // The check tries to find 5 cards in sequence and then checks if they are all of the same suit
    // since they are in sequence, no other card can be in between
    bool straightFlush = false;
    for (int i = 0; i < 3; ++i)
    {
        if (card2int(cards[i]) + 1 == card2int(cards[i+1]) && card2int(cards[i]) + 2 == card2int(cards[i+2]) && card2int(cards[i]) + 3== card2int(cards[i+3]) && card2int(cards[i]) + 4  == card2int(cards[i+4]))
        {
            if (cards[i].suit == cards[i + 1].suit && cards[i].suit == cards[i + 2].suit && cards[i].suit == cards[i + 3].suit && cards[i].suit == cards[i + 4].suit)
            {
                straightFlush = true;
                break;
            }
        }
    }
    return straightFlush;
}

int checkNumberOfAKind(card* cards)
{
    //Check for four or three of a kind
    // The check tries to find 4 cards with the same pips
    int hand[4] = {-1, -1, -1, -1};
    for (int i = 0; i < 4; ++i)
    {
        hand[0] = cards[i].pips;
        int count = 0;
        for (int j = i + 1; j < 7; ++j)
        {
            if (cards[j].pips == hand[0])
            {
                hand[++count] = j;
            }
        }
        if (count == 3)
        {
            return 4;
        }else if(count == 2){
            return 3;
        }

    }
    return 0;
}

bool checkFullHouse(card* cards){
    //Check for full house
    // The check tries to find 3 cards with the same pips and 2 cards with the same pips
    bool fullHouse = false;
    int hand[3] = {-1, -1, -1};
    for (int i = 0; i < 5; ++i)
    {
        //trying to find three of a kind
        int pips = cards[i].pips;
        hand[0] = i;
        int count = 0;
        for (int j = i + 1; j < 7; ++j)
        {
            if (cards[j].pips == pips)
            {
                hand[++count] = j;
            }
        }
        if (count == 2)
        { //now we don't have to check over the same cards again to find a pair
            for (int j = 0; j < 6; ++j)
            {
                bool found = false;
                for(int k= 0; k<3; ++k)
                {
                    if (j == hand[k])
                    {
                        found = true;
                    }
                }
                if(!found){
                  for(int k= j+1; k<7; ++k)
                  {
                        if (cards[j].pips == cards[k].pips)
                        {
                            fullHouse = true;
                            break;
                        }
                  }
                }
            }
        }
        if (fullHouse)
        {
            break;
        }
    }
    return fullHouse;
}

bool checkFlush(card* cards)
{
    //Check for flush
    // The check tries to find 5 cards with the same suit
    int hand[5] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 3; ++i)
    {
        suits s = cards[i].suit;
        hand[0]= i;
        int count = 0;
        for(int j = i+1; j<7; ++j){
            if(cards[j].suit == s){
                hand[++count] = j;
            }
            if(count == 4)
                return true;
        }
    }
    return false;
}

bool checkStraight(card* cards){
    // Check for straight
    // The check tries to find 5 cards in sequence
    // first sort cards by pips in a new array, so that we can check for sequence easily
    // since we don't want to modify the original array, we copy it to a new array
    // and hands is stored as the index of the card in the sorted array (as opposed to the original array)
    card sortedCardsByPips[7];

    for (int i = 0; i < 7; ++i)
    {   
        sortedCardsByPips[i] = cards[i];
        }
    for(int i = 0; i<7; ++i){
        for (int j = i + 1; j < 7; ++j)
        {
            if (sortedCardsByPips[i].pips > sortedCardsByPips[j].pips)
            {
                card temp = sortedCardsByPips[i];
                sortedCardsByPips[i] = sortedCardsByPips[j];
                sortedCardsByPips[j] = temp;
            }
        }
    }
    

    int hand[5] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 4; ++i)
    {
        int pips = sortedCardsByPips[i].pips;
        hand[0]= i;
        int count = 0;
        for(int j = i+1; j<7; ++j){
            if(sortedCardsByPips[j].pips  == pips + 1){
                hand[++count] = j;
                pips = sortedCardsByPips[j].pips;
            }
            if(count == 4)
               return true;
            else if (count == 3 && pips == 13)
            {
                // this means we found a 10 .. king, now we return to begining of the array to see if there is any ace
                for (int k= 0; k< 3; ++k)
                {
                    if (sortedCardsByPips[k].pips == 1)
                    {
                        hand[4] = k;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int checkNumberOfPairs(card* cards){
    //  Check for pairs
    // The check tries to find 2 cards with the same pips
    // and returns the aggregate number of pairs (it can be three but we are only intrested in 1 or +2)
    int numberOfPairs = 0;
    int foundPip = -1;
    for (int i = 0; i < 6; ++i)
    {
        if(cards[i].pips == foundPip)
            continue;
        for (int j = i+1; j<7 ; ++j)
        {
            if (cards[i].pips == cards[j].pips && cards[i].pips != foundPip)
            {
               ++numberOfPairs;
               foundPip = cards[i].pips;
               break;
            }
        }
    }
    return numberOfPairs;
}

void sortCards(card* cards)
{
    //sort cards by pips
    for (int i = 0; i < 7; ++i)
    {
        for (int j = i + 1; j < 7; ++j)
        {
            if (card2int(cards[i]) > card2int(cards[j]))
            {
                card temp = cards[i];
                cards[i] = cards[j];
                cards[j] = temp;
            }
        }
    }

    //sort cards by suit
    for (int i = 0; i < 7; ++i)
    {
        for (int j = i + 1; j < 7; ++j)
        {
            if (cards[i].pips == cards[j].pips)
            {
                if (cards[i].suit > cards[j].suit)
                {
                    card temp = cards[i];
                    cards[i] = cards[j];
                    cards[j] = temp;
                }
            }
        }
    }
}
    



handType checkHandType(card* deck)
{
    //deal seven cards
    card cards[7];
    for (int i = 0; i < 7; ++i)
    {
        cards[i] = deck[i];
    }
    
    sortCards(cards);

    int numberOfAKind = checkNumberOfAKind(cards);
    int numberOfPairs = checkNumberOfPairs(cards);
    if(checkRoyalFlush(cards)){
        return royalFlush;
    }else if(checkStraightFlush(cards)){
        return straightFlush;
    }else if (numberOfAKind == 4){
        return fourOfAKind;
    }else if (checkFullHouse(cards)){
        return fullHouse;
    }else if (checkFlush(cards)){
        return flush;
    }else if (checkStraight(cards)){
        return straight;
    }else if (numberOfAKind == 3){
        return threeOfAKind;
    }else if (numberOfPairs >= 2){
        return twoPair;
    }else if (numberOfPairs == 1){
        return pair;
    }
    //else 
    return none;
}

// Output functions
void printOutputs(int count[], double probability[], int sum_counts, double sum_probabilities)
{
    printf("+-----------------+----------------------+---------+\n");
    printf("| Hand            | Probability          | Count   |\n");
    printf("+-----------------+----------------------+---------+\n");
    printf("| Royal Flush     | %20lf | %7d |\n", probability[9], count[9]);
    printf("| Straight Flush  | %20lf | %7d |\n", probability[8], count[8]);
    printf("| Four of a Kind  | %20lf | %7d |\n", probability[7], count[7]);
    printf("| Full House      | %20lf | %7d |\n", probability[6], count[6]);
    printf("| Flush           | %20lf | %7d |\n", probability[5], count[5]);
    printf("| Straight        | %20lf | %7d |\n", probability[4], count[4]);
    printf("| Three of a Kind | %20lf | %7d |\n", probability[3], count[3]);
    printf("| Two Pair        | %20lf | %7d |\n", probability[2], count[2]);
    printf("| Pair            | %20lf | %7d |\n", probability[1], count[1]);
    printf("| Ace High or Less| %20lf | %7d |\n", probability[0], count[0]);
    printf("+-----------------+----------------------+---------+\n");
    printf("| Total           | %20lf | %7d |\n", sum_probabilities, sum_counts);
    printf("+-----------------+----------------------+---------+\n");
}